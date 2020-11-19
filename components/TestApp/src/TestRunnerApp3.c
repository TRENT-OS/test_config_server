/*
   *  TestRunnerApp connected to a ConfigServer component to run all tests remote
   *  in in a multiclient setup with other TestRunnerApps.
   *
   *  Copyright (C) 2020, Hensoldt Cyber GmbH
*/


#include "system_config.h"

#include "OS_Error.h"
#include "OS_ConfigService.h"
#include "OS_Dataport.h"

#include "LibDebug/Debug.h"

#include "test_parameter_get_functions.h"
#include "test_parameter_set_functions.h"

#include <string.h>
#include <camkes.h>

/* Defines -------------------------------------------------------------------*/
#define TEST_APP     TEST_APP3
#define DOMAIN_APP   DOMAIN_APP3

//------------------------------------------------------------------------------
static void
sync_with_other_apps(void)
{
    test_done_emit();
    app2_test_done_wait();
}

int
run(void)
{
    OS_Error_t err = OS_ERROR_GENERIC;

    //Wait until App1 finishes the basic single client tests
    app2_test_done_wait();

    //Open remote handle of API
    OS_ConfigServiceHandle_t remoteHandle;
    static OS_ConfigService_ClientCtx_t ctx =
    {
        .dataport = OS_DATAPORT_ASSIGN(cfg_dataport_buf)
    };

    if ((err = OS_ConfigService_createHandleRemote(
                   &ctx,
                   &remoteHandle)) != OS_SUCCESS)
    {
        Debug_LOG_ERROR("OS_ConfigService_createHandleRemote() failed with %d", err);
        return -1;
    }

    Debug_LOG_DEBUG("%s: Starting multiclient test of ConfigServer...\n", TEST_APP);
    //Test get parameter functions in multiclient environment
    test_GetInteger32FromFsBackend_pos(&remoteHandle, DOMAIN_APP, TEST_APP,
                                     APP3_PARAMETER_32_NAME_0, APP3_PARAMETER_32_VALUE_0);
    sync_with_other_apps();
    test_GetInteger64FromFsBackend_pos(&remoteHandle, DOMAIN_APP, TEST_APP,
                                     APP3_PARAMETER_64_NAME_0, APP3_PARAMETER_64_VALUE_0);
    sync_with_other_apps();
    test_GetStringsFromFsBackend_pos(&remoteHandle, DOMAIN_APP, TEST_APP,
                                   APP3_PARAMETER_STRING_NAME_0, APP3_PARAMETER_STRING_VALUE_0,
                                   sizeof(APP3_PARAMETER_STRING_VALUE_0));
    sync_with_other_apps();
    test_GetBlobsFromFsBackend_pos(&remoteHandle, DOMAIN_APP, TEST_APP,
                                 APP3_PARAMETER_BLOB_NAME_0, APP3_PARAMETER_BLOB_VALUE_0,
                                 sizeof(APP3_PARAMETER_BLOB_VALUE_0));
    sync_with_other_apps();
    test_GetBlobsFromFsBackend_pos(&remoteHandle, DOMAIN_APP, TEST_APP,
                                 APP3_PARAMETER_BLOB_NAME_3, APP3_PARAMETER_BLOB_VALUE_3,
                                 sizeof(APP3_PARAMETER_BLOB_VALUE_3));
    sync_with_other_apps();

    //Test set parameter functions in multiclient environment
    test_ParameterSetValueAsU32_pos(&remoteHandle, DOMAIN_APP, TEST_APP,
                                  APP3_PARAMETER_32_NAME_0, APP3_PARAMETER_32_VALUE_0_NEW);
    sync_with_other_apps();
    test_ParameterSetValueAsU64_pos(&remoteHandle, DOMAIN_APP, TEST_APP,
                                  APP3_PARAMETER_64_NAME_0, APP3_PARAMETER_64_VALUE_0_NEW);
    sync_with_other_apps();
    test_ParameterSetValueAsString_pos(&remoteHandle, DOMAIN_APP, TEST_APP,
                                     APP3_PARAMETER_STRING_NAME_0, APP3_PARAMETER_STRING_VALUE_0_NEW,
                                     sizeof(APP3_PARAMETER_STRING_VALUE_0_NEW));
    sync_with_other_apps();
    test_ParameterSetValueAsBlob_pos(&remoteHandle, DOMAIN_APP, TEST_APP,
                                   APP3_PARAMETER_BLOB_NAME_0, APP3_PARAMETER_BLOB_VALUE_0_NEW,
                                   sizeof(APP3_PARAMETER_BLOB_VALUE_0_NEW));
    sync_with_other_apps();
    test_ParameterSetValueAsBlob_pos(&remoteHandle, DOMAIN_APP, TEST_APP,
                                   APP3_PARAMETER_BLOB_NAME_3, APP3_PARAMETER_BLOB_VALUE_3_NEW,
                                   sizeof(APP3_PARAMETER_BLOB_VALUE_3_NEW));
    sync_with_other_apps();

    Debug_LOG_DEBUG("%s: All tests completed.\n", TEST_APP);

    return 0;
}
