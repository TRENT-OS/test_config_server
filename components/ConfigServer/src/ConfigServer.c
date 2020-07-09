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


/* Private types -------------------------------------------------------------*/
static OS_FileSystem_Config_t cfg =
{
    .type = OS_FileSystem_Type_LITTLEFS,
    .storage = OS_FILESYSTEM_ASSIGN_Storage(
        OS_FileSystem_STORAGE_MAX,
        storage_rpc_write,
        storage_rpc_read,
        storage_rpc_erase,
        storage_rpc_getSize,
        storage_rpc_getState,
        storage_dp),
};

static bool
initializeConfigBackend(void)
{
    OS_ConfigServiceInstanceStore_t* serverInstanceStore =
        OS_ConfigService_getInstances();
    OS_ConfigServiceLib_t* configLib =
        OS_ConfigServiceInstanceStore_getInstance(serverInstanceStore, 0);

    // Wait until Tester1 is done with its local tests
    app1_local_test_done_wait();

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

    return true;
}


void pre_init(void)
{
    Debug_LOG_INFO("Starting ConfigServer...");
    //Wait for ConfigFileInjector component to create the config file
    Debug_LOG_INFO("ConfigServer waiting for ConfigFileInjector to create file...");
    injector_component_backend_injected();

    if (!initializeConfigBackend())
    {
        Debug_LOG_ERROR("initializeConfigBackend failed!");
    }

    Debug_LOG_INFO("Config Server initialized.");
}
