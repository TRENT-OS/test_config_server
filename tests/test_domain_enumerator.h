/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "OS_ConfigService.h"

#include "LibDebug/Debug.h"

#include "util/helper_func.h"

#include <string.h>


// -----------------------------------------------------------------------------
void TestDomainEnumerator_increment_ok(OS_ConfigServiceHandle_t* handle,
                                       const char* componentName,
                                       unsigned int maxDomainIndex);

void TestDomainEnumerator_reset_ok(OS_ConfigServiceHandle_t* handle,
                                   const char* componentName,
                                   unsigned int maxDomainIndex);

void
TestDomainEnumerator_init_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle);
void
TestDomainEnumerator_close_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle);
void
TestDomainEnumerator_reset_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle);
void
TestDomainEnumerator_increment_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle);
void
TestDomainEnumerator_getElement_fail_no_server_init(
    OS_ConfigServiceHandle_t* handle);
