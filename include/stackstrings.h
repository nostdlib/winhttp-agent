#pragma once
#include "types.h"
#include "wintypes.h"
#include "protocol.h"

#define STRLEN_BYTES_WINHTTP 22

static inline VOID BuildWinHttpDllName(PWCHAR buf)
{
    *(volatile WCHAR *)&buf[0] = L'w'; // w
    *(volatile WCHAR *)&buf[1] = L'i'; // i
    *(volatile WCHAR *)&buf[2] = L'n'; // n
    *(volatile WCHAR *)&buf[3] = L'h'; // h
    *(volatile WCHAR *)&buf[4] = L't'; // t
    *(volatile WCHAR *)&buf[5] = L't'; // t
    *(volatile WCHAR *)&buf[6] = L'p'; // p
    *(volatile WCHAR *)&buf[7] = L'.'; // .
    *(volatile WCHAR *)&buf[8] = L'd'; // d
    *(volatile WCHAR *)&buf[9] = L'l'; // l
    *(volatile WCHAR *)&buf[10] = L'l'; // l
    *(volatile WCHAR *)&buf[11] = L'\0'; // null terminator
}

static inline VOID BuildUserAgent(PWCHAR buf)
{
    *(volatile WCHAR *)&buf[0] = L'm'; // M
    *(volatile WCHAR *)&buf[1] = L'i'; // i
    *(volatile WCHAR *)&buf[2] = L'n'; // n
    *(volatile WCHAR *)&buf[3] = L'i'; // i
    *(volatile WCHAR *)&buf[4] = L'm'; // m
    *(volatile WCHAR *)&buf[5] = L'a'; // a
    *(volatile WCHAR *)&buf[6] = L'l'; // l
    *(volatile WCHAR *)&buf[7] = L'_'; //_
    *(volatile WCHAR *)&buf[8] = L'a'; // a
    *(volatile WCHAR *)&buf[9] = L'g'; // g
    *(volatile WCHAR *)&buf[10] = L'e'; // e
    *(volatile WCHAR *)&buf[11] = L'n'; // n
    *(volatile WCHAR *)&buf[12] = L't'; // t
    *(volatile WCHAR *)&buf[13] = L'/'; // /
    *(volatile WCHAR *)&buf[14] = L'1'; // 1
    *(volatile WCHAR *)&buf[15] = L'.'; // .
    *(volatile WCHAR *)&buf[16] = L'0'; // 0
    *(volatile WCHAR *)&buf[17] = L'\0'; // null terminator
}


static inline VOID BuildShellCommandLine(PWCHAR buf)
{
    *(volatile WCHAR *)&buf[0] = L'c'; 
    *(volatile WCHAR *)&buf[1] = L'm'; 
    *(volatile WCHAR *)&buf[2] = L'd'; 
    *(volatile WCHAR *)&buf[3] = L'.'; 
    *(volatile WCHAR *)&buf[4] = L'e';
    *(volatile WCHAR *)&buf[5] = L'x';
    *(volatile WCHAR *)&buf[6] = L'e';
    *(volatile WCHAR *)&buf[7] = L' ';
    *(volatile WCHAR *)&buf[8] = L'/';
    *(volatile WCHAR *)&buf[9] = L'K';
    *(volatile WCHAR *)&buf[10] = L' '; 
    *(volatile WCHAR *)&buf[11] = L'c';
    *(volatile WCHAR *)&buf[12] = L'h';
    *(volatile WCHAR *)&buf[13] = L'c';
    *(volatile WCHAR *)&buf[14] = L'p';
    *(volatile WCHAR *)&buf[15] = L' ';
    *(volatile WCHAR *)&buf[16] = L'6';
    *(volatile WCHAR *)&buf[17] = L'5';
    *(volatile WCHAR *)&buf[18] = L'0';
    *(volatile WCHAR *)&buf[19] = L'0';
    *(volatile WCHAR *)&buf[20] = L'1';
    *(volatile WCHAR *)&buf[21] = L' ';
    *(volatile WCHAR *)&buf[22] = L'>';
    *(volatile WCHAR *)&buf[23] = L'n';
    *(volatile WCHAR *)&buf[24] = L'u';
    *(volatile WCHAR *)&buf[25] = L'l';
    *(volatile WCHAR *)&buf[26] = L'\0';
}

