/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "seos_config.h"

#include "LibDebug/Debug.h"

#include "util/helper_func.h"

#include <string.h>


// -----------------------------------------------------------------------------
void TestCreateHandle_ok(SeosConfigHandle* handle,
                         SeosConfigLib_HandleKind handleKind,
                         const char* componentName);

void TestCreateHandle_fail(SeosConfigHandle* handle,
                           SeosConfigLib_HandleKind handleKind,
                           const char* componentName);