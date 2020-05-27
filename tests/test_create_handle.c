/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "test_create_handle.h"


// -----------------------------------------------------------------------------
void
TestCreateHandle_ok(OS_ConfigServiceHandle_t* handle,
                    OS_ConfigServiceHandle_HandleKind_t handleKind,
                    const char* componentName)
{
    OS_Error_t err;

    // Open local handle of API
    err = OS_ConfigService_createHandle(handleKind, 0, handle);
    Debug_ASSERT_PRINTFLN(err == OS_SUCCESS, "err %d", err);

    char handleType[15];
    if (OS_CONFIG_HANDLE_KIND_RPC == handleKind)
    {
        initializeName(handleType, sizeof(handleType), "Rpc");
    }

    else if (OS_CONFIG_HANDLE_KIND_LOCAL == handleKind)
    {
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

    // Invalid handle type
    err = OS_ConfigService_createHandle(666, 0, handle);
    Debug_ASSERT_PRINTFLN(err == OS_ERROR_INVALID_PARAMETER, "err %d", err);

    // Invalid handle id
    err = OS_ConfigService_createHandle(handleKind, 8, handle);
    Debug_ASSERT_PRINTFLN(err == OS_ERROR_INVALID_PARAMETER, "err %d", err);

    char handleType[15];
    if (OS_CONFIG_HANDLE_KIND_RPC == handleKind)
    {
        initializeName(handleType, sizeof(handleType), "Rpc");
    }

    else if (OS_CONFIG_HANDLE_KIND_LOCAL == handleKind)
    {
        initializeName(handleType, sizeof(handleType), "Local");
    }

    Debug_LOG_INFO("->%s: %s HandleKind:%s OK\n", __func__, componentName, handleType);
}