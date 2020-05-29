/*
   *  ConfigFileInjector component used to create a config file for the ConfigServer
   *  tests.
   *
   *  Copyright (C) 2020, Hensoldt Cyber GmbH
*/


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <camkes.h>

#include "LibDebug/Debug.h"

#include "OS_ConfigService.h"

#if defined(OS_CONFIG_SERVICE_BACKEND_FILESYSTEM)
#include "create_fs_backend.h"
#include "create_parameters.h"

/* Defines -------------------------------------------------------------------*/
#define PARTITION_ID            0


/* Private types -------------------------------------------------------------*/
hPartition_t phandle;
OS_PartitionManagerDataTypes_DiskData_t pm_disk_data;
OS_PartitionManagerDataTypes_PartitionData_t pm_partition_data;
#endif

void injector_component_backend_injected()
{
    Debug_LOG_DEBUG("injector_component_backend_injected call received");
}

#if defined(OS_CONFIG_SERVICE_BACKEND_FILESYSTEM)
static bool
TestCreateFSBackend(void)
{
    OS_Error_t pm_result = OS_PartitionManager_getInfoDisk(&pm_disk_data);
    if (pm_result != OS_SUCCESS)
    {
        Debug_LOG_ERROR("Fail to get disk info: %d", pm_result);
        return false;
    }

    pm_result = OS_PartitionManager_getInfoPartition(PARTITION_ID,
                                                     &pm_partition_data);
    if (pm_result != OS_SUCCESS)
    {
        Debug_LOG_ERROR("Fail to get partition info: %d!",
                        pm_partition_data.partition_id);
        return false;
    }

    OS_Error_t fs_result = OS_Filesystem_init(pm_partition_data.partition_id, 0);
    if (fs_result != OS_SUCCESS)
    {
        Debug_LOG_ERROR("Fail to init partition: %d!", fs_result);
        return false;
    }

    if ( (phandle = OS_Filesystem_open(pm_partition_data.partition_id)) < 0)
    {
        Debug_LOG_ERROR("Fail to open partition: %d!", pm_partition_data.partition_id);
        return false;
    }

    if (OS_Filesystem_create(
            phandle,
            FS_TYPE_FAT16,
            pm_partition_data.partition_size,
            0,  // default value: size of sector:   512
            0,  // default value: size of cluster:  512
            0,  // default value: reserved sectors count: FAT12/FAT16 = 1; FAT32 = 3
            0,  // default value: count file/dir entries: FAT12/FAT16 = 16; FAT32 = 0
            0,  // default value: count header sectors: 512
            FS_PARTITION_OVERWRITE_CREATE)
        != OS_SUCCESS)
    {
        Debug_LOG_ERROR("Fail to create filesystem on partition: %d!",
                        pm_partition_data.partition_id);
        return false;
    }

    if (OS_Filesystem_mount(phandle) != OS_SUCCESS)
    {
        return false;
    }

    OS_ConfigServiceInstanceStore_t* serverInstanceStore =
        OS_ConfigService_getInstances();
    OS_ConfigServiceLib_t* configLib =
        OS_ConfigServiceInstanceStore_getInstance(serverInstanceStore, 0);

    // Create the file backends
    OS_Error_t result = initializeWithFileBackends(configLib, phandle);
    if (result != OS_SUCCESS)
    {
        Debug_LOG_ERROR("initializeWithFileBackends failed with: %d", result);
        return false;
    }

    // Create the parameters in the instance.
    Debug_LOG_DEBUG("Enumerating %s", DOMAIN_APP1);
    result = initializeDomainsAndParameters(configLib, DOMAIN_APP1);
    if  (result != OS_SUCCESS)
    {
        Debug_LOG_ERROR("initializeDomainAndParameters for %s failed with: %d",
                        DOMAIN_APP1, result);
        return false;
    }

    Debug_LOG_DEBUG("Enumerating %s", DOMAIN_APP2);
    result = initializeDomainsAndParameters(configLib, DOMAIN_APP2);
    if  (result != OS_SUCCESS)
    {
        Debug_LOG_ERROR("initializeDomainAndParameters for %s failed with: %d",
                        DOMAIN_APP2,    result);
        return false;
    }

    Debug_LOG_DEBUG("Enumerating %s", DOMAIN_APP3);
    result = initializeDomainsAndParameters(configLib, DOMAIN_APP3);
    if  (result != OS_SUCCESS)
    {
        Debug_LOG_ERROR("initializeDomainAndParameters for %s failed with: %d",
                        DOMAIN_APP3,    result);
        return false;
    }

    Debug_LOG_DEBUG("Enumerating %s", DOMAIN_APP4);
    result = initializeDomainsAndParameters(configLib, DOMAIN_APP4);
    if  (result != OS_SUCCESS)
    {
        Debug_LOG_ERROR("initializeDomainAndParameters for %s failed with: %d",
                        DOMAIN_APP4,    result);
        return false;
    }

    if (OS_Filesystem_close(phandle) != OS_SUCCESS)
    {
        Debug_LOG_ERROR("Fail to close partition: %d!",
                        pm_partition_data.partition_id);
        return false;
    }

    Debug_LOG_INFO("->%s: OK\n", __func__);

    return true;
}
#endif

void pre_init(void)
{
    Debug_LOG_INFO("Starting ConfigFileInjector...");
#if defined(OS_CONFIG_SERVICE_BACKEND_FILESYSTEM)
    // Create the fs backend
    if (!TestCreateFSBackend())
    {
        Debug_LOG_ERROR("Failed to create filesystem backend!");
    }
    Debug_LOG_INFO("FS Backend injected.");
#endif

}
