/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "test_domain_enumerator.h"

#include "util/TestMacros.h"

#include "util/helper_func.h"


// -----------------------------------------------------------------------------
void
test_DomainEnumerator_init_pos(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorInit(
                    configHandle,
                    &domainEnumerator));

    TEST_FINISH();
}

void
test_DomainEnumerator_init_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceHandle_t configHandle = { 0 };
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;

    // Uninitialized config handle
    TEST_INVAL_HANDLE(OS_ConfigService_domainEnumeratorInit(
                        configHandle,
                        &domainEnumerator));

    // Empty domain enumerator
    configHandle = *handle;
    TEST_INVAL_PARAM(OS_ConfigService_domainEnumeratorInit(
                        configHandle,
                        NULL));

    TEST_FINISH();
}

void
test_DomainEnumerator_init_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceHandle_t configHandle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t enumerator;

    configHandle = *handle;
    TEST_INVAL_STATE(OS_ConfigService_domainEnumeratorInit(
                        configHandle,
                        &enumerator));

    TEST_FINISH();
}

void
test_DomainEnumerator_close_pos(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorInit(
                    configHandle,
                    &domainEnumerator));

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorClose(
                    configHandle,
                    &domainEnumerator));

    TEST_FINISH();
}

void
test_DomainEnumerator_close_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;

    // Uninitialized domain enumerator
    TEST_INVAL_PARAM(OS_ConfigService_domainEnumeratorClose(
                        configHandle,
                        &domainEnumerator));

    // Initialize domain enumerator
    TEST_SUCCESS(OS_ConfigService_domainEnumeratorInit(
                        configHandle,
                        &domainEnumerator));

    // Uninitialized config handle
    OS_ConfigServiceHandle_t uninitializedHandle = { 0 };
    TEST_INVAL_HANDLE(OS_ConfigService_domainEnumeratorClose(
                        uninitializedHandle,
                        &domainEnumerator));

    // Empty domain enumerator
    TEST_INVAL_PARAM(OS_ConfigService_domainEnumeratorClose(
                        configHandle,
                        NULL));

    TEST_FINISH();
}

void
test_DomainEnumerator_close_no_server_init_neg(
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
test_DomainEnumerator_increment_pos(
    OS_ConfigServiceHandle_t* handle,
    const char* componentName,
    unsigned int maxDomainIndex)
{
    OS_ConfigServiceHandle_HandleKind_t handleKind =
        OS_ConfigServiceHandle_getHandleKind(*handle);

    TEST_START(handleKind, componentName);

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorInit(
                    configHandle,
                    &domainEnumerator));

    for (int i = 0; i < (maxDomainIndex-1); i++)
    {
        TEST_SUCCESS(OS_ConfigService_domainEnumeratorIncrement(
                        configHandle,
                        &domainEnumerator));

        // Check if the index actually got incremented
        TEST_TRUE((1+i) == domainEnumerator.index);
    }

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorClose(
                    configHandle,
                    &domainEnumerator));

    TEST_FINISH();
}

void
test_DomainEnumerator_increment_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;

    // Uninitialized domain enumerator
    TEST_INVAL_PARAM(OS_ConfigService_domainEnumeratorIncrement(
                        configHandle,
                        &domainEnumerator));

    // Make sure the index did not get incremented
    TEST_TRUE(0 == domainEnumerator.index);

    // Initialize domain enumerator
    TEST_SUCCESS(OS_ConfigService_domainEnumeratorInit(
                        configHandle,
                        &domainEnumerator));

    // Uninitialized config handle
    OS_ConfigServiceHandle_t uninitializedHandle = { 0 };
    TEST_INVAL_HANDLE(OS_ConfigService_domainEnumeratorIncrement(
                        uninitializedHandle,
                        &domainEnumerator));

    // Make sure the index did not get incremented
    TEST_TRUE(0 == domainEnumerator.index);

    // Empty domain enumerator
    TEST_INVAL_PARAM(OS_ConfigService_domainEnumeratorIncrement(
                        configHandle,
                        NULL));

    // Make sure the index did not get incremented
    TEST_TRUE(0 == domainEnumerator.index);

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorClose(
                        configHandle,
                        &domainEnumerator));

    TEST_FINISH();
}

void
test_DomainEnumerator_increment_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;

    TEST_INVAL_STATE(OS_ConfigService_domainEnumeratorIncrement(
                        configHandle,
                        &domainEnumerator));

    TEST_FINISH();
}

