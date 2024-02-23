/**
 * Copyright (C) 2020-2024, HENSOLDT Cyber GmbH
 * 
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * For commercial licensing, contact: info.cyber@hensoldt.net
 */

#include "OS_ConfigService.h"


// -----------------------------------------------------------------------------
void
test_multiClient_environment(
    OS_ConfigServiceHandle_t* cfgHandle,
    TestApp_t* testApp,
    void (*sync_with_other_clients)());