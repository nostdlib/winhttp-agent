#pragma once

#include "types.h"

enum CommandType : UINT8
{
    Command_OpenShell = 1,
    Command_WriteShell = 2,
    Command_ReadShell = 3,
    Command_CloseShell = 4,
    Command_GetDirectoryContent = 5,
    Command_GetFileContent = 6,
    Command_GetFileChunkHash = 7,
    Command_GetDisplays = 8,
    Command_GetScreenshot = 9,
    Command_Exit = 10,
    CommandTypeCount
};


#define CAPABILITY_MASK_BYTES   8

#ifndef SUPPORT_SHELL
#define SUPPORT_SHELL            1
#endif

#define STATUS_OK               0
#define STATUS_ERROR            1

#define IDENTITY_FRAME_SIZE     754
#define AGENT_HOSTNAME_SIZE        256
#define AGENT_USERNAME_SIZE        256

#define AGENT_OS_VERSION_SIZE      128
#define AGENT_API_VERSION       1
#define AGENT_NAME_ID           5

#ifndef AGENT_BUILD_NUMBER
#define AGENT_BUILD_NUMBER         1
#endif

#ifndef AGENT_COMMIT_HASH
#define AGENT_COMMIT_HASH "course01"
#endif

#define SHELL_POOL_SIZE         256
#define SHELL_READ_CHUNK        512

#define RECV_FRAGMENT_SIZE      512

#define MAX_MESSAGE_SIZE        512

#define RC_EXIT                 0

#define RC_SESSION_LOST         2

#define RC_LOCAL_ERROR          1

typedef enum {
	Capability_Shell = 0,
    CapabilityBitCount
} CapabilityBit;

typedef struct {
	UINT8 Bits[CAPABILITY_MASK_BYTES];
} CapabilityMask;


static inline VOID SetCapability(CapabilityMask *mask, CapabilityBit bit, int supported)
{
	if (supported) {
		USIZE b = (USIZE)bit;
		mask->Bits[b / 8] |= (UINT8)(1u << (b % 8));
	}
}

static inline CapabilityMask BuildCapabilityMask(VOID)
{
	CapabilityMask mask = {0};
	SetCapability(&mask, Capability_Shell, SUPPORT_SHELL);
	return mask;
}