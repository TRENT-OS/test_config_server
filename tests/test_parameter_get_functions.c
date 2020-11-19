/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "test_parameter_get_functions.h"

#include "util/TestMacros.h"

#include "util/helper_func.h"


// -----------------------------------------------------------------------------
void
test_GetInteger32FromFsBackend_pos(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const uint32_t parameterValue)
{
    OS_ConfigServiceHandle_HandleKind_t handleKind =
        OS_ConfigServiceHandle_getHandleKind(*handle);

    TEST_START(handleKind, componentName, parameterName);

    TEST_SUCCESS(verify_integer32_parameter(
                     handle,
                     domainName,
                     parameterName,
                     parameterValue));

    TEST_FINISH();
}

void
test_GetInteger64FromFsBackend_pos(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const uint64_t parameterValue)
{
    OS_ConfigServiceHandle_HandleKind_t handleKind =
        OS_ConfigServiceHandle_getHandleKind(*handle);

    TEST_START(handleKind, componentName, parameterName);

    TEST_SUCCESS(verify_integer64_parameter(
                     handle,
                     domainName,
                     parameterName,
                     parameterValue));

    TEST_FINISH();
}

void
test_GetStringsFromFsBackend_pos(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const char* parameterValue,
    size_t parameterLength)
{
    OS_ConfigServiceHandle_HandleKind_t handleKind =
        OS_ConfigServiceHandle_getHandleKind(*handle);

    TEST_START(handleKind, componentName, parameterName);

    TEST_SUCCESS(verify_string_parameter(
                     handle,
                     domainName,
                     parameterName,
                     parameterValue,
                     parameterLength));

    TEST_FINISH();
}

void
test_GetBlobsFromFsBackend_pos(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const char* parameterValue,
    size_t parameterLength)
{
    OS_ConfigServiceHandle_HandleKind_t handleKind =
        OS_ConfigServiceHandle_getHandleKind(*handle);

    TEST_START(handleKind, componentName, parameterName);

    TEST_SUCCESS(verify_blob_parameter(
                     handle,
                     domainName,
                     parameterName,
                     parameterValue,
                     parameterLength));

    TEST_FINISH();
}

void
test_ParameterGetValue_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceLibTypes_Parameter_t dummy;
    char buffer;
    size_t read;

    TEST_INVAL_STATE(OS_ConfigService_parameterGetValue(
                         *handle,
                         &dummy,
                         &buffer,
                         sizeof(buffer),
                         &read));

    TEST_FINISH();
}

void
test_ParameterGetValueAsU32_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceLibTypes_Parameter_t dummy;
    uint32_t value;

    TEST_INVAL_STATE(OS_ConfigService_parameterGetValueAsU32(
                         *handle,
                         &dummy,
                         &value));

    TEST_FINISH();
}

void
test_ParameterGetValueAsU64_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceLibTypes_Parameter_t dummy;
    uint64_t value;

    TEST_INVAL_STATE(OS_ConfigService_parameterGetValueAsU64(
                         *handle,
                         &dummy,
                         &value));

    TEST_FINISH();
}

void
test_ParameterGetValueAsString_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceLibTypes_Parameter_t dummy;
    char buffer;

    TEST_INVAL_STATE(OS_ConfigService_parameterGetValueAsString(
                         *handle,
                         &dummy,
                         &buffer,
                         sizeof(buffer)));

    TEST_FINISH();
}

void
test_ParameterGetValueAsBlob_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceLibTypes_Parameter_t dummy;
    char buffer;

    TEST_INVAL_STATE(OS_ConfigService_parameterGetValueAsBlob(
                         *handle,
                         &dummy,
                         &buffer,
                         sizeof(buffer)));

    TEST_FINISH();
}

void
test_ParameterGetValueFromDomainName_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceLibTypes_ParameterType_t parameterType =
        OS_CONFIG_LIB_PARAMETER_TYPE_BLOB;
    OS_ConfigServiceLibTypes_DomainName_t domainName;
    OS_ConfigServiceLibTypes_ParameterName_t parameterName;
    char buffer;
    size_t read;

    TEST_INVAL_STATE(OS_ConfigService_parameterGetValueFromDomainName(
                         *handle,
                         &domainName,
                         &parameterName,
                         parameterType,
                         &buffer,
                         sizeof(buffer),
                         &read));

    TEST_FINISH();
}
