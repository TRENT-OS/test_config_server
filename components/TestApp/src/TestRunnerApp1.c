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

#include "test_create_handle.h"
#include "test_access_right.h"
#include "test_domain_enumerator.h"
#include "test_parameter_enumerator.h"
#include "test_parameter_get_functions.h"
#include "test_parameter_set_functions.h"

#include "LibDebug/Debug.h"
#include <string.h>
#include <camkes.h>

/* Defines -------------------------------------------------------------------*/
#define TEST_APP     TEST_APP1
#define DOMAIN_APP   DOMAIN_APP1


/* Private types -------------------------------------------------------------*/
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

    test_CreateHandle_pos(&configHandle, handleKind, TEST_APP);

    test_DomainEnumerator_increment_pos(&configHandle, TEST_APP,
                                      instance->domainBackend.numberOfRecords);

    test_DomainEnumerator_reset_pos(&configHandle, TEST_APP,
                                  instance->domainBackend.numberOfRecords);

    test_ParameterEnumerator_increment_pos(&configHandle,
                                         TEST_APP,
                                         instance->domainBackend.numberOfRecords,
                                         instance->parameterBackend.numberOfRecords);

    test_ParameterEnumerator_reset_pos(&configHandle,
                                     TEST_APP,
                                     instance->domainBackend.numberOfRecords,
                                     instance->parameterBackend.numberOfRecords);

    //Test get parameter functions
    test_GetInteger32FromFsBackend_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_32_NAME_0, APP1_PARAMETER_32_VALUE_0);

    test_GetInteger32FromFsBackend_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_32_NAME_1, APP1_PARAMETER_32_VALUE_1);

    test_GetInteger32FromFsBackend_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_32_NAME_2, APP1_PARAMETER_32_VALUE_2);

    test_GetInteger32FromFsBackend_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_32_NAME_3, APP1_PARAMETER_32_VALUE_3);

    test_GetInteger64FromFsBackend_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_64_NAME_0, APP1_PARAMETER_64_VALUE_0);

    test_GetInteger64FromFsBackend_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_64_NAME_1, APP1_PARAMETER_64_VALUE_1);

    test_GetInteger64FromFsBackend_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_64_NAME_2, APP1_PARAMETER_64_VALUE_2);

    test_GetInteger64FromFsBackend_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_64_NAME_3, APP1_PARAMETER_64_VALUE_3);

    test_GetStringsFromFsBackend_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_STRING_NAME_0, APP1_PARAMETER_STRING_VALUE_0,
                                   sizeof(APP1_PARAMETER_STRING_VALUE_0));

    test_GetStringsFromFsBackend_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_STRING_NAME_1, APP1_PARAMETER_STRING_VALUE_1,
                                   sizeof(APP1_PARAMETER_STRING_VALUE_1));

    test_GetStringsFromFsBackend_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_STRING_NAME_2, APP1_PARAMETER_STRING_VALUE_2,
                                   sizeof(APP1_PARAMETER_STRING_VALUE_2));

    test_GetStringsFromFsBackend_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_STRING_NAME_3, APP1_PARAMETER_STRING_VALUE_3,
                                   sizeof(APP1_PARAMETER_STRING_VALUE_3));

    test_GetBlobsFromFsBackend_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                 APP1_PARAMETER_BLOB_NAME_0, APP1_PARAMETER_BLOB_VALUE_0,
                                 sizeof(APP1_PARAMETER_BLOB_VALUE_0));

    test_GetBlobsFromFsBackend_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                 APP1_PARAMETER_BLOB_NAME_1, APP1_PARAMETER_BLOB_VALUE_1,
                                 sizeof(APP1_PARAMETER_BLOB_VALUE_1));

    test_GetBlobsFromFsBackend_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                 APP1_PARAMETER_BLOB_NAME_2, APP1_PARAMETER_BLOB_VALUE_2,
                                 sizeof(APP1_PARAMETER_BLOB_VALUE_2));

    test_GetBlobsFromFsBackend_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                 APP1_PARAMETER_BLOB_NAME_3, APP1_PARAMETER_BLOB_VALUE_3,
                                 sizeof(APP1_PARAMETER_BLOB_VALUE_3));

    //Test fetching a parameter that has no read access rights
    test_ParameterReadAccessRight_pos(&configHandle, DOMAIN_APP2, TEST_APP,
                                    APP2_PARAMETER_BLOB_NAME_2, APP2_PARAMETER_BLOB_VALUE_2,
                                    sizeof(APP2_PARAMETER_BLOB_VALUE_2));

    //Test set parameter functions
    test_ParameterSetValueAsU32_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_32_NAME_0, APP1_PARAMETER_32_VALUE_0_NEW);

    test_ParameterSetValueAsU32_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_32_NAME_1, APP1_PARAMETER_32_VALUE_1_NEW);

    test_ParameterSetValueAsU32_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_32_NAME_2, APP1_PARAMETER_32_VALUE_2_NEW);

    test_ParameterSetValueAsU32_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_32_NAME_3, APP1_PARAMETER_32_VALUE_3_NEW);

    test_ParameterSetValueAsU64_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_64_NAME_0, APP1_PARAMETER_64_VALUE_0_NEW);

    test_ParameterSetValueAsU64_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_64_NAME_1, APP1_PARAMETER_64_VALUE_1_NEW);

    test_ParameterSetValueAsU64_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_64_NAME_2, APP1_PARAMETER_64_VALUE_2_NEW);

    test_ParameterSetValueAsU64_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_64_NAME_3, APP1_PARAMETER_64_VALUE_3_NEW);

    test_ParameterSetValueAsString_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_STRING_NAME_0, APP1_PARAMETER_STRING_VALUE_0_NEW,
                                     sizeof(APP1_PARAMETER_STRING_VALUE_0_NEW));

    test_ParameterSetValueAsString_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_STRING_NAME_1, APP1_PARAMETER_STRING_VALUE_1_NEW,
                                     sizeof(APP1_PARAMETER_STRING_VALUE_1_NEW));

    test_ParameterSetValueAsString_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_STRING_NAME_2, APP1_PARAMETER_STRING_VALUE_2_NEW,
                                     sizeof(APP1_PARAMETER_STRING_VALUE_2_NEW));

    test_ParameterSetValueAsString_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_STRING_NAME_3, APP1_PARAMETER_STRING_VALUE_3_NEW,
                                     sizeof(APP1_PARAMETER_STRING_VALUE_3_NEW));

    test_ParameterSetValueAsBlob_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_BLOB_NAME_0, APP1_PARAMETER_BLOB_VALUE_0_NEW,
                                   sizeof(APP1_PARAMETER_BLOB_VALUE_0_NEW));

    test_ParameterSetValueAsBlob_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_BLOB_NAME_1, APP1_PARAMETER_BLOB_VALUE_1_NEW,
                                   sizeof(APP1_PARAMETER_BLOB_VALUE_1_NEW));

    test_ParameterSetValueAsBlob_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_BLOB_NAME_2, APP1_PARAMETER_BLOB_VALUE_2_NEW,
                                   sizeof(APP1_PARAMETER_BLOB_VALUE_2_NEW));

    test_ParameterSetValueAsBlob_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_BLOB_NAME_3, APP1_PARAMETER_BLOB_VALUE_3_NEW,
                                   sizeof(APP1_PARAMETER_BLOB_VALUE_3_NEW));

    // Test setting a parameter that has no write access rights
    test_ParameterWriteAccessRight_pos(&configHandle, DOMAIN_APP2, TEST_APP,
                                     APP2_PARAMETER_BLOB_NAME_1, APP2_PARAMETER_BLOB_VALUE_1_NEW,
                                     sizeof(APP2_PARAMETER_BLOB_VALUE_1_NEW));
    // Test generic SetValue
    uint32_t interger32Value = APP1_PARAMETER_32_VALUE_0;
    uint64_t integer64Value = APP1_PARAMETER_64_VALUE_0;
    test_ParameterSetValue_pos(&configHandle, DOMAIN_APP, TEST_APP,
                             APP1_PARAMETER_32_NAME_0, &interger32Value, sizeof(interger32Value));

    test_ParameterSetValue_pos(&configHandle, DOMAIN_APP, TEST_APP,
                             APP1_PARAMETER_64_NAME_0, &integer64Value, sizeof(integer64Value));

    test_ParameterSetValue_pos(&configHandle, DOMAIN_APP, TEST_APP,
                             APP1_PARAMETER_STRING_NAME_0, APP1_PARAMETER_STRING_VALUE_0,
                             sizeof(APP1_PARAMETER_STRING_VALUE_0));

    test_ParameterSetValue_pos(&configHandle, DOMAIN_APP, TEST_APP,
                             APP1_PARAMETER_BLOB_NAME_0, APP1_PARAMETER_BLOB_VALUE_0,
                             sizeof(APP1_PARAMETER_BLOB_VALUE_0));

    // Reset altered parameters to original values
    test_ParameterSetValueAsU32_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_32_NAME_1, APP1_PARAMETER_32_VALUE_1);

    test_ParameterSetValueAsU32_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_32_NAME_2, APP1_PARAMETER_32_VALUE_2);

    test_ParameterSetValueAsU32_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_32_NAME_3, APP1_PARAMETER_32_VALUE_3);

    test_ParameterSetValueAsU64_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_64_NAME_1, APP1_PARAMETER_64_VALUE_1);

    test_ParameterSetValueAsU64_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_64_NAME_2, APP1_PARAMETER_64_VALUE_2);

    test_ParameterSetValueAsU64_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_64_NAME_3, APP1_PARAMETER_64_VALUE_3);

    test_ParameterSetValueAsString_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_STRING_NAME_1, APP1_PARAMETER_STRING_VALUE_1,
                                     sizeof(APP1_PARAMETER_STRING_VALUE_1));

    test_ParameterSetValueAsString_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_STRING_NAME_2, APP1_PARAMETER_STRING_VALUE_2,
                                     sizeof(APP1_PARAMETER_STRING_VALUE_2));

    test_ParameterSetValueAsString_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_STRING_NAME_3, APP1_PARAMETER_STRING_VALUE_3,
                                     sizeof(APP1_PARAMETER_STRING_VALUE_3));

    test_ParameterSetValueAsBlob_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_BLOB_NAME_1, APP1_PARAMETER_BLOB_VALUE_1,
                                   sizeof(APP1_PARAMETER_BLOB_VALUE_1));

    test_ParameterSetValueAsBlob_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_BLOB_NAME_2, APP1_PARAMETER_BLOB_VALUE_2,
                                   sizeof(APP1_PARAMETER_BLOB_VALUE_2));

    test_ParameterSetValueAsBlob_pos(&configHandle, DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_BLOB_NAME_3, APP1_PARAMETER_BLOB_VALUE_3,
                                   sizeof(APP1_PARAMETER_BLOB_VALUE_3));
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
                    TEST_APP);

    Debug_LOG_DEBUG("%s: Starting multiclient test of ConfigServer...", TEST_APP);
    OS_ConfigServiceHandle_t remoteHandle;
    test_CreateHandle_pos(&remoteHandle, OS_CONFIG_HANDLE_KIND_RPC, TEST_APP);
    //Test get parameter functions in multiclient environment
    test_GetInteger32FromFsBackend_pos(&remoteHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_32_NAME_0, APP1_PARAMETER_32_VALUE_0);
    sync_with_other_apps();
    test_GetInteger64FromFsBackend_pos(&remoteHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_64_NAME_0, APP1_PARAMETER_64_VALUE_0);
    sync_with_other_apps();
    test_GetStringsFromFsBackend_pos(&remoteHandle,  DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_STRING_NAME_0, APP1_PARAMETER_STRING_VALUE_0,
                                   sizeof(APP1_PARAMETER_STRING_VALUE_0));
    sync_with_other_apps();
    test_GetBlobsFromFsBackend_pos(&remoteHandle, DOMAIN_APP, TEST_APP,
                                 APP1_PARAMETER_BLOB_NAME_0, APP1_PARAMETER_BLOB_VALUE_0,
                                 sizeof(APP1_PARAMETER_BLOB_VALUE_0));
    sync_with_other_apps();
    test_GetBlobsFromFsBackend_pos(&remoteHandle, DOMAIN_APP, TEST_APP,
                                 APP1_PARAMETER_BLOB_NAME_3, APP1_PARAMETER_BLOB_VALUE_3,
                                 sizeof(APP1_PARAMETER_BLOB_VALUE_3));
    sync_with_other_apps();

    //Test set parameter functions in multiclient environment
    test_ParameterSetValueAsU32_pos(&remoteHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_32_NAME_0, APP1_PARAMETER_32_VALUE_0_NEW);
    sync_with_other_apps();
    test_ParameterSetValueAsU64_pos(&remoteHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_64_NAME_0, APP1_PARAMETER_64_VALUE_0_NEW);
    sync_with_other_apps();
    test_ParameterSetValueAsString_pos(&remoteHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_STRING_NAME_0, APP1_PARAMETER_STRING_VALUE_0_NEW,
                                     sizeof(APP1_PARAMETER_STRING_VALUE_0_NEW));
    sync_with_other_apps();
    test_ParameterSetValueAsBlob_pos(&remoteHandle, DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_BLOB_NAME_0, APP1_PARAMETER_BLOB_VALUE_0_NEW,
                                   sizeof(APP1_PARAMETER_BLOB_VALUE_0_NEW));
    sync_with_other_apps();
    test_ParameterSetValueAsBlob_pos(&remoteHandle, DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_BLOB_NAME_3, APP1_PARAMETER_BLOB_VALUE_3_NEW,
                                   sizeof(APP1_PARAMETER_BLOB_VALUE_3_NEW));
    sync_with_other_apps();

    Debug_LOG_INFO("%s: All tests completed.", TEST_APP);

    return 0;
}
