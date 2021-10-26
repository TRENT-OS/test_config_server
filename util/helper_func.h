/**
 * Copyright (C) 2020, HENSOLDT Cyber GmbH
 */

#pragma once

#include "OS_Error.h"
#include "OS_ConfigService.h"


void initializeName(char* buf, size_t bufSize, char const* name);

OS_Error_t
initializeDomainName(
    OS_ConfigServiceLibTypes_DomainName_t* domainName,
    char const* name);

OS_Error_t
initializeParameterName(
    OS_ConfigServiceLibTypes_ParameterName_t* parameterName,
    char const* name);

OS_Error_t
verify_integer32_parameter(
    OS_ConfigServiceHandle_t* handle,
    const char* DomainName,
    const char* ParameterName,
    const uint32_t IntegerValue);


OS_Error_t
verify_integer64_parameter(
    OS_ConfigServiceHandle_t* handle,
    const char* DomainName,
    const char* ParameterName,
    const uint64_t IntegerValue);

OS_Error_t
verify_string_parameter(
    OS_ConfigServiceHandle_t* handle,
    const char* DomainName,
    const char* ParameterName,
    const char* StringValue,
    size_t parameterLength);

OS_Error_t
verify_blob_parameter(
    OS_ConfigServiceHandle_t* handle,
    const char* DomainName,
    const char* ParameterName,
    const char* BlobValue,
    size_t parameterLength);

OS_Error_t
verify_parameter(
    OS_ConfigServiceHandle_t* handle,
    const char* DomainName,
    const char* ParameterName,
    const char* parameterValue,
    size_t parameterLength);

OS_Error_t
set_integer32_parameter(
    OS_ConfigServiceHandle_t* handle,
    const char* DomainName,
    const char* ParameterName,
    const uint32_t IntegerValue);

OS_Error_t
set_integer64_parameter(
    OS_ConfigServiceHandle_t* handle,
    const char* DomainName,
    const char* ParameterName,
    const uint64_t IntegerValue);

OS_Error_t
set_string_parameter(
    OS_ConfigServiceHandle_t* handle,
    const char* DomainName,
    const char* ParameterName,
    const char* StringValue,
    size_t parameterLength);

OS_Error_t
set_blob_parameter(
    OS_ConfigServiceHandle_t* handle,
    const char* DomainName,
    const char* ParameterName,
    const char* BlobValue,
    size_t parameterLength);

OS_Error_t
set_parameter(
    OS_ConfigServiceHandle_t* handle,
    const char* DomainName,
    const char* ParameterName,
    const void* parameterValue,
    size_t parameterLength);
