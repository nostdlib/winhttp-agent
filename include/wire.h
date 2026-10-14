#pragma once
#include "winhttp_api.h"
#include "memory.h"

typedef struct {
    CHAR *cur;
    CHAR *end;
    int   ok;
} hwriter;

static inline unsigned ReadU32LE(const unsigned char *data, int off)
{
    return (unsigned)data[off]
         | ((unsigned)data[off + 1] << 8)
         | ((unsigned)data[off + 2] << 16)
         | ((unsigned)data[off + 3] << 24);
}

static inline void WriteU32LE(unsigned char *buf, int *pos, unsigned value)
{
    for (int i = 0; i < 4; i++)
        buf[(*pos)++] = (unsigned char)(value >> (8 * i));
}


static inline void WriteU64LE(unsigned char *buf, int *pos, unsigned long long value)
{
    for (int i = 0; i < 8; i++)
        buf[(*pos)++] = (unsigned char)(value >> (8 * i));
}
static inline void WriteText(hwriter *w, const CHAR *text)
{
    while (*text != '\0') {
        if (!w->ok || w->cur >= w->end) { w->ok = 0; return; }
        *w->cur++ = *text++;
    }
}

static inline void WriteDecimal(hwriter *w, UINT32 value)
{
    CHAR rev[10];
    INT32 n = 0;
    do {
        rev[n++] = (CHAR)((value % 10) + '0');
        value /= 10;
    } while (value != 0);
    while (n > 0) {
        CHAR digit[2] = {rev[--n], '\0'};
        WriteText(w, digit);
    }
}

static inline DWORD SendErrorResponse(const WINHTTP_API *winhttp, HINTERNET socket, unsigned int correlationId)
{
    unsigned char response[8];
    MemoryZero(response, 8);
    int position = 4;
    WriteU32LE(response, &position, correlationId);
    return winhttp->WinHttpWebSocketSend(socket, WINHTTP_WEB_SOCKET_BINARY_MESSAGE_BUFFER_TYPE, response, sizeof(response));
}