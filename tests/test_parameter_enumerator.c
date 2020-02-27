/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "test_parameter_enumerator.h"

// -----------------------------------------------------------------------------
void
TestParameterEnumerator_init_ok(
    SeosConfigHandle* handle)
{
    seos_err_t err;
    SeosConfigHandle configHandle = *handle;
    SeosConfigLib_DomainEnumerator domainEnumerator;
    SeosConfigLib_ParameterEnumerator parameterEnumerator;

    err = seos_configuration_domainEnumeratorInit(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    err = seos_configuration_parameterEnumeratorInit(configHandle,
                                                    &domainEnumerator,
                                                    &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestParameterEnumerator_init_fail(
    SeosConfigHandle* handle)
{
    seos_err_t err;
    SeosConfigHandle configHandle = *handle;
    SeosConfigLib_DomainEnumerator domainEnumerator;
    SeosConfigLib_ParameterEnumerator parameterEnumerator;

    err = seos_configuration_domainEnumeratorInit(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    // Uninitialized config handle
    SeosConfigHandle uninitializedHandle;
    err = seos_configuration_parameterEnumeratorInit(uninitializedHandle,
                                                    &domainEnumerator,
                                                    &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_INVALID_HANDLE == err, "err %d", err);

    // Empty domain enumerator
    err = seos_configuration_parameterEnumeratorInit(configHandle,
                                                    NULL, &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_INVALID_PARAMETER == err, "err %d", err);

    // Empty parameter enumerator
    configHandle = *handle;
    err = seos_configuration_parameterEnumeratorInit(configHandle,
                                                    &domainEnumerator, NULL);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_INVALID_PARAMETER == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestParameterEnumerator_close_ok(
    SeosConfigHandle* handle)
{
    seos_err_t err;
    SeosConfigHandle configHandle = *handle;
    SeosConfigLib_DomainEnumerator domainEnumerator;
    SeosConfigLib_ParameterEnumerator parameterEnumerator;

    err = seos_configuration_domainEnumeratorInit(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    err = seos_configuration_parameterEnumeratorInit(configHandle,
                                                    &domainEnumerator,
                                                    &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    // Close parameter enumerator
    err = seos_configuration_parameterEnumeratorClose(configHandle,
                                                    &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    err = seos_configuration_domainEnumeratorClose(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestParameterEnumerator_close_fail(
    SeosConfigHandle* handle)
{
    seos_err_t err;
    SeosConfigHandle configHandle = *handle;
    SeosConfigLib_DomainEnumerator domainEnumerator;
    SeosConfigLib_ParameterEnumerator parameterEnumerator;

    err = seos_configuration_domainEnumeratorInit(configHandle,
                                                    &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    err = seos_configuration_parameterEnumeratorInit(configHandle,
                                                    &domainEnumerator,
                                                    &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    // Uninitialized config handle
    SeosConfigHandle uninitializedHandle;
    err = seos_configuration_parameterEnumeratorClose(uninitializedHandle,
                                                         &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_INVALID_HANDLE == err, "err %d", err);

    // Empty parameter enumerator
    err = seos_configuration_parameterEnumeratorClose(configHandle, NULL);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_INVALID_PARAMETER == err, "err %d", err);

    err = seos_configuration_domainEnumeratorClose(configHandle,
                                                          &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestParameterEnumerator_increment_ok(SeosConfigHandle* handle,
                                     const char* componentName,
                                     unsigned int maxDomainIndex,
                                     unsigned int maxParameterIndex)
{
    seos_err_t err;
    SeosConfigHandle configHandle = *handle;
    SeosConfigLib_DomainEnumerator domainEnumerator;
    SeosConfigLib_ParameterEnumerator parameterEnumerator;
    unsigned int maxIndex = (maxParameterIndex / maxDomainIndex);

    err = seos_configuration_domainEnumeratorInit(configHandle,
                                                    &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    err = seos_configuration_parameterEnumeratorInit(configHandle,
                                                    &domainEnumerator,
                                                    &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    for (int i = 0; i < (maxIndex-1); i++)
    {
        err = seos_configuration_parameterEnumeratorIncrement(configHandle,
                                                          &parameterEnumerator);
        Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);
        // Check if the index actually got incremented
        Debug_ASSERT_PRINTFLN((1+i) == parameterEnumerator.index,
                                  "Index value: %d", parameterEnumerator.index);
    }

    err = seos_configuration_parameterEnumeratorClose(configHandle,
                                                          &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    err = seos_configuration_domainEnumeratorClose(configHandle,
                                                          &domainEnumerator);
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
TestParameterEnumerator_increment_fail(
    SeosConfigHandle* handle)
{
    seos_err_t err;
    SeosConfigHandle configHandle = *handle;
    SeosConfigLib_DomainEnumerator domainEnumerator;
    SeosConfigLib_ParameterEnumerator parameterEnumerator;

    err = seos_configuration_domainEnumeratorInit(configHandle,
                                                    &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    err = seos_configuration_parameterEnumeratorInit(configHandle,
                                                    &domainEnumerator,
                                                    &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    // Uninitialized config handle
    SeosConfigHandle uninitializedHandle;
    err = seos_configuration_parameterEnumeratorIncrement(uninitializedHandle,
                                                          &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_INVALID_HANDLE == err, "err %d", err);
    // Make sure the index did not get incremented
    Debug_ASSERT_PRINTFLN(0 == parameterEnumerator.index,
                                "Index value: %d", parameterEnumerator.index);

    // Empty parameter enumerator
    err = seos_configuration_parameterEnumeratorIncrement(configHandle,
                                                          NULL);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_INVALID_PARAMETER == err, "err %d", err);
    // Make sure the index did not get incremented
    Debug_ASSERT_PRINTFLN(0 == parameterEnumerator.index,
                                "Index value: %d", parameterEnumerator.index);

    err = seos_configuration_parameterEnumeratorClose(configHandle,
                                                          &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    err = seos_configuration_domainEnumeratorClose(configHandle,
                                                    &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestParameterEnumerator_reset_ok(SeosConfigHandle* handle,
                                 const char* componentName,
                                 unsigned int maxDomainIndex,
                                 unsigned int maxParameterIndex)
{
    seos_err_t err;
    SeosConfigHandle configHandle = *handle;
    SeosConfigLib_DomainEnumerator domainEnumerator;
    SeosConfigLib_ParameterEnumerator parameterEnumerator;
    unsigned int maxIndex = (maxParameterIndex / maxDomainIndex);

    err = seos_configuration_domainEnumeratorInit(configHandle,
                                                    &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    err = seos_configuration_parameterEnumeratorInit(configHandle,
                                                    &domainEnumerator,
                                                    &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    // Increment parameter enumerator index
    err = seos_configuration_parameterEnumeratorIncrement(configHandle,
                                                          &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);
    // Check if the index actually got incremented
    Debug_ASSERT_PRINTFLN(1 == parameterEnumerator.index,
                                  "Index value: %d", parameterEnumerator.index);

    err = seos_configuration_parameterEnumeratorReset(configHandle,
                                                        &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);
    // Check if the index actually got reset
    Debug_ASSERT_PRINTFLN(0 == parameterEnumerator.index,
                                  "Index value: %d", parameterEnumerator.index);

    for (int i = 0; i < (maxIndex-1); i++)
    {
        err = seos_configuration_parameterEnumeratorIncrement(configHandle,
                                                          &parameterEnumerator);
        Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);
        // Check if the index actually got incremented
        Debug_ASSERT_PRINTFLN((1+i) == parameterEnumerator.index,
                                  "Index value: %d", parameterEnumerator.index);
    }

    err = seos_configuration_parameterEnumeratorReset(configHandle,
                                                        &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);
    // Check if the index actually got reset
    Debug_ASSERT_PRINTFLN(0 == parameterEnumerator.index,
                                  "Index value: %d", parameterEnumerator.index);

    err = seos_configuration_parameterEnumeratorClose(configHandle,
                                                          &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    err = seos_configuration_domainEnumeratorClose(configHandle,
                                                          &domainEnumerator);
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
TestParameterEnumerator_reset_fail(
    SeosConfigHandle* handle)
{
    seos_err_t err;
    SeosConfigHandle configHandle = *handle;
    SeosConfigLib_DomainEnumerator domainEnumerator;
    SeosConfigLib_ParameterEnumerator parameterEnumerator;

    err = seos_configuration_domainEnumeratorInit(configHandle,
                                                    &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    err = seos_configuration_parameterEnumeratorInit(configHandle,
                                                    &domainEnumerator,
                                                    &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    // Uninitialized config handle
    SeosConfigHandle uninitializedHandle;
    err = seos_configuration_parameterEnumeratorReset(uninitializedHandle, &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_INVALID_HANDLE == err, "err %d", err);

    // Empty parameter enumerator
    err = seos_configuration_parameterEnumeratorReset(configHandle, NULL);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_INVALID_PARAMETER == err, "err %d", err);

    err = seos_configuration_parameterEnumeratorClose(configHandle,
                                                          &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    err = seos_configuration_domainEnumeratorClose(configHandle,
                                                            &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestParameterEnumerator_getElement_ok(
    SeosConfigHandle* handle)
{
    seos_err_t err;
    SeosConfigHandle configHandle = *handle;
    SeosConfigLib_DomainEnumerator    domainEnumerator;
    SeosConfigLib_ParameterEnumerator parameterEnumerator;
    SeosConfigLib_Parameter           parameter;

    err = seos_configuration_domainEnumeratorInit(configHandle,
                                                    &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    err = seos_configuration_parameterEnumeratorInit(configHandle,
                                                    &domainEnumerator,
                                                    &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    //Retrieve parameter for parameter enumerator
    err = seos_configuration_parameterEnumeratorGetElement(configHandle,
                                                           &parameterEnumerator,
                                                           &parameter);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    err = seos_configuration_parameterEnumeratorClose(configHandle,
                                                          &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    err = seos_configuration_domainEnumeratorClose(configHandle,
                                                            &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestParameterEnumerator_getElement_fail(
    SeosConfigHandle* handle)
{
    seos_err_t err;
    SeosConfigHandle configHandle = *handle;
    SeosConfigLib_DomainEnumerator    domainEnumerator;
    SeosConfigLib_ParameterEnumerator parameterEnumerator;
    SeosConfigLib_Parameter           parameter;

    err = seos_configuration_domainEnumeratorInit(configHandle,
                                                    &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    err = seos_configuration_parameterEnumeratorInit(configHandle,
                                                    &domainEnumerator,
                                                    &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    // Uninitialized config handle
    SeosConfigHandle uninitializedHandle;
    err = seos_configuration_parameterEnumeratorGetElement(uninitializedHandle,
                                                        &parameterEnumerator,
                                                        &parameter);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_INVALID_HANDLE == err, "err %d", err);

    // Emtpy parameter enumerator
    err = seos_configuration_parameterEnumeratorGetElement(configHandle,
                                                    NULL, &parameter);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_INVALID_PARAMETER == err, "err %d", err);

    // Empty parameter
    err = seos_configuration_parameterEnumeratorGetElement(uninitializedHandle,
                                                        &parameterEnumerator,
                                                        NULL);
    Debug_ASSERT_PRINTFLN(SEOS_ERROR_INVALID_PARAMETER == err, "err %d", err);

    err = seos_configuration_parameterEnumeratorClose(configHandle,
                                                          &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    err = seos_configuration_domainEnumeratorClose(configHandle,
                                                            &domainEnumerator);
    Debug_ASSERT_PRINTFLN(SEOS_SUCCESS == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

// -----------------------------------------------------------------------------

void TestParameterEnumerator_testAll(SeosConfigHandle* handle,const char* componentName, unsigned int maxDomainIndex, unsigned int maxParameterIndex)
{
    Debug_LOG_DEBUG("Executing Test Parameter Enumerator tests");

    TestParameterEnumerator_init_ok(handle);
    TestParameterEnumerator_init_fail(handle);

    TestParameterEnumerator_close_ok(handle);
    TestParameterEnumerator_close_fail(handle);

    TestParameterEnumerator_increment_ok(handle, componentName, maxDomainIndex, maxParameterIndex);
    TestParameterEnumerator_increment_fail(handle);

    TestParameterEnumerator_reset_ok(handle, componentName, maxDomainIndex, maxParameterIndex);
    TestParameterEnumerator_reset_fail(handle);

    TestParameterEnumerator_getElement_ok(handle);
    TestParameterEnumerator_getElement_fail(handle);
}