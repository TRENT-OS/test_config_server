/**
 * Copyright (C) 2019, Hensoldt Cyber GmbH
 */
#if defined(OS_CONFIG_SERVICE_BACKEND_FILESYSTEM)
#pragma once

#include "OS_Error.h"
#include "OS_ConfigService.h"

OS_Error_t initializeWithFileBackends(OS_ConfigServiceLib_t* configLib,
                                      hPartition_t phandle);

#endif