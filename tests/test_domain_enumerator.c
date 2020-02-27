/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "test_domain_enumerator.h"

// -----------------------------------------------------------------------------
void
TestDomainEnumerator_init_ok(
    SeosConfigHandle* handle)
{
    seos_err_t err;
    SeosConfigHandle configHandle = *handle;
    SeosConfigLib_DomainEnumerator domainEnumerator;

    err = seos_configuration_domainEnumeratorInit(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestDomainEnumerator_init_fail(
    SeosConfigHandle* handle)
{
    seos_err_t err;
    SeosConfigHandle configHandle;
    SeosConfigLib_DomainEnumerator domainEnumerator;

    // Uninitialized config handle
    err = seos_configuration_domainEnumeratorInit(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_INVALID_HANDLE == err, "err %d", err);

    // Empty domain enumerator
    configHandle = *handle;
    err = seos_configuration_domainEnumeratorInit(configHandle, NULL);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_INVALID_PARAMETER == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestDomainEnumerator_close_ok(
    SeosConfigHandle* handle)
{
    seos_err_t err;
    SeosConfigHandle configHandle = *handle;
    SeosConfigLib_DomainEnumerator domainEnumerator;

    err = seos_configuration_domainEnumeratorInit(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    err = seos_configuration_domainEnumeratorClose(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestDomainEnumerator_close_fail(
    SeosConfigHandle* handle)
{
    seos_err_t err;
    SeosConfigHandle configHandle = *handle;
    SeosConfigLib_DomainEnumerator domainEnumerator;

    // Uninitialized domain enumerator
    err = seos_configuration_domainEnumeratorClose(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_INVALID_PARAMETER == err, "err %d", err);

    // Initialize domain enumerator
    err = seos_configuration_domainEnumeratorInit(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    // Uninitialized config handle
    SeosConfigHandle uninitializedHandle;
    err = seos_configuration_domainEnumeratorClose(uninitializedHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_INVALID_HANDLE == err, "err %d", err);

    // Empty domain enumerator
    err = seos_configuration_domainEnumeratorClose(configHandle, NULL);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_INVALID_PARAMETER == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestDomainEnumerator_increment_ok(
    SeosConfigHandle* handle,
    const char* componentName,
    unsigned int maxDomainIndex)
{
    seos_err_t err;
    SeosConfigHandle configHandle = *handle;
    SeosConfigLib_DomainEnumerator domainEnumerator;

    err = seos_configuration_domainEnumeratorInit(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    for (int i = 0; i < (maxDomainIndex-1); i++)
    {
        err = seos_configuration_domainEnumeratorIncrement(configHandle, &domainEnumerator);
        Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);
        // Check if the index actually got incremented
        Debug_ASSERT_PRINTFLN((1+i) == domainEnumerator.index, "Index value: %d", domainEnumerator.index);
    }

    err = seos_configuration_domainEnumeratorClose(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    char handleKind[15];
    if (SEOS_CONFIG_HANDLE_KIND_RPC == seos_configuration_handle_getHandleKind(
            *handle))
    {
        initializeName(handleKind, sizeof(handleKind), "Rpc");
    }

    else if (SEOS_CONFIG_HANDLE_KIND_LOCAL == seos_configuration_handle_getHandleKind(
            *handle))
    {
        initializeName(handleKind, sizeof(handleKind), "Local");
    }

    Debug_LOG_INFO("->%s: %s HandleKind:%s OK\n", __func__, componentName, handleKind);
}

void
TestDomainEnumerator_increment_fail(
    SeosConfigHandle* handle)
{
    seos_err_t err;
    SeosConfigHandle configHandle = *handle;
    SeosConfigLib_DomainEnumerator domainEnumerator;

    // Uninitialized domain enumerator
    err = seos_configuration_domainEnumeratorIncrement(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_INVALID_PARAMETER == err, "err %d", err);
    // Make sure the index did not get incremented
    Debug_ASSERT_PRINTFLN(0 == domainEnumerator.index, "Index value: %d", domainEnumerator.index);

    // Initialize domain enumerator
    err = seos_configuration_domainEnumeratorInit(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    // Uninitialized config handle
    SeosConfigHandle uninitializedHandle;
    err = seos_configuration_domainEnumeratorIncrement(uninitializedHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_INVALID_HANDLE == err, "err %d", err);
    // Make sure the index did not get incremented
    Debug_ASSERT_PRINTFLN(0 == domainEnumerator.index, "Index value: %d", domainEnumerator.index);

    // Empty domain enumerator
    err = seos_configuration_domainEnumeratorIncrement(configHandle, NULL);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_INVALID_PARAMETER == err, "err %d", err);
    // Make sure the index did not get incremented
    Debug_ASSERT_PRINTFLN(0 == domainEnumerator.index, "Index value: %d", domainEnumerator.index);

    err = seos_configuration_domainEnumeratorClose(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestDomainEnumerator_reset_ok(
    SeosConfigHandle* handle,
    const char* componentName,
    unsigned int maxDomainIndex)
{
    seos_err_t err;
    SeosConfigHandle configHandle = *handle;
    SeosConfigLib_DomainEnumerator domainEnumerator;

    err = seos_configuration_domainEnumeratorInit(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    err = seos_configuration_domainEnumeratorIncrement(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);
    // Check if the index actually got incremented
    Debug_ASSERT_PRINTFLN(1 == domainEnumerator.index, "Index value: %d", domainEnumerator.index);

    err = seos_configuration_domainEnumeratorReset(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);
    // Check if the index actually got reset
    Debug_ASSERT_PRINTFLN(0 == domainEnumerator.index, "Index value: %d", domainEnumerator.index);

    for (int i = 0; i < (maxDomainIndex-1); i++)
    {
        err = seos_configuration_domainEnumeratorIncrement(configHandle, &domainEnumerator);
        Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);
        // Check if the index actually got incremented
        Debug_ASSERT_PRINTFLN((1+i) == domainEnumerator.index, "Index value: %d", domainEnumerator.index);
    }

    err = seos_configuration_domainEnumeratorReset(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);
    // Check if the index actually got reset
    Debug_ASSERT_PRINTFLN(0 == domainEnumerator.index, "Index value: %d", domainEnumerator.index);

    err = seos_configuration_domainEnumeratorClose(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    char handleKind[15];
    if (SEOS_CONFIG_HANDLE_KIND_RPC == seos_configuration_handle_getHandleKind(
            *handle))
    {
        initializeName(handleKind, sizeof(handleKind), "Rpc");
    }

    else if (SEOS_CONFIG_HANDLE_KIND_LOCAL == seos_configuration_handle_getHandleKind(
            *handle))
    {
        initializeName(handleKind, sizeof(handleKind), "Local");
    }

    Debug_LOG_INFO("->%s: %s HandleKind:%s OK\n", __func__, componentName, handleKind);
}

void
TestDomainEnumerator_reset_fail(
    SeosConfigHandle* handle)
{
    seos_err_t err;
    SeosConfigHandle configHandle = *handle;
    SeosConfigLib_DomainEnumerator domainEnumerator;

    // Uninitialized domain enumerator
    err = seos_configuration_domainEnumeratorReset(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_INVALID_PARAMETER == err, "err %d", err);

    // Initialize domain enumerator
    err = seos_configuration_domainEnumeratorInit(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    // Uninitialized config handle
    SeosConfigHandle uninitializedHandle;
    err = seos_configuration_domainEnumeratorReset(uninitializedHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_INVALID_HANDLE == err, "err %d", err);

    // Empty domain enumerator
    err = seos_configuration_domainEnumeratorReset(configHandle, NULL);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_INVALID_PARAMETER == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestDomainEnumerator_getElement_ok(
    SeosConfigHandle* handle)
{
    seos_err_t err;
    SeosConfigHandle configHandle = *handle;
    SeosConfigLib_DomainEnumerator domainEnumerator;
    SeosConfigLib_Domain           domain;

    err = seos_configuration_domainEnumeratorInit(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    err = seos_configuration_domainEnumeratorGetElement(
                                      configHandle, &domainEnumerator, &domain);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    err = seos_configuration_domainEnumeratorClose(
                                               configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestDomainEnumerator_getElement_fail(
    SeosConfigHandle* handle)
{
    seos_err_t err;
    SeosConfigHandle configHandle = *handle;
    SeosConfigLib_DomainEnumerator domainEnumerator;
    SeosConfigLib_Domain           domain;

    // Uninitialized domain enumerator
    err = seos_configuration_domainEnumeratorGetElement(configHandle,
                                                    &domainEnumerator, &domain);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_INVALID_PARAMETER == err, "err %d", err);

    // Initialize domain enumerator
    err = seos_configuration_domainEnumeratorInit(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    // Uninitialized config handle
    SeosConfigHandle uninitializedHandle;
    err = seos_configuration_domainEnumeratorGetElement(uninitializedHandle,
                                                    &domainEnumerator, &domain);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_INVALID_HANDLE == err, "err %d", err);

    // Empty domain enumerator
    err = seos_configuration_domainEnumeratorGetElement(configHandle, NULL, &domain);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_INVALID_PARAMETER == err, "err %d", err);

    // Empty domain
    err = seos_configuration_domainEnumeratorGetElement(configHandle,
                                                        &domainEnumerator, NULL);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_INVALID_PARAMETER == err, "err %d", err);

    err = seos_configuration_domainEnumeratorClose(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

// -----------------------------------------------------------------------------

void TestDomainEnumerator_testAll(SeosConfigHandle* handle,const char* componentName, unsigned int maxDomainIndex)
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