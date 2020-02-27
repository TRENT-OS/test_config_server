/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "seos_config_client.h"

#include "LibDebug/Debug.h"

#include "util/helper_func.h"

#include <string.h>


// -----------------------------------------------------------------------------
void TestDomainEnumerator_increment_ok(SeosConfigHandle* handle,
                                       const char* componentName,
                                       unsigned int maxDomainIndex);

void TestDomainEnumerator_reset_ok(SeosConfigHandle* handle,
                                   const char* componentName,
                                   unsigned int maxDomainIndex);