#include "system_facts.h"
#include "ntdll.h"
#include "kernel32.h"
#include "advapi.h"
#include "memory.h"
#include "stackstrings.h"

static BOOL GetMachineUUID(UUID *uuid){
    if (uuid == NULL)
        return FALSE;
    *uuid = UUID();
            
    SYSTEM_FIRMWARE_TABLE_INFORMATION request{};
    request.ProviderSignature = 0x52534D42u;
    request.Action = 1;
    request.TableID = 0;
    request.TableBufferLength = 0;

    NTDLL ntdll;
    if (!NTDLL_Ctor(&ntdll) || ntdll.ZwQuerySystemInformation == NULL ||
        ntdll.RtlAllocateHeap == NULL || ntdll.RtlFreeHeap == NULL)
        return FALSE;

    const UINT32 informationClass = 76;
    const UINT32 headerSize = 16;
    const UINT32 maximumBufferSize = 65536 + headerSize;
    UINT32 requiredSize = 0;
    (void)ntdll.ZwQuerySystemInformation(informationClass, &request, headerSize, &requiredSize);
    if (requiredSize <= headerSize + 8 || requiredSize > maximumBufferSize)
        return FALSE;

    PPEB peb = GetCurrentPEB();
    if (peb == NULL || peb->ProcessHeap == NULL)
        return FALSE;

    PUINT8 buffer = (PUINT8)ntdll.RtlAllocateHeap(peb->ProcessHeap, 0, requiredSize);
    if (buffer == NULL)
        return FALSE;

    auto firmwareInfo = (PSYSTEM_FIRMWARE_TABLE_INFORMATION)buffer;
    firmwareInfo->ProviderSignature = request.ProviderSignature;
    firmwareInfo->Action = 1;
    firmwareInfo->TableID = 0;
    firmwareInfo->TableBufferLength = requiredSize - headerSize;

    UINT32 returnedSize = 0;
    BOOL found = FALSE;
    if (ntdll.ZwQuerySystemInformation(informationClass, firmwareInfo, requiredSize, &returnedSize) == 0 && returnedSize >= headerSize + 8){
        PUINT8 rawSmbios = firmwareInfo->TableBuffer;
        UINT32 tableLength = (UINT32)rawSmbios[4] |
                             ((UINT32)rawSmbios[5] << 8) |
                             ((UINT32)rawSmbios[6] << 16) |
                             ((UINT32)rawSmbios[7] << 24);
        if (tableLength <= returnedSize - headerSize - 8){
            PUINT8 tableData = rawSmbios + 8;
            PUINT8 tableEnd = tableData + tableLength;

            while (tableData < tableEnd){
                if ((USIZE)(tableEnd - tableData) < 4)
                    break;
                UINT8 structureLength = tableData[1];
                if (structureLength < 4 || structureLength > (USIZE)(tableEnd - tableData))
                    break;

                // Type 1 = System Information; UUID begins at offset 8.
                if (tableData[0] == 1 && structureLength >= 0x19){
                        PUINT8 smbiosUuid = tableData + 8;
                        BOOL allZero = TRUE;
                        BOOL allFF = TRUE;
                        for (INT32 i = 0; i < 16; i++) {
                            if (smbiosUuid[i] != 0x00) allZero = FALSE;
                            if (smbiosUuid[i] != 0xFF) allFF = FALSE;
                        }

                        if (!allZero && !allFF) {
                            UINT8 uuidBytes[16];
                            UINT8 smbiosMajor = rawSmbios[1];
                            UINT8 smbiosMinor = rawSmbios[2];
                            BOOL usesMixedEndian = smbiosMajor > 2 ||
                                    (smbiosMajor == 2 && smbiosMinor >= 6);
                            if (usesMixedEndian) {
                                uuidBytes[0] = smbiosUuid[3];
                                uuidBytes[1] = smbiosUuid[2];
                                uuidBytes[2] = smbiosUuid[1];
                                uuidBytes[3] = smbiosUuid[0];
                                uuidBytes[4] = smbiosUuid[5];
                                uuidBytes[5] = smbiosUuid[4];
                                uuidBytes[6] = smbiosUuid[7];
                                uuidBytes[7] = smbiosUuid[6];
                                for (INT32 i = 8; i < 16; i++)
                                    uuidBytes[i] = smbiosUuid[i];
                            } else {
                                for (INT32 i = 0; i < 16; i++)
                                    uuidBytes[i] = smbiosUuid[i];
                            }

                            *uuid = UUID(uuidBytes);
                            found = TRUE;
                            break;
                    }
                }

                PUINT8 stringTable = tableData + structureLength;
                while (stringTable < tableEnd - 1 && !(stringTable[0] == 0 && stringTable[1] == 0))
                    stringTable++;
                if (stringTable >= tableEnd - 1)
                    break;
                tableData = stringTable + 2;
            }
        }
    }

    ntdll.RtlFreeHeap(peb->ProcessHeap, 0, buffer);
    return found;
}


void GetSystemInfo(SystemInfo *facts)
{
    MemoryZero(facts, sizeof(*facts));
    BOOL res = GetMachineUUID(&facts->MachineUUID);
    if (!res)
        MemoryZero(&facts->MachineUUID, sizeof(facts->MachineUUID));

    NTDLL ntdll;
    KERNEL32 kernel;
    ADVAPI advapi;

    if(!KERNEL32_Ctor(&kernel) || !NTDLL_Ctor(&ntdll)){
        return;
    }

    DWORD n = sizeof(facts->hostname);
    if(kernel.GetComputerNameA){
        kernel.GetComputerNameA(facts->hostname, &n);
    } else {
        facts->hostname[0] = '\0';
    }

    if (!ADVAPI_Ctor(&advapi)) {
        facts->username[0] = '\0';
    } else {
        n = sizeof(facts->username);
        advapi.GetUserNameA(facts->username, &n);
    }

    if (ntdll.RtlGetVersion) {
        OSVERSIONINFOW info;

        MemoryZero(&info, sizeof(info));
        info.dwOSVersionInfoSize = sizeof(info);

        if (ntdll.RtlGetVersion(&info) == 0) {
            INT32 pos = 0;
            UINT32 parts[3];
            volatile UINT32 *pv = parts;
            pv[0] = info.dwMajorVersion; pv[1] = info.dwMinorVersion;
            pv[2] = info.dwBuildNumber;
            for (INT32 k = 0; k < 3; k++) {
                CHAR rev[12]; INT32 n = 0;
                UINT32 v = parts[k];
                do { rev[n++] = (CHAR)((v % 10) + '0'); v /= 10; } while (v);
                while (n > 0) facts->os_version[pos++] = rev[--n];
                if (k < 2) facts->os_version[pos++] = '.';
            }
            facts->os_version[pos] = 0;
        }
    }
}