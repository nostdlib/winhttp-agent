#pragma once

#include "types.h"
#include "wintypes.h"

typedef struct NTDLL
{
    NTSTATUS (WINAPI *LdrLoadDll)(WCHAR *PathToFile, UINT32 Flags, PUNICODE_STRING ModuleFileName,void* *ModuleHandle);
    NTSTATUS (WINAPI *RtlGetVersion)(void* VersionInformation);
    NTSTATUS (WINAPI *ZwQuerySystemInformation)(UINT32 SystemInformationClass, PVOID SystemInformation, UINT32 SystemInformationLength, UINT32 *ReturnLength);
    PVOID (WINAPI *RtlAllocateHeap)(PVOID HeapHandle, UINT32 Flags, SIZE_T Size);
    UINT8 (WINAPI *RtlFreeHeap)(PVOID HeapHandle, UINT32 Flags, PVOID BaseAddress);
} NTDLL;

BOOL NTDLL_Ctor(NTDLL* ntdll);
