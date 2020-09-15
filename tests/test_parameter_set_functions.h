/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "OS_ConfigService.h"


// -----------------------------------------------------------------------------
void test_ParameterSetValueAsU32_pos(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const uint32_t parameterValue);

void test_ParameterSetValueAsU64_pos(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const uint64_t parameterValue);

void test_ParameterSetValueAsString_pos(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const char* parameterValue,
    size_t parameterSize);

void test_ParameterSetValueAsBlob_pos(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const char* parameterValue,
    size_t parameterSize);

void test_ParameterSetValue_pos(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const void* parameterValue,
    size_t parameterSize);
