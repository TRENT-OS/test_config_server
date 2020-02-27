/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "test_parameter_set_functions.h"

// -----------------------------------------------------------------------------
void
TestParameterSetValueAsU32_ok(
    SeosConfigHandle* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const uint32_t parameterValue)
{
    seos_err_t err;

    err = set_integer32_parameter(handle,
                                  domainName,
                                  parameterName,
                                  parameterValue);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    err = verify_integer32_parameter(handle,
                                     domainName,
                                     parameterName,
                                     parameterValue);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

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
TestParameterSetValueAsU64_ok(
    SeosConfigHandle* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const uint64_t parameterValue)
{
    seos_err_t err;

    err = set_integer64_parameter(handle,
                                  domainName,
                                  parameterName,
                                  parameterValue);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    err = verify_integer64_parameter(handle,
                                     domainName,
                                     parameterName,
                                     parameterValue);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

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
TestParameterSetValueAsString_ok(
    SeosConfigHandle* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const char* parameterValue,
    size_t parameterSize)
{
    seos_err_t err;

    err = set_string_parameter(handle,
                               domainName,
                               parameterName,
                               parameterValue,
                               parameterSize);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    err = verify_string_parameter(handle,
                                  domainName,
                                  parameterName,
                                  parameterValue,
                                  parameterSize);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

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
TestParameterSetValueAsBlob_ok(
    SeosConfigHandle* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const char* parameterValue,
    size_t parameterSize)
{
    seos_err_t err;

    err = set_blob_parameter(handle,
                             domainName,
                             parameterName,
                             parameterValue,
                             parameterSize);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    err = verify_blob_parameter(handle,
                                domainName,
                                parameterName,
                                parameterValue,
                                parameterSize);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

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
TestParameterSetValue_ok(
    SeosConfigHandle* handle,
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
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    err = verify_parameter(handle,
                           domainName,
                           parameterName,
                           parameterValue,
                           parameterSize);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

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