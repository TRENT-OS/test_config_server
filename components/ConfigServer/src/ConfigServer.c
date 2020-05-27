/*
   *  ConfigServer component that can be initialized either with a memory or a filesystem
   *  backend.
   *
   *  Copyright (C) 2019, Hensoldt Cyber GmbH
*/


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <camkes.h>

#include "LibDebug/Debug.h"
#include "OS_Error.h"

#include "OS_ConfigService.h"

#include "create_parameters.h"

#include "init_lib_with_fs_backend.h"
#include "init_lib_with_mem_backend.h"


/* Defines -------------------------------------------------------------------*/
#define PARTITION_ID            0


/* Private types -------------------------------------------------------------*/
#if defined(OS_CONFIG_SERVICE_BACKEND_FILESYSTEM)
hPartition_t phandle;
pm_disk_data_t pm_disk_data;
pm_partition_data_t pm_partition_data;
#endif

static bool
initializeConfigBackend(void)
{
    OS_Error_t ret;

    OS_ConfigServiceInstanceStore_t* serverInstanceStore =
        OS_ConfigService_getInstances();
    OS_ConfigServiceLib_t* configLib =
        OS_ConfigServiceInstanceStore_getInstance(serverInstanceStore, 0);

#if defined(OS_CONFIG_SERVICE_BACKEND_FILESYSTEM)
    OS_Error_t pm_result = partition_manager_get_info_disk(&pm_disk_data);
    if (pm_result != OS_SUCCESS)
    {
        Debug_LOG_ERROR("Fail to get disk info: %d", pm_result);
        return false;
    }

    pm_result = partition_manager_get_info_partition(PARTITION_ID,
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

    if (OS_Filesystem_mount(phandle) != OS_SUCCESS)
    {
        return false;
    }

    // Create the file backends
    Debug_LOG_INFO("ConfigServer: Initializing with file backend...");
    ret = initializeWithFileBackends(configLib, phandle);
    if (ret != OS_SUCCESS)
    {
        Debug_LOG_ERROR("initializeWithFileBackends failed with: %d", ret);
        return false;
    }
#endif

#if defined(OS_CONFIG_SERVICE_BACKEND_MEMORY)
    // Create the backends in the instance.
    Debug_LOG_INFO("ConfigServer: Initializing with mem backend...");
    ret = initializeWithMemoryBackends(configLib);
    if (ret != OS_SUCCESS)
    {
        Debug_LOG_ERROR("initializeWithMemoryBackends failed with: %d", ret);
        return false;
    }

    // Create the parameters in the instance.
    Debug_LOG_DEBUG("Enumerating %s", DOMAIN_APP1);
    ret = initializeDomainsAndParameters(configLib, DOMAIN_APP1);
    if (ret != OS_SUCCESS)
    {
        Debug_LOG_ERROR("initializeDomainAndParameters for %s failed with: %d",
                        DOMAIN_APP1, ret);
        return false;
    }

    Debug_LOG_DEBUG("Enumerating %s", DOMAIN_APP2);
    ret = initializeDomainsAndParameters(configLib, DOMAIN_APP2);
    if (ret != OS_SUCCESS)
    {
        Debug_LOG_ERROR("initializeDomainAndParameters for %s failed with: %d",
                        DOMAIN_APP2, ret);
        return false;
    }

    Debug_LOG_DEBUG("Enumerating %s", DOMAIN_APP3);
    ret = initializeDomainsAndParameters(configLib, DOMAIN_APP3);
    if (ret != OS_SUCCESS)
    {
        Debug_LOG_ERROR("initializeDomainAndParameters for %s failed with: %d",
                        DOMAIN_APP3, ret);
        return false;
    }

    Debug_LOG_DEBUG("Enumerating %s", DOMAIN_APP4);
    ret = initializeDomainsAndParameters(configLib, DOMAIN_APP4);
    if (ret != OS_SUCCESS)
    {
        Debug_LOG_ERROR("initializeDomainAndParameters for %s failed with: %d",
                        DOMAIN_APP4, ret);
        return false;
    }
#endif
    return true;
}


void pre_init(void)
{
    Debug_LOG_INFO("Starting ConfigServer...");
#if defined(OS_CONFIG_SERVICE_BACKEND_FILESYSTEM)
    //Wait for ConfigFileInjector component to create the config file
    Debug_LOG_INFO("ConfigServer waiting for ConfigFileInjector to create file...");
    injector_component_backend_injected();

#endif

    if (!initializeConfigBackend())
    {
        Debug_LOG_ERROR("initializeConfigBackend failed!");
    }

    Debug_LOG_INFO("Config Server initialized.");
}
