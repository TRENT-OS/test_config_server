/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include <string.h>
#include <stdio.h>

#include "LibDebug/Debug.h"

#include "helper_func.h"

// -----------------------------------------------------------------------------
void initializeName(char* buf, size_t bufSize, char const* name)
{
    memset(buf, 0, bufSize);
    strncpy(buf, name, bufSize - 1);
}

//------------------------------------------------------------------------------
static
OS_Error_t
compareDomainName(OS_ConfigServiceLibTypes_DomainName_t const* a,
                  OS_ConfigServiceLibTypes_DomainName_t const* b)
{
    for (unsigned int k = 0; k < OS_CONFIG_LIB_DOMAIN_NAME_LEN; ++k)
    {
        if (a->name[k] != b->name[k])
        {
            Debug_LOG_DEBUG("Error: function: %s - line: %d\n", __FUNCTION__, __LINE__);
            return OS_ERROR_GENERIC;
        }
    }

    return OS_SUCCESS;
}

//------------------------------------------------------------------------------
static
OS_Error_t
find_domain(
    OS_ConfigServiceHandle_t handle,
    OS_ConfigServiceLibTypes_DomainEnumerator_t* enumerator,
    OS_ConfigServiceLibTypes_DomainName_t const* domainName,
    OS_ConfigServiceLibTypes_Domain_t* domain)
{
    OS_Error_t ret;

    OS_ConfigService_domainEnumeratorInit(handle, enumerator);
    for (;;)
    {
        ret = OS_ConfigService_domainEnumeratorGetElement(
                    handle,
                    enumerator,
                    domain);
        if (0 != ret)
        {
            Debug_LOG_ERROR("OS_ConfigService_domainEnumeratorGetElement() failed, ret %d",
                            ret);
            return OS_ERROR_GENERIC;
        }

        OS_ConfigServiceLibTypes_DomainName_t domainNameTmp;
        OS_ConfigService_domainGetName(domain, &domainNameTmp);
        if (OS_SUCCESS == compareDomainName(&domainNameTmp, domainName))
        {
            // enumerator holds the right domain
            return OS_SUCCESS;
        }

        ret = OS_ConfigService_domainEnumeratorIncrement(handle, enumerator);
        if (0 != ret)
        {
            Debug_LOG_ERROR("OS_ConfigService_domainEnumeratorIncrement() failed, ret %d",
                            ret);
            return OS_ERROR_GENERIC;
        }
    } // end for(;;)
}

//------------------------------------------------------------------------------
static
OS_Error_t
get_parameter_enumerator(
    OS_ConfigServiceHandle_t handle,
    const char* DomainName,
    const char* ParameterName,
    OS_ConfigServiceLibTypes_ParameterEnumerator_t* parameterEnumerator)
{
    OS_Error_t ret;

    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator = {0};
    OS_ConfigServiceLibTypes_DomainName_t domainName;
    OS_ConfigServiceLibTypes_ParameterName_t parameterName;
    OS_ConfigServiceLibTypes_Domain_t domain = {0};

    initializeDomainName(&domainName, DomainName);

    initializeParameterName(&parameterName, ParameterName);

    ret = find_domain(handle, &domainEnumerator, &domainName, &domain);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("find_domain() failed, ret %d", ret);
        return OS_ERROR_CONFIG_DOMAIN_NOT_FOUND;
    }

    ret = OS_ConfigService_domainEnumeratorGetElement(handle, &domainEnumerator, &domain);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("OS_ConfigServiceLibTypes_DomainEnumerator_tGetElement() failed, ret %d", ret);
        return OS_ERROR_GENERIC;
    }

    ret = OS_ConfigService_domainCreateParameterEnumerator(handle, &domain, &parameterName, parameterEnumerator);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("OS_ConfigServiceLibTypes_Domain_tCreateParameterEnumerator() failed, ret %d", ret);
        return OS_ERROR_GENERIC;
    }

    return OS_SUCCESS;
}