static inline VOID BuildHexDigits(PCHAR buf)
{
    *(volatile CHAR *)&buf[0] = '0';
    *(volatile CHAR *)&buf[1] = '1';
    *(volatile CHAR *)&buf[2] = '2';
    *(volatile CHAR *)&buf[3] = '3';
    *(volatile CHAR *)&buf[4] = '4';
    *(volatile CHAR *)&buf[5] = '5';
    *(volatile CHAR *)&buf[6] = '6';
    *(volatile CHAR *)&buf[7] = '7';
    *(volatile CHAR *)&buf[8] = '8';
    *(volatile CHAR *)&buf[9] = '9';
    *(volatile CHAR *)&buf[10] = 'a';
    *(volatile CHAR *)&buf[11] = 'b';
    *(volatile CHAR *)&buf[12] = 'c';
    *(volatile CHAR *)&buf[13] = 'd';
    *(volatile CHAR *)&buf[14] = 'e';
    *(volatile CHAR *)&buf[15] = 'f';
    *(volatile CHAR *)&buf[16] = 0;
}



static inline VOID BuildMachineGuidRegistryPath(PCHAR buf)
{
    *(volatile CHAR *)&buf[0] ='S';
    *(volatile CHAR *)&buf[1] = 'O';
    *(volatile CHAR *)&buf[2] = 'F';
    *(volatile CHAR *)&buf[3] = 'T';
    *(volatile CHAR *)&buf[4] = 'W';
    *(volatile CHAR *)&buf[5] = 'A';
    *(volatile CHAR *)&buf[6] = 'R';
    *(volatile CHAR *)&buf[7] = 'E';
    *(volatile CHAR *)&buf[8] = '\\';
    *(volatile CHAR *)&buf[9] = 'M';
    *(volatile CHAR *)&buf[10] = 'i';
    *(volatile CHAR *)&buf[11] = 'c';
    *(volatile CHAR *)&buf[12] = 'r';
    *(volatile CHAR *)&buf[13] = 'o';
    *(volatile CHAR *)&buf[14] = 's';
    *(volatile CHAR *)&buf[15] = 'o';
    *(volatile CHAR *)&buf[16] = 'f';
    *(volatile CHAR *)&buf[17] = 't';
    *(volatile CHAR *)&buf[18] = '\\';
    *(volatile CHAR *)&buf[19] = 'C';
    *(volatile CHAR *)&buf[20] = 'r';
    *(volatile CHAR *)&buf[21] = 'y';
    *(volatile CHAR *)&buf[22] = 'p';
    *(volatile CHAR *)&buf[23] = 't';
    *(volatile CHAR *)&buf[24] = 'o';
    *(volatile CHAR *)&buf[25] = 'g';
    *(volatile CHAR *)&buf[26] = 'r';
    *(volatile CHAR *)&buf[27] = 'a';
    *(volatile CHAR *)&buf[28] = 'p';
    *(volatile CHAR *)&buf[29] = 'h';
    *(volatile CHAR *)&buf[30] = 'y';
    *(volatile CHAR *)&buf[31] = 0;
}

static inline VOID BuildMachineGuidValueName(PCHAR buf)
{
    *(volatile CHAR *)&buf[0] = 'M';
    *(volatile CHAR *)&buf[1] = 'a';
    *(volatile CHAR *)&buf[2] = 'c';
    *(volatile CHAR *)&buf[3] = 'h';
    *(volatile CHAR *)&buf[4] = 'i';
    *(volatile CHAR *)&buf[5] = 'n';
    *(volatile CHAR *)&buf[6] = 'e';
    *(volatile CHAR *)&buf[7] = 'G';
    *(volatile CHAR *)&buf[8] = 'u';
    *(volatile CHAR *)&buf[9] = 'i';
    *(volatile CHAR *)&buf[10] = 'd';
    *(volatile CHAR *)&buf[11] = 0;
}

