/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "test_create_handle.h"


// -----------------------------------------------------------------------------
void
TestParameterReadAccessRight_ok(SeosConfigHandle* handle,
                                const char* domainName,
                                const char* componentName,
                                const char* parameterName,
                                const char* parameterValue,
                                size_t parameterLength)
{
    seos_err_t err;

    err = verify_parameter(handle,
                           domainName,
                           parameterName,
                           parameterValue,
                           parameterLength);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_CONFIG_PARAMETER_NOT_FOUND == err, "err %d", err);

    char handleKind[15];
    if (SEOS_CONFIG_HANDLE_KIND_RPC == seos_configuration_handle_getHandleKind(
            *handle))
    {
        initializeName(handleKind, sizeof(handleKind), "Rpc");
    }

    else if (SEOS_CONFIG_HANDLE_KIND_LOCAL == seos_configuration_handle_getHandleKind(
            *handle))
    {
        initializeName(handleKind, sizeof(handleKind), "Local");
    }

    Debug_LOG_INFO("->%s: %s HandleKind:%s Parameter:%s OK\n", __func__, componentName, handleKind, parameterName);
}

void
TestParameterWriteAccessRight_ok(SeosConfigHandle* handle,
                                 const char* domainName,
                                 const char* componentName,
                                 const char* parameterName,
                                 const void* parameterValue,
                                 size_t parameterSize)
{
    seos_err_t err;

    err = set_parameter(handle,
                        domainName,
                        parameterName,
                        parameterValue,
                        parameterSize);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_GENERIC == err, "err %d", err);

    char handleKind[15];
    if (SEOS_CONFIG_HANDLE_KIND_RPC == seos_configuration_handle_getHandleKind(
            *handle))
    {
        initializeName(handleKind, sizeof(handleKind), "Rpc");
    }

    else if (SEOS_CONFIG_HANDLE_KIND_LOCAL == seos_configuration_handle_getHandleKind(
            *handle))
    {
        initializeName(handleKind, sizeof(handleKind), "Local");
    }

    Debug_LOG_INFO("->%s: %s HandleKind:%s Parameter:%s OK\n", __func__, componentName, handleKind, parameterName);
}