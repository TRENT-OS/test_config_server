/**
 * Copyright (C) 2019, Hensoldt Cyber GmbH
 */
#if defined(OS_CONFIG_SERVICE_BACKEND_FILESYSTEM)
#include <string.h>
#include <stdio.h>

#include "LibDebug/Debug.h"

#include "init_lib_with_fs_backend.h"

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

seos_err_t initializeWithFileBackends(OS_ConfigServiceLib_t* configLib,
                                      hPartition_t phandle)
{
    seos_err_t result = 0;

    OS_ConfigServiceBackend_t parameterBackend;
    OS_ConfigServiceBackend_t domainBackend;
    OS_ConfigServiceBackend_t stringBackend;
    OS_ConfigServiceBackend_t blobBackend;
    OS_ConfigServiceBackend_FileName_t name;

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