void
test_DomainEnumerator_reset_pos(
    OS_ConfigServiceHandle_t* handle,
    const char* componentName,
    unsigned int maxDomainIndex)
{
    OS_ConfigServiceHandle_HandleKind_t handleKind =
        OS_ConfigServiceHandle_getHandleKind(*handle);

    TEST_START(handleKind, componentName);

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorInit(
                    configHandle,
                    &domainEnumerator));

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorIncrement(
                    configHandle,
                    &domainEnumerator));

    // Check if the index actually got incremented
    TEST_TRUE(1 == domainEnumerator.index);

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorReset(
                    configHandle,
                    &domainEnumerator));

    // Check if the index actually got reset
    TEST_TRUE(0 == domainEnumerator.index);

    for (int i = 0; i < (maxDomainIndex-1); i++)
    {
        TEST_SUCCESS(OS_ConfigService_domainEnumeratorIncrement(
                        configHandle,
                        &domainEnumerator));

        // Check if the index actually got incremented
        TEST_TRUE((1+i) == domainEnumerator.index);
    }

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorReset(
                    configHandle,
                    &domainEnumerator));

    // Check if the index actually got reset
    TEST_TRUE(0 == domainEnumerator.index);

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorClose(
                    configHandle,
                    &domainEnumerator));

    TEST_FINISH();
}

void
test_DomainEnumerator_reset_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;

    // Uninitialized domain enumerator
    TEST_INVAL_PARAM(OS_ConfigService_domainEnumeratorReset(
                        configHandle,
                        &domainEnumerator));

    // Initialize domain enumerator
    TEST_SUCCESS(OS_ConfigService_domainEnumeratorInit(
                        configHandle,
                        &domainEnumerator));

    // Uninitialized config handle
    OS_ConfigServiceHandle_t uninitializedHandle = { 0 };
    TEST_INVAL_HANDLE(OS_ConfigService_domainEnumeratorReset(
                        uninitializedHandle,
                        &domainEnumerator));

    // Empty domain enumerator
    TEST_INVAL_PARAM(OS_ConfigService_domainEnumeratorReset(
                        configHandle,
                        NULL));

    TEST_FINISH();
}

void
test_DomainEnumerator_reset_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;

    TEST_INVAL_STATE(OS_ConfigService_domainEnumeratorReset(
                        configHandle,
                        &domainEnumerator));

    TEST_FINISH();
}

void
test_DomainEnumerator_getElement_pos(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;
    OS_ConfigServiceLibTypes_Domain_t           domain;

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorInit(
                    configHandle,
                    &domainEnumerator));

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorGetElement(
                    configHandle,
                    &domainEnumerator,
                    &domain));

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorClose(
                    configHandle,
                    &domainEnumerator));

    TEST_FINISH();
}

void
test_DomainEnumerator_getElement_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator = { 0 };
    OS_ConfigServiceLibTypes_Domain_t           domain;

    // Uninitialized domain enumerator
    TEST_INVAL_PARAM(OS_ConfigService_domainEnumeratorGetElement(
                        configHandle,
                        &domainEnumerator,
                        &domain));

    // Initialize domain enumerator
    TEST_SUCCESS(OS_ConfigService_domainEnumeratorInit(
                        configHandle,
                        &domainEnumerator));

    // Uninitialized config handle
    OS_ConfigServiceHandle_t uninitializedHandle = { 0 };
    TEST_INVAL_HANDLE(OS_ConfigService_domainEnumeratorGetElement(
                        uninitializedHandle,
                        &domainEnumerator,
                        &domain));

    // Empty domain enumerator
    TEST_INVAL_PARAM(OS_ConfigService_domainEnumeratorGetElement(
                        configHandle,
                        NULL,
                        &domain));

    // Empty domain
    TEST_INVAL_PARAM(OS_ConfigService_domainEnumeratorGetElement(
                        configHandle,
                        &domainEnumerator,
                        NULL));

    TEST_SUCCESS(OS_ConfigService_domainEnumeratorClose(
                        configHandle,
                        &domainEnumerator));

    TEST_FINISH();
}

void
test_DomainEnumerator_getElement_no_server_init_neg(
    OS_ConfigServiceHandle_t* handle)
{
    TEST_START();

    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator = { 0 };
    OS_ConfigServiceLibTypes_Domain_t           domain = { 0 };

    TEST_INVAL_STATE(OS_ConfigService_domainEnumeratorGetElement(
                        configHandle,
                        &domainEnumerator,
                        &domain));

    TEST_FINISH();
}

// -----------------------------------------------------------------------------

void test_DomainEnumerator_testAll(OS_ConfigServiceHandle_t* handle,const char* componentName, unsigned int maxDomainIndex)
{
    Debug_LOG_DEBUG("Executing Test Domain Enumerator tests");

    test_DomainEnumerator_init_pos(handle);
    test_DomainEnumerator_init_neg(handle);

    test_DomainEnumerator_close_pos(handle);
    test_DomainEnumerator_close_neg(handle);

    test_DomainEnumerator_increment_pos(handle, componentName, maxDomainIndex);
    test_DomainEnumerator_increment_neg(handle);

    test_DomainEnumerator_reset_pos(handle, componentName, maxDomainIndex);
    test_DomainEnumerator_reset_neg(handle);

    test_DomainEnumerator_getElement_pos(handle);
    test_DomainEnumerator_getElement_neg(handle);
}
