/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "OS_ConfigService.h"

#include "LibDebug/Debug.h"

#include "util/helper_func.h"

#include <string.h>


// -----------------------------------------------------------------------------
void test_CreateHandle_pos(
    OS_ConfigServiceHandle_t* handle,
    OS_ConfigServiceHandle_HandleKind_t handleKind,
    const char* componentName);
