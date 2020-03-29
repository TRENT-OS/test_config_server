/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "OS_ConfigService.h"

#include "LibDebug/Debug.h"

#include "util/helper_func.h"

#include <string.h>


// -----------------------------------------------------------------------------
void TestCreateHandle_ok(OS_ConfigServiceHandle_t* handle,
                         OS_ConfigServiceHandle_HandleKind_t handleKind,
                         const char* componentName);

void TestCreateHandle_fail(OS_ConfigServiceHandle_t* handle,
                           OS_ConfigServiceHandle_HandleKind_t handleKind,
                           const char* componentName);