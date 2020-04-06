/*
   *  TestRunner component that utilizes the ConfigServer as a library but is
   *  additionally connected to a ConfigServer component to run all tests remote
   *  and local.
   *
   *  Copyright (C) 2020, Hensoldt Cyber GmbH
*/


#include "system_config.h"

#include "SeosError.h"
#include "OS_ConfigService.h"

#include "create_parameters.h"

#include "init_lib_with_fs_backend.h"
#include "init_lib_with_mem_backend.h"

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
#define PARTITION_ID            0

#define TEST_APP     TEST_APP1
#define DOMAIN_APP   DOMAIN_APP1

#if defined(OS_CONFIG_SERVICE_BACKEND_FILESYSTEM)
/* Private types -------------------------------------------------------------*/
hPartition_t phandle;
pm_disk_data_t pm_disk_data;
pm_partition_data_t pm_partition_data;
#endif

//------------------------------------------------------------------------------
static void
sync_with_other_apps(void)
{
    test_done_emit();
    app4_test_done_wait();
}


static bool
initializeConfigBackend(void)
{
    seos_err_t ret;

    OS_ConfigServiceInstanceStore_t* clientInstanceStore =
        OS_ConfigService_getInstances();
    OS_ConfigServiceLib_t* configLib =
        OS_ConfigServiceInstanceStore_getInstance(clientInstanceStore, 0);

#if defined(OS_CONFIG_SERVICE_BACKEND_FILESYSTEM)

    seos_err_t pm_result = partition_manager_get_info_disk(&pm_disk_data);
    if (pm_result != SEOS_SUCCESS)
    {
        Debug_LOG_ERROR("Fail to get disk info: %d", pm_result);
        return false;
    }

    pm_result = partition_manager_get_info_partition(PARTITION_ID,
                                                     &pm_partition_data);
    if (pm_result != SEOS_SUCCESS)
    {
        Debug_LOG_ERROR("Fail to get partition info: %d!",
                        pm_partition_data.partition_id);
        return false;
    }

    seos_err_t fs_result = OS_Filesystem_init(pm_partition_data.partition_id, 0);
    if (fs_result != SEOS_SUCCESS)
    {
        Debug_LOG_ERROR("Fail to init partition: %d!", fs_result);
        return false;
    }

    if ( (phandle = OS_Filesystem_open(pm_partition_data.partition_id)) < 0)
    {
        Debug_LOG_ERROR("Fail to open partition: %d!", pm_partition_data.partition_id);
        return false;
    }

    if (OS_Filesystem_mount(phandle) != SEOS_SUCCESS)
    {
        return false;
    }

    // Create the file backends
    Debug_LOG_INFO("Initializing with file backend");
    ret = initializeWithFileBackends(configLib, phandle);
    if (ret != SEOS_SUCCESS)
    {
        Debug_LOG_ERROR("initializeWithFileBackends failed with: %d", ret);
        return ret;
    }
#endif

#if defined(OS_CONFIG_SERVICE_BACKEND_MEMORY)
    // Create the backends in the instance.
    Debug_LOG_INFO("%s: Initializing with mem backend", TEST_APP);
    ret = initializeWithMemoryBackends(configLib);
    if (ret != SEOS_SUCCESS)
    {
        Debug_LOG_ERROR("initializeWithMemoryBackends failed with: %d", ret);
        return false;
    }

    // Create the parameters in the instance.
    Debug_LOG_DEBUG("Enumerating %s", DOMAIN_APP1);
    ret = initializeDomainsAndParameters(configLib, DOMAIN_APP);
    if (ret != SEOS_SUCCESS)
    {
        Debug_LOG_ERROR("initializeDomainAndParameters for %s failed with: %d",
                        DOMAIN_APP, ret);
        return false;
    }

    Debug_LOG_DEBUG("Enumerating %s", DOMAIN_APP2);
    ret = initializeDomainsAndParameters(configLib, DOMAIN_APP2);
    if (ret != SEOS_SUCCESS)
    {
        Debug_LOG_ERROR("initializeDomainAndParameters for %s failed with: %d",
                        DOMAIN_APP2, ret);
        return false;
    }

    Debug_LOG_DEBUG("Enumerating %s", DOMAIN_APP3);
    ret = initializeDomainsAndParameters(configLib, DOMAIN_APP3);
    if (ret != SEOS_SUCCESS)
    {
        Debug_LOG_ERROR("initializeDomainAndParameters for %s failed with: %d",
                        DOMAIN_APP3, ret);
        return false;
    }

    Debug_LOG_DEBUG("Enumerating %s", DOMAIN_APP4);
    ret = initializeDomainsAndParameters(configLib, DOMAIN_APP4);
    if (ret != SEOS_SUCCESS)
    {
        Debug_LOG_ERROR("initializeDomainAndParameters for %s failed with: %d",
                        DOMAIN_APP4, ret);
        return false;
    }
#endif
    return true;
}

