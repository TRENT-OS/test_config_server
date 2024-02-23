/*
 * Copyright (C) 2019-2024, HENSOLDT Cyber GmbH
 * 
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * For commercial licensing, contact: info.cyber@hensoldt.net
 */

#include <string.h>
#include <stdio.h>

#include "lib_debug/Debug.h"

#include "create_fs_backend.h"

#define PARAMETER_FILE "PARAM.BIN"
#define DOMAIN_FILE "DOMAIN.BIN"
#define STRING_FILE "STRING.BIN"
#define BLOB_FILE "BLOB.BIN"


static
void initializeName(char* buf, size_t bufSize, char const* name)
{
    memset(buf, 0, bufSize);
    strncpy(buf, name, bufSize - 1);
}

static
OS_Error_t createFileBackends(OS_FileSystem_Handle_t hFs)
{
    OS_Error_t result = 0;
    OS_ConfigServiceBackend_FileName_t name;

    // Create the file backends.
    Debug_LOG_DEBUG("Size of ConfigLib_Domain: %zu",
                    sizeof(OS_ConfigServiceLibTypes_Domain_t));
    initializeName(name.buffer, OS_CONFIG_BACKEND_MAX_FILE_NAME_SIZE, DOMAIN_FILE);
    Debug_LOG_DEBUG("Name.buffer: %s", name.buffer);
    result = OS_ConfigServiceBackend_createFileBackend(
                 name,
                 hFs,
                 4,
                 sizeof(OS_ConfigServiceLibTypes_Domain_t));
    if (result != OS_SUCCESS)
    {
        return result;
    }

    Debug_LOG_DEBUG("Size of ConfigLib_Parameter: %zu",
                    sizeof(OS_ConfigServiceLibTypes_Parameter_t));
    initializeName(name.buffer, OS_CONFIG_BACKEND_MAX_FILE_NAME_SIZE,
                   PARAMETER_FILE);
    Debug_LOG_DEBUG("Name.buffer: %s", name.buffer);
    result = OS_ConfigServiceBackend_createFileBackend(
                 name,
                 hFs,
                 64,
                 sizeof(OS_ConfigServiceLibTypes_Parameter_t));
    if (result != OS_SUCCESS)
    {
        return result;
    }

    initializeName(name.buffer, OS_CONFIG_BACKEND_MAX_FILE_NAME_SIZE, STRING_FILE);
    Debug_LOG_DEBUG("Name.buffer: %s", name.buffer);
    result = OS_ConfigServiceBackend_createFileBackend(
                 name,
                 hFs,
                 16,
                 OS_CONFIG_LIB_PARAMETER_MAX_STRING_SIZE);
    if (result != OS_SUCCESS)
    {
        return result;
    }

    initializeName(name.buffer, OS_CONFIG_BACKEND_MAX_FILE_NAME_SIZE, BLOB_FILE);
    Debug_LOG_DEBUG("Name.buffer: %s", name.buffer);
    result = OS_ConfigServiceBackend_createFileBackend(
                 name,
                 hFs,
                 144,
                 OS_CONFIG_LIB_PARAMETER_MAX_BLOB_BLOCK_SIZE);
    if (result != OS_SUCCESS)
    {
        return result;
    }

    return OS_SUCCESS;
}

OS_Error_t
initializeWithFileBackends(
    OS_ConfigServiceLib_t* configLib,
    OS_FileSystem_Handle_t hFs)
{
    OS_Error_t result = 0;

    OS_ConfigServiceBackend_t parameterBackend;
    OS_ConfigServiceBackend_t domainBackend;
    OS_ConfigServiceBackend_t stringBackend;
    OS_ConfigServiceBackend_t blobBackend;
    OS_ConfigServiceBackend_FileName_t name;
    // Create the memory backends.
    result = createFileBackends(hFs);
    if (result != OS_SUCCESS)
    {
        return result;
    }

    Debug_LOG_DEBUG("file backends created.");

    // Initialize the backends in the config library object.
    initializeName(name.buffer, OS_CONFIG_BACKEND_MAX_FILE_NAME_SIZE, DOMAIN_FILE);
    result = OS_ConfigServiceBackend_initializeFileBackend(
                 &domainBackend,
                 name,
                 hFs);
    Debug_LOG_DEBUG("Domain name: %s", name.buffer);
    if (result != OS_SUCCESS)
    {
        return result;
    }

    initializeName(
        name.buffer,
        OS_CONFIG_BACKEND_MAX_FILE_NAME_SIZE,
        PARAMETER_FILE);
    result = OS_ConfigServiceBackend_initializeFileBackend(
                 &parameterBackend,
                 name,
                 hFs);
    if (result != OS_SUCCESS)
    {
        return result;
    }
    Debug_LOG_DEBUG("Parameter backend initialized.");

    initializeName(name.buffer, OS_CONFIG_BACKEND_MAX_FILE_NAME_SIZE, STRING_FILE);
    result = OS_ConfigServiceBackend_initializeFileBackend(
                 &stringBackend,
                 name,
                 hFs);
    if (result != OS_SUCCESS)
    {
        return result;
    }
    Debug_LOG_DEBUG("String backend initialized.");

    initializeName(name.buffer, OS_CONFIG_BACKEND_MAX_FILE_NAME_SIZE, BLOB_FILE);
    result = OS_ConfigServiceBackend_initializeFileBackend(&blobBackend, name, hFs);
    if (result != OS_SUCCESS)
    {
        return result;
    }
    Debug_LOG_DEBUG("Blob backend initialized.");

    result = OS_ConfigServiceLib_Init(
                 configLib,
                 &parameterBackend,
                 &domainBackend,
                 &stringBackend,
                 &blobBackend);
    if (result != OS_SUCCESS)
    {
        Debug_LOG_ERROR("OS_ConfigServiceLib_Init failed with: %d", result);
        return result;
    }
    return result;
}
