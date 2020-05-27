/*
   *  TestRunnerApp connected to a ConfigServer component to run all tests remote
   *  in in a multiclient setup with other TestRunnerApps.
   *
   *  Copyright (C) 2020, Hensoldt Cyber GmbH
*/


#include "system_config.h"

#include "OS_Error.h"
#include "OS_ConfigService.h"

#include "LibDebug/Debug.h"

#include "test_parameter_get_functions.h"
#include "test_parameter_set_functions.h"

#include <string.h>
#include <camkes.h>

/* Defines -------------------------------------------------------------------*/
#define TEST_APP     TEST_APP4
#define DOMAIN_APP   DOMAIN_APP4

//------------------------------------------------------------------------------
static void
sync_with_other_apps(void)
{
    test_done_emit();
    app3_test_done_wait();
}

int
run(void)
{
    OS_Error_t err = OS_ERROR_GENERIC;

    //wait until App1 finishes the basic single client tests
    app3_test_done_wait();

    //Open remote handle of API
    OS_ConfigServiceHandle_t remoteHandle;
    err = OS_ConfigService_createHandle(OS_CONFIG_HANDLE_KIND_RPC, 0, &remoteHandle);
    Debug_ASSERT_PRINTFLN(err == OS_SUCCESS, "err %d", err);

    Debug_LOG_DEBUG("%s: Starting multiclient test of ConfigServer...\n", TEST_APP);
    //Test get parameter functions in multiclient environment
    TestGetInteger32FromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                     APP4_PARAMETER_32_NAME_0, APP4_PARAMETER_32_VALUE_0);
    sync_with_other_apps();
    TestGetInteger64FromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                     APP4_PARAMETER_64_NAME_0, APP4_PARAMETER_64_VALUE_0);
    sync_with_other_apps();
    TestGetStringsFromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                   APP4_PARAMETER_STRING_NAME_0, APP4_PARAMETER_STRING_VALUE_0,
                                   sizeof(APP4_PARAMETER_STRING_VALUE_0));
    sync_with_other_apps();
    TestGetBlobsFromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                 APP4_PARAMETER_BLOB_NAME_0, APP4_PARAMETER_BLOB_VALUE_0,
                                 sizeof(APP4_PARAMETER_BLOB_VALUE_0));
    sync_with_other_apps();
    TestGetBlobsFromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                 APP4_PARAMETER_BLOB_NAME_3, APP4_PARAMETER_BLOB_VALUE_3,
                                 sizeof(APP4_PARAMETER_BLOB_VALUE_3));
    sync_with_other_apps();

    //Test set parameter functions in multiclient environment
    TestParameterSetValueAsU32_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                  APP4_PARAMETER_32_NAME_0, APP4_PARAMETER_32_VALUE_0_NEW);
    sync_with_other_apps();
    TestParameterSetValueAsU64_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                  APP4_PARAMETER_64_NAME_0, APP4_PARAMETER_64_VALUE_0_NEW);
    sync_with_other_apps();
    TestParameterSetValueAsString_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                     APP4_PARAMETER_STRING_NAME_0, APP4_PARAMETER_STRING_VALUE_0_NEW,
                                     sizeof(APP4_PARAMETER_STRING_VALUE_0_NEW));
    sync_with_other_apps();
    TestParameterSetValueAsBlob_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                   APP4_PARAMETER_BLOB_NAME_0, APP4_PARAMETER_BLOB_VALUE_0_NEW,
                                   sizeof(APP4_PARAMETER_BLOB_VALUE_0_NEW));
    sync_with_other_apps();
    TestParameterSetValueAsBlob_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                   APP4_PARAMETER_BLOB_NAME_3, APP4_PARAMETER_BLOB_VALUE_3_NEW,
                                   sizeof(APP4_PARAMETER_BLOB_VALUE_3_NEW));
    sync_with_other_apps();

    Debug_LOG_DEBUG("%s: All tests completed.\n", TEST_APP);

    return 0;
}
