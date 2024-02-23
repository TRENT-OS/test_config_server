/**
 * Copyright (C) 2020-2024, HENSOLDT Cyber GmbH
 * 
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * For commercial licensing, contact: info.cyber@hensoldt.net
 */

#include "test_types.h"

#include "test_parameter_get_functions.h"

#include "test_parameter_set_functions.h"

#include "test_multiclient_env.h"


// -----------------------------------------------------------------------------
void
test_multiClient_environment(
    OS_ConfigServiceHandle_t* cfgHandle,
    TestApp_t* testApp,
    void (*sync_with_other_clients)())
{
    test_GetInteger32FromFsBackend_pos(
        cfgHandle,
        testApp->appDomainName,
        testApp->appComponentName,
        testApp->uint32TestData.parameterName[0],
        testApp->uint32TestData.parameterValue.uint32Value[0]);
    sync_with_other_clients();

    test_GetInteger64FromFsBackend_pos(
        cfgHandle,
        testApp->appDomainName,
        testApp->appComponentName,
        testApp->uint64TestData.parameterName[0],
        testApp->uint64TestData.parameterValue.uint64Value[0]);
    sync_with_other_clients();

    test_GetStringsFromFsBackend_pos(
        cfgHandle,
        testApp->appDomainName,
        testApp->appComponentName,
        testApp->strTestData.parameterName[0],
        testApp->strTestData.parameterValue.stringValue[0],
        testApp->strTestData.parameterSize[0]);
    sync_with_other_clients();

    test_GetBlobsFromFsBackend_pos(
        cfgHandle,
        testApp->appDomainName,
        testApp->appComponentName,
        testApp->blobTestData.parameterName[0],
        testApp->blobTestData.parameterValue.rawValue[0],
        testApp->blobTestData.parameterSize[0]);
    sync_with_other_clients();

    test_GetBlobsFromFsBackend_pos(
        cfgHandle,
        testApp->appDomainName,
        testApp->appComponentName,
        testApp->blobTestData.parameterName[3],
        testApp->blobTestData.parameterValue.rawValue[3],
        testApp->blobTestData.parameterSize[3]);
    sync_with_other_clients();

    //Test set parameter functions in multiclient environment
    test_ParameterSetValueAsU32_pos(
        cfgHandle,
        testApp->appDomainName,
        testApp->appComponentName,
        testApp->uint32TestData.parameterName[0],
        testApp->uint32TestData.newParameterValue.uint32Value[0]);
    sync_with_other_clients();

    test_ParameterSetValueAsU64_pos(
        cfgHandle,
        testApp->appDomainName,
        testApp->appComponentName,
        testApp->uint64TestData.parameterName[0],
        testApp->uint64TestData.newParameterValue.uint64Value[0]);
    sync_with_other_clients();

    test_ParameterSetValueAsString_pos(
        cfgHandle,
        testApp->appDomainName,
        testApp->appComponentName,
        testApp->strTestData.parameterName[0],
        testApp->strTestData.newParameterValue.stringValue[0],
        testApp->strTestData.newParameterSize[0]);
    sync_with_other_clients();

    test_ParameterSetValueAsBlob_pos(
        cfgHandle,
        testApp->appDomainName,
        testApp->appComponentName,
        testApp->blobTestData.parameterName[0],
        testApp->blobTestData.newParameterValue.rawValue[0],
        testApp->blobTestData.newParameterSize[0]);
    sync_with_other_clients();

    test_ParameterSetValueAsBlob_pos(
        cfgHandle,
        testApp->appDomainName,
        testApp->appComponentName,
        testApp->blobTestData.parameterName[3],
        testApp->blobTestData.newParameterValue.rawValue[3],
        testApp->blobTestData.newParameterSize[3]);
    sync_with_other_clients();
}