//------------------------------------------------------------------------------
static
OS_Error_t
get_parameter_element(
    OS_ConfigServiceHandle_t handle,
    const char* DomainName,
    const char* ParameterName,
    OS_ConfigServiceLibTypes_DomainName_t* domainName,
    OS_ConfigServiceLibTypes_ParameterName_t* parameterName,
    OS_ConfigServiceLibTypes_Parameter_t* parameter)
{
    OS_Error_t ret;
    OS_ConfigServiceLibTypes_Domain_t domain;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator = {0};

    initializeDomainName(domainName, DomainName);
    initializeParameterName(parameterName, ParameterName);

    ret = find_domain(handle, &domainEnumerator, domainName, &domain);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("find_domain() failed, ret %d", ret);
        return OS_ERROR_CONFIG_DOMAIN_NOT_FOUND;
    }

    ret = OS_ConfigService_domainGetElement(handle, &domain, parameterName, parameter);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("domainGetElement() failed, ret %d", ret);
        return OS_ERROR_CONFIG_PARAMETER_NOT_FOUND;
    }

    return OS_SUCCESS;
}

//------------------------------------------------------------------------------
OS_Error_t
initializeDomainName(
    OS_ConfigServiceLibTypes_DomainName_t* domainName,
    char const* name)
{
    initializeName(domainName->name, OS_CONFIG_LIB_DOMAIN_NAME_LEN, name);

    return OS_SUCCESS;
}

OS_Error_t
initializeParameterName(
    OS_ConfigServiceLibTypes_ParameterName_t* parameterName,
    char const* name)
{
    initializeName(parameterName->name, OS_CONFIG_LIB_PARAMETER_NAME_LEN, name);

    return OS_SUCCESS;
}

//------------------------------------------------------------------------------
OS_Error_t verify_integer32_parameter(OS_ConfigServiceHandle_t* handle,
                                      const char* DomainName,
                                      const char* ParameterName,
                                      const uint32_t IntegerValue)
{
    OS_Error_t ret;
    size_t bytesCopied;
    OS_ConfigServiceLibTypes_DomainName_t domainName;
    OS_ConfigServiceLibTypes_ParameterName_t parameterName;
    OS_ConfigServiceLibTypes_Parameter_t parameter;
    OS_ConfigServiceHandle_t configHandle = *handle;
    uint32_t valueInteger32;

    ret = get_parameter_element(configHandle, DomainName, ParameterName, &domainName, &parameterName, &parameter);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("get_parameter_element() failed, ret %d", ret);
        return ret;
    }

    size_t parameterSize = OS_ConfigService_parameterGetSize(&parameter);
    if (parameterSize != sizeof(uint32_t))
    {
        Debug_LOG_ERROR("retrieved integer size does not match expected size");
        return OS_ERROR_GENERIC;
    }

    OS_ConfigServiceLibTypes_ParameterType_t parameterType;
    OS_ConfigService_parameterGetType(&parameter, &parameterType);
    if (parameterType != OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER32)
    {
        Debug_LOG_ERROR("retrieved parameter does not match expected type");
        return OS_ERROR_CONFIG_TYPE_MISMATCH;
    }

    ret = OS_ConfigService_parameterGetValueAsU32(configHandle, &parameter, &valueInteger32);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("parameterGetValueAsU32() failed, ret %d", ret);
        return ret;
    }

    if (valueInteger32 != IntegerValue)
    {
        Debug_LOG_ERROR("retrieved integer value does not match expected value");
        return OS_ERROR_GENERIC;
    }

    valueInteger32 = 0;

    ret = OS_ConfigService_parameterGetValueFromDomainName(
                                                configHandle,
                                                &domainName,
                                                &parameterName,
                                                OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER32,
                                                &valueInteger32,
                                                sizeof(valueInteger32),
                                                &bytesCopied);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("parameterGetValueFromDomainName() failed, ret %d", ret);
        return ret;
    }

    if (valueInteger32 != IntegerValue)
    {
        Debug_LOG_ERROR("retrieved integer value does not match expected value");
        return OS_ERROR_GENERIC;
    }

    return OS_SUCCESS;
}

