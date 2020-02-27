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
seos_err_t
compareDomainName(SeosConfigLib_DomainName const* a,
                  SeosConfigLib_DomainName const* b)
{
    for (unsigned int k = 0; k < SEOS_CONFIG_LIB_DOMAIN_NAME_LEN; ++k)
    {
        if (a->name[k] != b->name[k])
        {
            Debug_LOG_DEBUG("Error: function: %s - line: %d\n", __FUNCTION__, __LINE__);
            return SEOS_ERROR_GENERIC;
        }
    }

    return SEOS_SUCCESS;
}

//------------------------------------------------------------------------------
static
seos_err_t
find_domain(
    SeosConfigHandle handle,
    SeosConfigLib_DomainEnumerator* enumerator,
    SeosConfigLib_DomainName const* domainName,
    SeosConfigLib_Domain* domain)
{
    seos_err_t ret;

    seos_configuration_domainEnumeratorInit(handle, enumerator);
    for (;;)
    {
        ret = seos_configuration_domainEnumeratorGetElement(
                    handle,
                    enumerator,
                    domain);
        if (0 != ret)
        {
            Debug_LOG_ERROR("seos_configuration_domainEnumeratorGetElement() failed, ret %d",
                            ret);
            return SEOS_ERROR_GENERIC;
        }

        SeosConfigLib_DomainName domainNameTmp;
        seos_configuration_domainGetName(domain, &domainNameTmp);
        if (SEOS_SUCCESS == compareDomainName(&domainNameTmp, domainName))
        {
            // enumerator holds the right domain
            return SEOS_SUCCESS;
        }

        ret = seos_configuration_domainEnumeratorIncrement(handle, enumerator);
        if (0 != ret)
        {
            Debug_LOG_ERROR("seos_configuration_domainEnumeratorIncrement() failed, ret %d",
                            ret);
            return SEOS_ERROR_GENERIC;
        }
    } // end for(;;)
}

//------------------------------------------------------------------------------
static
seos_err_t
get_parameter_enumerator(
    SeosConfigHandle handle,
    const char* DomainName,
    const char* ParameterName,
    SeosConfigLib_ParameterEnumerator* parameterEnumerator)
{
    seos_err_t ret;

    SeosConfigLib_DomainEnumerator domainEnumerator = {0};
    SeosConfigLib_DomainName domainName;
    SeosConfigLib_ParameterName parameterName;
    SeosConfigLib_Domain domain = {0};

    seos_configuration_initializeDomainName(&domainName,
                                        DomainName);

    seos_configuration_initializeParameterName(&parameterName, ParameterName);

    ret = find_domain(handle, &domainEnumerator, &domainName, &domain);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("find_domain() failed, ret %d", ret);
        return SEOS_ERROR_CONFIG_DOMAIN_NOT_FOUND;
    }

    ret = seos_configuration_domainEnumeratorGetElement(handle, &domainEnumerator, &domain);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("SeosConfigLib_domainEnumeratorGetElement() failed, ret %d", ret);
        return SEOS_ERROR_GENERIC;
    }

    ret = seos_configuration_domainCreateParameterEnumerator(handle, &domain, &parameterName, parameterEnumerator);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("SeosConfigLib_domainCreateParameterEnumerator() failed, ret %d", ret);
        return SEOS_ERROR_GENERIC;
    }

    return SEOS_SUCCESS;
}

//------------------------------------------------------------------------------
static
seos_err_t
get_parameter_element(
    SeosConfigHandle handle,
    const char* DomainName,
    const char* ParameterName,
    SeosConfigLib_DomainName* domainName,
    SeosConfigLib_ParameterName* parameterName,
    SeosConfigLib_Parameter* parameter)
{
    seos_err_t ret;
    SeosConfigLib_Domain domain;
    SeosConfigLib_DomainEnumerator domainEnumerator = {0};

    seos_configuration_initializeDomainName(domainName,
                                           DomainName);
    seos_configuration_initializeParameterName(parameterName, ParameterName);

    ret = find_domain(handle, &domainEnumerator, domainName, &domain);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("find_domain() failed, ret %d", ret);
        return SEOS_ERROR_CONFIG_DOMAIN_NOT_FOUND;
    }

    ret = seos_configuration_domainGetElement(handle, &domain, parameterName, parameter);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("domainGetElement() failed, ret %d", ret);
        return SEOS_ERROR_CONFIG_PARAMETER_NOT_FOUND;
    }

    return SEOS_SUCCESS;
}

