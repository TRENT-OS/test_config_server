/*
   *  TestRunnerApp connected to a ConfigServer component to run all tests remote
   *  in in a multiclient setup with other TestRunnerApps.
   *
   *  Copyright (C) 2020, HENSOLDT Cyber GmbH
*/


#include "system_config.h"

#include "OS_Error.h"
#include "OS_ConfigService.h"
#include "OS_Dataport.h"

#include "lib_debug/Debug.h"

#include "test_types.h"
#include "test_multiclient_env.h"

#include <string.h>
#include <camkes.h>


/* Private variables ---------------------------------------------------------*/
static TestApp_t testApp =
{
    .appDomainName    = DOMAIN_APP4,
    .appComponentName = TEST_APP4,
    .uint32TestData =
    {
        .parameterName =
        {
            APP4_PARAMETER_32_NAME_0,
            APP4_PARAMETER_32_NAME_1,
            APP4_PARAMETER_32_NAME_2,
            APP4_PARAMETER_32_NAME_3
        },
        .parameterValue.uint32Value =
        {
            APP4_PARAMETER_32_VALUE_0,
            APP4_PARAMETER_32_VALUE_1,
            APP4_PARAMETER_32_VALUE_2,
            APP4_PARAMETER_32_VALUE_3
        },
        .newParameterValue.uint32Value =
        {
            APP4_PARAMETER_32_VALUE_0_NEW,
            APP4_PARAMETER_32_VALUE_1_NEW,
            APP4_PARAMETER_32_VALUE_2_NEW,
            APP4_PARAMETER_32_VALUE_3_NEW
        }
    },
    .uint64TestData =
    {
        .parameterName =
        {
            APP4_PARAMETER_64_NAME_0,
            APP4_PARAMETER_64_NAME_1,
            APP4_PARAMETER_64_NAME_2,
            APP4_PARAMETER_64_NAME_3
        },
        .parameterValue.uint64Value =
        {
            APP4_PARAMETER_64_VALUE_0,
            APP4_PARAMETER_64_VALUE_1,
            APP4_PARAMETER_64_VALUE_2,
            APP4_PARAMETER_64_VALUE_3
        },
        .newParameterValue.uint64Value =
        {
            APP4_PARAMETER_64_VALUE_0_NEW,
            APP4_PARAMETER_64_VALUE_1_NEW,
            APP4_PARAMETER_64_VALUE_2_NEW,
            APP4_PARAMETER_64_VALUE_3_NEW
        }
    },
    .strTestData =
    {
        .parameterName =
        {
            APP4_PARAMETER_STRING_NAME_0,
            APP4_PARAMETER_STRING_NAME_1,
            APP4_PARAMETER_STRING_NAME_2,
            APP4_PARAMETER_STRING_NAME_3
        },
        .parameterValue.stringValue =
        {
            APP4_PARAMETER_STRING_VALUE_0,
            APP4_PARAMETER_STRING_VALUE_1,
            APP4_PARAMETER_STRING_VALUE_2,
            APP4_PARAMETER_STRING_VALUE_3
        },
        .parameterSize =
        {
            (strlen(APP4_PARAMETER_STRING_VALUE_0) + 1),
            (strlen(APP4_PARAMETER_STRING_VALUE_1) + 1),
            (strlen(APP4_PARAMETER_STRING_VALUE_2) + 1),
            (strlen(APP4_PARAMETER_STRING_VALUE_3) + 1)
        },
        .newParameterValue.stringValue =
        {
            APP4_PARAMETER_STRING_VALUE_0_NEW,
            APP4_PARAMETER_STRING_VALUE_1_NEW,
            APP4_PARAMETER_STRING_VALUE_2_NEW,
            APP4_PARAMETER_STRING_VALUE_3_NEW
        },
        .newParameterSize =
        {
            (strlen(APP4_PARAMETER_STRING_VALUE_0_NEW) + 1),
            (strlen(APP4_PARAMETER_STRING_VALUE_1_NEW) + 1),
            (strlen(APP4_PARAMETER_STRING_VALUE_2_NEW) + 1),
            (strlen(APP4_PARAMETER_STRING_VALUE_3_NEW) + 1)
        }
    },
    .blobTestData =
    {
        .parameterName =
        {
            APP4_PARAMETER_BLOB_NAME_0,
            APP4_PARAMETER_BLOB_NAME_1,
            APP4_PARAMETER_BLOB_NAME_2,
            APP4_PARAMETER_BLOB_NAME_3
        },
        .parameterValue.rawValue =
        {
            APP4_PARAMETER_BLOB_VALUE_0,
            APP4_PARAMETER_BLOB_VALUE_1,
            APP4_PARAMETER_BLOB_VALUE_2,
            APP4_PARAMETER_BLOB_VALUE_3
        },
        .parameterSize =
        {
            sizeof(APP4_PARAMETER_BLOB_VALUE_0),
            sizeof(APP4_PARAMETER_BLOB_VALUE_1),
            sizeof(APP4_PARAMETER_BLOB_VALUE_2),
            sizeof(APP4_PARAMETER_BLOB_VALUE_3)
        },
        .newParameterValue.rawValue =
        {
            APP4_PARAMETER_BLOB_VALUE_0_NEW,
            APP4_PARAMETER_BLOB_VALUE_1_NEW,
            APP4_PARAMETER_BLOB_VALUE_2_NEW,
            APP4_PARAMETER_BLOB_VALUE_3_NEW
        },
        .newParameterSize =
        {
            sizeof(APP4_PARAMETER_BLOB_VALUE_0_NEW),
            sizeof(APP4_PARAMETER_BLOB_VALUE_1_NEW),
            sizeof(APP4_PARAMETER_BLOB_VALUE_2_NEW),
            sizeof(APP4_PARAMETER_BLOB_VALUE_3_NEW)
        }
    }
};

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
    static OS_ConfigService_ClientCtx_t ctx =
    {
        .dataport = OS_DATAPORT_ASSIGN(cfg_port)
    };

    if ((err = OS_ConfigService_createHandleRemote(
                   &ctx,
                   &remoteHandle)) != OS_SUCCESS)
    {
        Debug_LOG_ERROR("OS_ConfigService_createHandleRemote() failed with %d", err);
        return -1;
    }

    Debug_LOG_DEBUG("%s: Starting multiclient test of ConfigServer...\n",
                    testApp.appComponentName);

    //Test the remote Server in a multiclient environment
    test_multiClient_environment(&remoteHandle, &testApp, sync_with_other_apps);

    Debug_LOG_DEBUG("%s: All tests completed.\n", testApp.appComponentName);

    return 0;
}
