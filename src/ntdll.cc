#include "ntdll.h"
#include "system.h"
#include "types.h"
#include "djb2.h"

BOOL NTDLL_Ctor(NTDLL *ntdll)
{
    if (ntdll == NULL)
        return FALSE;
    
    PVOID module;
    module = GetModuleHandleFromPEB(HashAscii("ntdll.dll"));
    if (module == NULL)
        return FALSE;

    ntdll->LdrLoadDll = (NTSTATUS (WINAPI *)(WCHAR *, UINT32, PUNICODE_STRING, PVOID *)) ResolveExportByHash(module, HashAscii("LdrLoadDll"));
    ntdll->RtlGetVersion = (NTSTATUS (WINAPI *)(PVOID)) ResolveExportByHash(module, HashAscii("RtlGetVersion"));
    ntdll->ZwQuerySystemInformation = (NTSTATUS (WINAPI *)(UINT32, PVOID, UINT32, UINT32 *)) ResolveExportByHash(module, HashAscii("ZwQuerySystemInformation"));
    ntdll->RtlAllocateHeap = (PVOID (WINAPI *)(PVOID, UINT32, SIZE_T)) ResolveExportByHash(module, HashAscii("RtlAllocateHeap"));
    ntdll->RtlFreeHeap = (UINT8 (WINAPI *)(PVOID, UINT32, PVOID)) ResolveExportByHash(module, HashAscii("RtlFreeHeap"));

    return (ntdll->LdrLoadDll != NULL && ntdll->RtlGetVersion != NULL && ntdll->ZwQuerySystemInformation != NULL && ntdll->RtlAllocateHeap != NULL && ntdll->RtlFreeHeap != NULL);
}
