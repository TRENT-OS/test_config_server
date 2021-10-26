/*
   *  ConfigServer component that can be initialized either with a memory or a filesystem
   *  backend.
   *
   *  Copyright (C) 2019, HENSOLDT Cyber GmbH
*/


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <camkes.h>

#include "lib_debug/Debug.h"
#include "OS_Error.h"

#include "OS_ConfigService.h"

#include "create_parameters.h"

#include "init_lib_with_fs_backend.h"


/* Private variables ---------------------------------------------------------*/
static OS_FileSystem_Config_t cfg =
{
    .type = OS_FileSystem_Type_FATFS,
    .size = OS_FileSystem_USE_STORAGE_MAX,
    .storage = IF_OS_STORAGE_ASSIGN(
        storage_rpc,
        storage_port),
};

/* Private functions ---------------------------------------------------------*/
static bool
initializeConfigBackend(void)
{
    OS_ConfigServiceLib_t* configLib =
        OS_ConfigService_getInstance();

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
