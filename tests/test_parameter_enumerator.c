/**
 * Copyright (C) 2020-2024, HENSOLDT Cyber GmbH
 * 
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * For commercial licensing, contact: info.cyber@hensoldt.net
 */

#include "test_parameter_enumerator.h"

#include "lib_macros/Test.h"

#include "util/helper_func.h"


// -----------------------------------------------------------------------------
void
test_ParameterEnumerator_init_pos(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator;

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorInit(
                     configHandle,
                     &domainEnumerator));

    TEST_SUCCESS(OS_ConfigService_parameterEnumeratorInit(
                     configHandle,
                     &domainEnumerator,
                     &parameterEnumerator));

    TEST_FINISH();
}

void
test_ParameterEnumerator_init_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator;

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorInit(
                     configHandle,
                     &domainEnumerator));

    // Uninitialized config handle
    OS_ConfigServiceHandle_t uninitializedHandle = { 0 };
    TEST_INVAL_HANDLE(OS_ConfigService_parameterEnumeratorInit(
                          uninitializedHandle,
                          &domainEnumerator,
                          &parameterEnumerator));

    // Empty domain enumerator
    TEST_INVAL_PARAM(OS_ConfigService_parameterEnumeratorInit(
                         configHandle,
                         NULL,
                         &parameterEnumerator));

    // Empty parameter enumerator
    configHandle = *handle;
    TEST_INVAL_PARAM(OS_ConfigService_parameterEnumeratorInit(
                         configHandle,
                         &domainEnumerator,
                         NULL));

    TEST_FINISH();
}

void
test_ParameterEnumerator_init_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator = { 0 };
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator = { 0 };

    TEST_INVAL_STATE(OS_ConfigService_parameterEnumeratorInit(
                         configHandle,
                         &domainEnumerator,
                         &parameterEnumerator));

    TEST_FINISH();
}

void
test_ParameterEnumerator_close_pos(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator;

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorInit(
                     configHandle,
                     &domainEnumerator));

    TEST_SUCCESS(OS_ConfigService_parameterEnumeratorInit(
                     configHandle,
                     &domainEnumerator,
                     &parameterEnumerator));

    // Close parameter enumerator
    TEST_SUCCESS(OS_ConfigService_parameterEnumeratorClose(
                     configHandle,
                     &parameterEnumerator));

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorClose(
                     configHandle,
                     &domainEnumerator));

    TEST_FINISH();
}

void
test_ParameterEnumerator_close_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator;

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorInit(
                     configHandle,
                     &domainEnumerator));

    TEST_SUCCESS(OS_ConfigService_parameterEnumeratorInit(
                     configHandle,
                     &domainEnumerator,
                     &parameterEnumerator));

    // Uninitialized config handle
    OS_ConfigServiceHandle_t uninitializedHandle = { 0 };
    TEST_INVAL_HANDLE(OS_ConfigService_parameterEnumeratorClose(
                          uninitializedHandle,
                          &parameterEnumerator));

    // Empty parameter enumerator
    TEST_INVAL_PARAM(OS_ConfigService_parameterEnumeratorClose(
                         configHandle,
                         NULL));

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorClose(
                     configHandle,
                     &domainEnumerator));

    TEST_FINISH();
}

void
test_ParameterEnumerator_close_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;

    TEST_INVAL_STATE(OS_ConfigService_domainEnumeratorClose(
                         configHandle,
                         &domainEnumerator));

    TEST_FINISH();
}

void
test_ParameterEnumerator_increment_pos(
    OS_ConfigServiceHandle_t* handle,
    const char* componentName,
    unsigned int maxDomainIndex,
    unsigned int maxParameterIndex)
{
    OS_ConfigServiceHandle_HandleKind_t handleKind =
        OS_ConfigServiceHandle_getHandleKind(*handle);

    TEST_START("i", handleKind, "s", componentName);

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator;
    unsigned int maxIndex = (maxParameterIndex / maxDomainIndex);

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorInit(
                     configHandle,
                     &domainEnumerator));

    TEST_SUCCESS(OS_ConfigService_parameterEnumeratorInit(
                     configHandle,
                     &domainEnumerator,
                     &parameterEnumerator));

    for (int i = 0; i < (maxIndex - 1); i++)
    {
        TEST_SUCCESS(OS_ConfigService_parameterEnumeratorIncrement(
                         configHandle,
                         &parameterEnumerator));

        // Check if the index actually got incremented
        TEST_TRUE((1 + i) == parameterEnumerator.index);
    }

    TEST_SUCCESS(OS_ConfigService_parameterEnumeratorClose(
                     configHandle,
                     &parameterEnumerator));

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorClose(
                     configHandle,
                     &domainEnumerator));

    TEST_FINISH();
}