//------------------------------------------------------------------------------
OS_Error_t verify_integer64_parameter(OS_ConfigServiceHandle_t* handle,
                                      const char* DomainName,
                                      const char* ParameterName,
                                      const uint64_t IntegerValue)
{
    OS_Error_t ret;
    size_t bytesCopied;
    OS_ConfigServiceLibTypes_DomainName_t domainName;
    OS_ConfigServiceLibTypes_ParameterName_t parameterName;
    OS_ConfigServiceLibTypes_Parameter_t parameter;
    OS_ConfigServiceHandle_t configHandle = *handle;
    uint64_t valueInteger64;

    ret = get_parameter_element(configHandle, DomainName, ParameterName, &domainName, &parameterName, &parameter);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("get_parameter_element() failed, ret %d", ret);
        return ret;
    }

    size_t parameterSize = OS_ConfigService_parameterGetSize(&parameter);
    if (parameterSize != sizeof(uint64_t))
    {
        Debug_LOG_ERROR("retrieved integer size does not match expected size");
        return OS_ERROR_GENERIC;
    }

    OS_ConfigServiceLibTypes_ParameterType_t parameterType;
    OS_ConfigService_parameterGetType(&parameter, &parameterType);
    if (parameterType != OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER64)
    {
        Debug_LOG_ERROR("retrieved parameter does not match expected type");
        return OS_ERROR_CONFIG_TYPE_MISMATCH;
    }

    ret = OS_ConfigService_parameterGetValueAsU64(configHandle, &parameter, &valueInteger64);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("parameterGetValueFromDomainName() failed, ret %d", ret);
        return ret;
    }

    if (valueInteger64 != IntegerValue)
    {
        Debug_LOG_ERROR("retrieved integer value does not match expected value");
        return OS_ERROR_GENERIC;
    }

    valueInteger64 = 0;

    ret = OS_ConfigService_parameterGetValueFromDomainName(
                                                configHandle,
                                                &domainName,
                                                &parameterName,
                                                OS_CONFIG_LIB_PARAMETER_TYPE_INTEGER64,
                                                &valueInteger64,
                                                sizeof(valueInteger64),
                                                &bytesCopied);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("parameterGetValueFromDomainName() failed, ret %d", ret);
        return ret;
    }

    if (valueInteger64 != IntegerValue)
    {
        return OS_ERROR_GENERIC;
    }

    return OS_SUCCESS;
}

//------------------------------------------------------------------------------
OS_Error_t verify_string_parameter(OS_ConfigServiceHandle_t* handle,
                                   const char* DomainName,
                                   const char* ParameterName,
                                   const char* StringValue,
                                   size_t parameterLength)
{
    OS_Error_t ret;
    size_t bytesCopied;
    OS_ConfigServiceLibTypes_DomainName_t domainName;
    OS_ConfigServiceLibTypes_ParameterName_t parameterName;
    OS_ConfigServiceLibTypes_Parameter_t parameter;
    char configString[OS_CONFIG_LIB_PARAMETER_MAX_STRING_LENGTH];
    OS_ConfigServiceHandle_t configHandle = *handle;

    ret = get_parameter_element(configHandle, DomainName, ParameterName, &domainName, &parameterName, &parameter);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("get_parameter_element() failed, ret %d", ret);
        return ret;
    }

    size_t parameterSize = OS_ConfigService_parameterGetSize(&parameter);
    if (parameterSize != parameterLength)
    {
        Debug_LOG_ERROR("retrieved string size does not match expected size for parameter %s", ParameterName);
        return OS_ERROR_GENERIC;
    }

    OS_ConfigServiceLibTypes_ParameterType_t parameterType;
    OS_ConfigService_parameterGetType(&parameter, &parameterType);
    if (parameterType != OS_CONFIG_LIB_PARAMETER_TYPE_STRING)
    {
        Debug_LOG_ERROR("retrieved parameter does not match expected type");
        return OS_ERROR_CONFIG_TYPE_MISMATCH;
    }

    ret = OS_ConfigService_parameterGetValueAsString(configHandle,
                                                       &parameter,
                                                       configString,
                                                       sizeof(configString));
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("parameterGetValueAsString() failed, ret %d", ret);
        return ret;
    }

    ret = strcmp(configString, StringValue);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("strcmp() failed, ret %d", ret);
        return ret;
    }

    memset(configString,0,sizeof(configString));

    ret = OS_ConfigService_parameterGetValueFromDomainName(
                                                configHandle,
                                                &domainName,
                                                &parameterName,
                                                OS_CONFIG_LIB_PARAMETER_TYPE_STRING,
                                                configString,
                                                sizeof(configString),
                                                &bytesCopied);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("parameterGetValueFromDomainName() failed, ret %d", ret);
        return ret;
    }

    ret = strcmp(configString, StringValue);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("strcmp() failed, ret %d", ret);
        return ret;
    }

    return OS_SUCCESS;
}

