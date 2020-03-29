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