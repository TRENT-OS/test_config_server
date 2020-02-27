/**
 * Copyright (C) 2019, Hensoldt Cyber GmbH
 */

#if defined(CONFIG_SERVER_BACKEND_FILESYSTEM)
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
    SeosConfigBackend_FileName name;

    // Create the file backends.
    Debug_LOG_DEBUG("Size of ConfigLib_Domain: %d", sizeof(SeosConfigLib_Domain));
    initializeName(name.buffer, SEOS_CONFIG_BACKEND_MAX_FILE_NAME_LEN, DOMAIN_FILE);
    Debug_LOG_DEBUG("Name.buffer: %s", name.buffer);
    result = SeosConfigBackend_createFileBackend(name, phandle, 4,
                                                 sizeof(SeosConfigLib_Domain));
    if (result != SEOS_SUCCESS)
    {
        return result;
    }

    Debug_LOG_DEBUG("Size of ConfigLib_Parameter: %d", sizeof(SeosConfigLib_Parameter));
    initializeName(name.buffer, SEOS_CONFIG_BACKEND_MAX_FILE_NAME_LEN,
                   PARAMETER_FILE);
    Debug_LOG_DEBUG("Name.buffer: %s", name.buffer);
    result = SeosConfigBackend_createFileBackend(name, phandle, 64,
                                                 sizeof(SeosConfigLib_Parameter));
    if (result != SEOS_SUCCESS)
    {
        return result;
    }

    initializeName(name.buffer, SEOS_CONFIG_BACKEND_MAX_FILE_NAME_LEN, STRING_FILE);
    Debug_LOG_DEBUG("Name.buffer: %s", name.buffer);
    result = SeosConfigBackend_createFileBackend(name, phandle, 16,
                                                 SEOS_CONFIG_LIB_PARAMETER_MAX_STRING_LENGTH);
    if (result != SEOS_SUCCESS)
    {
        return result;
    }

    initializeName(name.buffer, SEOS_CONFIG_BACKEND_MAX_FILE_NAME_LEN, BLOB_FILE);
    Debug_LOG_DEBUG("Name.buffer: %s", name.buffer);
    result = SeosConfigBackend_createFileBackend(name, phandle, 144,
                                                 SEOS_CONFIG_LIB_PARAMETER_MAX_BLOB_BLOCK_LENGTH);
    if (result != SEOS_SUCCESS)
    {
        return result;
    }

    return SEOS_SUCCESS;
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
    // Create the memory backends.
    result = createFileBackends(phandle);
    if (result != SEOS_SUCCESS)
    {
        return result;
    }

    Debug_LOG_DEBUG("file backends created.");

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