//------------------------------------------------------------------------------
OS_Error_t verify_blob_parameter(OS_ConfigServiceHandle_t* handle,
                                 const char* DomainName,
                                 const char* ParameterName,
                                 const char* BlobValue,
                                 size_t parameterLength)
{
    OS_Error_t ret;
    size_t bytesCopied;
    OS_ConfigServiceLibTypes_DomainName_t domainName;
    OS_ConfigServiceLibTypes_ParameterName_t parameterName;
    OS_ConfigServiceLibTypes_Parameter_t parameter;
    char configBlob[parameterLength];
    OS_ConfigServiceHandle_t configHandle = *handle;

    ret = get_parameter_element(configHandle, DomainName, ParameterName, &domainName, &parameterName, &parameter);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("get_parameter_element() failed, ret %d", ret);
        return ret;
    }

    size_t parameterSize = OS_ConfigService_parameterGetSize(&parameter);
    if (parameterSize != parameterLength)
    {
        Debug_LOG_ERROR("retrieved blob size does not match expected size");
        return OS_ERROR_GENERIC;
    }

    OS_ConfigServiceLibTypes_ParameterType_t parameterType;
    OS_ConfigService_parameterGetType(&parameter, &parameterType);
    if (parameterType != OS_CONFIG_LIB_PARAMETER_TYPE_BLOB)
    {
        Debug_LOG_ERROR("retrieved parameter does not match expected type");
        return OS_ERROR_CONFIG_TYPE_MISMATCH;
    }

    ret = OS_ConfigService_parameterGetValueAsBlob(configHandle,
                                                       &parameter,
                                                       configBlob,
                                                       sizeof(configBlob));
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("parameterGetValueAsBlob() failed, ret %d", ret);
        return ret;
    }

    ret = memcmp(configBlob, BlobValue, parameterLength);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("memcmp() failed, ret %d", ret);
        return ret;
    }

    memset(configBlob,0,sizeof(configBlob));

    ret = OS_ConfigService_parameterGetValueFromDomainName(
                                                configHandle,
                                                &domainName,
                                                &parameterName,
                                                OS_CONFIG_LIB_PARAMETER_TYPE_BLOB,
                                                configBlob,
                                                sizeof(configBlob),
                                                &bytesCopied);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("parameterGetValueFromDomainName() failed, ret %d", ret);
        return ret;
    }

    ret = memcmp(configBlob, BlobValue, parameterLength);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("memcmp() failed, ret %d", ret);
        return ret;
    }

    return OS_SUCCESS;
}

