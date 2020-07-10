/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "camkes.h"
#include "test_create_handle.h"


// -----------------------------------------------------------------------------
void
TestCreateHandle_ok(OS_ConfigServiceHandle_t* handle,
                    OS_ConfigServiceHandle_HandleKind_t handleKind,
                    const char* componentName)
{
    OS_Error_t err;

    char handleType[15];
    if (OS_CONFIG_HANDLE_KIND_RPC == handleKind)
    {
        static OS_ConfigService_ClientCtx_t ctx =
        {
            .dataport = OS_DATAPORT_ASSIGN(cfg_dataport_buf)
        };
        // Open local handle of API
        err = OS_ConfigService_createHandleRemote(
                0,
                &ctx,
                handle);
        Debug_ASSERT_PRINTFLN(err == OS_SUCCESS, "err %d", err);

        initializeName(handleType, sizeof(handleType), "Rpc");
    }

    else if (OS_CONFIG_HANDLE_KIND_LOCAL == handleKind)
    {
        // Open local handle of API
        err = OS_ConfigService_createHandleLocal(0, handle);
        Debug_ASSERT_PRINTFLN(err == OS_SUCCESS, "err %d", err);

        initializeName(handleType, sizeof(handleType), "Local");
    }

    Debug_LOG_INFO("->%s: %s HandleKind:%s OK\n", __func__, componentName, handleType);
}


void
TestCreateHandle_fail(OS_ConfigServiceHandle_t* handle,
                      OS_ConfigServiceHandle_HandleKind_t handleKind,
                      const char* componentName)
{
    OS_Error_t err;

    char handleType[15];
    if (OS_CONFIG_HANDLE_KIND_RPC == handleKind)
    {
        // Invalid handle id
        static OS_ConfigService_ClientCtx_t ctx =
        {
            .dataport = OS_DATAPORT_ASSIGN(cfg_dataport_buf)
        };
        err = OS_ConfigService_createHandleRemote(
                8,
                &ctx,
                handle);
        Debug_ASSERT_PRINTFLN(err == OS_ERROR_INVALID_PARAMETER, "err %d", err);

        initializeName(handleType, sizeof(handleType), "Rpc");
    }

    else if (OS_CONFIG_HANDLE_KIND_LOCAL == handleKind)
    {
        // Invalid handle id
        err = OS_ConfigService_createHandleLocal(8, handle);
        Debug_ASSERT_PRINTFLN(err == OS_ERROR_INVALID_PARAMETER, "err %d", err);
        initializeName(handleType, sizeof(handleType), "Local");
    }

    Debug_LOG_INFO("->%s: %s HandleKind:%s OK\n", __func__, componentName, handleType);
}
