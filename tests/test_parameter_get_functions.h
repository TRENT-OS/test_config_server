/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "OS_ConfigService.h"

#include "LibDebug/Debug.h"

#include "util/helper_func.h"

#include <string.h>


// -----------------------------------------------------------------------------
void test_GetInteger32FromFsBackend_pos(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const uint32_t parameterValue);

void test_GetInteger64FromFsBackend_pos(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const uint64_t parameterValue);

void test_GetStringsFromFsBackend_pos(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const char* parameterValue,
    size_t parameterLength);

void test_GetBlobsFromFsBackend_pos(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const char* parameterValue,
    size_t parameterLength);

void
test_ParameterGetValue_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle);

void
test_ParameterGetValueAsU32_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle);

void
test_ParameterGetValueAsU64_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle);

void
test_ParameterGetValueAsString_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle);

void
test_ParameterGetValueAsBlob_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle);

void
test_ParameterGetValueFromDomainName_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle);

void
test_ParameterSetValue_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle);

void
test_ParameterSetValueAsU32_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle);

void
test_ParameterSetValueAsU64_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle);

void
test_ParameterSetValueAsString_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle);

void
test_ParameterSetValueAsBlob_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle);
