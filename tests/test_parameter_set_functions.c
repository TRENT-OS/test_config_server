/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "test_parameter_set_functions.h"

// -----------------------------------------------------------------------------
void
TestParameterSetValueAsU32_ok(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const uint32_t parameterValue)
{
    OS_Error_t err;

    err = set_integer32_parameter(handle,
                                  domainName,
                                  parameterName,
                                  parameterValue);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    err = verify_integer32_parameter(handle,
                                     domainName,
                                     parameterName,
                                     parameterValue);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    char handleKind[15];
    if (OS_CONFIG_HANDLE_KIND_RPC == OS_ConfigServiceHandle_getHandleKind(
            *handle))
    {
        initializeName(handleKind, sizeof(handleKind), "Rpc");
    }

    else if (OS_CONFIG_HANDLE_KIND_LOCAL == OS_ConfigServiceHandle_getHandleKind(
            *handle))
    {
        initializeName(handleKind, sizeof(handleKind), "Local");
    }

    Debug_LOG_INFO("->%s: %s HandleKind:%s Parameter:%s OK\n", __func__, componentName, handleKind, parameterName);
}

void
TestParameterSetValueAsU64_ok(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const uint64_t parameterValue)
{
    OS_Error_t err;

    err = set_integer64_parameter(handle,
                                  domainName,
                                  parameterName,
                                  parameterValue);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    err = verify_integer64_parameter(handle,
                                     domainName,
                                     parameterName,
                                     parameterValue);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    char handleKind[15];
    if (OS_CONFIG_HANDLE_KIND_RPC == OS_ConfigServiceHandle_getHandleKind(
            *handle))
    {
        initializeName(handleKind, sizeof(handleKind), "Rpc");
    }

    else if (OS_CONFIG_HANDLE_KIND_LOCAL == OS_ConfigServiceHandle_getHandleKind(
            *handle))
    {
        initializeName(handleKind, sizeof(handleKind), "Local");
    }

    Debug_LOG_INFO("->%s: %s HandleKind:%s Parameter:%s OK\n", __func__, componentName, handleKind, parameterName);
}

void
TestParameterSetValueAsString_ok(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const char* parameterValue,
    size_t parameterSize)
{
    OS_Error_t err;

    err = set_string_parameter(handle,
                               domainName,
                               parameterName,
                               parameterValue,
                               parameterSize);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    err = verify_string_parameter(handle,
                                  domainName,
                                  parameterName,
                                  parameterValue,
                                  parameterSize);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    char handleKind[15];
    if (OS_CONFIG_HANDLE_KIND_RPC == OS_ConfigServiceHandle_getHandleKind(
            *handle))
    {
        initializeName(handleKind, sizeof(handleKind), "Rpc");
    }

    else if (OS_CONFIG_HANDLE_KIND_LOCAL == OS_ConfigServiceHandle_getHandleKind(
            *handle))
    {
        initializeName(handleKind, sizeof(handleKind), "Local");
    }

    Debug_LOG_INFO("->%s: %s HandleKind:%s Parameter:%s OK\n", __func__, componentName, handleKind, parameterName);
}


void
TestParameterSetValueAsBlob_ok(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const char* parameterValue,
    size_t parameterSize)
{
    OS_Error_t err;

    err = set_blob_parameter(handle,
                             domainName,
                             parameterName,
                             parameterValue,
                             parameterSize);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    err = verify_blob_parameter(handle,
                                domainName,
                                parameterName,
                                parameterValue,
                                parameterSize);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    char handleKind[15];
    if (OS_CONFIG_HANDLE_KIND_RPC == OS_ConfigServiceHandle_getHandleKind(
            *handle))
    {
        initializeName(handleKind, sizeof(handleKind), "Rpc");
    }

    else if (OS_CONFIG_HANDLE_KIND_LOCAL == OS_ConfigServiceHandle_getHandleKind(
            *handle))
    {
        initializeName(handleKind, sizeof(handleKind), "Local");
    }

    Debug_LOG_INFO("->%s: %s HandleKind:%s Parameter:%s OK\n", __func__, componentName, handleKind, parameterName);
}


void
TestParameterSetValue_ok(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const void* parameterValue,
    size_t parameterSize)
{
    OS_Error_t err;

    err = set_parameter(handle,
                        domainName,
                        parameterName,
                        parameterValue,
                        parameterSize);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    err = verify_parameter(handle,
                           domainName,
                           parameterName,
                           parameterValue,
                           parameterSize);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    char handleKind[15];
    if (OS_CONFIG_HANDLE_KIND_RPC == OS_ConfigServiceHandle_getHandleKind(
            *handle))
    {
        initializeName(handleKind, sizeof(handleKind), "Rpc");
    }

    else if (OS_CONFIG_HANDLE_KIND_LOCAL == OS_ConfigServiceHandle_getHandleKind(
            *handle))
    {
        initializeName(handleKind, sizeof(handleKind), "Local");
    }

    Debug_LOG_INFO("->%s: %s HandleKind:%s Parameter:%s OK\n", __func__, componentName, handleKind, parameterName);
}

void
TestParameterSetValue_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle)
{
    OS_ConfigServiceLibTypes_ParameterEnumerator_t enumerator;
    OS_ConfigServiceLibTypes_ParameterType_t parameterType =
        OS_CONFIG_LIB_PARAMETER_TYPE_BLOB;
    char buffer;

    OS_Error_t err = OS_ConfigService_parameterSetValue(
                        *handle,
                        &enumerator,
                        parameterType,
                        &buffer,
                        sizeof(buffer));
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_STATE == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestParameterSetValueAsU32_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle)
{
    OS_ConfigServiceLibTypes_ParameterEnumerator_t enumerator;

    OS_Error_t err = OS_ConfigService_parameterSetValueAsU32(
                        *handle,
                        &enumerator,
                        0);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_STATE == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestParameterSetValueAsU64_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle)
{
    OS_ConfigServiceLibTypes_ParameterEnumerator_t enumerator;

    OS_Error_t err = OS_ConfigService_parameterSetValueAsU64(
                        *handle,
                        &enumerator,
                        0);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_STATE == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestParameterSetValueAsString_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle)
{
    OS_ConfigServiceLibTypes_ParameterEnumerator_t enumerator;
    OS_ConfigServiceLibTypes_ParameterType_t parameterType =
        OS_CONFIG_LIB_PARAMETER_TYPE_BLOB;
    char buffer;

    OS_Error_t err = OS_ConfigService_parameterSetValueAsString(
                        *handle,
                        &enumerator,
                        parameterType,
                        &buffer,
                        sizeof(buffer));
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_STATE == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestParameterSetValueAsBlob_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle)
{
   OS_ConfigServiceLibTypes_ParameterEnumerator_t enumerator;
    OS_ConfigServiceLibTypes_ParameterType_t parameterType =
        OS_CONFIG_LIB_PARAMETER_TYPE_BLOB;
    char buffer;

    OS_Error_t err = OS_ConfigService_parameterSetValueAsBlob(
                        *handle,
                        &enumerator,
                        parameterType,
                        &buffer,
                        sizeof(buffer));
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_STATE == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}