static inline VOID BuildUrlEnvironmentVariableName(PCHAR buf)
{
    *(volatile CHAR *)&buf[0] = 'W'; // W
    *(volatile CHAR *)&buf[1] = '_'; // _
    *(volatile CHAR *)&buf[2] = 'U'; // U
    *(volatile CHAR *)&buf[3] = 'R'; // R
    *(volatile CHAR *)&buf[4] = 'L'; // L
    *(volatile CHAR *)&buf[5] = '\0'; // null terminator
}

// static inline VOID BuildDefaultCommitHash(PCHAR buf)
// {
//     *(volatile CHAR *)&buf[0] = 'c';
//     *(volatile CHAR *)&buf[1] = 'o';
//     *(volatile CHAR *)&buf[2] = 'u';
//     *(volatile CHAR *)&buf[3] = 'r';
//     *(volatile CHAR *)&buf[4] = 's';
//     *(volatile CHAR *)&buf[5] = 'e';
//     *(volatile CHAR *)&buf[6] = '0';
//     *(volatile CHAR *)&buf[7] = '1';
//     *(volatile CHAR *)&buf[8] = 0;
// }

// X-Api-Version:
static inline VOID BuildApiVersionHeaderPrefix(PCHAR buf)
{
    *(volatile CHAR *)&buf[0] = 'X';
    *(volatile CHAR *)&buf[1] = '-';
    *(volatile CHAR *)&buf[2] = 'A';
    *(volatile CHAR *)&buf[3] = 'p';
    *(volatile CHAR *)&buf[4] = 'i';
    *(volatile CHAR *)&buf[5] = '-';
    *(volatile CHAR *)&buf[6] = 'V';
    *(volatile CHAR *)&buf[7] = 'e';
    *(volatile CHAR *)&buf[8] = 'r';
    *(volatile CHAR *)&buf[9] = 's';
    *(volatile CHAR *)&buf[10] = 'i';
    *(volatile CHAR *)&buf[11] = 'o';
    *(volatile CHAR *)&buf[12] = 'n';
    *(volatile CHAR *)&buf[13] = ':';
    *(volatile CHAR *)&buf[14] = ' ';
    *(volatile CHAR *)&buf[15] = 0;
}


//X-Device-Id:
static inline VOID BuildMachineUuidHeaderPrefix(PCHAR buf)
{
    *(volatile CHAR *)&buf[0] = 'X';
    *(volatile CHAR *)&buf[1] = '-';
    *(volatile CHAR *)&buf[2] = 'D';
    *(volatile CHAR *)&buf[3] = 'e';
    *(volatile CHAR *)&buf[4] = 'v';
    *(volatile CHAR *)&buf[5] = 'i';
    *(volatile CHAR *)&buf[6] = 'c';
    *(volatile CHAR *)&buf[7] = 'e';
    *(volatile CHAR *)&buf[8] = '-';
    *(volatile CHAR *)&buf[9] = 'I';
    *(volatile CHAR *)&buf[10] = 'd';
    *(volatile CHAR *)&buf[11] = ':';
    *(volatile CHAR *)&buf[12] = ' ';
    *(volatile CHAR *)&buf[13] = 0;
}

// X-Session-Id: 
static inline VOID BuildSessionIdHeaderPrefix(PCHAR buf){
    *(volatile CHAR *)&buf[0] = 'X';
    *(volatile CHAR *)&buf[1] = '-';
    *(volatile CHAR *)&buf[2] = 'S';
    *(volatile CHAR *)&buf[3] = 'e';
    *(volatile CHAR *)&buf[4] = 's';
    *(volatile CHAR *)&buf[5] = 's';
    *(volatile CHAR *)&buf[6] = 'i';
    *(volatile CHAR *)&buf[7] = 'o';
    *(volatile CHAR *)&buf[8] = 'n';
    *(volatile CHAR *)&buf[9] = '-';
    *(volatile CHAR *)&buf[10] = 'I';
    *(volatile CHAR *)&buf[11] = 'd';
    *(volatile CHAR *)&buf[12] = ':';
    *(volatile CHAR *)&buf[13] = ' ';
    *(volatile CHAR *)&buf[14] = 0;
}


