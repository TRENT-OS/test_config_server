/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "test_create_handle.h"


// -----------------------------------------------------------------------------
void
TestCreateHandle_ok(SeosConfigHandle* handle,
                    SeosConfigLib_HandleKind handleKind,
                    const char* componentName)
{
    seos_err_t err;

    // Open local handle of API
    err = seos_configuration_createHandle(handleKind, 0, handle);
    Debug_ASSERT_PRINTFLN(err == SEOS_SUCCESS, "err %d", err);

    char handleType[15];
    if (SEOS_CONFIG_HANDLE_KIND_RPC == handleKind)
    {
        initializeName(handleType, sizeof(handleType), "Rpc");
    }

    else if (SEOS_CONFIG_HANDLE_KIND_LOCAL == handleKind)
    {
        initializeName(handleType, sizeof(handleType), "Local");
    }

    Debug_LOG_INFO("->%s: %s HandleKind:%s OK\n", __func__, componentName, handleType);
}


void
TestCreateHandle_fail(SeosConfigHandle* handle,
                      SeosConfigLib_HandleKind handleKind,
                      const char* componentName)
{
    seos_err_t err;

    // Invalid handle type
    err = seos_configuration_createHandle(666, 0, handle);
    Debug_ASSERT_PRINTFLN(err == SEOS_ERROR_INVALID_PARAMETER, "err %d", err);

    // Invalid handle id
    err = seos_configuration_createHandle(handleKind, 8, handle);
    Debug_ASSERT_PRINTFLN(err == SEOS_ERROR_INVALID_PARAMETER, "err %d", err);

    char handleType[15];
    if (SEOS_CONFIG_HANDLE_KIND_RPC == handleKind)
    {
        initializeName(handleType, sizeof(handleType), "Rpc");
    }

    else if (SEOS_CONFIG_HANDLE_KIND_LOCAL == handleKind)
    {
        initializeName(handleType, sizeof(handleType), "Local");
    }

    Debug_LOG_INFO("->%s: %s HandleKind:%s OK\n", __func__, componentName, handleType);
}