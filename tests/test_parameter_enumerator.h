/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "OS_ConfigService.h"

#include "LibDebug/Debug.h"

#include "util/helper_func.h"

#include <string.h>


// -----------------------------------------------------------------------------
void test_ParameterEnumerator_increment_pos(
    OS_ConfigServiceHandle_t* handle,
    const char* componentName,
    unsigned int maxDomainIndex,
    unsigned int maxParameterIndex);

void test_ParameterEnumerator_reset_pos(
    OS_ConfigServiceHandle_t* handle,
    const char* componentName,
    unsigned int maxDomainIndex,
    unsigned int maxParameterIndex);

void
test_ParameterEnumerator_init_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle);
void
test_ParameterEnumerator_close_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle);
void
test_ParameterEnumerator_reset_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle);
void
test_ParameterEnumerator_increment_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle);
void
test_ParameterEnumerator_getElement_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle);
