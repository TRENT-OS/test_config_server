/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "OS_ConfigService.h"

#include "LibDebug/Debug.h"

#include "util/helper_func.h"

#include <string.h>


// -----------------------------------------------------------------------------
void TestGetInteger32FromFsBackend_ok(OS_ConfigServiceHandle_t* handle,
                                      const char* domainName,
                                      const char* componentName,
                                      const char* parameterName,
                                      const uint32_t parameterValue);

void TestGetInteger64FromFsBackend_ok(OS_ConfigServiceHandle_t* handle,
                                      const char* domainName,
                                      const char* componentName,
                                      const char* parameterName,
                                      const uint64_t parameterValue);

void TestGetStringsFromFsBackend_ok(OS_ConfigServiceHandle_t* handle,
                                    const char* domainName,
                                    const char* componentName,
                                    const char* parameterName,
                                    const char* parameterValue,
                                    size_t parameterLength);

void TestGetBlobsFromFsBackend_ok(OS_ConfigServiceHandle_t* handle,
                                  const char* domainName,
                                  const char* componentName,
                                  const char* parameterName,
                                  const char* parameterValue,
                                  size_t parameterLength);

void
TestParameterGetValue_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle);
void
TestParameterGetValue_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle);
void
TestParameterGetValueAsU32_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle);
void
TestParameterGetValueAsU64_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle);
void
TestParameterGetValueAsString_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle);
void
TestParameterGetValueAsBlob_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle);
void
TestParameterGetValueFromDomainName_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle);
void
TestParameterSetValue_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle);
void
TestParameterSetValueAsU32_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle);
void
TestParameterSetValueAsU64_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle);
void
TestParameterSetValueAsString_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle);
void
TestParameterSetValueAsBlob_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle);
