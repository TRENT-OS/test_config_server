/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "seos_config.h"

#include "LibDebug/Debug.h"

#include "util/helper_func.h"

#include <string.h>


// -----------------------------------------------------------------------------
void TestParameterSetValueAsU32_ok(SeosConfigHandle* handle,
                                   const char* domainName,
                                   const char* componentName,
                                   const char* parameterName,
                                   const uint32_t parameterValue);

void TestParameterSetValueAsU64_ok(SeosConfigHandle* handle,
                                   const char* domainName,
                                   const char* componentName,
                                   const char* parameterName,
                                   const uint64_t parameterValue);

void TestParameterSetValueAsString_ok(SeosConfigHandle* handle,
                                      const char* domainName,
                                      const char* componentName,
                                      const char* parameterName,
                                      const char* parameterValue,
                                      size_t parameterSize);

void TestParameterSetValueAsBlob_ok(SeosConfigHandle* handle,
                                    const char* domainName,
                                    const char* componentName,
                                    const char* parameterName,
                                    const char* parameterValue,
                                    size_t parameterSize);

void TestParameterSetValue_ok(SeosConfigHandle* handle,
                              const char* domainName,
                              const char* componentName,
                              const char* parameterName,
                              const void* parameterValue,
                              size_t parameterSize);
