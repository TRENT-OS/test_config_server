/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "seos_config.h"

#include "LibDebug/Debug.h"

#include "util/helper_func.h"

#include <string.h>


// -----------------------------------------------------------------------------
void TestGetInteger32FromFsBackend_ok(SeosConfigHandle* handle,
                                      const char* domainName,
                                      const char* componentName,
                                      const char* parameterName,
                                      const uint32_t parameterValue);

void TestGetInteger64FromFsBackend_ok(SeosConfigHandle* handle,
                                      const char* domainName,
                                      const char* componentName,
                                      const char* parameterName,
                                      const uint64_t parameterValue);

void TestGetStringsFromFsBackend_ok(SeosConfigHandle* handle,
                                    const char* domainName,
                                    const char* componentName,
                                    const char* parameterName,
                                    const char* parameterValue,
                                    size_t parameterLength);

void TestGetBlobsFromFsBackend_ok(SeosConfigHandle* handle,
                                  const char* domainName,
                                  const char* componentName,
                                  const char* parameterName,
                                  const char* parameterValue,
                                  size_t parameterLength);