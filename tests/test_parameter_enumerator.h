/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "OS_ConfigService.h"

#include "LibDebug/Debug.h"

#include "util/helper_func.h"

#include <string.h>


// -----------------------------------------------------------------------------
void TestParameterEnumerator_increment_ok(OS_ConfigServiceHandle_t* handle,
                                          const char* componentName,
                                          unsigned int maxDomainIndex,
                                          unsigned int maxParameterIndex);

void TestParameterEnumerator_reset_ok(OS_ConfigServiceHandle_t* handle,
                                      const char* componentName,
                                      unsigned int maxDomainIndex,
                                      unsigned int maxParameterIndex);