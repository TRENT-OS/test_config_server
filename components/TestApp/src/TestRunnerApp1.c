/*
   *  TestRunner component that utilizes the ConfigServer as a library but is
   *  additionally connected to a ConfigServer component to run all tests remote
   *  and local.
   *
   *  Copyright (C) 2020, Hensoldt Cyber GmbH
*/


#include "system_config.h"

#include "OS_Error.h"
#include "OS_ConfigService.h"

#include "create_parameters.h"

#include "init_lib_with_fs_backend.h"

#include "test_types.h"
#include "test_create_handle.h"
#include "test_access_right.h"
#include "test_domain_enumerator.h"
#include "test_parameter_enumerator.h"
#include "test_parameter_get_functions.h"
#include "test_parameter_set_functions.h"
#include "test_multiclient_env.h"

#include "lib_debug/Debug.h"
#include <string.h>
#include <camkes.h>


/* Private variables ---------------------------------------------------------*/
static TestApp_t testApp =
{
    .appDomainName    = DOMAIN_APP1,
    .appComponentName = TEST_APP1,
    .uint32TestData =
    {
        .parameterName =
        {
            APP1_PARAMETER_32_NAME_0,
            APP1_PARAMETER_32_NAME_1,
            APP1_PARAMETER_32_NAME_2,
            APP1_PARAMETER_32_NAME_3
        },
        .parameterValue.uint32Value =
        {
            APP1_PARAMETER_32_VALUE_0,
            APP1_PARAMETER_32_VALUE_1,
            APP1_PARAMETER_32_VALUE_2,
            APP1_PARAMETER_32_VALUE_3
        },
        .newParameterValue.uint32Value =
        {
            APP1_PARAMETER_32_VALUE_0_NEW,
            APP1_PARAMETER_32_VALUE_1_NEW,
            APP1_PARAMETER_32_VALUE_2_NEW,
            APP1_PARAMETER_32_VALUE_3_NEW
        }
    },
    .uint64TestData =
    {
        .parameterName =
        {
            APP1_PARAMETER_64_NAME_0,
            APP1_PARAMETER_64_NAME_1,
            APP1_PARAMETER_64_NAME_2,
            APP1_PARAMETER_64_NAME_3
        },
        .parameterValue.uint64Value =
        {
            APP1_PARAMETER_64_VALUE_0,
            APP1_PARAMETER_64_VALUE_1,
            APP1_PARAMETER_64_VALUE_2,
            APP1_PARAMETER_64_VALUE_3
        },
        .newParameterValue.uint64Value =
        {
            APP1_PARAMETER_64_VALUE_0_NEW,
            APP1_PARAMETER_64_VALUE_1_NEW,
            APP1_PARAMETER_64_VALUE_2_NEW,
            APP1_PARAMETER_64_VALUE_3_NEW
        }
    },
    .strTestData =
    {
        .parameterName =
        {
            APP1_PARAMETER_STRING_NAME_0,
            APP1_PARAMETER_STRING_NAME_1,
            APP1_PARAMETER_STRING_NAME_2,
            APP1_PARAMETER_STRING_NAME_3
        },
        .parameterValue.stringValue =
        {
            APP1_PARAMETER_STRING_VALUE_0,
            APP1_PARAMETER_STRING_VALUE_1,
            APP1_PARAMETER_STRING_VALUE_2,
            APP1_PARAMETER_STRING_VALUE_3
        },
        .parameterSize =
        {
            (strlen(APP1_PARAMETER_STRING_VALUE_0) + 1),
            (strlen(APP1_PARAMETER_STRING_VALUE_1) + 1),
            (strlen(APP1_PARAMETER_STRING_VALUE_2) + 1),
            (strlen(APP1_PARAMETER_STRING_VALUE_3) + 1)
        },
        .newParameterValue.stringValue =
        {
            APP1_PARAMETER_STRING_VALUE_0_NEW,
            APP1_PARAMETER_STRING_VALUE_1_NEW,
            APP1_PARAMETER_STRING_VALUE_2_NEW,
            APP1_PARAMETER_STRING_VALUE_3_NEW
        },
        .newParameterSize =
        {
            (strlen(APP1_PARAMETER_STRING_VALUE_0_NEW) + 1),
            (strlen(APP1_PARAMETER_STRING_VALUE_1_NEW) + 1),
            (strlen(APP1_PARAMETER_STRING_VALUE_2_NEW) + 1),
            (strlen(APP1_PARAMETER_STRING_VALUE_3_NEW) + 1)
        }
    },
    .blobTestData =
    {
        .parameterName =
        {
            APP1_PARAMETER_BLOB_NAME_0,
            APP1_PARAMETER_BLOB_NAME_1,
            APP1_PARAMETER_BLOB_NAME_2,
            APP1_PARAMETER_BLOB_NAME_3
        },
        .parameterValue.rawValue =
        {
            APP1_PARAMETER_BLOB_VALUE_0,
            APP1_PARAMETER_BLOB_VALUE_1,
            APP1_PARAMETER_BLOB_VALUE_2,
            APP1_PARAMETER_BLOB_VALUE_3
        },
        .parameterSize =
        {
            sizeof(APP1_PARAMETER_BLOB_VALUE_0),
            sizeof(APP1_PARAMETER_BLOB_VALUE_1),
            sizeof(APP1_PARAMETER_BLOB_VALUE_2),
            sizeof(APP1_PARAMETER_BLOB_VALUE_3)
        },
        .newParameterValue.rawValue =
        {
            APP1_PARAMETER_BLOB_VALUE_0_NEW,
            APP1_PARAMETER_BLOB_VALUE_1_NEW,
            APP1_PARAMETER_BLOB_VALUE_2_NEW,
            APP1_PARAMETER_BLOB_VALUE_3_NEW
        },
        .newParameterSize =
        {
            sizeof(APP1_PARAMETER_BLOB_VALUE_0_NEW),
            sizeof(APP1_PARAMETER_BLOB_VALUE_1_NEW),
            sizeof(APP1_PARAMETER_BLOB_VALUE_2_NEW),
            sizeof(APP1_PARAMETER_BLOB_VALUE_3_NEW)
        }
    }
};

