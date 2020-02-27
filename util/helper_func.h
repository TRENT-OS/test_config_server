/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#pragma once

#include "SeosConfigLib.h"
#include "SeosConfigBackend.h"

#include "seos_config_client.h"


void initializeName(char* buf, size_t bufSize, char const* name);

seos_err_t
seos_configuration_initializeDomainName(SeosConfigLib_DomainName* domainName,
                                        char const* name);

seos_err_t
seos_configuration_initializeParameterName(SeosConfigLib_ParameterName* parameterName,
                                           char const* name);

seos_err_t
verify_integer32_parameter(SeosConfigHandle* handle,
                           const char* DomainName,
                           const char* ParameterName,
                           const uint32_t IntegerValue);


seos_err_t
verify_integer64_parameter(SeosConfigHandle* handle,
                           const char* DomainName,
                           const char* ParameterName,
                           const uint64_t IntegerValue);

seos_err_t
verify_string_parameter(SeosConfigHandle* handle,
                        const char* DomainName,
                        const char* ParameterName,
                        const char* StringValue,
                        size_t parameterLength);

seos_err_t
verify_blob_parameter(SeosConfigHandle* handle,
                      const char* DomainName,
                      const char* ParameterName,
                      const char* BlobValue,
                      size_t parameterLength);

seos_err_t
verify_parameter(SeosConfigHandle* handle,
                 const char* DomainName,
                 const char* ParameterName,
                 const char* parameterValue,
                 size_t parameterLength);

seos_err_t
set_integer32_parameter(SeosConfigHandle* handle,
                        const char* DomainName,
                        const char* ParameterName,
                        const uint32_t IntegerValue);

seos_err_t
set_integer64_parameter(SeosConfigHandle* handle,
                        const char* DomainName,
                        const char* ParameterName,
                        const uint64_t IntegerValue);

seos_err_t
set_string_parameter(SeosConfigHandle* handle,
                     const char* DomainName,
                     const char* ParameterName,
                     const char* StringValue,
                     size_t parameterLength);

seos_err_t
set_blob_parameter(SeosConfigHandle* handle,
                   const char* DomainName,
                   const char* ParameterName,
                   const char* BlobValue,
                   size_t parameterLength);

seos_err_t
set_parameter(SeosConfigHandle* handle,
              const char* DomainName,
              const char* ParameterName,
              const void* parameterValue,
              size_t parameterLength);