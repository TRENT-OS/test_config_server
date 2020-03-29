/**
 * Copyright (C) 2019, Hensoldt Cyber GmbH
 */

#pragma once

#include "SeosError.h"
#include "OS_ConfigService.h"

seos_err_t initializeWithFileBackends(OS_ConfigServiceLib_t* configLib,
                                      hPartition_t phandle);