// X-Device-Name: 
static inline VOID BuildDeviceNameHeaderPrefix(PCHAR buf)
{
    *(volatile CHAR *)&buf[0] = 'X';
    *(volatile CHAR *)&buf[1] = '-';
    *(volatile CHAR *)&buf[2] = 'D';
    *(volatile CHAR *)&buf[3] = 'e';
    *(volatile CHAR *)&buf[4] = 'v';
    *(volatile CHAR *)&buf[5] = 'i';
    *(volatile CHAR *)&buf[6] = 'c';
    *(volatile CHAR *)&buf[7] = 'e';
    *(volatile CHAR *)&buf[8] = '-';
    *(volatile CHAR *)&buf[9] = 'N';
    *(volatile CHAR *)&buf[10] = 'a';
    *(volatile CHAR *)&buf[11] = 'm';
    *(volatile CHAR *)&buf[12] = 'e';
    *(volatile CHAR *)&buf[13] = ':';
    *(volatile CHAR *)&buf[14] = ' ';
    *(volatile CHAR *)&buf[15] = 0;
}


// X-User-Id: 
static inline VOID BuildUserIdHeaderPrefix(PCHAR buf)
{
    *(volatile CHAR *)&buf[0] = 'X';
    *(volatile CHAR *)&buf[1] = '-';
    *(volatile CHAR *)&buf[2] = 'U';
    *(volatile CHAR *)&buf[3] = 's';
    *(volatile CHAR *)&buf[4] = 'e';
    *(volatile CHAR *)&buf[5] = 'r';
    *(volatile CHAR *)&buf[6] = '-';
    *(volatile CHAR *)&buf[7] = 'I';
    *(volatile CHAR *)&buf[8] = 'd';
    *(volatile CHAR *)&buf[9] = ':';
    *(volatile CHAR *)&buf[10] = ' ';
    *(volatile CHAR *)&buf[11] = 0;
}

// X-Device-Arch: 
static inline VOID BuildDeviceArchitectureHeaderPrefix(PCHAR buf)
{
    *(volatile CHAR *)&buf[0] = 'X';
    *(volatile CHAR *)&buf[1] = '-';
    *(volatile CHAR *)&buf[2] = 'D';
    *(volatile CHAR *)&buf[3] = 'e';
    *(volatile CHAR *)&buf[4] = 'v';
    *(volatile CHAR *)&buf[5] = 'i';
    *(volatile CHAR *)&buf[6] = 'c';
    *(volatile CHAR *)&buf[7] = 'e';
    *(volatile CHAR *)&buf[8] = '-';
    *(volatile CHAR *)&buf[9] = 'A';
    *(volatile CHAR *)&buf[10] = 'r';
    *(volatile CHAR *)&buf[11] = 'c';
    *(volatile CHAR *)&buf[12] = 'h';
    *(volatile CHAR *)&buf[13] = ':';
    *(volatile CHAR *)&buf[14] = ' ';
    *(volatile CHAR *)&buf[15] = 0;
}

// X-App-Arch: 
static inline VOID BuildAppArchitectureHeaderPrefix(PCHAR buf)
{
    *(volatile CHAR *)&buf[0] = 'X';
    *(volatile CHAR *)&buf[1] = '-';
    *(volatile CHAR *)&buf[2] = 'A';
    *(volatile CHAR *)&buf[3] = 'p';
    *(volatile CHAR *)&buf[4] = 'p';
    *(volatile CHAR *)&buf[5] = '-';
    *(volatile CHAR *)&buf[6] = 'A';
    *(volatile CHAR *)&buf[7] = 'r';
    *(volatile CHAR *)&buf[8] = 'c';
    *(volatile CHAR *)&buf[9] = 'h';
    *(volatile CHAR *)&buf[10] = ':';
    *(volatile CHAR *)&buf[11] = ' ';
    *(volatile CHAR *)&buf[12] = 0;
}

