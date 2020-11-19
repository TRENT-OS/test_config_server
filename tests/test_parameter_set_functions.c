/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "test_parameter_set_functions.h"

#include "util/TestMacros.h"

#include "util/helper_func.h"


// -----------------------------------------------------------------------------
void
test_ParameterSetValueAsU32_pos(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const uint32_t parameterValue)
{
    OS_ConfigServiceHandle_HandleKind_t handleKind =
        OS_ConfigServiceHandle_getHandleKind(*handle);

    TEST_START(handleKind, componentName, parameterName);

    TEST_SUCCESS(set_integer32_parameter(
                     handle,
                     domainName,
                     parameterName,
                     parameterValue));

    TEST_SUCCESS(verify_integer32_parameter(
                     handle,
                     domainName,
                     parameterName,
                     parameterValue));

    TEST_FINISH();
}

void
test_ParameterSetValueAsU64_pos(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const uint64_t parameterValue)
{
    OS_ConfigServiceHandle_HandleKind_t handleKind =
        OS_ConfigServiceHandle_getHandleKind(*handle);

    TEST_START(handleKind, componentName, parameterName);

    TEST_SUCCESS(set_integer64_parameter(
                     handle,
                     domainName,
                     parameterName,
                     parameterValue));

    TEST_SUCCESS(verify_integer64_parameter(
                     handle,
                     domainName,
                     parameterName,
                     parameterValue));

    TEST_FINISH();
}

void
test_ParameterSetValueAsString_pos(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const char* parameterValue,
    size_t parameterSize)
{
    OS_ConfigServiceHandle_HandleKind_t handleKind =
        OS_ConfigServiceHandle_getHandleKind(*handle);

    TEST_START(handleKind, componentName, parameterName);

    TEST_SUCCESS(set_string_parameter(
                     handle,
                     domainName,
                     parameterName,
                     parameterValue,
                     parameterSize));

    TEST_SUCCESS(set_string_parameter(
                     handle,
                     domainName,
                     parameterName,
                     parameterValue,
                     parameterSize));

    TEST_FINISH();
}


void
test_ParameterSetValueAsBlob_pos(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const char* parameterValue,
    size_t parameterSize)
{
    OS_ConfigServiceHandle_HandleKind_t handleKind =
        OS_ConfigServiceHandle_getHandleKind(*handle);

    TEST_START(handleKind, componentName, parameterName);

    TEST_SUCCESS(set_blob_parameter(
                     handle,
                     domainName,
                     parameterName,
                     parameterValue,
                     parameterSize));

    TEST_SUCCESS(set_blob_parameter(
                     handle,
                     domainName,
                     parameterName,
                     parameterValue,
                     parameterSize));

    TEST_FINISH();
}


void
test_ParameterSetValue_pos(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const void* parameterValue,
    size_t parameterSize)
{
    OS_ConfigServiceHandle_HandleKind_t handleKind =
        OS_ConfigServiceHandle_getHandleKind(*handle);

    TEST_START(handleKind, componentName, parameterName);

    TEST_SUCCESS(set_parameter(
                     handle,
                     domainName,
                     parameterName,
                     parameterValue,
                     parameterSize));

    TEST_SUCCESS(verify_parameter(
                     handle,
                     domainName,
                     parameterName,
                     parameterValue,
                     parameterSize));

    TEST_FINISH();
}

void
test_ParameterSetValue_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceLibTypes_ParameterEnumerator_t enumerator;
    OS_ConfigServiceLibTypes_ParameterType_t parameterType =
        OS_CONFIG_LIB_PARAMETER_TYPE_BLOB;
    char buffer;

    TEST_INVAL_STATE(OS_ConfigService_parameterSetValue(
                         *handle,
                         &enumerator,
                         parameterType,
                         &buffer,
                         sizeof(buffer)));

    TEST_FINISH();
}

void
test_ParameterSetValueAsU32_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceLibTypes_ParameterEnumerator_t enumerator;

    TEST_INVAL_STATE(OS_ConfigService_parameterSetValueAsU32(
                         *handle,
                         &enumerator,
                         0));

    TEST_FINISH();
}

void
test_ParameterSetValueAsU64_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceLibTypes_ParameterEnumerator_t enumerator;

    TEST_INVAL_STATE(OS_ConfigService_parameterSetValueAsU64(
                         *handle,
                         &enumerator,
                         0));

    TEST_FINISH();
}

void
test_ParameterSetValueAsString_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceLibTypes_ParameterEnumerator_t enumerator;
    OS_ConfigServiceLibTypes_ParameterType_t parameterType =
        OS_CONFIG_LIB_PARAMETER_TYPE_BLOB;
    char buffer;

    TEST_INVAL_STATE(OS_ConfigService_parameterSetValueAsString(
                         *handle,
                         &enumerator,
                         parameterType,
                         &buffer,
                         sizeof(buffer)));

    TEST_FINISH();
}

void
test_ParameterSetValueAsBlob_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceLibTypes_ParameterEnumerator_t enumerator;
    OS_ConfigServiceLibTypes_ParameterType_t parameterType =
        OS_CONFIG_LIB_PARAMETER_TYPE_BLOB;
    char buffer;

    TEST_INVAL_STATE(OS_ConfigService_parameterSetValueAsBlob(
                         *handle,
                         &enumerator,
                         parameterType,
                         &buffer,
                         sizeof(buffer)));

    TEST_FINISH();
}
