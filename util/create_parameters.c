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
#include "create_parameters.h"

static
OS_Error_t
OS_ConfigService_writeVariableLengthBlob(
    OS_ConfigServiceBackend_t* backend,
    uint32_t index,
    uint32_t numberOfBlocks,
    void const* buffer,
    size_t bufferLength)
{
    size_t blobBlockSize = OS_ConfigServiceBackend_getSizeOfRecords(backend);
    size_t blobCapacity = blobBlockSize * numberOfBlocks;

    if (bufferLength > blobCapacity)
    {
        Debug_LOG_DEBUG("Error: function: %s - line: %d\n", __FUNCTION__, __LINE__);
        return OS_ERROR_GENERIC;
    }

    // We anticipate a maximum size here which should be ok to place on the stack.
    char tmpBuf[OS_CONFIG_LIB_PARAMETER_MAX_BLOB_BLOCK_SIZE];
    size_t bytesCopied = 0;

    while (bytesCopied < bufferLength)
    {
        size_t bytesToCopy;

        if ((bufferLength - bytesCopied) >= blobBlockSize)
        {
            bytesToCopy = blobBlockSize;
        }
        else
        {
            bytesToCopy = bufferLength - bytesCopied;
        }

        memcpy(tmpBuf, (char*)buffer + bytesCopied, bytesToCopy);

        OS_Error_t fetchResult = OS_ConfigServiceBackend_writeRecord(
                                     backend,
                                     index,
                                     tmpBuf,
                                     sizeof(tmpBuf));

        if (OS_SUCCESS != fetchResult)
        {
            Debug_LOG_DEBUG("Error: function: %s - line: %d\n", __FUNCTION__, __LINE__);
            return OS_ERROR_GENERIC;
        }

        bytesCopied += bytesToCopy;
        index++;
    }

    return OS_SUCCESS;
}



static
void
initializeName(char* buf, size_t bufSize, char const* name)
{
    memset(buf, 0, bufSize);
    strncpy(buf, name, bufSize - 1);
}


static
void
initializeDomain(OS_ConfigServiceLibTypes_Domain_t* domain, char const* name)
{
    initializeName(domain->name.name, OS_CONFIG_LIB_DOMAIN_NAME_SIZE, name);
    domain->enumerator.index = 0;
}