// writing architecture name
static inline VOID BuildArchitectureName(PCHAR buf)
{
#if defined(ENVIRONMENT_x86_64) || defined(__x86_64__) || defined(_M_X64)
    *(volatile CHAR *)&buf[0] = 'x';
    *(volatile CHAR *)&buf[1] = '8';
    *(volatile CHAR *)&buf[2] = '6';
    *(volatile CHAR *)&buf[3] = '_';
    *(volatile CHAR *)&buf[4] = '6';
    *(volatile CHAR *)&buf[5] = '4';
    *(volatile CHAR *)&buf[6] = 0;
#elif defined(ENVIRONMENT_ARM64) || defined(__aarch64__) || defined(_M_ARM64)
    *(volatile CHAR *)&buf[0] = 'a';
    *(volatile CHAR *)&buf[1] = 'a';
    *(volatile CHAR *)&buf[2] = 'r';
    *(volatile CHAR *)&buf[3] = 'c';
    *(volatile CHAR *)&buf[4] = 'h';
    *(volatile CHAR *)&buf[5] = '6';
    *(volatile CHAR *)&buf[6] = '4';
    *(volatile CHAR *)&buf[7] = 0;
#elif defined(ENVIRONMENT_ARM32) || defined(__arm__) || defined(_M_ARM)
    *(volatile CHAR *)&buf[0] = 'a';
    *(volatile CHAR *)&buf[1] = 'r';
    *(volatile CHAR *)&buf[2] = 'm';
    *(volatile CHAR *)&buf[3] = 0;
#else
    *(volatile CHAR *)&buf[0] = 'i';
    *(volatile CHAR *)&buf[1] = '3';
    *(volatile CHAR *)&buf[2] = '8';
    *(volatile CHAR *)&buf[3] = '6';
    *(volatile CHAR *)&buf[4] = 0;
#endif
}

// X-Platform: windows
static inline VOID BuildAgentPlatformHeader(PCHAR buf){
    *(volatile CHAR *)&buf[0] = 'X';
    *(volatile CHAR *)&buf[1] = '-';
    *(volatile CHAR *)&buf[2] = 'P';
    *(volatile CHAR *)&buf[3] = 'l';
    *(volatile CHAR *)&buf[4] = 'a';
    *(volatile CHAR *)&buf[5] = 't';
    *(volatile CHAR *)&buf[6] = 'f';
    *(volatile CHAR *)&buf[7] = 'o';
    *(volatile CHAR *)&buf[8] = 'r';
    *(volatile CHAR *)&buf[9] = 'm';
    *(volatile CHAR *)&buf[10] = ':';
    *(volatile CHAR *)&buf[11] = ' ';
    *(volatile CHAR *)&buf[12] = 'w';
    *(volatile CHAR *)&buf[13] = 'i';
    *(volatile CHAR *)&buf[14] = 'n';
    *(volatile CHAR *)&buf[15] = 'd';
    *(volatile CHAR *)&buf[16] = 'o';
    *(volatile CHAR *)&buf[17] = 'w';
    *(volatile CHAR *)&buf[18] = 's';
    *(volatile CHAR *)&buf[19] = 0;
}

// X-OS-Version: 
static inline VOID BuildOsVersionHeaderPrefix(PCHAR buf)
{
    *(volatile CHAR *)&buf[0] = 'X';
    *(volatile CHAR *)&buf[1] = '-';
    *(volatile CHAR *)&buf[2] = 'O';
    *(volatile CHAR *)&buf[3] = 'S';
    *(volatile CHAR *)&buf[4] = '-';
    *(volatile CHAR *)&buf[5] = 'V';
    *(volatile CHAR *)&buf[6] = 'e';
    *(volatile CHAR *)&buf[7] = 'r';
    *(volatile CHAR *)&buf[8] = 's';
    *(volatile CHAR *)&buf[9] = 'i';
    *(volatile CHAR *)&buf[10] = 'o';
    *(volatile CHAR *)&buf[11] = 'n';
    *(volatile CHAR *)&buf[12] = ':';
    *(volatile CHAR *)&buf[13] = ' ';
    *(volatile CHAR *)&buf[14] = 0;
}