static OS_FileSystem_Config_t cfg =
{
    .type = OS_FileSystem_Type_FATFS,
    .size = OS_FileSystem_USE_STORAGE_MAX,
    .storage = IF_OS_STORAGE_ASSIGN(
        storage_rpc,
        storage_dp),
};

//------------------------------------------------------------------------------
static void
sync_with_other_apps(void)
{
    test_done_emit();
    app4_test_done_wait();
}

static void
runBasicTestSuite(
    OS_ConfigServiceLib_t* instance,
    OS_ConfigServiceHandle_HandleKind_t handleKind)
{
    OS_ConfigServiceHandle_t configHandle;

    test_CreateHandle_pos(
        &configHandle,
        handleKind,
        testApp.appComponentName);

    test_DomainEnumerator_increment_pos(
        &configHandle,
        testApp.appComponentName,
        instance->domainBackend.numberOfRecords);

    test_DomainEnumerator_reset_pos(
        &configHandle,
        testApp.appComponentName,
        instance->domainBackend.numberOfRecords);

    test_ParameterEnumerator_increment_pos(
        &configHandle,
        testApp.appComponentName,
        instance->domainBackend.numberOfRecords,
        instance->parameterBackend.numberOfRecords);

    test_ParameterEnumerator_reset_pos(
        &configHandle,
        testApp.appComponentName,
        instance->domainBackend.numberOfRecords,
        instance->parameterBackend.numberOfRecords);

    //Test get parameter functions
    for (uint8_t i = 0; i < (NUM_TEST_PARAMETERS); i++)
    {
        test_GetInteger32FromFsBackend_pos(
            &configHandle,
            testApp.appDomainName,
            testApp.appComponentName,
            testApp.uint32TestData.parameterName[i],
            testApp.uint32TestData.parameterValue.uint32Value[i]);

        test_GetInteger64FromFsBackend_pos(
            &configHandle,
            testApp.appDomainName,
            testApp.appComponentName,
            testApp.uint64TestData.parameterName[i],
            testApp.uint64TestData.parameterValue.uint64Value[i]);

        test_GetStringsFromFsBackend_pos(
            &configHandle,
            testApp.appDomainName,
            testApp.appComponentName,
            testApp.strTestData.parameterName[i],
            testApp.strTestData.parameterValue.stringValue[i],
            testApp.strTestData.parameterSize[i]);

        test_GetBlobsFromFsBackend_pos(
            &configHandle,
            testApp.appDomainName,
            testApp.appComponentName,
            testApp.blobTestData.parameterName[i],
            testApp.blobTestData.parameterValue.rawValue[i],
            testApp.blobTestData.parameterSize[i]);
    }

    //Test fetching a parameter that has no read access rights
    test_ParameterReadAccessRight_pos(
        &configHandle,
        DOMAIN_APP2,
        testApp.appComponentName,
        APP2_PARAMETER_BLOB_NAME_2,
        APP2_PARAMETER_BLOB_VALUE_2,
        sizeof(APP2_PARAMETER_BLOB_VALUE_2));

    //Test set parameter functions
    for (uint8_t i = 0; i < (NUM_TEST_PARAMETERS); i++)
    {
        test_ParameterSetValueAsU32_pos(
            &configHandle,
            testApp.appDomainName,
            testApp.appComponentName,
            testApp.uint32TestData.parameterName[i],
            testApp.uint32TestData.newParameterValue.uint32Value[i]);

        test_ParameterSetValueAsU64_pos(
            &configHandle,
            testApp.appDomainName,
            testApp.appComponentName,
            testApp.uint64TestData.parameterName[i],
            testApp.uint64TestData.newParameterValue.uint64Value[i]);

        test_ParameterSetValueAsString_pos(
            &configHandle,
            testApp.appDomainName,
            testApp.appComponentName,
            testApp.strTestData.parameterName[i],
            testApp.strTestData.newParameterValue.stringValue[i],
            testApp.strTestData.newParameterSize[i]);

        test_ParameterSetValueAsBlob_pos(
            &configHandle,
            testApp.appDomainName,
            testApp.appComponentName,
            testApp.blobTestData.parameterName[i],
            testApp.blobTestData.newParameterValue.rawValue[i],
            testApp.blobTestData.newParameterSize[i]);
    }

    // Test setting a parameter that has no write access rights
    test_ParameterWriteAccessRight_pos(
        &configHandle,
        DOMAIN_APP2,
        testApp.appComponentName,
        APP2_PARAMETER_BLOB_NAME_1,
        APP2_PARAMETER_BLOB_VALUE_1_NEW,
        sizeof(APP2_PARAMETER_BLOB_VALUE_1_NEW));

    // Test generic SetValue
    uint32_t interger32Value = testApp.uint32TestData.parameterValue.uint32Value[0];
    uint64_t integer64Value = testApp.uint32TestData.parameterValue.uint64Value[0];
    test_ParameterSetValue_pos(
        &configHandle,
        testApp.appDomainName,
        testApp.appComponentName,
        testApp.uint32TestData.parameterName[0],
        &interger32Value,
        sizeof(interger32Value));

    test_ParameterSetValue_pos(
        &configHandle,
        testApp.appDomainName,
        testApp.appComponentName,
        testApp.uint64TestData.parameterName[0],
        &integer64Value,
        sizeof(integer64Value));

    test_ParameterSetValue_pos(
        &configHandle,
        testApp.appDomainName,
        testApp.appComponentName,
        testApp.strTestData.parameterName[0],
        testApp.strTestData.parameterValue.stringValue[0],
        testApp.strTestData.parameterSize[0]);

    test_ParameterSetValue_pos(
        &configHandle,
        testApp.appDomainName,
        testApp.appComponentName,
        testApp.blobTestData.parameterName[0],
        testApp.blobTestData.parameterValue.rawValue[0],
        testApp.blobTestData.parameterSize[0]);

    // Reset altered parameters to original values
    for (uint8_t i = 0; i < (NUM_TEST_PARAMETERS); i++)
    {
        test_ParameterSetValueAsU32_pos(
            &configHandle,
            testApp.appDomainName,
            testApp.appComponentName,
            testApp.uint32TestData.parameterName[i],
            testApp.uint32TestData.parameterValue.uint32Value[i]);

        test_ParameterSetValueAsU64_pos(
            &configHandle,
            testApp.appDomainName,
            testApp.appComponentName,
            testApp.uint64TestData.parameterName[i],
            testApp.uint64TestData.parameterValue.uint64Value[i]);

        test_ParameterSetValueAsString_pos(
            &configHandle,
            testApp.appDomainName,
            testApp.appComponentName,
            testApp.strTestData.parameterName[i],
            testApp.strTestData.parameterValue.stringValue[i],
            testApp.strTestData.parameterSize[i]);

        test_ParameterSetValueAsBlob_pos(
            &configHandle,
            testApp.appDomainName,
            testApp.appComponentName,
            testApp.blobTestData.parameterName[i],
            testApp.blobTestData.parameterValue.rawValue[i],
            testApp.blobTestData.parameterSize[i]);
    }
}

