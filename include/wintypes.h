#pragma once
#include "types.h"

#define RSMB_PROVIDER_SIGNATURE 0x52534D42 
#define SystemFirmwareTableInformation 76
#define SystemFirmwareTable_Get 1

typedef enum _WINHTTP_WEB_SOCKET_BUFFER_TYPE
{
    WINHTTP_WEB_SOCKET_BINARY_MESSAGE_BUFFER_TYPE       = 0,
    WINHTTP_WEB_SOCKET_BINARY_FRAGMENT_BUFFER_TYPE      = 1,
    WINHTTP_WEB_SOCKET_UTF8_MESSAGE_BUFFER_TYPE         = 2,
    WINHTTP_WEB_SOCKET_UTF8_FRAGMENT_BUFFER_TYPE        = 3,
    WINHTTP_WEB_SOCKET_CLOSE_BUFFER_TYPE                = 4
} WINHTTP_WEB_SOCKET_BUFFER_TYPE;

typedef struct _UNICODE_STRING
{
	UINT16 Length;
	UINT16 MaximumLength;
	PWCHAR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _SECURITY_ATTRIBUTES {
  DWORD nLength;
  PVOID lpSecurityDescriptor;
  BOOL bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

typedef struct _STARTUPINFOW {
  DWORD  cb;
  PWCHAR lpReserved;
  PWCHAR lpDesktop;
  PWCHAR lpTitle;
  DWORD  dwX;
  DWORD  dwY;
  DWORD  dwXSize;
  DWORD  dwYSize;
  DWORD  dwXCountChars;
  DWORD  dwYCountChars;
  DWORD  dwFillAttribute;
  DWORD  dwFlags;
  UINT16   wShowWindow;
  UINT16   cbReserved2;
  unsigned char *lpReserved2;
  HANDLE hStdInput;
  HANDLE hStdOutput;
  HANDLE hStdError;
} STARTUPINFOW, *LPSTARTUPINFOW;

typedef struct _PROCESS_INFORMATION {
  HANDLE hProcess;
  HANDLE hThread;
  DWORD  dwProcessId;
  DWORD  dwThreadId;
} PROCESS_INFORMATION, *PPROCESS_INFORMATION, *LPPROCESS_INFORMATION;

typedef struct _OSVERSIONINFOW {
  DWORD dwOSVersionInfoSize;
  DWORD dwMajorVersion;
  DWORD dwMinorVersion;
  DWORD dwBuildNumber;
  DWORD dwPlatformId;
  WCHAR szCSDVersion[128];
} OSVERSIONINFOW, *POSVERSIONINFOW, *LPOSVERSIONINFOW, RTL_OSVERSIONINFOW, *PRTL_OSVERSIONINFOW;
<<<<<<< Updated upstream
=======

typedef struct _SYSTEM_FIRMWARE_TABLE_INFORMATION
{
	UINT32 ProviderSignature;  ///< Firmware table provider ('RSMB' for SMBIOS, 'FIRM' for firmware, 'ACPI' for ACPI)
	UINT32 Action;             ///< SystemFirmwareTable_Enumerate or SystemFirmwareTable_Get
	UINT32 TableID;            ///< Table identifier (0 for SMBIOS raw table)
	UINT32 TableBufferLength;  ///< Size of TableBuffer in bytes
	UINT8  TableBuffer[1];     ///< Variable-length buffer containing the firmware table data
} SYSTEM_FIRMWARE_TABLE_INFORMATION, *PSYSTEM_FIRMWARE_TABLE_INFORMATION;

typedef struct _RAW_SMBIOS_DATA
{
	UINT8  Used20CallingMethod; ///< Whether the 2.0 calling method was used
	UINT8  SMBIOSMajorVersion;  ///< SMBIOS major version
	UINT8  SMBIOSMinorVersion;  ///< SMBIOS minor version
	UINT8  DmiRevision;         ///< DMI revision
	UINT32 Length;              ///< Total length of SMBIOSTableData in bytes
	UINT8  SMBIOSTableData[1];  ///< Variable-length SMBIOS structure data
} RAW_SMBIOS_DATA, *PRAW_SMBIOS_DATA;

typedef struct _SMBIOS_HEADER
{
	UINT8  Type;   ///< Structure type (0=BIOS, 1=System, 2=Baseboard, etc.)
	UINT8  Length; ///< Length of the formatted area (including this header)
	UINT16 Handle; ///< Unique handle for this structure instance
} SMBIOS_HEADER, *PSMBIOS_HEADER;


typedef struct _SMBIOS_TYPE1_SYSTEM_INFORMATION
{
	SMBIOS_HEADER Header;      ///< Type=1, Length>=0x19 for UUID-bearing entries
	UINT8  Manufacturer;       ///< String index for manufacturer name
	UINT8  ProductName;        ///< String index for product name
	UINT8  Version;            ///< String index for version string
	UINT8  SerialNumber;       ///< String index for serial number
	UINT8  UUID[16];           ///< 16-byte system UUID (valid when Header.Length >= 0x19)
} SMBIOS_TYPE1_SYSTEM_INFORMATION, *PSMBIOS_TYPE1_SYSTEM_INFORMATION;



>>>>>>> Stashed changes