void
test_ParameterEnumerator_increment_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator;

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorInit(
                     configHandle,
                     &domainEnumerator));

    TEST_SUCCESS(OS_ConfigService_parameterEnumeratorInit(
                     configHandle,
                     &domainEnumerator,
                     &parameterEnumerator));

    // Uninitialized config handle
    OS_ConfigServiceHandle_t uninitializedHandle = { 0 };
    TEST_INVAL_HANDLE(OS_ConfigService_parameterEnumeratorIncrement(
                          uninitializedHandle,
                          &parameterEnumerator));

    // Make sure the index did not get incremented
    TEST_TRUE(0 == parameterEnumerator.index);

    // Empty parameter enumerator
    TEST_INVAL_PARAM(OS_ConfigService_parameterEnumeratorIncrement(
                         configHandle,
                         NULL));

    // Make sure the index did not get incremented
    TEST_TRUE(0 == parameterEnumerator.index);

    TEST_SUCCESS(OS_ConfigService_parameterEnumeratorClose(
                     configHandle,
                     &parameterEnumerator));

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorClose(
                     configHandle,
                     &domainEnumerator));

    TEST_FINISH();
}

void
test_ParameterEnumerator_increment_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator;

    TEST_INVAL_STATE(OS_ConfigService_parameterEnumeratorIncrement(
                         configHandle,
                         &parameterEnumerator));

    TEST_FINISH();
}

void
test_ParameterEnumerator_reset_pos(
    OS_ConfigServiceHandle_t* handle,
    const char* componentName,
    unsigned int maxDomainIndex,
    unsigned int maxParameterIndex)
{
    OS_ConfigServiceHandle_HandleKind_t handleKind =
        OS_ConfigServiceHandle_getHandleKind(*handle);

    TEST_START("i", handleKind, "s", componentName);

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator;
    unsigned int maxIndex = (maxParameterIndex / maxDomainIndex);

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorInit(
                     configHandle,
                     &domainEnumerator));

    TEST_SUCCESS(OS_ConfigService_parameterEnumeratorInit(
                     configHandle,
                     &domainEnumerator,
                     &parameterEnumerator));

    // Increment parameter enumerator index
    TEST_SUCCESS(OS_ConfigService_parameterEnumeratorIncrement(
                     configHandle,
                     &parameterEnumerator));

    // Check if the index actually got incremented
    TEST_TRUE(1 == parameterEnumerator.index);

    TEST_SUCCESS(OS_ConfigService_parameterEnumeratorReset(
                     configHandle,
                     &parameterEnumerator));

    // Check if the index actually got reset
    TEST_TRUE(0 == parameterEnumerator.index);

    for (int i = 0; i < (maxIndex - 1); i++)
    {
        TEST_SUCCESS(OS_ConfigService_parameterEnumeratorIncrement(
                         configHandle,
                         &parameterEnumerator));

        // Check if the index actually got incremented
        TEST_TRUE((1 + i) == parameterEnumerator.index);
    }

    TEST_SUCCESS(OS_ConfigService_parameterEnumeratorReset(
                     configHandle,
                     &parameterEnumerator));

    // Check if the index actually got reset
    TEST_TRUE(0 == parameterEnumerator.index);

    TEST_SUCCESS(OS_ConfigService_parameterEnumeratorClose(
                     configHandle,
                     &parameterEnumerator));

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorClose(
                     configHandle,
                     &domainEnumerator));

    TEST_FINISH();
}

