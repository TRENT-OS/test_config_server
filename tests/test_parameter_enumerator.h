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

void
TestParameterEnumerator_init_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle);
void
TestParameterEnumerator_close_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle);
void
TestParameterEnumerator_reset_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle);
void
TestParameterEnumerator_increment_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle);
void
TestParameterEnumerator_getElement_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle);
