/*
   *  TestRunnerApp connected to a ConfigServer component to run all tests remote
   *  in in a multiclient setup with other TestRunnerApps.
   *
   *  Copyright (C) 2020, Hensoldt Cyber GmbH
*/



#include "seos_system_config.h"

#include "SeosError.h"
#include "seos_config.h"

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
    seos_err_t err = SEOS_ERROR_GENERIC;

    //Wait until App1 finishes the basic single client tests
    app2_test_done_wait();

    //Open remote handle of API
    SeosConfigHandle remoteHandle;
    err = seos_configuration_createHandle(SEOS_CONFIG_HANDLE_KIND_RPC, 0, &remoteHandle);
    Debug_ASSERT_PRINTFLN(err == SEOS_SUCCESS, "err %d", err);

    Debug_LOG_DEBUG("%s: Starting multiclient test of ConfigServer...\n", TEST_APP);
    //Test get parameter functions in multiclient environment
    TestGetInteger32FromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                     APP3_PARAMETER_32_NAME_0, APP3_PARAMETER_32_VALUE_0);
    sync_with_other_apps();
    TestGetInteger64FromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                     APP3_PARAMETER_64_NAME_0, APP3_PARAMETER_64_VALUE_0);
    sync_with_other_apps();
    TestGetStringsFromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                   APP3_PARAMETER_STRING_NAME_0, APP3_PARAMETER_STRING_VALUE_0,
                                   sizeof(APP3_PARAMETER_STRING_VALUE_0));
    sync_with_other_apps();
    TestGetBlobsFromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                 APP3_PARAMETER_BLOB_NAME_0, APP3_PARAMETER_BLOB_VALUE_0,
                                 sizeof(APP3_PARAMETER_BLOB_VALUE_0));
    sync_with_other_apps();
    TestGetBlobsFromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                 APP3_PARAMETER_BLOB_NAME_3, APP3_PARAMETER_BLOB_VALUE_3,
                                 sizeof(APP3_PARAMETER_BLOB_VALUE_3));
    sync_with_other_apps();

    //Test set parameter functions in multiclient environment
    TestParameterSetValueAsU32_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                  APP3_PARAMETER_32_NAME_0, APP3_PARAMETER_32_VALUE_0_NEW);
    sync_with_other_apps();
    TestParameterSetValueAsU64_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                  APP3_PARAMETER_64_NAME_0, APP3_PARAMETER_64_VALUE_0_NEW);
    sync_with_other_apps();
    TestParameterSetValueAsString_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                     APP3_PARAMETER_STRING_NAME_0, APP3_PARAMETER_STRING_VALUE_0_NEW,
                                     sizeof(APP3_PARAMETER_STRING_VALUE_0_NEW));
    sync_with_other_apps();
    TestParameterSetValueAsBlob_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                   APP3_PARAMETER_BLOB_NAME_0, APP3_PARAMETER_BLOB_VALUE_0_NEW,
                                   sizeof(APP3_PARAMETER_BLOB_VALUE_0_NEW));
    sync_with_other_apps();
    TestParameterSetValueAsBlob_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                   APP3_PARAMETER_BLOB_NAME_3, APP3_PARAMETER_BLOB_VALUE_3_NEW,
                                   sizeof(APP3_PARAMETER_BLOB_VALUE_3_NEW));
    sync_with_other_apps();

    Debug_LOG_DEBUG("%s: All tests completed.\n", TEST_APP);

    return 0;
}