//------------------------------------------------------------------------------
seos_err_t
seos_configuration_initializeDomainName(
    SeosConfigLib_DomainName* domainName,
    char const* name)
{
    initializeName(domainName->name, SEOS_CONFIG_LIB_DOMAIN_NAME_LEN, name);

    return SEOS_SUCCESS;
}

seos_err_t
seos_configuration_initializeParameterName(
    SeosConfigLib_ParameterName* parameterName,
    char const* name)
{
    initializeName(parameterName->name, SEOS_CONFIG_LIB_PARAMETER_NAME_LEN, name);

    return SEOS_SUCCESS;
}

//------------------------------------------------------------------------------
seos_err_t verify_integer32_parameter(SeosConfigHandle* handle,
                                      const char* DomainName,
                                      const char* ParameterName,
                                      const uint32_t IntegerValue)
{
    seos_err_t ret;
    size_t bytesCopied;
    SeosConfigLib_DomainName domainName;
    SeosConfigLib_ParameterName parameterName;
    SeosConfigLib_Parameter parameter;
    SeosConfigHandle configHandle = *handle;
    uint32_t valueInteger32;

    ret = get_parameter_element(configHandle, DomainName, ParameterName, &domainName, &parameterName, &parameter);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("get_parameter_element() failed, ret %d", ret);
        return ret;
    }

    size_t parameterSize = seos_configuration_parameterGetSize(&parameter);
    if (parameterSize != sizeof(uint32_t))
    {
        Debug_LOG_ERROR("retrieved integer size does not match expected size");
        return SEOS_ERROR_GENERIC;
    }

    SeosConfigLib_ParameterType parameterType;
    seos_configuration_parameterGetType(&parameter, &parameterType);
    if (parameterType != SEOS_CONFIG_LIB_PARAMETER_TYPE_INTEGER32)
    {
        Debug_LOG_ERROR("retrieved parameter does not match expected type");
        return SEOS_ERROR_CONFIG_TYPE_MISMATCH;
    }

    ret = seos_configuration_parameterGetValueAsU32(configHandle, &parameter, &valueInteger32);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("parameterGetValueAsU32() failed, ret %d", ret);
        return ret;
    }

    if (valueInteger32 != IntegerValue)
    {
        Debug_LOG_ERROR("retrieved integer value does not match expected value");
        return SEOS_ERROR_GENERIC;
    }

    valueInteger32 = 0;

    ret = seos_configuration_parameterGetValueFromDomainName(
                                                configHandle,
                                                &domainName,
                                                &parameterName,
                                                SEOS_CONFIG_LIB_PARAMETER_TYPE_INTEGER32,
                                                &valueInteger32,
                                                sizeof(valueInteger32),
                                                &bytesCopied);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("parameterGetValueFromDomainName() failed, ret %d", ret);
        return ret;
    }

    if (valueInteger32 != IntegerValue)
    {
        Debug_LOG_ERROR("retrieved integer value does not match expected value");
        return SEOS_ERROR_GENERIC;
    }

    return SEOS_SUCCESS;
}

//------------------------------------------------------------------------------
seos_err_t verify_integer64_parameter(SeosConfigHandle* handle,
                                      const char* DomainName,
                                      const char* ParameterName,
                                      const uint64_t IntegerValue)
{
    seos_err_t ret;
    size_t bytesCopied;
    SeosConfigLib_DomainName domainName;
    SeosConfigLib_ParameterName parameterName;
    SeosConfigLib_Parameter parameter;
    SeosConfigHandle configHandle = *handle;
    uint64_t valueInteger64;

    ret = get_parameter_element(configHandle, DomainName, ParameterName, &domainName, &parameterName, &parameter);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("get_parameter_element() failed, ret %d", ret);
        return ret;
    }

    size_t parameterSize = seos_configuration_parameterGetSize(&parameter);
    if (parameterSize != sizeof(uint64_t))
    {
        Debug_LOG_ERROR("retrieved integer size does not match expected size");
        return SEOS_ERROR_GENERIC;
    }

    SeosConfigLib_ParameterType parameterType;
    seos_configuration_parameterGetType(&parameter, &parameterType);
    if (parameterType != SEOS_CONFIG_LIB_PARAMETER_TYPE_INTEGER64)
    {
        Debug_LOG_ERROR("retrieved parameter does not match expected type");
        return SEOS_ERROR_CONFIG_TYPE_MISMATCH;
    }

    ret = seos_configuration_parameterGetValueAsU64(configHandle, &parameter, &valueInteger64);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("parameterGetValueFromDomainName() failed, ret %d", ret);
        return ret;
    }

    if (valueInteger64 != IntegerValue)
    {
        Debug_LOG_ERROR("retrieved integer value does not match expected value");
        return SEOS_ERROR_GENERIC;
    }

    valueInteger64 = 0;

    ret = seos_configuration_parameterGetValueFromDomainName(
                                                configHandle,
                                                &domainName,
                                                &parameterName,
                                                SEOS_CONFIG_LIB_PARAMETER_TYPE_INTEGER64,
                                                &valueInteger64,
                                                sizeof(valueInteger64),
                                                &bytesCopied);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("parameterGetValueFromDomainName() failed, ret %d", ret);
        return ret;
    }

    if (valueInteger64 != IntegerValue)
    {
        return SEOS_ERROR_GENERIC;
    }

    return SEOS_SUCCESS;
}

