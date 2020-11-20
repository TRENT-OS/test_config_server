/**
 * Copyright (C) 2019, Hensoldt Cyber GmbH
 */

#pragma once

#include "OS_Error.h"
#include "OS_ConfigService.h"

OS_Error_t
initializeWithFileBackends(
    OS_ConfigServiceLib_t* configLib,
    OS_FileSystem_Handle_t hFs);

