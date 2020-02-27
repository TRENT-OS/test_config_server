/**
 * Copyright (C) 2019, Hensoldt Cyber GmbH
 */

#if defined(CONFIG_SERVER_BACKEND_MEMORY)
#include <string.h>
#include <stdio.h>

#include "LibDebug/Debug.h"

#include "init_lib_with_mem_backend.h"

#include "SeosConfigBackend.h"
#include "SeosConfigLib.h"

// Sizes of the buffers are defined to at least cover the total size of the
// parameters added to the backend
static char parameterBuf[12000];
static char domainBuf[2000];
static char stringBuf[2000];
static char blobBuf[12000];

static
seos_err_t
formatMemoryBackends(SeosConfigLib* configLib)
{
    seos_err_t result = 0;

    // Create the memory backends.
    result = SeosConfigBackend_createMemBackend(domainBuf, sizeof(domainBuf), 4,
                                                sizeof(SeosConfigLib_Domain));
    if (result != SEOS_SUCCESS)
    {
        Debug_LOG_ERROR("createMemBackend failed with: %d", result);
        return result;
    }

    result = SeosConfigBackend_createMemBackend(parameterBuf, sizeof(parameterBuf),
                                                64, sizeof(SeosConfigLib_Parameter));
    if (result != SEOS_SUCCESS)
    {
        Debug_LOG_ERROR("createMemBackend failed with: %d", result);
        return result;
    }

    result = SeosConfigBackend_createMemBackend(
                 stringBuf,
                 sizeof(stringBuf),
                 16,
                 SEOS_CONFIG_LIB_PARAMETER_MAX_STRING_LENGTH);
    if (result != SEOS_SUCCESS)
    {
        Debug_LOG_ERROR("createMemBackend failed with: %d", result);
        return result;
    }

    result = SeosConfigBackend_createMemBackend(
                 blobBuf,
                 sizeof(blobBuf),
                 144,
                 SEOS_CONFIG_LIB_PARAMETER_MAX_BLOB_BLOCK_LENGTH);
    if (result != SEOS_SUCCESS)
    {
        Debug_LOG_ERROR("createMemBackend failed with: %d", result);
        return result;
    }
    Debug_LOG_DEBUG("Memory backends formatted");
    return SEOS_SUCCESS;
}

seos_err_t
initializeWithMemoryBackends(SeosConfigLib* configLib)
{
    seos_err_t result = 0;
    SeosConfigBackend parameterBackend;
    SeosConfigBackend domainBackend;
    SeosConfigBackend stringBackend;
    SeosConfigBackend blobBackend;

    // Create the memory backends.
    result = formatMemoryBackends(configLib);
    if (result != SEOS_SUCCESS)
    {
        Debug_LOG_ERROR("formatMemoryBackends failed with: %d", result);
        return result;
    }

    // Initialize the backends in the config library object.
    result = SeosConfigBackend_initializeMemBackend(&domainBackend, domainBuf,
                                                    sizeof(domainBuf));
    if (result != SEOS_SUCCESS)
    {
        Debug_LOG_ERROR("initializeMemBackend failed with: %d", result);
        return result;
    }

    result = SeosConfigBackend_initializeMemBackend(&parameterBackend, parameterBuf,
                                                    sizeof(parameterBuf));
    if (result != SEOS_SUCCESS)
    {
        Debug_LOG_ERROR("initializeMemBackend failed with: %d", result);
        return result;
    }

    result = SeosConfigBackend_initializeMemBackend(&stringBackend, stringBuf,
                                                    sizeof(stringBuf));
    if (result != SEOS_SUCCESS)
    {
        Debug_LOG_ERROR("initializeMemBackend failed with: %d", result);
        return result;
    }

    result = SeosConfigBackend_initializeMemBackend(&blobBackend, blobBuf,
                                                    sizeof(blobBuf));
    if (result != SEOS_SUCCESS)
    {
        Debug_LOG_ERROR("initializeMemBackend failed with: %d", result);
        return result;
    }

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