//------------------------------------------------------------------------------
seos_err_t verify_string_parameter(SeosConfigHandle* handle,
                                   const char* DomainName,
                                   const char* ParameterName,
                                   const char* StringValue,
                                   size_t parameterLength)
{
    seos_err_t ret;
    size_t bytesCopied;
    SeosConfigLib_DomainName domainName;
    SeosConfigLib_ParameterName parameterName;
    SeosConfigLib_Parameter parameter;
    char configString[SEOS_CONFIG_LIB_PARAMETER_MAX_STRING_LENGTH];
    SeosConfigHandle configHandle = *handle;

    ret = get_parameter_element(configHandle, DomainName, ParameterName, &domainName, &parameterName, &parameter);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("get_parameter_element() failed, ret %d", ret);
        return ret;
    }

    size_t parameterSize = seos_configuration_parameterGetSize(&parameter);
    if (parameterSize != parameterLength)
    {
        Debug_LOG_ERROR("retrieved string size does not match expected size for parameter %s", ParameterName);
        return SEOS_ERROR_GENERIC;
    }

    SeosConfigLib_ParameterType parameterType;
    seos_configuration_parameterGetType(&parameter, &parameterType);
    if (parameterType != SEOS_CONFIG_LIB_PARAMETER_TYPE_STRING)
    {
        Debug_LOG_ERROR("retrieved parameter does not match expected type");
        return SEOS_ERROR_CONFIG_TYPE_MISMATCH;
    }

    ret = seos_configuration_parameterGetValueAsString(configHandle,
                                                       &parameter,
                                                       configString,
                                                       sizeof(configString));
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("parameterGetValueAsString() failed, ret %d", ret);
        return ret;
    }

    ret = strcmp(configString, StringValue);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("strcmp() failed, ret %d", ret);
        return ret;
    }

    memset(configString,0,sizeof(configString));

    ret = seos_configuration_parameterGetValueFromDomainName(
                                                configHandle,
                                                &domainName,
                                                &parameterName,
                                                SEOS_CONFIG_LIB_PARAMETER_TYPE_STRING,
                                                configString,
                                                sizeof(configString),
                                                &bytesCopied);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("parameterGetValueFromDomainName() failed, ret %d", ret);
        return ret;
    }

    ret = strcmp(configString, StringValue);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("strcmp() failed, ret %d", ret);
        return ret;
    }

    return SEOS_SUCCESS;
}

//------------------------------------------------------------------------------
seos_err_t verify_blob_parameter(SeosConfigHandle* handle,
                                 const char* DomainName,
                                 const char* ParameterName,
                                 const char* BlobValue,
                                 size_t parameterLength)
{
    seos_err_t ret;
    size_t bytesCopied;
    SeosConfigLib_DomainName domainName;
    SeosConfigLib_ParameterName parameterName;
    SeosConfigLib_Parameter parameter;
    char configBlob[parameterLength];
    SeosConfigHandle configHandle = *handle;

    ret = get_parameter_element(configHandle, DomainName, ParameterName, &domainName, &parameterName, &parameter);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("get_parameter_element() failed, ret %d", ret);
        return ret;
    }

    size_t parameterSize = seos_configuration_parameterGetSize(&parameter);
    if (parameterSize != parameterLength)
    {
        Debug_LOG_ERROR("retrieved blob size does not match expected size");
        return SEOS_ERROR_GENERIC;
    }

    SeosConfigLib_ParameterType parameterType;
    seos_configuration_parameterGetType(&parameter, &parameterType);
    if (parameterType != SEOS_CONFIG_LIB_PARAMETER_TYPE_BLOB)
    {
        Debug_LOG_ERROR("retrieved parameter does not match expected type");
        return SEOS_ERROR_CONFIG_TYPE_MISMATCH;
    }

    ret = seos_configuration_parameterGetValueAsBlob(configHandle,
                                                       &parameter,
                                                       configBlob,
                                                       sizeof(configBlob));
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("parameterGetValueAsBlob() failed, ret %d", ret);
        return ret;
    }

    ret = memcmp(configBlob, BlobValue, parameterLength);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("memcmp() failed, ret %d", ret);
        return ret;
    }

    memset(configBlob,0,sizeof(configBlob));

    ret = seos_configuration_parameterGetValueFromDomainName(
                                                configHandle,
                                                &domainName,
                                                &parameterName,
                                                SEOS_CONFIG_LIB_PARAMETER_TYPE_BLOB,
                                                configBlob,
                                                sizeof(configBlob),
                                                &bytesCopied);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("parameterGetValueFromDomainName() failed, ret %d", ret);
        return ret;
    }

    ret = memcmp(configBlob, BlobValue, parameterLength);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("memcmp() failed, ret %d", ret);
        return ret;
    }

    return SEOS_SUCCESS;
}

