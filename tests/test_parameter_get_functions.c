/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "test_parameter_get_functions.h"

// -----------------------------------------------------------------------------
void
TestGetInteger32FromFsBackend_ok(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const uint32_t parameterValue)
{
    OS_Error_t err;

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
TestGetInteger64FromFsBackend_ok(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const uint64_t parameterValue)
{
    OS_Error_t err;

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
TestGetStringsFromFsBackend_ok(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const char* parameterValue,
    size_t parameterLength)
{
    OS_Error_t err;

    err = verify_string_parameter(handle,
                                  domainName,
                                  parameterName,
                                  parameterValue,
                                  parameterLength);
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
TestGetBlobsFromFsBackend_ok(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const char* parameterValue,
    size_t parameterLength)
{
    OS_Error_t err;

    err = verify_blob_parameter(handle,
                                domainName,
                                parameterName,
                                parameterValue,
                                parameterLength);
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
TestParameterGetValue_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle)
{
    OS_ConfigServiceLibTypes_Parameter_t dummy;
    char buffer;
    size_t read;

    OS_Error_t err = OS_ConfigService_parameterGetValue(
                        *handle,
                        &dummy,
                        &buffer,
                        sizeof(buffer),
                        &read);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_STATE == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestParameterGetValueAsU32_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle)
{
    OS_ConfigServiceLibTypes_Parameter_t dummy;
    uint32_t value;

    OS_Error_t err = OS_ConfigService_parameterGetValueAsU32(
                        *handle,
                        &dummy,
                        &value);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_STATE == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestParameterGetValueAsU64_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle)
{
    OS_ConfigServiceLibTypes_Parameter_t dummy;
    uint64_t value;

    OS_Error_t err = OS_ConfigService_parameterGetValueAsU64(
                        *handle,
                        &dummy,
                        &value);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_STATE == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestParameterGetValueAsString_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle)
{
    OS_ConfigServiceLibTypes_Parameter_t dummy;
    char buffer;

    OS_Error_t err = OS_ConfigService_parameterGetValueAsString(
                        *handle,
                        &dummy,
                        &buffer,
                        sizeof(buffer));
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_STATE == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestParameterGetValueAsBlob_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle)
{
    OS_ConfigServiceLibTypes_Parameter_t dummy;
    char buffer;

    OS_Error_t err = OS_ConfigService_parameterGetValueAsBlob(
                        *handle,
                        &dummy,
                        &buffer,
                        sizeof(buffer));
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_STATE == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestParameterGetValueFromDomainName_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle)
{
    OS_ConfigServiceLibTypes_ParameterType_t parameterType =
        OS_CONFIG_LIB_PARAMETER_TYPE_BLOB;
    OS_ConfigServiceLibTypes_DomainName_t domainName;
    OS_ConfigServiceLibTypes_ParameterName_t parameterName;
    char buffer;
    size_t read;

    OS_Error_t err = OS_ConfigService_parameterGetValueFromDomainName(
                        *handle,
                        &domainName,
                        &parameterName,
                        parameterType,
                        &buffer,
                        sizeof(buffer),
                        &read);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_STATE == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}
