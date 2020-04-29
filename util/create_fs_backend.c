/**
 * Copyright (C) 2019, Hensoldt Cyber GmbH
 */

#if defined(OS_CONFIG_SERVICE_BACKEND_FILESYSTEM)
#include <string.h>
#include <stdio.h>

#include "LibDebug/Debug.h"

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
seos_err_t createFileBackends(hPartition_t phandle)
{
    seos_err_t result = 0;
    OS_ConfigServiceBackend_FileName_t name;

    // Create the file backends.
    Debug_LOG_DEBUG("Size of ConfigLib_Domain: %zu", sizeof(OS_ConfigServiceLibTypes_Domain_t));
    initializeName(name.buffer, OS_CONFIG_BACKEND_MAX_FILE_NAME_LEN, DOMAIN_FILE);
    Debug_LOG_DEBUG("Name.buffer: %s", name.buffer);
    result = OS_ConfigServiceBackend_createFileBackend(name, phandle, 4,
                                                 sizeof(OS_ConfigServiceLibTypes_Domain_t));
    if (result != SEOS_SUCCESS)
    {
        return result;
    }

    Debug_LOG_DEBUG("Size of ConfigLib_Parameter: %zu", sizeof(OS_ConfigServiceLibTypes_Parameter_t));
    initializeName(name.buffer, OS_CONFIG_BACKEND_MAX_FILE_NAME_LEN,
                   PARAMETER_FILE);
    Debug_LOG_DEBUG("Name.buffer: %s", name.buffer);
    result = OS_ConfigServiceBackend_createFileBackend(name, phandle, 64,
                                                 sizeof(OS_ConfigServiceLibTypes_Parameter_t));
    if (result != SEOS_SUCCESS)
    {
        return result;
    }

    initializeName(name.buffer, OS_CONFIG_BACKEND_MAX_FILE_NAME_LEN, STRING_FILE);
    Debug_LOG_DEBUG("Name.buffer: %s", name.buffer);
    result = OS_ConfigServiceBackend_createFileBackend(name, phandle, 16,
                                                 OS_CONFIG_LIB_PARAMETER_MAX_STRING_LENGTH);
    if (result != SEOS_SUCCESS)
    {
        return result;
    }

    initializeName(name.buffer, OS_CONFIG_BACKEND_MAX_FILE_NAME_LEN, BLOB_FILE);
    Debug_LOG_DEBUG("Name.buffer: %s", name.buffer);
    result = OS_ConfigServiceBackend_createFileBackend(name, phandle, 144,
                                                 OS_CONFIG_LIB_PARAMETER_MAX_BLOB_BLOCK_LENGTH);
    if (result != SEOS_SUCCESS)
    {
        return result;
    }

    return SEOS_SUCCESS;
}

seos_err_t initializeWithFileBackends(OS_ConfigServiceLib_t* configLib,
                                      hPartition_t phandle)
{
    seos_err_t result = 0;

    OS_ConfigServiceBackend_t parameterBackend;
    OS_ConfigServiceBackend_t domainBackend;
    OS_ConfigServiceBackend_t stringBackend;
    OS_ConfigServiceBackend_t blobBackend;
    OS_ConfigServiceBackend_FileName_t name;
    // Create the memory backends.
    result = createFileBackends(phandle);
    if (result != SEOS_SUCCESS)
    {
        return result;
    }

    Debug_LOG_DEBUG("file backends created.");

    // Initialize the backends in the config library object.
    initializeName(name.buffer, OS_CONFIG_BACKEND_MAX_FILE_NAME_LEN, DOMAIN_FILE);
    result = OS_ConfigServiceBackend_initializeFileBackend(&domainBackend, name, phandle);
    Debug_LOG_DEBUG("Domain name: %s", name.buffer);
    if (result != SEOS_SUCCESS)
    {
        return result;
    }

    initializeName(name.buffer, OS_CONFIG_BACKEND_MAX_FILE_NAME_LEN,
                   PARAMETER_FILE);
    result = OS_ConfigServiceBackend_initializeFileBackend(&parameterBackend, name,
                                                     phandle);
    if (result != SEOS_SUCCESS)
    {
        return result;
    }
    Debug_LOG_DEBUG("Parameter backend initialized.");

    initializeName(name.buffer, OS_CONFIG_BACKEND_MAX_FILE_NAME_LEN, STRING_FILE);
    result = OS_ConfigServiceBackend_initializeFileBackend(&stringBackend, name, phandle);
    if (result != SEOS_SUCCESS)
    {
        return result;
    }
    Debug_LOG_DEBUG("String backend initialized.");

    initializeName(name.buffer, OS_CONFIG_BACKEND_MAX_FILE_NAME_LEN, BLOB_FILE);
    result = OS_ConfigServiceBackend_initializeFileBackend(&blobBackend, name, phandle);
    if (result != SEOS_SUCCESS)
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
    if (result != SEOS_SUCCESS)
    {
        Debug_LOG_ERROR("OS_ConfigServiceLib_Init failed with: %d", result);
        return result;
    }
    return result;
}
#endif