//------------------------------------------------------------------------------
seos_err_t verify_parameter(SeosConfigHandle* handle,
                            const char* DomainName,
                            const char* ParameterName,
                            const char* parameterValue,
                            size_t parameterLength)
{
    seos_err_t ret;
    size_t bytesCopied;
    SeosConfigLib_DomainName domainName;
    SeosConfigLib_ParameterName parameterName;
    SeosConfigLib_Parameter parameter;
    char configBlob[parameterLength];
    SeosConfigHandle configHandle = *handle;

    ret = get_parameter_element(configHandle, DomainName, ParameterName, &domainName, &parameterName, &parameter);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("get_parameter_element() failed, ret %d", ret);
        return ret;
    }

    size_t parameterSize = seos_configuration_parameterGetSize(&parameter);
    if (parameterSize != parameterLength)
    {
        Debug_LOG_ERROR("retrieved blob size does not match expected size");
        return SEOS_ERROR_GENERIC;
    }

    SeosConfigLib_ParameterType parameterType;
    seos_configuration_parameterGetType(&parameter, &parameterType);

    ret = seos_configuration_parameterGetValue(configHandle,
                                               &parameter,
                                               configBlob,
                                               sizeof(configBlob),
                                               &bytesCopied);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("parameterGetValue() failed, ret %d", ret);
        return ret;
    }

    ret = memcmp(configBlob, parameterValue, parameterLength);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("memcmp() failed, ret %d", ret);
        return ret;
    }

    ret = seos_configuration_parameterGetValueFromDomainName(
                                                configHandle,
                                                &domainName,
                                                &parameterName,
                                                parameterType,
                                                configBlob,
                                                sizeof(configBlob),
                                                &bytesCopied);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("parameterGetValueFromDomainName() failed, ret %d", ret);
        return ret;
    }

    ret = memcmp(configBlob, parameterValue, parameterLength);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("memcmp() failed, ret %d", ret);
        return ret;
    }

    return SEOS_SUCCESS;
}

//------------------------------------------------------------------------------
seos_err_t set_integer32_parameter(SeosConfigHandle* handle,
                                   const char* DomainName,
                                   const char* ParameterName,
                                   const uint32_t IntegerValue)
{
    seos_err_t ret;

    SeosConfigHandle configHandle = *handle;
    SeosConfigLib_ParameterEnumerator parameterEnumerator = {0};

    ret = get_parameter_enumerator(configHandle,
                                   DomainName,
                                   ParameterName,
                                   &parameterEnumerator);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("get_parameter_enumerator() failed, ret %d", ret);
        return SEOS_ERROR_GENERIC;
    }

    ret = seos_configuration_parameterSetValueAsU32(configHandle,
                                                    &parameterEnumerator,
                                                    IntegerValue);
    if (ret < 0)
    {
        Debug_LOG_ERROR("seos_configuration_parameterSetValue() failed, ret %d", ret);
        // ToDo: seos_configuration_parameterSetValue() should return error codes
        //       about the actual problem, so we can return them
        return SEOS_ERROR_GENERIC;
    }

    return SEOS_SUCCESS;
}

//------------------------------------------------------------------------------
seos_err_t set_integer64_parameter(SeosConfigHandle* handle,
                                   const char* DomainName,
                                   const char* ParameterName,
                                   const uint64_t IntegerValue)
{
    seos_err_t ret;

    SeosConfigHandle configHandle = *handle;
    SeosConfigLib_ParameterEnumerator parameterEnumerator = {0};

    ret = get_parameter_enumerator(configHandle,
                                   DomainName,
                                   ParameterName,
                                   &parameterEnumerator);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("get_parameter_enumerator() failed, ret %d", ret);
        return SEOS_ERROR_GENERIC;
    }

    ret = seos_configuration_parameterSetValueAsU64(configHandle,
                                                    &parameterEnumerator,
                                                    IntegerValue);
    if (ret < 0)
    {
        Debug_LOG_ERROR("seos_configuration_parameterSetValue() failed, ret %d", ret);
        // ToDo: seos_configuration_parameterSetValue() should return error codes
        //       about the actual problem, so we can return them
        return SEOS_ERROR_GENERIC;
    }

    return SEOS_SUCCESS;
}

