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

#include "lib_debug/Debug.h"

#include "lib_macros/Test.h"

#include "OS_ConfigService.h"

#include "create_fs_backend.h"
#include "create_parameters.h"


void injector_component_backend_injected()
{
    Debug_LOG_DEBUG("injector_component_backend_injected call received");
}

/* Private variables ---------------------------------------------------------*/
static OS_FileSystem_Config_t cfg =
{
    .type = OS_FileSystem_Type_FATFS,
    .size = OS_FileSystem_USE_STORAGE_MAX,
    .storage = IF_OS_STORAGE_ASSIGN(
        storage_rpc,
        storage_dp),
};

/* Private functions ---------------------------------------------------------*/
static bool
test_CreateFSBackend_pos(void)
{
    TEST_START();

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

    OS_ConfigServiceLib_t* configLib =
        OS_ConfigService_getInstance();

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

    TEST_FINISH();

    return true;
}

void pre_init(void)
{
    Debug_LOG_INFO("Starting ConfigFileInjector...");
    // Create the fs backend
    if (!test_CreateFSBackend_pos())
    {
        Debug_LOG_ERROR("Failed to create filesystem backend!");
    }
    Debug_LOG_INFO("FS Backend injected.");
}
