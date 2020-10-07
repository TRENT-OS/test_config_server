/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "test_domain_enumerator.h"

// -----------------------------------------------------------------------------
void
TestDomainEnumerator_init_ok(
    OS_ConfigServiceHandle_t* handle)
{
    OS_Error_t err;
    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;

    err = OS_ConfigService_domainEnumeratorInit(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestDomainEnumerator_init_fail(
    OS_ConfigServiceHandle_t* handle)
{
    OS_Error_t err;
    OS_ConfigServiceHandle_t configHandle = { 0 };
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;

    // Uninitialized config handle
    err = OS_ConfigService_domainEnumeratorInit(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_HANDLE == err, "err %d", err);

    // Empty domain enumerator
    configHandle = *handle;
    err = OS_ConfigService_domainEnumeratorInit(configHandle, NULL);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_PARAMETER == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestDomainEnumerator_close_ok(
    OS_ConfigServiceHandle_t* handle)
{
    OS_Error_t err;
    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;

    err = OS_ConfigService_domainEnumeratorInit(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    err = OS_ConfigService_domainEnumeratorClose(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestDomainEnumerator_close_fail(
    OS_ConfigServiceHandle_t* handle)
{
    OS_Error_t err;
    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;

    // Uninitialized domain enumerator
    err = OS_ConfigService_domainEnumeratorClose(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_PARAMETER == err, "err %d", err);

    // Initialize domain enumerator
    err = OS_ConfigService_domainEnumeratorInit(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    // Uninitialized config handle
    OS_ConfigServiceHandle_t uninitializedHandle = { 0 };
    err = OS_ConfigService_domainEnumeratorClose(uninitializedHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_HANDLE == err, "err %d", err);

    // Empty domain enumerator
    err = OS_ConfigService_domainEnumeratorClose(configHandle, NULL);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_PARAMETER == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestDomainEnumerator_increment_ok(
    OS_ConfigServiceHandle_t* handle,
    const char* componentName,
    unsigned int maxDomainIndex)
{
    OS_Error_t err;
    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;

    err = OS_ConfigService_domainEnumeratorInit(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    for (int i = 0; i < (maxDomainIndex-1); i++)
    {
        err = OS_ConfigService_domainEnumeratorIncrement(configHandle, &domainEnumerator);
        Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);
        // Check if the index actually got incremented
        Debug_ASSERT_PRINTFLN((1+i) == domainEnumerator.index, "Index value: %d", domainEnumerator.index);
    }

    err = OS_ConfigService_domainEnumeratorClose(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    char handleKind[15];
    if (OS_CONFIG_HANDLE_KIND_RPC == OS_ConfigServiceHandle_getHandleKind(
            *handle))
    {
        initializeName(handleKind, sizeof(handleKind), "Rpc");
    }

    else if (OS_CONFIG_HANDLE_KIND_LOCAL == OS_ConfigServiceHandle_getHandleKind(
            *handle))
    {
        initializeName(handleKind, sizeof(handleKind), "Local");
    }

    Debug_LOG_INFO("->%s: %s HandleKind:%s OK\n", __func__, componentName, handleKind);
}

void
TestDomainEnumerator_increment_fail(
    OS_ConfigServiceHandle_t* handle)
{
    OS_Error_t err;
    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;

    // Uninitialized domain enumerator
    err = OS_ConfigService_domainEnumeratorIncrement(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_PARAMETER == err, "err %d", err);
    // Make sure the index did not get incremented
    Debug_ASSERT_PRINTFLN(0 == domainEnumerator.index, "Index value: %d", domainEnumerator.index);

    // Initialize domain enumerator
    err = OS_ConfigService_domainEnumeratorInit(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    // Uninitialized config handle
    OS_ConfigServiceHandle_t uninitializedHandle = { 0 };
    err = OS_ConfigService_domainEnumeratorIncrement(uninitializedHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_HANDLE == err, "err %d", err);
    // Make sure the index did not get incremented
    Debug_ASSERT_PRINTFLN(0 == domainEnumerator.index, "Index value: %d", domainEnumerator.index);

    // Empty domain enumerator
    err = OS_ConfigService_domainEnumeratorIncrement(configHandle, NULL);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_PARAMETER == err, "err %d", err);
    // Make sure the index did not get incremented
    Debug_ASSERT_PRINTFLN(0 == domainEnumerator.index, "Index value: %d", domainEnumerator.index);

    err = OS_ConfigService_domainEnumeratorClose(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestDomainEnumerator_reset_ok(
    OS_ConfigServiceHandle_t* handle,
    const char* componentName,
    unsigned int maxDomainIndex)
{
    OS_Error_t err;
    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;

    err = OS_ConfigService_domainEnumeratorInit(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    err = OS_ConfigService_domainEnumeratorIncrement(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);
    // Check if the index actually got incremented
    Debug_ASSERT_PRINTFLN(1 == domainEnumerator.index, "Index value: %d", domainEnumerator.index);

    err = OS_ConfigService_domainEnumeratorReset(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);
    // Check if the index actually got reset
    Debug_ASSERT_PRINTFLN(0 == domainEnumerator.index, "Index value: %d", domainEnumerator.index);

    for (int i = 0; i < (maxDomainIndex-1); i++)
    {
        err = OS_ConfigService_domainEnumeratorIncrement(configHandle, &domainEnumerator);
        Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);
        // Check if the index actually got incremented
        Debug_ASSERT_PRINTFLN((1+i) == domainEnumerator.index, "Index value: %d", domainEnumerator.index);
    }

    err = OS_ConfigService_domainEnumeratorReset(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);
    // Check if the index actually got reset
    Debug_ASSERT_PRINTFLN(0 == domainEnumerator.index, "Index value: %d", domainEnumerator.index);

    err = OS_ConfigService_domainEnumeratorClose(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    char handleKind[15];
    if (OS_CONFIG_HANDLE_KIND_RPC == OS_ConfigServiceHandle_getHandleKind(
            *handle))
    {
        initializeName(handleKind, sizeof(handleKind), "Rpc");
    }

    else if (OS_CONFIG_HANDLE_KIND_LOCAL == OS_ConfigServiceHandle_getHandleKind(
            *handle))
    {
        initializeName(handleKind, sizeof(handleKind), "Local");
    }

    Debug_LOG_INFO("->%s: %s HandleKind:%s OK\n", __func__, componentName, handleKind);
}

void
TestDomainEnumerator_reset_fail(
    OS_ConfigServiceHandle_t* handle)
{
    OS_Error_t err;
    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;

    // Uninitialized domain enumerator
    err = OS_ConfigService_domainEnumeratorReset(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_PARAMETER == err, "err %d", err);

    // Initialize domain enumerator
    err = OS_ConfigService_domainEnumeratorInit(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    // Uninitialized config handle
    OS_ConfigServiceHandle_t uninitializedHandle = { 0 };
    err = OS_ConfigService_domainEnumeratorReset(uninitializedHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_HANDLE == err, "err %d", err);

    // Empty domain enumerator
    err = OS_ConfigService_domainEnumeratorReset(configHandle, NULL);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_PARAMETER == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestDomainEnumerator_getElement_ok(
    OS_ConfigServiceHandle_t* handle)
{
    OS_Error_t err;
    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;
    OS_ConfigServiceLibTypes_Domain_t           domain;

    err = OS_ConfigService_domainEnumeratorInit(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    err = OS_ConfigService_domainEnumeratorGetElement(
                                      configHandle, &domainEnumerator, &domain);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    err = OS_ConfigService_domainEnumeratorClose(
                                               configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestDomainEnumerator_getElement_fail(
    OS_ConfigServiceHandle_t* handle)
{
    OS_Error_t err;
    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator = { 0 };
    OS_ConfigServiceLibTypes_Domain_t           domain;

    // Uninitialized domain enumerator
    err = OS_ConfigService_domainEnumeratorGetElement(configHandle,
                                                    &domainEnumerator, &domain);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_PARAMETER == err, "err %d", err);

    // Initialize domain enumerator
    err = OS_ConfigService_domainEnumeratorInit(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    // Uninitialized config handle
    OS_ConfigServiceHandle_t uninitializedHandle = { 0 };
    err = OS_ConfigService_domainEnumeratorGetElement(uninitializedHandle,
                                                    &domainEnumerator, &domain);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_HANDLE == err, "err %d", err);

    // Empty domain enumerator
    err = OS_ConfigService_domainEnumeratorGetElement(configHandle, NULL, &domain);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_PARAMETER == err, "err %d", err);

    // Empty domain
    err = OS_ConfigService_domainEnumeratorGetElement(configHandle,
                                                        &domainEnumerator, NULL);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_PARAMETER == err, "err %d", err);

    err = OS_ConfigService_domainEnumeratorClose(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

// -----------------------------------------------------------------------------

void TestDomainEnumerator_testAll(OS_ConfigServiceHandle_t* handle,const char* componentName, unsigned int maxDomainIndex)
{
    Debug_LOG_DEBUG("Executing Test Domain Enumerator tests");

    TestDomainEnumerator_init_ok(handle);
    TestDomainEnumerator_init_fail(handle);

    TestDomainEnumerator_close_ok(handle);
    TestDomainEnumerator_close_fail(handle);

    TestDomainEnumerator_increment_ok(handle, componentName, maxDomainIndex);
    TestDomainEnumerator_increment_fail(handle);

    TestDomainEnumerator_reset_ok(handle, componentName, maxDomainIndex);
    TestDomainEnumerator_reset_fail(handle);

    TestDomainEnumerator_getElement_ok(handle);
    TestDomainEnumerator_getElement_fail(handle);
}