//------------------------------------------------------------------------------
seos_err_t set_string_parameter(SeosConfigHandle* handle,
                                   const char* DomainName,
                                   const char* ParameterName,
                                   const char* StringValue,
                                   size_t parameterLength)
{
    seos_err_t ret;

    SeosConfigHandle configHandle = *handle;
    SeosConfigLib_ParameterEnumerator parameterEnumerator = {0};

    ret = get_parameter_enumerator(configHandle,
                                   DomainName,
                                   ParameterName,
                                   &parameterEnumerator);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("get_parameter_enumerator() failed, ret %d", ret);
        return SEOS_ERROR_GENERIC;
    }

    ret = seos_configuration_parameterSetValueAsString(configHandle,
                                                    &parameterEnumerator,
                                                    SEOS_CONFIG_LIB_PARAMETER_TYPE_STRING,
                                                    StringValue,
                                                    parameterLength);
    if (ret < 0)
    {
        Debug_LOG_ERROR("seos_configuration_parameterSetValue() failed, ret %d", ret);
        // ToDo: seos_configuration_parameterSetValue() should return error codes
        //       about the actual problem, so we can return them
        return SEOS_ERROR_GENERIC;
    }

    return SEOS_SUCCESS;
}

//------------------------------------------------------------------------------
seos_err_t set_blob_parameter(SeosConfigHandle* handle,
                                   const char* DomainName,
                                   const char* ParameterName,
                                   const char* BlobValue,
                                   size_t parameterLength)
{
    seos_err_t ret;

    SeosConfigHandle configHandle = *handle;
    SeosConfigLib_ParameterEnumerator parameterEnumerator = {0};

    ret = get_parameter_enumerator(configHandle,
                                   DomainName,
                                   ParameterName,
                                   &parameterEnumerator);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("get_parameter_enumerator() failed, ret %d", ret);
        return SEOS_ERROR_GENERIC;
    }

    ret = seos_configuration_parameterSetValueAsBlob(configHandle,
                                                    &parameterEnumerator,
                                                    SEOS_CONFIG_LIB_PARAMETER_TYPE_BLOB,
                                                    BlobValue,
                                                    parameterLength);
    if (ret < 0)
    {
        Debug_LOG_ERROR("seos_configuration_parameterSetValue() failed, ret %d", ret);
        // ToDo: seos_configuration_parameterSetValue() should return error codes
        //       about the actual problem, so we can return them
        return SEOS_ERROR_GENERIC;
    }

    return SEOS_SUCCESS;
}

//------------------------------------------------------------------------------
seos_err_t set_parameter(SeosConfigHandle* handle,
                         const char* DomainName,
                         const char* ParameterName,
                         const void* parameterValue,
                         size_t parameterLength)
{
    seos_err_t ret;
    SeosConfigHandle configHandle = *handle;
    SeosConfigLib_ParameterEnumerator parameterEnumerator = {0};
    SeosConfigLib_DomainName domainName;
    SeosConfigLib_ParameterName parameterName;
    SeosConfigLib_Parameter parameter;

    ret = get_parameter_element(configHandle, DomainName, ParameterName, &domainName, &parameterName, &parameter);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("get_parameter_element() failed, ret %d", ret);
        return ret;
    }

    ret = get_parameter_enumerator(configHandle,
                                   DomainName,
                                   ParameterName,
                                   &parameterEnumerator);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("get_parameter_enumerator() failed, ret %d", ret);
        return SEOS_ERROR_GENERIC;
    }

    SeosConfigLib_ParameterType parameterType;
    seos_configuration_parameterGetType(&parameter, &parameterType);

    ret = seos_configuration_parameterSetValue(configHandle,
                                               &parameterEnumerator,
                                               parameterType,
                                               parameterValue,
                                               parameterLength);
    if (ret < 0)
    {
        Debug_LOG_ERROR("seos_configuration_parameterSetValue() failed, ret %d", ret);
        // ToDo: seos_configuration_parameterSetValue() should return error codes
        //       about the actual problem, so we can return them
        return SEOS_ERROR_GENERIC;
    }

    return SEOS_SUCCESS;
}