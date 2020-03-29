/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "OS_ConfigService.h"

#include "LibDebug/Debug.h"

#include "util/helper_func.h"

#include <string.h>


// -----------------------------------------------------------------------------
void TestParameterReadAccessRight_ok(OS_ConfigServiceHandle_t* handle,
                                     const char* domainName,
                                     const char* componentName,
                                     const char* parameterName,
                                     const char* parameterValue,
                                     size_t parameterLength);

void TestParameterWriteAccessRight_ok(OS_ConfigServiceHandle_t* handle,
                                      const char* domainName,
                                      const char* componentName,
                                      const char* parameterName,
                                      const void* parameterValue,
                                      size_t parameterSize);
