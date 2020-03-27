/**
 * Copyright (C) 2019, Hensoldt Cyber GmbH
 */
#if defined(CONFIG_SERVER_BACKEND_FILESYSTEM)
#pragma once

#include "SeosError.h"
#include "seos_config.h"

seos_err_t initializeWithFileBackends(SeosConfigLib* configLib,
                                      hPartition_t phandle);

#endif