//------------------------------------------------------------------------------
OS_Error_t verify_parameter(OS_ConfigServiceHandle_t* handle,
                            const char* DomainName,
                            const char* ParameterName,
                            const char* parameterValue,
                            size_t parameterLength)
{
    OS_Error_t ret;
    size_t bytesCopied;
    OS_ConfigServiceLibTypes_DomainName_t domainName;
    OS_ConfigServiceLibTypes_ParameterName_t parameterName;
    OS_ConfigServiceLibTypes_Parameter_t parameter;
    char configBlob[parameterLength];
    OS_ConfigServiceHandle_t configHandle = *handle;

    ret = get_parameter_element(configHandle, DomainName, ParameterName, &domainName, &parameterName, &parameter);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("get_parameter_element() failed, ret %d", ret);
        return ret;
    }

    size_t parameterSize = OS_ConfigService_parameterGetSize(&parameter);
    if (parameterSize != parameterLength)
    {
        Debug_LOG_ERROR("retrieved blob size does not match expected size");
        return OS_ERROR_GENERIC;
    }

    OS_ConfigServiceLibTypes_ParameterType_t parameterType;
    OS_ConfigService_parameterGetType(&parameter, &parameterType);

    ret = OS_ConfigService_parameterGetValue(configHandle,
                                               &parameter,
                                               configBlob,
                                               sizeof(configBlob),
                                               &bytesCopied);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("parameterGetValue() failed, ret %d", ret);
        return ret;
    }

    ret = memcmp(configBlob, parameterValue, parameterLength);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("memcmp() failed, ret %d", ret);
        return ret;
    }

    ret = OS_ConfigService_parameterGetValueFromDomainName(
                                                configHandle,
                                                &domainName,
                                                &parameterName,
                                                parameterType,
                                                configBlob,
                                                sizeof(configBlob),
                                                &bytesCopied);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("parameterGetValueFromDomainName() failed, ret %d", ret);
        return ret;
    }

    ret = memcmp(configBlob, parameterValue, parameterLength);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("memcmp() failed, ret %d", ret);
        return ret;
    }

    return OS_SUCCESS;
}

//------------------------------------------------------------------------------
OS_Error_t set_integer32_parameter(OS_ConfigServiceHandle_t* handle,
                                   const char* DomainName,
                                   const char* ParameterName,
                                   const uint32_t IntegerValue)
{
    OS_Error_t ret;

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator = {0};

    ret = get_parameter_enumerator(configHandle,
                                   DomainName,
                                   ParameterName,
                                   &parameterEnumerator);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("get_parameter_enumerator() failed, ret %d", ret);
        return OS_ERROR_GENERIC;
    }

    ret = OS_ConfigService_parameterSetValueAsU32(configHandle,
                                                    &parameterEnumerator,
                                                    IntegerValue);
    if (ret < 0)
    {
        Debug_LOG_ERROR("OS_ConfigService_parameterSetValue() failed, ret %d", ret);
        // ToDo: OS_ConfigService_parameterSetValue() should return error codes
        //       about the actual problem, so we can return them
        return OS_ERROR_GENERIC;
    }

    return OS_SUCCESS;
}

//------------------------------------------------------------------------------
OS_Error_t set_integer64_parameter(OS_ConfigServiceHandle_t* handle,
                                   const char* DomainName,
                                   const char* ParameterName,
                                   const uint64_t IntegerValue)
{
    OS_Error_t ret;

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator = {0};

    ret = get_parameter_enumerator(configHandle,
                                   DomainName,
                                   ParameterName,
                                   &parameterEnumerator);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("get_parameter_enumerator() failed, ret %d", ret);
        return OS_ERROR_GENERIC;
    }

    ret = OS_ConfigService_parameterSetValueAsU64(configHandle,
                                                    &parameterEnumerator,
                                                    IntegerValue);
    if (ret < 0)
    {
        Debug_LOG_ERROR("OS_ConfigService_parameterSetValue() failed, ret %d", ret);
        // ToDo: OS_ConfigService_parameterSetValue() should return error codes
        //       about the actual problem, so we can return them
        return OS_ERROR_GENERIC;
    }

    return OS_SUCCESS;
}

