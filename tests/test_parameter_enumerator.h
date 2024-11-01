/**
 * Copyright (C) 2020-2024, HENSOLDT Cyber GmbH
 * 
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * For commercial licensing, contact: info.cyber@hensoldt.net
 */

#include "OS_ConfigService.h"


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