void
test_ParameterEnumerator_reset_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator;

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorInit(
                     configHandle,
                     &domainEnumerator));

    TEST_SUCCESS(OS_ConfigService_parameterEnumeratorInit(
                     configHandle,
                     &domainEnumerator,
                     &parameterEnumerator));

    // Uninitialized config handle
    OS_ConfigServiceHandle_t uninitializedHandle = { 0 };
    TEST_INVAL_HANDLE(OS_ConfigService_parameterEnumeratorReset(
                          uninitializedHandle,
                          &parameterEnumerator));

    // Empty parameter enumerator
    TEST_INVAL_PARAM(OS_ConfigService_parameterEnumeratorReset(
                         configHandle,
                         NULL));

    TEST_SUCCESS(OS_ConfigService_parameterEnumeratorClose(
                     configHandle,
                     &parameterEnumerator));

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorClose(
                     configHandle,
                     &domainEnumerator));

    TEST_FINISH();
}

void
test_ParameterEnumerator_reset_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator;

    TEST_INVAL_STATE(OS_ConfigService_parameterEnumeratorReset(
                         configHandle,
                         &parameterEnumerator));

    TEST_FINISH();
}

void
test_ParameterEnumerator_getElement_pos(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t    domainEnumerator;
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator;
    OS_ConfigServiceLibTypes_Parameter_t           parameter;

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorInit(
                     configHandle,
                     &domainEnumerator));

    TEST_SUCCESS(OS_ConfigService_parameterEnumeratorInit(
                     configHandle,
                     &domainEnumerator,
                     &parameterEnumerator));

    //Retrieve parameter for parameter enumerator
    TEST_SUCCESS(OS_ConfigService_parameterEnumeratorGetElement(
                     configHandle,
                     &parameterEnumerator,
                     &parameter));

    TEST_SUCCESS(OS_ConfigService_parameterEnumeratorClose(
                     configHandle,
                     &parameterEnumerator));

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorClose(
                     configHandle,
                     &domainEnumerator));

    TEST_FINISH();
}

void
test_ParameterEnumerator_getElement_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t    domainEnumerator;
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator;
    OS_ConfigServiceLibTypes_Parameter_t           parameter;

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorInit(
                     configHandle,
                     &domainEnumerator));

    TEST_SUCCESS(OS_ConfigService_parameterEnumeratorInit(
                     configHandle,
                     &domainEnumerator,
                     &parameterEnumerator));

    // Uninitialized config handle
    OS_ConfigServiceHandle_t uninitializedHandle = { 0 };
    TEST_INVAL_HANDLE(OS_ConfigService_parameterEnumeratorGetElement(
                          uninitializedHandle,
                          &parameterEnumerator,
                          &parameter));

    // Emtpy parameter enumerator
    TEST_INVAL_PARAM(OS_ConfigService_parameterEnumeratorGetElement(
                         configHandle,
                         NULL,
                         &parameter));

    // Empty parameter
    TEST_INVAL_PARAM(OS_ConfigService_parameterEnumeratorGetElement(
                         uninitializedHandle,
                         &parameterEnumerator,
                         NULL));

    TEST_SUCCESS(OS_ConfigService_parameterEnumeratorClose(
                     configHandle,
                     &parameterEnumerator));

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorClose(
                     configHandle,
                     &domainEnumerator));

    TEST_FINISH();
}

void
test_ParameterEnumerator_getElement_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator = { 0 };
    OS_ConfigServiceLibTypes_Parameter_t           parameter = { 0 };

    TEST_INVAL_STATE(OS_ConfigService_parameterEnumeratorGetElement(
                         configHandle,
                         &parameterEnumerator,
                         &parameter));

    TEST_FINISH();
}

// -----------------------------------------------------------------------------

void test_ParameterEnumerator_testAll(
    OS_ConfigServiceHandle_t* handle,
    const char* componentName,
    unsigned int maxDomainIndex,
    unsigned int maxParameterIndex)
{
    Debug_LOG_DEBUG("Executing Test Parameter Enumerator tests");

    test_ParameterEnumerator_init_pos(handle);
    test_ParameterEnumerator_init_neg(handle);

    test_ParameterEnumerator_close_pos(handle);
    test_ParameterEnumerator_close_neg(handle);

    test_ParameterEnumerator_increment_pos(handle, componentName, maxDomainIndex,
                                           maxParameterIndex);
    test_ParameterEnumerator_increment_neg(handle);

    test_ParameterEnumerator_reset_pos(handle, componentName, maxDomainIndex,
                                       maxParameterIndex);
    test_ParameterEnumerator_reset_neg(handle);

    test_ParameterEnumerator_getElement_pos(handle);
    test_ParameterEnumerator_getElement_neg(handle);
}