OS_Error_t
initializeDomainsAndParameters(
    OS_ConfigServiceLib_t* configLib,
    char const* domainName)
{
    OS_Error_t result;

    if (strcmp(domainName, DOMAIN_APP1) == 0)
    {
        // Initialize the domains
        Debug_LOG_DEBUG("initializing APP1 Domain\n");
        OS_ConfigServiceLibTypes_Domain_t domain;
        initializeDomain(&domain, domainName);
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->domainBackend,
                     0,
                     &domain,
                     sizeof(domain));
        if (result != 0)
        {
            return result;
        }

        // Initialize the parameters
        OS_ConfigServiceLibTypes_Parameter_t parameter;
        OS_ConfigServiceAccessRights_SetAll(&parameter.readAccess);
        OS_ConfigServiceAccessRights_SetAll(&parameter.writeAccess);

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER32;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP1_PARAMETER_32_NAME_0);
        parameter.parameterValue.valueInteger32 = APP1_PARAMETER_32_VALUE_0;
        parameter.domain.index = 0;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     0,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER32;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP1_PARAMETER_32_NAME_1);
        parameter.parameterValue.valueInteger32 = APP1_PARAMETER_32_VALUE_1;
        parameter.domain.index = 0;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     1,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER32;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP1_PARAMETER_32_NAME_2);
        parameter.parameterValue.valueInteger32 = APP1_PARAMETER_32_VALUE_2;
        parameter.domain.index = 0;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     2,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER32;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP1_PARAMETER_32_NAME_3);
        parameter.parameterValue.valueInteger32 = APP1_PARAMETER_32_VALUE_3;
        parameter.domain.index = 0;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     3,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER64;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP1_PARAMETER_64_NAME_0);
        parameter.parameterValue.valueInteger64 = APP1_PARAMETER_64_VALUE_0;
        parameter.domain.index = 0;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     4,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER64;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP1_PARAMETER_64_NAME_1);
        parameter.parameterValue.valueInteger64 = APP1_PARAMETER_64_VALUE_1;
        parameter.domain.index = 0;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     5,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER64;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP1_PARAMETER_64_NAME_2);
        parameter.parameterValue.valueInteger64 = APP1_PARAMETER_64_VALUE_2;
        parameter.domain.index = 0;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     6,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER64;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP1_PARAMETER_64_NAME_3);
        parameter.parameterValue.valueInteger64 = APP1_PARAMETER_64_VALUE_3;
        parameter.domain.index = 0;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     7,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_STRING;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP1_PARAMETER_STRING_NAME_0);

        char str[OS_CONFIG_LIB_PARAMETER_MAX_STRING_SIZE];
        memset(str, 0, sizeof(str));
        strncpy(str, APP1_PARAMETER_STRING_VALUE_0, (sizeof(str) - 1));

        parameter.parameterValue.valueString.index = 0;
        parameter.parameterValue.valueString.size = strlen(str) + 1;
        parameter.domain.index = 0;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     8,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->stringBackend,
                     parameter.parameterValue.valueString.index,
                     str,
                     sizeof(str));
        if (result != 0)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_STRING;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP1_PARAMETER_STRING_NAME_1);

        memset(str, 0, sizeof(str));
        strncpy(str, APP1_PARAMETER_STRING_VALUE_1, sizeof(str));
        str[sizeof(str) - 1] = '\0';

        parameter.parameterValue.valueString.index = 1;
        parameter.parameterValue.valueString.size = strlen(str) + 1;
        parameter.domain.index = 0;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     9,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->stringBackend,
                     parameter.parameterValue.valueString.index,
                     str,
                     sizeof(str));
        if (result != 0)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_STRING;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP1_PARAMETER_STRING_NAME_2);

        memset(str, 0, sizeof(str));
        strncpy(str, APP1_PARAMETER_STRING_VALUE_2, sizeof(str));
        str[sizeof(str) - 1] = '\0';

        parameter.parameterValue.valueString.index = 2;
        parameter.parameterValue.valueString.size = strlen(str) + 1;
        parameter.domain.index = 0;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     10,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->stringBackend,
                     parameter.parameterValue.valueString.index,
                     str,
                     sizeof(str));
        if (result != 0)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_STRING;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP1_PARAMETER_STRING_NAME_3);

        memset(str, 0, sizeof(str));
        strncpy(str, APP1_PARAMETER_STRING_VALUE_3, sizeof(str));
        str[sizeof(str) - 1] = '\0';

        parameter.parameterValue.valueString.index = 3;
        parameter.parameterValue.valueString.size = strlen(str) + 1;
        parameter.domain.index = 0;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     11,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->stringBackend,
                     parameter.parameterValue.valueString.index,
                     str,
                     sizeof(str));
        if (result != 0)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_BLOB;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP1_PARAMETER_BLOB_NAME_0);
        char blob[OS_CONFIG_LIB_PARAMETER_MAX_BLOB_BLOCK_SIZE];
        memcpy(blob, APP1_PARAMETER_BLOB_VALUE_0, sizeof(APP1_PARAMETER_BLOB_VALUE_0));
        parameter.parameterValue.valueBlob.index = 0;
        parameter.parameterValue.valueBlob.numberOfBlocks = 1;
        parameter.parameterValue.valueBlob.size = sizeof(APP1_PARAMETER_BLOB_VALUE_0);
        parameter.domain.index = 0;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     12,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->blobBackend,
                     parameter.parameterValue.valueBlob.index,
                     blob,
                     sizeof(blob));
        if (result != 0)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_BLOB;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP1_PARAMETER_BLOB_NAME_1);

        memcpy(blob, APP1_PARAMETER_BLOB_VALUE_1, sizeof(APP1_PARAMETER_BLOB_VALUE_1));
        parameter.parameterValue.valueBlob.index = 1;
        parameter.parameterValue.valueBlob.numberOfBlocks = 1;
        parameter.parameterValue.valueBlob.size = sizeof(APP1_PARAMETER_BLOB_VALUE_1);
        parameter.domain.index = 0;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     13,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->blobBackend,
                     parameter.parameterValue.valueBlob.index,
                     blob,
                     sizeof(blob));
        if (result != 0)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_BLOB;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP1_PARAMETER_BLOB_NAME_2);

        memcpy(blob, APP1_PARAMETER_BLOB_VALUE_2, sizeof(APP1_PARAMETER_BLOB_VALUE_2));
        parameter.parameterValue.valueBlob.index = 2;
        parameter.parameterValue.valueBlob.numberOfBlocks = 1;
        parameter.parameterValue.valueBlob.size = sizeof(APP1_PARAMETER_BLOB_VALUE_2);
        parameter.domain.index = 0;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     14,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->blobBackend,
                     parameter.parameterValue.valueBlob.index,
                     blob,
                     sizeof(blob));
        if (result != 0)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_BLOB;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP1_PARAMETER_BLOB_NAME_3);
        char largeBlob[sizeof(APP1_PARAMETER_BLOB_VALUE_3)];
        memcpy(largeBlob, APP1_PARAMETER_BLOB_VALUE_3,
               sizeof(APP1_PARAMETER_BLOB_VALUE_3));
        parameter.parameterValue.valueBlob.index = 3;
        parameter.parameterValue.valueBlob.numberOfBlocks = 33;
        parameter.parameterValue.valueBlob.size = sizeof(APP1_PARAMETER_BLOB_VALUE_3);
        parameter.domain.index = 0;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     15,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigService_writeVariableLengthBlob(
                     &configLib->blobBackend,
                     parameter.parameterValue.valueBlob.index,
                     parameter.parameterValue.valueBlob.numberOfBlocks,
                     largeBlob,
                     sizeof(largeBlob));
        if (result != 0)
        {
            return result;
        }
    }

    if (strcmp(domainName, DOMAIN_APP2) == 0)
    {
        // Initialize the domains
        Debug_LOG_DEBUG("initializing APP2 Domain\n");
        OS_ConfigServiceLibTypes_Domain_t domain;
        initializeDomain(&domain, domainName);
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->domainBackend,
                     1,
                     &domain,
                     sizeof(domain));
        if (result != 0)
        {
            return result;
        }

        // Initialize the parameters
        OS_ConfigServiceLibTypes_Parameter_t parameter;
        OS_ConfigServiceAccessRights_SetAll(&parameter.readAccess);
        OS_ConfigServiceAccessRights_SetAll(&parameter.writeAccess);

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER32;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP2_PARAMETER_32_NAME_0);
        parameter.parameterValue.valueInteger32 = APP2_PARAMETER_32_VALUE_0;
        parameter.domain.index = 1;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     16,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER32;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP2_PARAMETER_32_NAME_1);
        parameter.parameterValue.valueInteger32 = APP2_PARAMETER_32_VALUE_1;
        parameter.domain.index = 1;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     17,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER32;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP2_PARAMETER_32_NAME_2);
        parameter.parameterValue.valueInteger32 = APP2_PARAMETER_32_VALUE_2;
        parameter.domain.index = 1;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     18,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER32;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP2_PARAMETER_32_NAME_3);
        parameter.parameterValue.valueInteger32 = APP2_PARAMETER_32_VALUE_3;
        parameter.domain.index = 1;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     19,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER64;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP2_PARAMETER_64_NAME_0);
        parameter.parameterValue.valueInteger64 = APP2_PARAMETER_64_VALUE_0;
        parameter.domain.index = 1;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     20,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER64;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP2_PARAMETER_64_NAME_1);
        parameter.parameterValue.valueInteger64 = APP2_PARAMETER_64_VALUE_1;
        parameter.domain.index = 1;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     21,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER64;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP2_PARAMETER_64_NAME_2);
        parameter.parameterValue.valueInteger64 = APP2_PARAMETER_64_VALUE_2;
        parameter.domain.index = 1;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     22,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER64;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP2_PARAMETER_64_NAME_3);
        parameter.parameterValue.valueInteger64 = APP2_PARAMETER_64_VALUE_3;
        parameter.domain.index = 1;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     23,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_STRING;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP2_PARAMETER_STRING_NAME_0);

        char str[OS_CONFIG_LIB_PARAMETER_MAX_STRING_SIZE];
        memset(str, 0, sizeof(str));
        strncpy(str, APP2_PARAMETER_STRING_VALUE_0, (sizeof(str) - 1));

        parameter.parameterValue.valueString.index = 4;
        parameter.parameterValue.valueString.size = strlen(str) + 1;
        parameter.domain.index = 1;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     24,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->stringBackend,
                     parameter.parameterValue.valueString.index,
                     str,
                     sizeof(str));
        if (result != 0)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_STRING;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP2_PARAMETER_STRING_NAME_1);

        memset(str, 0, sizeof(str));
        strncpy(str, APP2_PARAMETER_STRING_VALUE_1, (sizeof(str) - 1));

        parameter.parameterValue.valueString.index = 5;
        parameter.parameterValue.valueString.size = strlen(str) + 1;
        parameter.domain.index = 1;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     25,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->stringBackend,
                     parameter.parameterValue.valueString.index,
                     str,
                     sizeof(str));
        if (result != 0)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_STRING;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP2_PARAMETER_STRING_NAME_2);

        memset(str, 0, sizeof(str));
        strncpy(str, APP2_PARAMETER_STRING_VALUE_2, (sizeof(str) - 1));

        parameter.parameterValue.valueString.index = 6;
        parameter.parameterValue.valueString.size = strlen(str) + 1;
        parameter.domain.index = 1;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     26,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->stringBackend,
                     parameter.parameterValue.valueString.index,
                     str,
                     sizeof(str));
        if (result != 0)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_STRING;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP2_PARAMETER_STRING_NAME_3);

        memset(str, 0, sizeof(str));
        strncpy(str, APP2_PARAMETER_STRING_VALUE_3, (sizeof(str) - 1));

        parameter.parameterValue.valueString.index = 7;
        parameter.parameterValue.valueString.size = strlen(str) + 1;
        parameter.domain.index = 1;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     27,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->stringBackend,
                     parameter.parameterValue.valueString.index,
                     str,
                     sizeof(str));
        if (result != 0)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_BLOB;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP2_PARAMETER_BLOB_NAME_0);
        char blob[OS_CONFIG_LIB_PARAMETER_MAX_BLOB_BLOCK_SIZE];
        memcpy(blob, APP2_PARAMETER_BLOB_VALUE_0, sizeof(APP2_PARAMETER_BLOB_VALUE_0));
        parameter.parameterValue.valueBlob.index = 36;
        parameter.parameterValue.valueBlob.numberOfBlocks = 1;
        parameter.parameterValue.valueBlob.size = sizeof(APP2_PARAMETER_BLOB_VALUE_0);
        parameter.domain.index = 1;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     28,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->blobBackend,
                     parameter.parameterValue.valueBlob.index,
                     blob,
                     sizeof(blob));
        if (result != 0)
        {
            return result;
        }

        OS_ConfigServiceAccessRights_ClearAll(&parameter.writeAccess);
        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_BLOB;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP2_PARAMETER_BLOB_NAME_1);

        memcpy(blob, APP2_PARAMETER_BLOB_VALUE_1, sizeof(APP2_PARAMETER_BLOB_VALUE_1));
        parameter.parameterValue.valueBlob.index = 37;
        parameter.parameterValue.valueBlob.numberOfBlocks = 1;
        parameter.parameterValue.valueBlob.size = sizeof(APP2_PARAMETER_BLOB_VALUE_1);
        parameter.domain.index = 1;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     29,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->blobBackend,
                     parameter.parameterValue.valueBlob.index,
                     blob,
                     sizeof(blob));
        if (result != 0)
        {
            return result;
        }

        OS_ConfigServiceAccessRights_ClearAll(&parameter.readAccess);
        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_BLOB;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP2_PARAMETER_BLOB_NAME_2);

        memcpy(blob, APP2_PARAMETER_BLOB_VALUE_2, sizeof(APP2_PARAMETER_BLOB_VALUE_2));
        parameter.parameterValue.valueBlob.index = 38;
        parameter.parameterValue.valueBlob.numberOfBlocks = 1;
        parameter.parameterValue.valueBlob.size = sizeof(APP2_PARAMETER_BLOB_VALUE_2);
        parameter.domain.index = 1;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     30,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->blobBackend,
                     parameter.parameterValue.valueBlob.index,
                     blob,
                     sizeof(blob));
        if (result != 0)
        {
            return result;
        }

        OS_ConfigServiceAccessRights_SetAll(&parameter.readAccess);
        OS_ConfigServiceAccessRights_SetAll(&parameter.writeAccess);
        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_BLOB;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP2_PARAMETER_BLOB_NAME_3);
        char largeBlob[sizeof(APP2_PARAMETER_BLOB_VALUE_3)];
        memcpy(largeBlob, APP2_PARAMETER_BLOB_VALUE_3,
               sizeof(APP2_PARAMETER_BLOB_VALUE_3));
        parameter.parameterValue.valueBlob.index = 39;
        parameter.parameterValue.valueBlob.numberOfBlocks = 33;
        parameter.parameterValue.valueBlob.size = sizeof(APP2_PARAMETER_BLOB_VALUE_3);
        parameter.domain.index = 1;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     31,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigService_writeVariableLengthBlob(
                     &configLib->blobBackend,
                     parameter.parameterValue.valueBlob.index,
                     parameter.parameterValue.valueBlob.numberOfBlocks,
                     largeBlob,
                     sizeof(largeBlob));
        if (result != 0)
        {
            return result;
        }

    }

    if (strcmp(domainName, DOMAIN_APP3) == 0)
    {
        // Initialize the domains
        Debug_LOG_DEBUG("initializing APP3 Domain\n");
        OS_ConfigServiceLibTypes_Domain_t domain;
        initializeDomain(&domain, domainName);
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->domainBackend,
                     2,
                     &domain,
                     sizeof(domain));
        if (result != 0)
        {
            return result;
        }

        // Initialize the parameters
        OS_ConfigServiceLibTypes_Parameter_t parameter;
        OS_ConfigServiceAccessRights_SetAll(&parameter.readAccess);
        OS_ConfigServiceAccessRights_SetAll(&parameter.writeAccess);

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER32;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP3_PARAMETER_32_NAME_0);
        parameter.parameterValue.valueInteger32 = APP3_PARAMETER_32_VALUE_0;
        parameter.domain.index = 2;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     32,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER32;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP3_PARAMETER_32_NAME_1);
        parameter.parameterValue.valueInteger32 = APP3_PARAMETER_32_VALUE_1;
        parameter.domain.index = 2;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     33,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER32;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP3_PARAMETER_32_NAME_2);
        parameter.parameterValue.valueInteger32 = APP3_PARAMETER_32_VALUE_2;
        parameter.domain.index = 2;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     34,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER32;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP3_PARAMETER_32_NAME_3);
        parameter.parameterValue.valueInteger32 = APP3_PARAMETER_32_VALUE_3;
        parameter.domain.index = 2;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     35,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER64;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP3_PARAMETER_64_NAME_0);
        parameter.parameterValue.valueInteger64 = APP3_PARAMETER_64_VALUE_0;
        parameter.domain.index = 2;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     36,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER64;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP3_PARAMETER_64_NAME_1);
        parameter.parameterValue.valueInteger64 = APP3_PARAMETER_64_VALUE_1;
        parameter.domain.index = 2;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     37,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER64;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP3_PARAMETER_64_NAME_2);
        parameter.parameterValue.valueInteger64 = APP3_PARAMETER_64_VALUE_2;
        parameter.domain.index = 2;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     38,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER64;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP3_PARAMETER_64_NAME_3);
        parameter.parameterValue.valueInteger64 = APP3_PARAMETER_64_VALUE_3;
        parameter.domain.index = 2;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     39,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_STRING;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP3_PARAMETER_STRING_NAME_0);

        char str[OS_CONFIG_LIB_PARAMETER_MAX_STRING_SIZE];
        memset(str, 0, sizeof(str));
        strncpy(str, APP3_PARAMETER_STRING_VALUE_0, (sizeof(str) - 1));

        parameter.parameterValue.valueString.index = 8;
        parameter.parameterValue.valueString.size = strlen(str) + 1;
        parameter.domain.index = 2;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     40,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->stringBackend,
                     parameter.parameterValue.valueString.index,
                     str,
                     sizeof(str));
        if (result != 0)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_STRING;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP3_PARAMETER_STRING_NAME_1);

        memset(str, 0, sizeof(str));
        strncpy(str, APP3_PARAMETER_STRING_VALUE_1, (sizeof(str) - 1));

        parameter.parameterValue.valueString.index = 9;
        parameter.parameterValue.valueString.size = strlen(str) + 1;
        parameter.domain.index = 2;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     41,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->stringBackend,
                     parameter.parameterValue.valueString.index,
                     str,
                     sizeof(str));
        if (result != 0)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_STRING;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP3_PARAMETER_STRING_NAME_2);

        memset(str, 0, sizeof(str));
        strncpy(str, APP3_PARAMETER_STRING_VALUE_2, (sizeof(str) - 1));

        parameter.parameterValue.valueString.index = 10;
        parameter.parameterValue.valueString.size = strlen(str) + 1;
        parameter.domain.index = 2;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     42,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->stringBackend,
                     parameter.parameterValue.valueString.index,
                     str,
                     sizeof(str));
        if (result != 0)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_STRING;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP3_PARAMETER_STRING_NAME_3);

        memset(str, 0, sizeof(str));
        strncpy(str, APP3_PARAMETER_STRING_VALUE_3, (sizeof(str) - 1));

        parameter.parameterValue.valueString.index = 11;
        parameter.parameterValue.valueString.size = strlen(str) + 1;
        parameter.domain.index = 2;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     43,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->stringBackend,
                     parameter.parameterValue.valueString.index,
                     str,
                     sizeof(str));
        if (result != 0)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_BLOB;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP3_PARAMETER_BLOB_NAME_0);
        char blob[OS_CONFIG_LIB_PARAMETER_MAX_BLOB_BLOCK_SIZE];
        memcpy(blob, APP3_PARAMETER_BLOB_VALUE_0, sizeof(APP3_PARAMETER_BLOB_VALUE_0));
        parameter.parameterValue.valueBlob.index = 72;
        parameter.parameterValue.valueBlob.numberOfBlocks = 1;
        parameter.parameterValue.valueBlob.size = sizeof(APP3_PARAMETER_BLOB_VALUE_0);
        parameter.domain.index = 2;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     44,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->blobBackend,
                     parameter.parameterValue.valueBlob.index,
                     blob,
                     sizeof(blob));
        if (result != 0)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_BLOB;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP3_PARAMETER_BLOB_NAME_1);

        memcpy(blob, APP3_PARAMETER_BLOB_VALUE_1, sizeof(APP3_PARAMETER_BLOB_VALUE_1));
        parameter.parameterValue.valueBlob.index = 73;
        parameter.parameterValue.valueBlob.numberOfBlocks = 1;
        parameter.parameterValue.valueBlob.size = sizeof(APP3_PARAMETER_BLOB_VALUE_1);
        parameter.domain.index = 2;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     45,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->blobBackend,
                     parameter.parameterValue.valueBlob.index,
                     blob,
                     sizeof(blob));
        if (result != 0)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_BLOB;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP3_PARAMETER_BLOB_NAME_2);

        memcpy(blob, APP3_PARAMETER_BLOB_VALUE_2, sizeof(APP3_PARAMETER_BLOB_VALUE_2));
        parameter.parameterValue.valueBlob.index = 74;
        parameter.parameterValue.valueBlob.numberOfBlocks = 1;
        parameter.parameterValue.valueBlob.size = sizeof(APP3_PARAMETER_BLOB_VALUE_2);
        parameter.domain.index = 2;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     46,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->blobBackend,
                     parameter.parameterValue.valueBlob.index,
                     blob,
                     sizeof(blob));
        if (result != 0)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_BLOB;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP3_PARAMETER_BLOB_NAME_3);
        char largeBlob[sizeof(APP3_PARAMETER_BLOB_VALUE_3)];
        memcpy(largeBlob, APP3_PARAMETER_BLOB_VALUE_3,
               sizeof(APP3_PARAMETER_BLOB_VALUE_3));
        parameter.parameterValue.valueBlob.index = 75;
        parameter.parameterValue.valueBlob.numberOfBlocks = 33;
        parameter.parameterValue.valueBlob.size = sizeof(APP3_PARAMETER_BLOB_VALUE_3);
        parameter.domain.index = 2;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     47,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigService_writeVariableLengthBlob(
                     &configLib->blobBackend,
                     parameter.parameterValue.valueBlob.index,
                     parameter.parameterValue.valueBlob.numberOfBlocks,
                     largeBlob,
                     sizeof(largeBlob));
        if (result != 0)
        {
            return result;
        }
    }

    if (strcmp(domainName, DOMAIN_APP4) == 0)
    {
        // Initialize the domains
        Debug_LOG_DEBUG("initializing APP4 Domain\n");
        OS_ConfigServiceLibTypes_Domain_t domain;
        initializeDomain(&domain, domainName);
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->domainBackend,
                     3,
                     &domain,
                     sizeof(domain));
        if (result != 0)
        {
            return result;
        }

        // Initialize the parameters
        OS_ConfigServiceLibTypes_Parameter_t parameter;
        OS_ConfigServiceAccessRights_SetAll(&parameter.readAccess);
        OS_ConfigServiceAccessRights_SetAll(&parameter.writeAccess);

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER32;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP4_PARAMETER_32_NAME_0);
        parameter.parameterValue.valueInteger32 = APP4_PARAMETER_32_VALUE_0;
        parameter.domain.index = 3;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     48,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER32;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP4_PARAMETER_32_NAME_1);
        parameter.parameterValue.valueInteger32 = APP4_PARAMETER_32_VALUE_1;
        parameter.domain.index = 3;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     49,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER32;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP4_PARAMETER_32_NAME_2);
        parameter.parameterValue.valueInteger32 = APP4_PARAMETER_32_VALUE_2;
        parameter.domain.index = 3;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     50,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER32;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP4_PARAMETER_32_NAME_3);
        parameter.parameterValue.valueInteger32 = APP4_PARAMETER_32_VALUE_3;
        parameter.domain.index = 3;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     51,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER64;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP4_PARAMETER_64_NAME_0);
        parameter.parameterValue.valueInteger64 = APP4_PARAMETER_64_VALUE_0;
        parameter.domain.index = 3;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     52,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER64;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP4_PARAMETER_64_NAME_1);
        parameter.parameterValue.valueInteger64 = APP4_PARAMETER_64_VALUE_1;
        parameter.domain.index = 3;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     53,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER64;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP4_PARAMETER_64_NAME_2);
        parameter.parameterValue.valueInteger64 = APP4_PARAMETER_64_VALUE_2;
        parameter.domain.index = 3;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     54,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER64;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP4_PARAMETER_64_NAME_3);
        parameter.parameterValue.valueInteger64 = APP4_PARAMETER_64_VALUE_3;
        parameter.domain.index = 3;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     55,
                     &parameter,
                     sizeof(parameter));
        if (OS_SUCCESS != result)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_STRING;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP4_PARAMETER_STRING_NAME_0);

        char str[OS_CONFIG_LIB_PARAMETER_MAX_STRING_SIZE];
        memset(str, 0, sizeof(str));
        strncpy(str, APP4_PARAMETER_STRING_VALUE_0, (sizeof(str) - 1));

        parameter.parameterValue.valueString.index = 12;
        parameter.parameterValue.valueString.size = strlen(str) + 1;
        parameter.domain.index = 3;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     56,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->stringBackend,
                     parameter.parameterValue.valueString.index,
                     str,
                     sizeof(str));
        if (result != 0)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_STRING;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP4_PARAMETER_STRING_NAME_1);

        memset(str, 0, sizeof(str));
        strncpy(str, APP4_PARAMETER_STRING_VALUE_1, (sizeof(str) - 1));

        parameter.parameterValue.valueString.index = 13;
        parameter.parameterValue.valueString.size = strlen(str) + 1;
        parameter.domain.index = 3;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     57,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->stringBackend,
                     parameter.parameterValue.valueString.index,
                     str,
                     sizeof(str));
        if (result != 0)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_STRING;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP4_PARAMETER_STRING_NAME_2);

        memset(str, 0, sizeof(str));
        strncpy(str, APP4_PARAMETER_STRING_VALUE_2, (sizeof(str) - 1));

        parameter.parameterValue.valueString.index = 14;
        parameter.parameterValue.valueString.size = strlen(str) + 1;
        parameter.domain.index = 3;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     58,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->stringBackend,
                     parameter.parameterValue.valueString.index,
                     str,
                     sizeof(str));
        if (result != 0)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_STRING;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP4_PARAMETER_STRING_NAME_3);

        memset(str, 0, sizeof(str));
        strncpy(str, APP4_PARAMETER_STRING_VALUE_3, (sizeof(str) - 1));

        parameter.parameterValue.valueString.index = 15;
        parameter.parameterValue.valueString.size = strlen(str) + 1;
        parameter.domain.index = 3;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     59,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->stringBackend,
                     parameter.parameterValue.valueString.index,
                     str,
                     sizeof(str));
        if (result != 0)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_BLOB;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP4_PARAMETER_BLOB_NAME_0);
        char blob[OS_CONFIG_LIB_PARAMETER_MAX_BLOB_BLOCK_SIZE];
        memcpy(blob, APP4_PARAMETER_BLOB_VALUE_0, sizeof(APP4_PARAMETER_BLOB_VALUE_0));
        parameter.parameterValue.valueBlob.index = 108;
        parameter.parameterValue.valueBlob.numberOfBlocks = 1;
        parameter.parameterValue.valueBlob.size = sizeof(APP4_PARAMETER_BLOB_VALUE_0);
        parameter.domain.index = 3;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     60,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->blobBackend,
                     parameter.parameterValue.valueBlob.index,
                     blob,
                     sizeof(blob));
        if (result != 0)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_BLOB;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP4_PARAMETER_BLOB_NAME_1);

        memcpy(blob, APP4_PARAMETER_BLOB_VALUE_1, sizeof(APP4_PARAMETER_BLOB_VALUE_1));
        parameter.parameterValue.valueBlob.index = 109;
        parameter.parameterValue.valueBlob.numberOfBlocks = 1;
        parameter.parameterValue.valueBlob.size = sizeof(APP4_PARAMETER_BLOB_VALUE_1);
        parameter.domain.index = 3;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     61,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->blobBackend,
                     parameter.parameterValue.valueBlob.index,
                     blob,
                     sizeof(blob));
        if (result != 0)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_BLOB;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP4_PARAMETER_BLOB_NAME_2);

        memcpy(blob, APP4_PARAMETER_BLOB_VALUE_2, sizeof(APP4_PARAMETER_BLOB_VALUE_2));
        parameter.parameterValue.valueBlob.index = 110;
        parameter.parameterValue.valueBlob.numberOfBlocks = 1;
        parameter.parameterValue.valueBlob.size = sizeof(APP4_PARAMETER_BLOB_VALUE_2);
        parameter.domain.index = 3;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     62,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->blobBackend,
                     parameter.parameterValue.valueBlob.index,
                     blob,
                     sizeof(blob));
        if (result != 0)
        {
            return result;
        }

        parameter.parameterType = OS_CONFIG_LIB_PARAMETER_TYPE_BLOB;
        initializeName(parameter.parameterName.name, OS_CONFIG_LIB_PARAMETER_NAME_SIZE,
                       APP4_PARAMETER_BLOB_NAME_3);
        char largeBlob[sizeof(APP4_PARAMETER_BLOB_VALUE_3)];
        memcpy(largeBlob, APP4_PARAMETER_BLOB_VALUE_3,
               sizeof(APP4_PARAMETER_BLOB_VALUE_3));
        parameter.parameterValue.valueBlob.index = 111;
        parameter.parameterValue.valueBlob.numberOfBlocks = 33;
        parameter.parameterValue.valueBlob.size = sizeof(APP4_PARAMETER_BLOB_VALUE_3);
        parameter.domain.index = 3;
        result = OS_ConfigServiceBackend_writeRecord(
                     &configLib->parameterBackend,
                     63,
                     &parameter,
                     sizeof(parameter));
        if (result != 0)
        {
            return result;
        }
        result = OS_ConfigService_writeVariableLengthBlob(
                     &configLib->blobBackend,
                     parameter.parameterValue.valueBlob.index,
                     parameter.parameterValue.valueBlob.numberOfBlocks,
                     largeBlob,
                     sizeof(largeBlob));
        if (result != 0)
        {
            return result;
        }
    }

    return 0;
}
