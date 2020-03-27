/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "seos_config.h"

#include "LibDebug/Debug.h"

#include "util/helper_func.h"

#include <string.h>


// -----------------------------------------------------------------------------
void TestParameterReadAccessRight_ok(SeosConfigHandle* handle,
                                     const char* domainName,
                                     const char* componentName,
                                     const char* parameterName,
                                     const char* parameterValue,
                                     size_t parameterLength);

void TestParameterWriteAccessRight_ok(SeosConfigHandle* handle,
                                      const char* domainName,
                                      const char* componentName,
                                      const char* parameterName,
                                      const void* parameterValue,
                                      size_t parameterSize);
