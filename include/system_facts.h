#pragma once

#include "types.h"
#include "protocol.h"
#include "uuid.h"

typedef struct {
    UUID MachineUUID;
    CHAR hostname[AGENT_HOSTNAME_SIZE];
    CHAR username[AGENT_USERNAME_SIZE];
    CHAR os_version[AGENT_OS_VERSION_SIZE];
} SystemInfo;

void GetSystemInfo(SystemInfo *facts);
int GetMachineGuidText(CHAR guid_text[40]);
