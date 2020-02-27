/**
 * Copyright (C) 2019, Hensoldt Cyber GmbH
 */
#if defined(CONFIG_SERVER_BACKEND_FILESYSTEM)
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

seos_err_t initializeWithFileBackends(SeosConfigLib* configLib,
                                      hPartition_t phandle)
{
    seos_err_t result = 0;

    SeosConfigBackend parameterBackend;
    SeosConfigBackend domainBackend;
    SeosConfigBackend stringBackend;
    SeosConfigBackend blobBackend;
    SeosConfigBackend_FileName name;

    // Initialize the backends in the config library object.
    initializeName(name.buffer, SEOS_CONFIG_BACKEND_MAX_FILE_NAME_LEN, DOMAIN_FILE);
    result = SeosConfigBackend_initializeFileBackend(&domainBackend, name, phandle);
    Debug_LOG_DEBUG("Domain name: %s", name.buffer);
    if (result != SEOS_SUCCESS)
    {
        return result;
    }

    initializeName(name.buffer, SEOS_CONFIG_BACKEND_MAX_FILE_NAME_LEN,
                   PARAMETER_FILE);
    result = SeosConfigBackend_initializeFileBackend(&parameterBackend, name,
                                                     phandle);
    if (result != SEOS_SUCCESS)
    {
        return result;
    }
    Debug_LOG_DEBUG("Parameter backend initialized.");

    initializeName(name.buffer, SEOS_CONFIG_BACKEND_MAX_FILE_NAME_LEN, STRING_FILE);
    result = SeosConfigBackend_initializeFileBackend(&stringBackend, name, phandle);
    if (result != SEOS_SUCCESS)
    {
        return result;
    }
    Debug_LOG_DEBUG("String backend initialized.");

    initializeName(name.buffer, SEOS_CONFIG_BACKEND_MAX_FILE_NAME_LEN, BLOB_FILE);
    result = SeosConfigBackend_initializeFileBackend(&blobBackend, name, phandle);
    if (result != SEOS_SUCCESS)
    {
        return result;
    }
    Debug_LOG_DEBUG("Blob backend initialized.");

    result = SeosConfigLib_Init(
                 configLib,
                 &parameterBackend,
                 &domainBackend,
                 &stringBackend,
                 &blobBackend);
    if (result != SEOS_SUCCESS)
    {
        Debug_LOG_ERROR("SeosConfigLib_Init failed with: %d", result);
        return result;
    }
    return result;
}
#endif