//------------------------------------------------------------------------------
int
run(void)
{
    OS_ConfigServiceHandle_t localHandle;
    OS_ConfigServiceHandle_t remoteHandle;
    OS_ConfigServiceLib_t* instance;

#if defined(OS_CONFIG_SERVICE_BACKEND_FILESYSTEM)
    //Wait until the remote backend is injected
    injector_component_backend_injected();
#endif

    //Create the fs backend
    if (!initializeConfigBackend())
    {
        Debug_LOG_ERROR("initializeConfigBackend failed!");
    }

    Debug_LOG_INFO("Starting tests of ConfigServer...");
    //Start with simple handle tests
    TestCreateHandle_ok(&localHandle, OS_CONFIG_HANDLE_KIND_LOCAL, TEST_APP);
    TestCreateHandle_ok(&remoteHandle, OS_CONFIG_HANDLE_KIND_RPC, TEST_APP);
    TestCreateHandle_fail(&localHandle, OS_CONFIG_HANDLE_KIND_LOCAL, TEST_APP);
    TestCreateHandle_fail(&remoteHandle, OS_CONFIG_HANDLE_KIND_RPC, TEST_APP);

    //Test enumerator increment and reset functions
    instance  = (OS_ConfigServiceLib_t*) OS_ConfigServiceHandle_getRemoteInstance(
                    localHandle);
    TestDomainEnumerator_increment_ok(&localHandle, TEST_APP,
                                      instance->domainBackend.numberOfRecords);
    TestDomainEnumerator_increment_ok(&remoteHandle, TEST_APP,
                                      instance->domainBackend.numberOfRecords);

    TestDomainEnumerator_reset_ok(&localHandle, TEST_APP,
                                  instance->domainBackend.numberOfRecords);
    TestDomainEnumerator_reset_ok(&remoteHandle, TEST_APP,
                                  instance->domainBackend.numberOfRecords);

    TestParameterEnumerator_increment_ok(&localHandle,
                                         TEST_APP,
                                         instance->domainBackend.numberOfRecords,
                                         instance->parameterBackend.numberOfRecords);
    TestParameterEnumerator_increment_ok(&remoteHandle,
                                         TEST_APP,
                                         instance->domainBackend.numberOfRecords,
                                         instance->parameterBackend.numberOfRecords);

    TestParameterEnumerator_reset_ok(&localHandle,
                                     TEST_APP,
                                     instance->domainBackend.numberOfRecords,
                                     instance->parameterBackend.numberOfRecords);
    TestParameterEnumerator_reset_ok(&remoteHandle,
                                     TEST_APP,
                                     instance->domainBackend.numberOfRecords,
                                     instance->parameterBackend.numberOfRecords);

    //Test get parameter functions
    TestGetInteger32FromFsBackend_ok(&localHandle,  DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_32_NAME_0, APP1_PARAMETER_32_VALUE_0);
    TestGetInteger32FromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_32_NAME_0, APP1_PARAMETER_32_VALUE_0);

    TestGetInteger32FromFsBackend_ok(&localHandle,  DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_32_NAME_1, APP1_PARAMETER_32_VALUE_1);
    TestGetInteger32FromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_32_NAME_1, APP1_PARAMETER_32_VALUE_1);

    TestGetInteger32FromFsBackend_ok(&localHandle,  DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_32_NAME_2, APP1_PARAMETER_32_VALUE_2);
    TestGetInteger32FromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_32_NAME_2, APP1_PARAMETER_32_VALUE_2);

    TestGetInteger32FromFsBackend_ok(&localHandle,  DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_32_NAME_3, APP1_PARAMETER_32_VALUE_3);
    TestGetInteger32FromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_32_NAME_3, APP1_PARAMETER_32_VALUE_3);


    TestGetInteger64FromFsBackend_ok(&localHandle,  DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_64_NAME_0, APP1_PARAMETER_64_VALUE_0);
    TestGetInteger64FromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_64_NAME_0, APP1_PARAMETER_64_VALUE_0);

    TestGetInteger64FromFsBackend_ok(&localHandle,  DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_64_NAME_1, APP1_PARAMETER_64_VALUE_1);
    TestGetInteger64FromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_64_NAME_1, APP1_PARAMETER_64_VALUE_1);

    TestGetInteger64FromFsBackend_ok(&localHandle,  DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_64_NAME_2, APP1_PARAMETER_64_VALUE_2);
    TestGetInteger64FromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_64_NAME_2, APP1_PARAMETER_64_VALUE_2);

    TestGetInteger64FromFsBackend_ok(&localHandle,  DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_64_NAME_3, APP1_PARAMETER_64_VALUE_3);
    TestGetInteger64FromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_64_NAME_3, APP1_PARAMETER_64_VALUE_3);


    TestGetStringsFromFsBackend_ok(&localHandle,  DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_STRING_NAME_0, APP1_PARAMETER_STRING_VALUE_0,
                                   sizeof(APP1_PARAMETER_STRING_VALUE_0));
    TestGetStringsFromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_STRING_NAME_0, APP1_PARAMETER_STRING_VALUE_0,
                                   sizeof(APP1_PARAMETER_STRING_VALUE_0));

    TestGetStringsFromFsBackend_ok(&localHandle,  DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_STRING_NAME_1, APP1_PARAMETER_STRING_VALUE_1,
                                   sizeof(APP1_PARAMETER_STRING_VALUE_1));
    TestGetStringsFromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_STRING_NAME_1, APP1_PARAMETER_STRING_VALUE_1,
                                   sizeof(APP1_PARAMETER_STRING_VALUE_1));

    TestGetStringsFromFsBackend_ok(&localHandle,  DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_STRING_NAME_2, APP1_PARAMETER_STRING_VALUE_2,
                                   sizeof(APP1_PARAMETER_STRING_VALUE_2));
    TestGetStringsFromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_STRING_NAME_2, APP1_PARAMETER_STRING_VALUE_2,
                                   sizeof(APP1_PARAMETER_STRING_VALUE_2));

    TestGetStringsFromFsBackend_ok(&localHandle,  DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_STRING_NAME_3, APP1_PARAMETER_STRING_VALUE_3,
                                   sizeof(APP1_PARAMETER_STRING_VALUE_3));
    TestGetStringsFromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_STRING_NAME_3, APP1_PARAMETER_STRING_VALUE_3,
                                   sizeof(APP1_PARAMETER_STRING_VALUE_3));


    TestGetBlobsFromFsBackend_ok(&localHandle,  DOMAIN_APP, TEST_APP,
                                 APP1_PARAMETER_BLOB_NAME_0, APP1_PARAMETER_BLOB_VALUE_0,
                                 sizeof(APP1_PARAMETER_BLOB_VALUE_0));
    TestGetBlobsFromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                 APP1_PARAMETER_BLOB_NAME_0, APP1_PARAMETER_BLOB_VALUE_0,
                                 sizeof(APP1_PARAMETER_BLOB_VALUE_0));

    TestGetBlobsFromFsBackend_ok(&localHandle,  DOMAIN_APP, TEST_APP,
                                 APP1_PARAMETER_BLOB_NAME_1, APP1_PARAMETER_BLOB_VALUE_1,
                                 sizeof(APP1_PARAMETER_BLOB_VALUE_1));
    TestGetBlobsFromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                 APP1_PARAMETER_BLOB_NAME_1, APP1_PARAMETER_BLOB_VALUE_1,
                                 sizeof(APP1_PARAMETER_BLOB_VALUE_1));

    TestGetBlobsFromFsBackend_ok(&localHandle,  DOMAIN_APP, TEST_APP,
                                 APP1_PARAMETER_BLOB_NAME_2, APP1_PARAMETER_BLOB_VALUE_2,
                                 sizeof(APP1_PARAMETER_BLOB_VALUE_2));
    TestGetBlobsFromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                 APP1_PARAMETER_BLOB_NAME_2, APP1_PARAMETER_BLOB_VALUE_2,
                                 sizeof(APP1_PARAMETER_BLOB_VALUE_2));

    TestGetBlobsFromFsBackend_ok(&localHandle,  DOMAIN_APP, TEST_APP,
                                 APP1_PARAMETER_BLOB_NAME_3, APP1_PARAMETER_BLOB_VALUE_3,
                                 sizeof(APP1_PARAMETER_BLOB_VALUE_3));
    TestGetBlobsFromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                 APP1_PARAMETER_BLOB_NAME_3, APP1_PARAMETER_BLOB_VALUE_3,
                                 sizeof(APP1_PARAMETER_BLOB_VALUE_3));

    //Test fetching a parameter that has no read access rights
    TestParameterReadAccessRight_ok(&localHandle, DOMAIN_APP2, TEST_APP,
                                    APP2_PARAMETER_BLOB_NAME_2, APP2_PARAMETER_BLOB_VALUE_2,
                                    sizeof(APP2_PARAMETER_BLOB_VALUE_2));
    TestParameterReadAccessRight_ok(&remoteHandle, DOMAIN_APP2, TEST_APP,
                                    APP2_PARAMETER_BLOB_NAME_2, APP2_PARAMETER_BLOB_VALUE_2,
                                    sizeof(APP2_PARAMETER_BLOB_VALUE_2));


    //Test set parameter functions
    TestParameterSetValueAsU32_ok(&localHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_32_NAME_0, APP1_PARAMETER_32_VALUE_0_NEW);
    TestParameterSetValueAsU32_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_32_NAME_0, APP1_PARAMETER_32_VALUE_0_NEW);

    TestParameterSetValueAsU32_ok(&localHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_32_NAME_1, APP1_PARAMETER_32_VALUE_1_NEW);
    TestParameterSetValueAsU32_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_32_NAME_1, APP1_PARAMETER_32_VALUE_1_NEW);

    TestParameterSetValueAsU32_ok(&localHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_32_NAME_2, APP1_PARAMETER_32_VALUE_2_NEW);
    TestParameterSetValueAsU32_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_32_NAME_2, APP1_PARAMETER_32_VALUE_2_NEW);

    TestParameterSetValueAsU32_ok(&localHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_32_NAME_3, APP1_PARAMETER_32_VALUE_3_NEW);
    TestParameterSetValueAsU32_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_32_NAME_3, APP1_PARAMETER_32_VALUE_3_NEW);


    TestParameterSetValueAsU64_ok(&localHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_64_NAME_0, APP1_PARAMETER_64_VALUE_0_NEW);
    TestParameterSetValueAsU64_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_64_NAME_0, APP1_PARAMETER_64_VALUE_0_NEW);

    TestParameterSetValueAsU64_ok(&localHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_64_NAME_1, APP1_PARAMETER_64_VALUE_1_NEW);
    TestParameterSetValueAsU64_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_64_NAME_1, APP1_PARAMETER_64_VALUE_1_NEW);

    TestParameterSetValueAsU64_ok(&localHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_64_NAME_2, APP1_PARAMETER_64_VALUE_2_NEW);
    TestParameterSetValueAsU64_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_64_NAME_2, APP1_PARAMETER_64_VALUE_2_NEW);

    TestParameterSetValueAsU64_ok(&localHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_64_NAME_3, APP1_PARAMETER_64_VALUE_3_NEW);
    TestParameterSetValueAsU64_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_64_NAME_3, APP1_PARAMETER_64_VALUE_3_NEW);


    TestParameterSetValueAsString_ok(&localHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_STRING_NAME_0, APP1_PARAMETER_STRING_VALUE_0_NEW,
                                     sizeof(APP1_PARAMETER_STRING_VALUE_0_NEW));
    TestParameterSetValueAsString_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_STRING_NAME_0, APP1_PARAMETER_STRING_VALUE_0_NEW,
                                     sizeof(APP1_PARAMETER_STRING_VALUE_0_NEW));

    TestParameterSetValueAsString_ok(&localHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_STRING_NAME_1, APP1_PARAMETER_STRING_VALUE_1_NEW,
                                     sizeof(APP1_PARAMETER_STRING_VALUE_1_NEW));
    TestParameterSetValueAsString_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_STRING_NAME_1, APP1_PARAMETER_STRING_VALUE_1_NEW,
                                     sizeof(APP1_PARAMETER_STRING_VALUE_1_NEW));

    TestParameterSetValueAsString_ok(&localHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_STRING_NAME_2, APP1_PARAMETER_STRING_VALUE_2_NEW,
                                     sizeof(APP1_PARAMETER_STRING_VALUE_2_NEW));
    TestParameterSetValueAsString_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_STRING_NAME_2, APP1_PARAMETER_STRING_VALUE_2_NEW,
                                     sizeof(APP1_PARAMETER_STRING_VALUE_2_NEW));

    TestParameterSetValueAsString_ok(&localHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_STRING_NAME_3, APP1_PARAMETER_STRING_VALUE_3_NEW,
                                     sizeof(APP1_PARAMETER_STRING_VALUE_3_NEW));
    TestParameterSetValueAsString_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_STRING_NAME_3, APP1_PARAMETER_STRING_VALUE_3_NEW,
                                     sizeof(APP1_PARAMETER_STRING_VALUE_3_NEW));


    TestParameterSetValueAsBlob_ok(&localHandle, DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_BLOB_NAME_0, APP1_PARAMETER_BLOB_VALUE_0_NEW,
                                   sizeof(APP1_PARAMETER_BLOB_VALUE_0_NEW));
    TestParameterSetValueAsBlob_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_BLOB_NAME_0, APP1_PARAMETER_BLOB_VALUE_0_NEW,
                                   sizeof(APP1_PARAMETER_BLOB_VALUE_0_NEW));

    TestParameterSetValueAsBlob_ok(&localHandle, DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_BLOB_NAME_1, APP1_PARAMETER_BLOB_VALUE_1_NEW,
                                   sizeof(APP1_PARAMETER_BLOB_VALUE_1_NEW));
    TestParameterSetValueAsBlob_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_BLOB_NAME_1, APP1_PARAMETER_BLOB_VALUE_1_NEW,
                                   sizeof(APP1_PARAMETER_BLOB_VALUE_1_NEW));

    TestParameterSetValueAsBlob_ok(&localHandle, DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_BLOB_NAME_2, APP1_PARAMETER_BLOB_VALUE_2_NEW,
                                   sizeof(APP1_PARAMETER_BLOB_VALUE_2_NEW));
    TestParameterSetValueAsBlob_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_BLOB_NAME_2, APP1_PARAMETER_BLOB_VALUE_2_NEW,
                                   sizeof(APP1_PARAMETER_BLOB_VALUE_2_NEW));

    TestParameterSetValueAsBlob_ok(&localHandle, DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_BLOB_NAME_3, APP1_PARAMETER_BLOB_VALUE_3_NEW,
                                   sizeof(APP1_PARAMETER_BLOB_VALUE_3_NEW));
    TestParameterSetValueAsBlob_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_BLOB_NAME_3, APP1_PARAMETER_BLOB_VALUE_3_NEW,
                                   sizeof(APP1_PARAMETER_BLOB_VALUE_3_NEW));

    //Test setting a parameter that has no write access rights
    TestParameterWriteAccessRight_ok(&localHandle, DOMAIN_APP2, TEST_APP,
                                     APP2_PARAMETER_BLOB_NAME_1, APP2_PARAMETER_BLOB_VALUE_1_NEW,
                                     sizeof(APP2_PARAMETER_BLOB_VALUE_1_NEW));
    TestParameterWriteAccessRight_ok(&remoteHandle, DOMAIN_APP2, TEST_APP,
                                     APP2_PARAMETER_BLOB_NAME_1, APP2_PARAMETER_BLOB_VALUE_1_NEW,
                                     sizeof(APP2_PARAMETER_BLOB_VALUE_1_NEW));

    uint32_t interger32Value = APP1_PARAMETER_32_VALUE_0;
    uint64_t integer64Value = APP1_PARAMETER_64_VALUE_0;
    TestParameterSetValue_ok(&localHandle, DOMAIN_APP, TEST_APP,
                             APP1_PARAMETER_32_NAME_0, &interger32Value, sizeof(interger32Value));
    TestParameterSetValue_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                             APP1_PARAMETER_32_NAME_0, &interger32Value, sizeof(interger32Value));

    TestParameterSetValue_ok(&localHandle, DOMAIN_APP, TEST_APP,
                             APP1_PARAMETER_64_NAME_0, &integer64Value, sizeof(integer64Value));
    TestParameterSetValue_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                             APP1_PARAMETER_64_NAME_0, &integer64Value, sizeof(integer64Value));

    TestParameterSetValue_ok(&localHandle, DOMAIN_APP, TEST_APP,
                             APP1_PARAMETER_STRING_NAME_0, APP1_PARAMETER_STRING_VALUE_0,
                             sizeof(APP1_PARAMETER_STRING_VALUE_0));
    TestParameterSetValue_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                             APP1_PARAMETER_STRING_NAME_0, APP1_PARAMETER_STRING_VALUE_0,
                             sizeof(APP1_PARAMETER_STRING_VALUE_0));

    TestParameterSetValue_ok(&localHandle, DOMAIN_APP, TEST_APP,
                             APP1_PARAMETER_BLOB_NAME_0, APP1_PARAMETER_BLOB_VALUE_0,
                             sizeof(APP1_PARAMETER_BLOB_VALUE_0));
    TestParameterSetValue_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                             APP1_PARAMETER_BLOB_NAME_0, APP1_PARAMETER_BLOB_VALUE_0,
                             sizeof(APP1_PARAMETER_BLOB_VALUE_0));

    Debug_LOG_DEBUG("%s: Basic functionality tests completed. Unblocking other clients...",
                    TEST_APP);

    Debug_LOG_DEBUG("%s: Starting multiclient test of ConfigServer...", TEST_APP);
    //Test get parameter functions in multiclient environment
    TestGetInteger32FromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_32_NAME_0, APP1_PARAMETER_32_VALUE_0);
    sync_with_other_apps();
    TestGetInteger64FromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_64_NAME_0, APP1_PARAMETER_64_VALUE_0);
    sync_with_other_apps();
    TestGetStringsFromFsBackend_ok(&remoteHandle,  DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_STRING_NAME_0, APP1_PARAMETER_STRING_VALUE_0,
                                   sizeof(APP1_PARAMETER_STRING_VALUE_0));
    sync_with_other_apps();
    TestGetBlobsFromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                 APP1_PARAMETER_BLOB_NAME_0, APP1_PARAMETER_BLOB_VALUE_0,
                                 sizeof(APP1_PARAMETER_BLOB_VALUE_0));
    sync_with_other_apps();
    TestGetBlobsFromFsBackend_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                 APP1_PARAMETER_BLOB_NAME_3, APP1_PARAMETER_BLOB_VALUE_3_NEW,
                                 sizeof(APP1_PARAMETER_BLOB_VALUE_3_NEW));
    sync_with_other_apps();

    //Test set parameter functions in multiclient environment
    TestParameterSetValueAsU32_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_32_NAME_0, APP1_PARAMETER_32_VALUE_0_NEW);
    sync_with_other_apps();
    TestParameterSetValueAsU64_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                  APP1_PARAMETER_64_NAME_0, APP1_PARAMETER_64_VALUE_0_NEW);
    sync_with_other_apps();
    TestParameterSetValueAsString_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                     APP1_PARAMETER_STRING_NAME_0, APP1_PARAMETER_STRING_VALUE_0_NEW,
                                     sizeof(APP1_PARAMETER_STRING_VALUE_0_NEW));
    sync_with_other_apps();
    TestParameterSetValueAsBlob_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_BLOB_NAME_0, APP1_PARAMETER_BLOB_VALUE_0_NEW,
                                   sizeof(APP1_PARAMETER_BLOB_VALUE_0_NEW));
    sync_with_other_apps();
    TestParameterSetValueAsBlob_ok(&remoteHandle, DOMAIN_APP, TEST_APP,
                                   APP1_PARAMETER_BLOB_NAME_3, APP1_PARAMETER_BLOB_VALUE_3_NEW,
                                   sizeof(APP1_PARAMETER_BLOB_VALUE_3_NEW));
    sync_with_other_apps();

    Debug_LOG_INFO("%s: All tests completed.", TEST_APP);

    return 0;
}