// X-OS-Build: 
static inline VOID BuildOsBuildHeaderPrefix(PCHAR buf)
{
    *(volatile CHAR *)&buf[0] = 'X';
    *(volatile CHAR *)&buf[1] = '-';
    *(volatile CHAR *)&buf[2] = 'O';
    *(volatile CHAR *)&buf[3] = 'S';
    *(volatile CHAR *)&buf[4] = '-';
    *(volatile CHAR *)&buf[5] = 'B';
    *(volatile CHAR *)&buf[6] = 'u';
    *(volatile CHAR *)&buf[7] = 'i';
    *(volatile CHAR *)&buf[8] = 'l';
    *(volatile CHAR *)&buf[9] = 'd';
    *(volatile CHAR *)&buf[10] = ':';
    *(volatile CHAR *)&buf[11] = ' ';
    *(volatile CHAR *)&buf[12] = 0;
}

// X-Client-Commit: 
static inline VOID BuildClientCommitHeaderPrefix(PCHAR buf)
{
    *(volatile CHAR *)&buf[0] = 'X';
    *(volatile CHAR *)&buf[1] = '-';
    *(volatile CHAR *)&buf[2] = 'C';
    *(volatile CHAR *)&buf[3] = 'l';
    *(volatile CHAR *)&buf[4] = 'i';
    *(volatile CHAR *)&buf[5] = 'e';
    *(volatile CHAR *)&buf[6] = 'n';
    *(volatile CHAR *)&buf[7] = 't';
    *(volatile CHAR *)&buf[8] = '-';
    *(volatile CHAR *)&buf[9] = 'C';
    *(volatile CHAR *)&buf[10] = 'o';
    *(volatile CHAR *)&buf[11] = 'm';
    *(volatile CHAR *)&buf[12] = 'm';
    *(volatile CHAR *)&buf[13] = 'i';
    *(volatile CHAR *)&buf[14] = 't';
    *(volatile CHAR *)&buf[15] = ':';
    *(volatile CHAR *)&buf[16] = ' ';
    *(volatile CHAR *)&buf[17] = 0;
}

// X-Client-Id: 
static inline VOID BuildClientIdHeaderPrefix(PCHAR buf)
{
    *(volatile CHAR *)&buf[0] = 'X';
    *(volatile CHAR *)&buf[1] = '-';
    *(volatile CHAR *)&buf[2] = 'C';
    *(volatile CHAR *)&buf[3] = 'l';
    *(volatile CHAR *)&buf[4] = 'i';
    *(volatile CHAR *)&buf[5] = 'e';
    *(volatile CHAR *)&buf[6] = 'n';
    *(volatile CHAR *)&buf[7] = 't';
    *(volatile CHAR *)&buf[8] = '-';
    *(volatile CHAR *)&buf[9] = 'I';
    *(volatile CHAR *)&buf[10] = 'd';
    *(volatile CHAR *)&buf[11] = ':';
    *(volatile CHAR *)&buf[12] = ' ';
    *(volatile CHAR *)&buf[13] = 0;
}

// X-Client-Features: 
static inline VOID BuildClientFeaturesHeaderPrefix(PCHAR buf)
{
    *(volatile CHAR *)&buf[0] = 'X';
    *(volatile CHAR *)&buf[1] = '-';
    *(volatile CHAR *)&buf[2] = 'C';
    *(volatile CHAR *)&buf[3] = 'l';
    *(volatile CHAR *)&buf[4] = 'i';
    *(volatile CHAR *)&buf[5] = 'e';
    *(volatile CHAR *)&buf[6] = 'n';
    *(volatile CHAR *)&buf[7] = 't';
    *(volatile CHAR *)&buf[8] = '-';
    *(volatile CHAR *)&buf[9] = 'F';
    *(volatile CHAR *)&buf[10] = 'e';
    *(volatile CHAR *)&buf[11] = 'a';
    *(volatile CHAR *)&buf[12] = 't';
    *(volatile CHAR *)&buf[13] = 'u';
    *(volatile CHAR *)&buf[14] = 'r';
    *(volatile CHAR *)&buf[15] = 'e';
    *(volatile CHAR *)&buf[16] = 's';
    *(volatile CHAR *)&buf[17] = ':';
    *(volatile CHAR *)&buf[18] = ' ';
    *(volatile CHAR *)&buf[19] = 0;
}

