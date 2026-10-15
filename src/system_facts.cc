#include "system_facts.h"
#include "ntdll.h"
#include "kernel32.h"
#include "advapi.h"
#include "memory.h"
#include "stackstrings.h"
#include "wintypes.h"

static BOOL GetMachineUUID(UUID *uuid){
    SYSTEM_FIRMWARE_TABLE_INFORMATION request{};
	request.ProviderSignature = RSMB_PROVIDER_SIGNATURE;
	request.Action = SystemFirmwareTable_Get;
	request.TableID = 0;
	request.TableBufferLength = 0;

    NTDLL ntdll;
    if (!NTDLL_Ctor(&ntdll) || ntdll.ZwQuerySystemInformation == NULL ||
        ntdll.RtlAllocateHeap == NULL || ntdll.RtlFreeHeap == NULL)
        return FALSE;

    UINT32 requiredSize = 0;
    (void)ntdll.ZwQuerySystemInformation(SystemFirmwareTableInformation, &request, sizeof(SYSTEM_FIRMWARE_TABLE_INFORMATION), &requiredSize);
    if (requiredSize == 0)
        return FALSE;

    PPEB peb = GetCurrentPEB();
    if (peb == NULL || peb->ProcessHeap == NULL)
        return FALSE;

    PUINT8 buffer = (PUINT8)ntdll.RtlAllocateHeap(peb->ProcessHeap, 0, requiredSize);
    if (buffer == NULL)
        return FALSE;

    auto firmwareInfo = (PSYSTEM_FIRMWARE_TABLE_INFORMATION)buffer;
	firmwareInfo->ProviderSignature = RSMB_PROVIDER_SIGNATURE;
	firmwareInfo->Action = SystemFirmwareTable_Get;
	firmwareInfo->TableID = 0;
	firmwareInfo->TableBufferLength = requiredSize - (UINT32)__builtin_offsetof(SYSTEM_FIRMWARE_TABLE_INFORMATION, TableBuffer);

    UINT32 returnedSize = 0;
    auto queryResult = ntdll.ZwQuerySystemInformation(SystemFirmwareTableInformation, firmwareInfo, requiredSize, &returnedSize);

    if (queryResult != NTSTATUS(0)){
        ntdll.RtlFreeHeap(peb->ProcessHeap, 0, buffer);
        return FALSE;
    }
    auto rawSmbios = (PRAW_SMBIOS_DATA)firmwareInfo->TableBuffer;
	PUINT8 tableData = rawSmbios->SMBIOSTableData;
	UINT32 tableLength = rawSmbios->Length;
	PUINT8 tableEnd = tableData + tableLength;

	BOOL found = false;

    while (tableData < tableEnd)
	{
		auto header = (PSMBIOS_HEADER)tableData;

		if (tableData + header->Length > tableEnd)
			break;

		// Type 1 = System Information, Length >= 0x19 means UUID field is present.
		if (header->Type == 1 && header->Length >= 0x19)
		{
			auto systemInfo = (PSMBIOS_TYPE1_SYSTEM_INFORMATION)tableData;

			// Check for all-FF (not set) or all-00 (not present).
			BOOL allZero = true;
			BOOL allFF = true;
			for (INT32 i = 0; i < 16; i++)
			{
				if (systemInfo->UUID[i] != 0x00) allZero = false;
				if (systemInfo->UUID[i] != 0xFF) allFF = false;
			}

			if (!allZero && !allFF)
			{
				// SMBIOS UUID is stored in mixed-endian format per spec.
				// First 3 fields are little-endian, remaining 8 bytes are big-endian.
				// Convert to standard RFC 9562 network byte order.
				UINT8 uuidBytes[16];

				// TimeLow (4 bytes, little-endian -> big-endian)
				uuidBytes[0] = systemInfo->UUID[3];
				uuidBytes[1] = systemInfo->UUID[2];
				uuidBytes[2] = systemInfo->UUID[1];
				uuidBytes[3] = systemInfo->UUID[0];

				// TimeMid (2 bytes, little-endian -> big-endian)
				uuidBytes[4] = systemInfo->UUID[5];
				uuidBytes[5] = systemInfo->UUID[4];

				// TimeHiAndVersion (2 bytes, little-endian -> big-endian)
				uuidBytes[6] = systemInfo->UUID[7];
				uuidBytes[7] = systemInfo->UUID[6];

				// Remaining 8 bytes are already in big-endian order.
				for (INT32 i = 8; i < 16; i++)
					uuidBytes[i] = systemInfo->UUID[i];

				*uuid = UUID(uuidBytes);
				found = true;
				break;
			}
		}

		// Skip past the formatted area to the string table.
		PUINT8 stringTable = tableData + header->Length;

		// The string table is terminated by a double null (0x00, 0x00).
		while (stringTable < tableEnd - 1 && !(stringTable[0] == 0x00 && stringTable[1] == 0x00))
			stringTable++;

		// Advance past the double null terminator to the next structure.
		tableData = stringTable + 2;
	}

	ntdll.RtlFreeHeap(peb->ProcessHeap, 0, buffer);
    return found;
}



void GetSystemInfo(SystemInfo *facts)
{
    MemoryZero(facts, sizeof(*facts));

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