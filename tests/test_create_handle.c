/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "camkes.h"

#include "test_create_handle.h"

#include "LibMacros/Test.h"

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
            .dataport = OS_DATAPORT_ASSIGN(cfg_dataport_buf)
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
