/**
 * Copyright (C) 2020-2024, HENSOLDT Cyber GmbH
 * 
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * For commercial licensing, contact: info.cyber@hensoldt.net
 */

#include "OS_ConfigService.h"


// -----------------------------------------------------------------------------
void test_DomainEnumerator_increment_pos(
    OS_ConfigServiceHandle_t* handle,
    const char* componentName,
    unsigned int maxDomainIndex);

void test_DomainEnumerator_reset_pos(
    OS_ConfigServiceHandle_t* handle,
    const char* componentName,
    unsigned int maxDomainIndex);

void
test_DomainEnumerator_init_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle);
void
test_DomainEnumerator_close_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle);
void
test_DomainEnumerator_reset_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle);
void
test_DomainEnumerator_increment_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle);
void
test_DomainEnumerator_getElement_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle);
