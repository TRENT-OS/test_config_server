/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "test_parameter_enumerator.h"

// -----------------------------------------------------------------------------
void
TestParameterEnumerator_init_ok(
    OS_ConfigServiceHandle_t* handle)
{
    OS_Error_t err;
    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator;

    err = OS_ConfigService_domainEnumeratorInit(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    err = OS_ConfigService_parameterEnumeratorInit(configHandle,
                                                    &domainEnumerator,
                                                    &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestParameterEnumerator_init_fail(
    OS_ConfigServiceHandle_t* handle)
{
    OS_Error_t err;
    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator;

    err = OS_ConfigService_domainEnumeratorInit(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    // Uninitialized config handle
    OS_ConfigServiceHandle_t uninitializedHandle = { 0 };
    err = OS_ConfigService_parameterEnumeratorInit(uninitializedHandle,
                                                    &domainEnumerator,
                                                    &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_HANDLE == err, "err %d", err);

    // Empty domain enumerator
    err = OS_ConfigService_parameterEnumeratorInit(configHandle,
                                                    NULL, &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_PARAMETER == err, "err %d", err);

    // Empty parameter enumerator
    configHandle = *handle;
    err = OS_ConfigService_parameterEnumeratorInit(configHandle,
                                                    &domainEnumerator, NULL);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_PARAMETER == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestParameterEnumerator_close_ok(
    OS_ConfigServiceHandle_t* handle)
{
    OS_Error_t err;
    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator;

    err = OS_ConfigService_domainEnumeratorInit(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    err = OS_ConfigService_parameterEnumeratorInit(configHandle,
                                                    &domainEnumerator,
                                                    &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    // Close parameter enumerator
    err = OS_ConfigService_parameterEnumeratorClose(configHandle,
                                                    &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    err = OS_ConfigService_domainEnumeratorClose(configHandle, &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestParameterEnumerator_close_fail(
    OS_ConfigServiceHandle_t* handle)
{
    OS_Error_t err;
    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator;

    err = OS_ConfigService_domainEnumeratorInit(configHandle,
                                                    &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    err = OS_ConfigService_parameterEnumeratorInit(configHandle,
                                                    &domainEnumerator,
                                                    &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    // Uninitialized config handle
    OS_ConfigServiceHandle_t uninitializedHandle = { 0 };
    err = OS_ConfigService_parameterEnumeratorClose(uninitializedHandle,
                                                         &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_HANDLE == err, "err %d", err);

    // Empty parameter enumerator
    err = OS_ConfigService_parameterEnumeratorClose(configHandle, NULL);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_PARAMETER == err, "err %d", err);

    err = OS_ConfigService_domainEnumeratorClose(configHandle,
                                                          &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestParameterEnumerator_increment_ok(OS_ConfigServiceHandle_t* handle,
                                     const char* componentName,
                                     unsigned int maxDomainIndex,
                                     unsigned int maxParameterIndex)
{
    OS_Error_t err;
    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator;
    unsigned int maxIndex = (maxParameterIndex / maxDomainIndex);

    err = OS_ConfigService_domainEnumeratorInit(configHandle,
                                                    &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    err = OS_ConfigService_parameterEnumeratorInit(configHandle,
                                                    &domainEnumerator,
                                                    &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    for (int i = 0; i < (maxIndex-1); i++)
    {
        err = OS_ConfigService_parameterEnumeratorIncrement(configHandle,
                                                          &parameterEnumerator);
        Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);
        // Check if the index actually got incremented
        Debug_ASSERT_PRINTFLN((1+i) == parameterEnumerator.index,
                                  "Index value: %d", parameterEnumerator.index);
    }

    err = OS_ConfigService_parameterEnumeratorClose(configHandle,
                                                          &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    err = OS_ConfigService_domainEnumeratorClose(configHandle,
                                                          &domainEnumerator);
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
TestParameterEnumerator_increment_fail(
    OS_ConfigServiceHandle_t* handle)
{
    OS_Error_t err;
    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator;

    err = OS_ConfigService_domainEnumeratorInit(configHandle,
                                                    &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    err = OS_ConfigService_parameterEnumeratorInit(configHandle,
                                                    &domainEnumerator,
                                                    &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    // Uninitialized config handle
    OS_ConfigServiceHandle_t uninitializedHandle = { 0 };
    err = OS_ConfigService_parameterEnumeratorIncrement(uninitializedHandle,
                                                          &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_HANDLE == err, "err %d", err);
    // Make sure the index did not get incremented
    Debug_ASSERT_PRINTFLN(0 == parameterEnumerator.index,
                                "Index value: %d", parameterEnumerator.index);

    // Empty parameter enumerator
    err = OS_ConfigService_parameterEnumeratorIncrement(configHandle,
                                                          NULL);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_PARAMETER == err, "err %d", err);
    // Make sure the index did not get incremented
    Debug_ASSERT_PRINTFLN(0 == parameterEnumerator.index,
                                "Index value: %d", parameterEnumerator.index);

    err = OS_ConfigService_parameterEnumeratorClose(configHandle,
                                                          &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    err = OS_ConfigService_domainEnumeratorClose(configHandle,
                                                    &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestParameterEnumerator_reset_ok(OS_ConfigServiceHandle_t* handle,
                                 const char* componentName,
                                 unsigned int maxDomainIndex,
                                 unsigned int maxParameterIndex)
{
    OS_Error_t err;
    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator;
    unsigned int maxIndex = (maxParameterIndex / maxDomainIndex);

    err = OS_ConfigService_domainEnumeratorInit(configHandle,
                                                    &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    err = OS_ConfigService_parameterEnumeratorInit(configHandle,
                                                    &domainEnumerator,
                                                    &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    // Increment parameter enumerator index
    err = OS_ConfigService_parameterEnumeratorIncrement(configHandle,
                                                          &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);
    // Check if the index actually got incremented
    Debug_ASSERT_PRINTFLN(1 == parameterEnumerator.index,
                                  "Index value: %d", parameterEnumerator.index);

    err = OS_ConfigService_parameterEnumeratorReset(configHandle,
                                                        &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);
    // Check if the index actually got reset
    Debug_ASSERT_PRINTFLN(0 == parameterEnumerator.index,
                                  "Index value: %d", parameterEnumerator.index);

    for (int i = 0; i < (maxIndex-1); i++)
    {
        err = OS_ConfigService_parameterEnumeratorIncrement(configHandle,
                                                          &parameterEnumerator);
        Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);
        // Check if the index actually got incremented
        Debug_ASSERT_PRINTFLN((1+i) == parameterEnumerator.index,
                                  "Index value: %d", parameterEnumerator.index);
    }

    err = OS_ConfigService_parameterEnumeratorReset(configHandle,
                                                        &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);
    // Check if the index actually got reset
    Debug_ASSERT_PRINTFLN(0 == parameterEnumerator.index,
                                  "Index value: %d", parameterEnumerator.index);

    err = OS_ConfigService_parameterEnumeratorClose(configHandle,
                                                          &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    err = OS_ConfigService_domainEnumeratorClose(configHandle,
                                                          &domainEnumerator);
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
TestParameterEnumerator_reset_fail(
    OS_ConfigServiceHandle_t* handle)
{
    OS_Error_t err;
    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t domainEnumerator;
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator;

    err = OS_ConfigService_domainEnumeratorInit(configHandle,
                                                    &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    err = OS_ConfigService_parameterEnumeratorInit(configHandle,
                                                    &domainEnumerator,
                                                    &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    // Uninitialized config handle
    OS_ConfigServiceHandle_t uninitializedHandle = { 0 };
    err = OS_ConfigService_parameterEnumeratorReset(uninitializedHandle, &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_HANDLE == err, "err %d", err);

    // Empty parameter enumerator
    err = OS_ConfigService_parameterEnumeratorReset(configHandle, NULL);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_PARAMETER == err, "err %d", err);

    err = OS_ConfigService_parameterEnumeratorClose(configHandle,
                                                          &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    err = OS_ConfigService_domainEnumeratorClose(configHandle,
                                                            &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestParameterEnumerator_getElement_ok(
    OS_ConfigServiceHandle_t* handle)
{
    OS_Error_t err;
    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t    domainEnumerator;
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator;
    OS_ConfigServiceLibTypes_Parameter_t           parameter;

    err = OS_ConfigService_domainEnumeratorInit(configHandle,
                                                    &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    err = OS_ConfigService_parameterEnumeratorInit(configHandle,
                                                    &domainEnumerator,
                                                    &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    //Retrieve parameter for parameter enumerator
    err = OS_ConfigService_parameterEnumeratorGetElement(configHandle,
                                                           &parameterEnumerator,
                                                           &parameter);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    err = OS_ConfigService_parameterEnumeratorClose(configHandle,
                                                          &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    err = OS_ConfigService_domainEnumeratorClose(configHandle,
                                                            &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

void
TestParameterEnumerator_getElement_fail(
    OS_ConfigServiceHandle_t* handle)
{
    OS_Error_t err;
    OS_ConfigServiceHandle_t configHandle = *handle;
    OS_ConfigServiceLibTypes_DomainEnumerator_t    domainEnumerator;
    OS_ConfigServiceLibTypes_ParameterEnumerator_t parameterEnumerator;
    OS_ConfigServiceLibTypes_Parameter_t           parameter;

    err = OS_ConfigService_domainEnumeratorInit(configHandle,
                                                    &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    err = OS_ConfigService_parameterEnumeratorInit(configHandle,
                                                    &domainEnumerator,
                                                    &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    // Uninitialized config handle
    OS_ConfigServiceHandle_t uninitializedHandle = { 0 };
    err = OS_ConfigService_parameterEnumeratorGetElement(uninitializedHandle,
                                                        &parameterEnumerator,
                                                        &parameter);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_HANDLE == err, "err %d", err);

    // Emtpy parameter enumerator
    err = OS_ConfigService_parameterEnumeratorGetElement(configHandle,
                                                    NULL, &parameter);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_PARAMETER == err, "err %d", err);

    // Empty parameter
    err = OS_ConfigService_parameterEnumeratorGetElement(uninitializedHandle,
                                                        &parameterEnumerator,
                                                        NULL);
    Debug_ASSERT_PRINTFLN(OS_ERROR_INVALID_PARAMETER == err, "err %d", err);

    err = OS_ConfigService_parameterEnumeratorClose(configHandle,
                                                          &parameterEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    err = OS_ConfigService_domainEnumeratorClose(configHandle,
                                                            &domainEnumerator);
    Debug_ASSERT_PRINTFLN(OS_SUCCESS == err, "err %d", err);

    Debug_LOG_INFO("->%s: OK\n", __func__);
}

// -----------------------------------------------------------------------------

void TestParameterEnumerator_testAll(OS_ConfigServiceHandle_t* handle,const char* componentName, unsigned int maxDomainIndex, unsigned int maxParameterIndex)
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
