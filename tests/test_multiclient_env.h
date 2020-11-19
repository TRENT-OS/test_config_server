/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "OS_ConfigService.h"


// -----------------------------------------------------------------------------
void
test_multiClient_environment(
    OS_ConfigServiceHandle_t* cfgHandle,
    TestApp_t* testApp,
    void (*sync_with_other_clients)());