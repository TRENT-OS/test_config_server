/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "OS_ConfigService.h"



// -----------------------------------------------------------------------------
void test_ParameterReadAccessRight_pos(OS_ConfigServiceHandle_t* handle,
                                     const char* domainName,
                                     const char* componentName,
                                     const char* parameterName,
                                     const char* parameterValue,
                                     size_t parameterLength);

void test_ParameterWriteAccessRight_pos(OS_ConfigServiceHandle_t* handle,
                                      const char* domainName,
                                      const char* componentName,
                                      const char* parameterName,
                                      const void* parameterValue,
                                      size_t parameterSize);
