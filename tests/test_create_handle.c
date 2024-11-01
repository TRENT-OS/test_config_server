/**
 * Copyright (C) 2020-2024, HENSOLDT Cyber GmbH
 * 
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * For commercial licensing, contact: info.cyber@hensoldt.net
 */

#include "camkes.h"

#include "test_create_handle.h"

#include "lib_macros/Test.h"

#include "util/helper_func.h"


// -----------------------------------------------------------------------------
void
test_CreateHandle_pos(
    OS_ConfigServiceHandle_t* handle,
    OS_ConfigServiceHandle_HandleKind_t handleKind,
    const char* componentName)
{
    TEST_START("i", handleKind, "s", componentName);

    if (OS_CONFIG_HANDLE_KIND_RPC == handleKind)
    {
        static OS_ConfigService_ClientCtx_t ctx =
        {
            .dataport = OS_DATAPORT_ASSIGN(cfg_port)
        };

        TEST_SUCCESS(OS_ConfigService_createHandleRemote(
                         &ctx,
                         handle));
    }

    else if (OS_CONFIG_HANDLE_KIND_LOCAL == handleKind)
    {
        TEST_SUCCESS(OS_ConfigService_createHandleLocal(handle));
    }

    TEST_FINISH();
}