//------------------------------------------------------------------------------
OS_Error_t set_string_parameter(OS_ConfigServiceHandle_t* handle,
                                   const char* DomainName,
                                   const char* ParameterName,
                                   const char* StringValue,
                                   size_t parameterLength)
{
    OS_Error_t ret;

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator = {0};

    ret = get_parameter_enumerator(configHandle,
                                   DomainName,
                                   ParameterName,
                                   &parameterEnumerator);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("get_parameter_enumerator() failed, ret %d", ret);
        return OS_ERROR_GENERIC;
    }

    ret = OS_ConfigService_parameterSetValueAsString(configHandle,
                                                    &parameterEnumerator,
                                                    OS_CONFIG_LIB_PARAMETER_TYPE_STRING,
                                                    StringValue,
                                                    parameterLength);
    if (ret < 0)
    {
        Debug_LOG_ERROR("OS_ConfigService_parameterSetValue() failed, ret %d", ret);
        // ToDo: OS_ConfigService_parameterSetValue() should return error codes
        //       about the actual problem, so we can return them
        return OS_ERROR_GENERIC;
    }

    return OS_SUCCESS;
}

//------------------------------------------------------------------------------
OS_Error_t set_blob_parameter(OS_ConfigServiceHandle_t* handle,
                                   const char* DomainName,
                                   const char* ParameterName,
                                   const char* BlobValue,
                                   size_t parameterLength)
{
    OS_Error_t ret;

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator = {0};

    ret = get_parameter_enumerator(configHandle,
                                   DomainName,
                                   ParameterName,
                                   &parameterEnumerator);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("get_parameter_enumerator() failed, ret %d", ret);
        return OS_ERROR_GENERIC;
    }

    ret = OS_ConfigService_parameterSetValueAsBlob(configHandle,
                                                    &parameterEnumerator,
                                                    OS_CONFIG_LIB_PARAMETER_TYPE_BLOB,
                                                    BlobValue,
                                                    parameterLength);
    if (ret < 0)
    {
        Debug_LOG_ERROR("OS_ConfigService_parameterSetValue() failed, ret %d", ret);
        // ToDo: OS_ConfigService_parameterSetValue() should return error codes
        //       about the actual problem, so we can return them
        return OS_ERROR_GENERIC;
    }

    return OS_SUCCESS;
}

//------------------------------------------------------------------------------
OS_Error_t set_parameter(OS_ConfigServiceHandle_t* handle,
                         const char* DomainName,
                         const char* ParameterName,
                         const void* parameterValue,
                         size_t parameterLength)
{
    OS_Error_t ret;
    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator = {0};
    OS_ConfigServiceLibTypes_DomainName_t domainName;
    OS_ConfigServiceLibTypes_ParameterName_t parameterName;
    OS_ConfigServiceLibTypes_Parameter_t parameter;

    ret = get_parameter_element(configHandle, DomainName, ParameterName, &domainName, &parameterName, &parameter);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("get_parameter_element() failed, ret %d", ret);
        return ret;
    }

    ret = get_parameter_enumerator(configHandle,
                                   DomainName,
                                   ParameterName,
                                   &parameterEnumerator);
    if (OS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("get_parameter_enumerator() failed, ret %d", ret);
        return OS_ERROR_GENERIC;
    }

    OS_ConfigServiceLibTypes_ParameterType_t parameterType;
    OS_ConfigService_parameterGetType(&parameter, &parameterType);

    ret = OS_ConfigService_parameterSetValue(configHandle,
                                               &parameterEnumerator,
                                               parameterType,
                                               parameterValue,
                                               parameterLength);
    if (ret < 0)
    {
        Debug_LOG_ERROR("OS_ConfigService_parameterSetValue() failed, ret %d", ret);
        // ToDo: OS_ConfigService_parameterSetValue() should return error codes
        //       about the actual problem, so we can return them
        return OS_ERROR_GENERIC;
    }

    return OS_SUCCESS;
}