static bool
runTestsOnLocalConfigServiceInstance(OS_ConfigServiceLib_t* configLib)
{
    OS_FileSystem_Handle_t hFs;

    if (OS_FileSystem_init(&hFs, &cfg) != OS_SUCCESS)
    {
        Debug_LOG_ERROR("OS_FileSystem_init() failed.");
        return false;
    }

    if (OS_FileSystem_mount(hFs) != OS_SUCCESS)
    {
        Debug_LOG_ERROR("OS_FileSystem_mount() failed.");
        return false;
    }

    // Create the file backends
    Debug_LOG_INFO("Initializing with file backend");
    if (initializeWithFileBackends(configLib, hFs) != OS_SUCCESS)
    {
        Debug_LOG_ERROR("initializeWithFileBackends() failed.");
        return false;
    }

    runBasicTestSuite(configLib, OS_CONFIG_HANDLE_KIND_LOCAL);

    if (OS_FileSystem_unmount(hFs) != OS_SUCCESS)
    {
        Debug_LOG_ERROR("OS_FileSystem_unmount() failed.");
        return false;
    }

    if (OS_FileSystem_free(hFs) != OS_SUCCESS)
    {
        Debug_LOG_ERROR("OS_FileSystem_free() failed.");
        return false;
    }

    // Unblock the ConfigServer for the remote tests
    local_test_done_emit();

    return true;
}

