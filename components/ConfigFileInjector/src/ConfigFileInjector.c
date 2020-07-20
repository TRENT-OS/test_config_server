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

#include "create_fs_backend.h"
#include "create_parameters.h"


void injector_component_backend_injected()
{
    Debug_LOG_DEBUG("injector_component_backend_injected call received");
}

static OS_FileSystem_Config_t cfg =
{
    .type = OS_FileSystem_Type_FATFS,
    .size = OS_FileSystem_STORAGE_MAX,
    .storage = OS_FILESYSTEM_ASSIGN_Storage(
        storage_rpc,
        storage_dp),
};

static bool
TestCreateFSBackend(void)
{
    OS_Error_t err;
    OS_FileSystem_Handle_t hFs;

    if (OS_FileSystem_init(&hFs, &cfg) != OS_SUCCESS)
    {
        Debug_LOG_ERROR("OS_FileSystem_init() failed.");
        return false;
    }

    if (OS_FileSystem_format(hFs) != OS_SUCCESS)
    {
        Debug_LOG_ERROR("OS_FileSystem_format() failed.");
        return false;
    }

    if (OS_FileSystem_mount(hFs) != OS_SUCCESS)
    {
        Debug_LOG_ERROR("OS_FileSystem_mount() failed.");
        return false;
    }

    OS_ConfigServiceInstanceStore_t* serverInstanceStore =
        OS_ConfigService_getInstances();
    OS_ConfigServiceLib_t* configLib =
        OS_ConfigServiceInstanceStore_getInstance(serverInstanceStore, 0);

    // Create the file backends
    Debug_LOG_INFO("Initializing with file backend");
    if (initializeWithFileBackends(configLib, hFs) != OS_SUCCESS)
    {
        Debug_LOG_ERROR("initializeWithFileBackends() failed.");
        return false;
    }

    // Create the parameters in the instance.
    Debug_LOG_DEBUG("Enumerating %s", DOMAIN_APP1);
    err = initializeDomainsAndParameters(configLib, DOMAIN_APP1);
    if  (err != OS_SUCCESS)
    {
        Debug_LOG_ERROR("initializeDomainAndParameters for %s failed with: %d",
                        DOMAIN_APP1, err);
        return false;
    }

    Debug_LOG_DEBUG("Enumerating %s", DOMAIN_APP2);
    err = initializeDomainsAndParameters(configLib, DOMAIN_APP2);
    if  (err != OS_SUCCESS)
    {
        Debug_LOG_ERROR("initializeDomainAndParameters for %s failed with: %d",
                        DOMAIN_APP2, err);
        return false;
    }

    Debug_LOG_DEBUG("Enumerating %s", DOMAIN_APP3);
    err = initializeDomainsAndParameters(configLib, DOMAIN_APP3);
    if  (err != OS_SUCCESS)
    {
        Debug_LOG_ERROR("initializeDomainAndParameters for %s failed with: %d",
                        DOMAIN_APP3, err);
        return false;
    }

    Debug_LOG_DEBUG("Enumerating %s", DOMAIN_APP4);
    err = initializeDomainsAndParameters(configLib, DOMAIN_APP4);
    if  (err != OS_SUCCESS)
    {
        Debug_LOG_ERROR("initializeDomainAndParameters for %s failed with: %d",
                        DOMAIN_APP4, err);
        return false;
    }

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

    Debug_LOG_INFO("->%s: OK\n", __func__);

    return true;
}

void pre_init(void)
{
    Debug_LOG_INFO("Starting ConfigFileInjector...");
    // Create the fs backend
    if (!TestCreateFSBackend())
    {
        Debug_LOG_ERROR("Failed to create filesystem backend!");
    }
    Debug_LOG_INFO("FS Backend injected.");
}
