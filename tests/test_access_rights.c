/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "test_create_handle.h"

#include "LibMacros/Test.h"

#include "util/helper_func.h"

// -----------------------------------------------------------------------------
void
test_ParameterReadAccessRight_pos(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const char* parameterValue,
    size_t parameterLength)
{
    OS_ConfigServiceHandle_HandleKind_t handleKind =
        OS_ConfigServiceHandle_getHandleKind(*handle);

    TEST_START("i", handleKind, "s", componentName);

    TEST_CFG_PARAM_NOT_FOUND(
        verify_parameter(
            handle,
            domainName,
            parameterName,
            parameterValue,
            parameterLength));

    TEST_FINISH();
}

void
test_ParameterWriteAccessRight_pos(
    OS_ConfigServiceHandle_t* handle,
    const char* domainName,
    const char* componentName,
    const char* parameterName,
    const void* parameterValue,
    size_t parameterSize)
{
    OS_ConfigServiceHandle_HandleKind_t handleKind =
        OS_ConfigServiceHandle_getHandleKind(*handle);

    TEST_START("i", handleKind, "s", componentName);

    TEST_GENERIC(set_parameter(
                     handle,
                     domainName,
                     parameterName,
                     parameterValue,
                     parameterSize));

    TEST_FINISH();
}
