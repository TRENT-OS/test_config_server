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

    test_DomainEnumerator_init_no_server_init_neg(&remoteHandle);
    test_DomainEnumerator_close_no_server_init_neg(&remoteHandle);
    test_DomainEnumerator_reset_no_server_init_neg(&remoteHandle);
    test_DomainEnumerator_increment_no_server_init_neg(&remoteHandle);
    test_DomainEnumerator_getElement_no_server_init_neg(&remoteHandle);

    test_ParameterEnumerator_init_no_server_init_neg(&remoteHandle);
    test_ParameterEnumerator_close_no_server_init_neg(&remoteHandle);
    test_ParameterEnumerator_reset_no_server_init_neg(&remoteHandle);
    test_ParameterEnumerator_increment_no_server_init_neg(&remoteHandle);
    test_ParameterEnumerator_getElement_no_server_init_neg(&remoteHandle);

    test_ParameterGetValue_no_server_init_neg(&remoteHandle);
    test_ParameterGetValueAsU32_no_server_init_neg(&remoteHandle);
    test_ParameterGetValueAsU64_no_server_init_neg(&remoteHandle);
    test_ParameterGetValueAsString_no_server_init_neg(&remoteHandle);
    test_ParameterGetValueAsBlob_no_server_init_neg(&remoteHandle);
    test_ParameterGetValueFromDomainName_no_server_init_neg(&remoteHandle);

    test_ParameterSetValue_no_server_init_neg(&remoteHandle);
    test_ParameterSetValueAsU32_no_server_init_neg(&remoteHandle);
    test_ParameterSetValueAsU64_no_server_init_neg(&remoteHandle);
    test_ParameterSetValueAsString_no_server_init_neg(&remoteHandle);
    test_ParameterSetValueAsBlob_no_server_init_neg(&remoteHandle);

    Debug_LOG_DEBUG("%s: All tests completed.\n", TEST_APP);
    return 0;
}
