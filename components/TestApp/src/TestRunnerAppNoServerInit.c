/*
   *  TestRunnerApp connected to a ConfigServer component to run all tests remote
   *  in in a multiclient setup with other TestRunnerApps.
   *
   *  Copyright (C) 2020, Hensoldt Cyber GmbH
*/


#include "system_config.h"

#include "OS_Error.h"
#include "OS_ConfigService.h"
#include "OS_Dataport.h"

#include "LibDebug/Debug.h"

#include "test_domain_enumerator.h"
#include "test_parameter_enumerator.h"
#include "test_parameter_get_functions.h"
#include "test_parameter_set_functions.h"

#include <string.h>
#include <camkes.h>

/* Defines -------------------------------------------------------------------*/
#define TEST_APP     TEST_APP_SERVER_NO_INIT
#define DOMAIN_APP   DOMAIN_APP_SERVER_NO_INIT

//------------------------------------------------------------------------------
int
run(void)
{
    OS_Error_t err = OS_ERROR_GENERIC;

    //Open remote handle of API
    OS_ConfigServiceHandle_t remoteHandle;
    static OS_ConfigService_ClientCtx_t ctx =
    {
        .dataport = OS_DATAPORT_ASSIGN(cfg_dataport_buf)
    };
    err = OS_ConfigService_createHandleRemote(
              &ctx,
              &remoteHandle);
    Debug_ASSERT_PRINTFLN(err == OS_SUCCESS, "err %d", err);

    Debug_LOG_DEBUG("%s: Starting test of not initialized ConfigServer...\n", TEST_APP);

    TestDomainEnumerator_init_fail_no_server_init(&remoteHandle);
    TestDomainEnumerator_close_fail_no_server_init(&remoteHandle);
    TestDomainEnumerator_reset_fail_no_server_init(&remoteHandle);
    TestDomainEnumerator_increment_fail_no_server_init(&remoteHandle);
    TestDomainEnumerator_getElement_fail_no_server_init(&remoteHandle);

    TestParameterEnumerator_init_fail_no_server_init(&remoteHandle);
    TestParameterEnumerator_close_fail_no_server_init(&remoteHandle);
    TestParameterEnumerator_reset_fail_no_server_init(&remoteHandle);
    TestParameterEnumerator_increment_fail_no_server_init(&remoteHandle);
    TestParameterEnumerator_getElement_fail_no_server_init(&remoteHandle);

    TestParameterGetValue_fail_no_server_init(&remoteHandle);
    TestParameterGetValueAsU32_fail_no_server_init(&remoteHandle);
    TestParameterGetValueAsU64_fail_no_server_init(&remoteHandle);
    TestParameterGetValueAsString_fail_no_server_init(&remoteHandle);
    TestParameterGetValueAsBlob_fail_no_server_init(&remoteHandle);
    TestParameterGetValueFromDomainName_fail_no_server_init(&remoteHandle);

    TestParameterSetValue_fail_no_server_init(&remoteHandle);
    TestParameterSetValueAsU32_fail_no_server_init(&remoteHandle);
    TestParameterSetValueAsU64_fail_no_server_init(&remoteHandle);
    TestParameterSetValueAsString_fail_no_server_init(&remoteHandle);
    TestParameterSetValueAsBlob_fail_no_server_init(&remoteHandle);

    Debug_LOG_DEBUG("%s: All tests completed.\n", TEST_APP);
    return 0;
}