//------------------------------------------------------------------------------
int
run(void)
{
    // Wait until the remote backend is injected
    injector_component_backend_injected();

    OS_ConfigServiceLib_t* instance =
        OS_ConfigService_getInstance();

    // Run basic tests on the local ConfigServer instance
    if (!runTestsOnLocalConfigServiceInstance(instance))
    {
        Debug_LOG_ERROR("runTestsOnLocalConfigServiceInstance failed!");
        return -1;
    }

    // Run basic tests on the remote ConfigServer
    Debug_LOG_INFO("Starting tests of remote ConfigServer instance...");
    runBasicTestSuite(instance, OS_CONFIG_HANDLE_KIND_RPC);

    Debug_LOG_DEBUG("%s: Basic functionality tests completed. Unblocking other clients...",
                    testApp.appComponentName);

    Debug_LOG_INFO("%s: Starting multiclient test of ConfigServer...\n",
                   testApp.appComponentName);

    // Initialize a handle to the remote ConfigServer component
    OS_ConfigServiceHandle_t remoteHandle;
    test_CreateHandle_pos(&remoteHandle, OS_CONFIG_HANDLE_KIND_RPC,
                          testApp.appComponentName);

    //Test the remote Server in a multiclient environment
    test_multiClient_environment(&remoteHandle, &testApp, sync_with_other_apps);

    Debug_LOG_INFO("%s: All tests completed.", testApp.appComponentName);

    return 0;
}
