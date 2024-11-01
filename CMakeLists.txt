#
# Test Configuration server
#
# Copyright (C) 2020-2024, HENSOLDT Cyber GmbH
# 
# SPDX-License-Identifier: GPL-2.0-or-later
#
# For commercial licensing, contact: info.cyber@hensoldt.net
#

cmake_minimum_required(VERSION 3.7.2)

#-------------------------------------------------------------------------------
# use the SDK
find_package("os-sdk" REQUIRED)
os_sdk_set_defaults()
os_sdk_setup(CONFIG_FILE "system_config.h" CONFIG_PROJECT "system_config")


#-------------------------------------------------------------------------------
project(test_config_server C)

DeclareCAmkESComponent(
    ConfigFileInjector
    INCLUDES
        util
    SOURCES
        components/ConfigFileInjector/src/ConfigFileInjector.c
        util/create_parameters.c
        util/create_fs_backend.c
    C_FLAGS
        -Wall
        -Werror
        -DOS_CONFIG_SERVICE_BACKEND_FILESYSTEM
    LIBS
        system_config
        lib_debug
        lib_macros
        os_core_api
        os_configuration
        os_filesystem
)

DeclareCAmkESComponent(
    ConfigServer
    INCLUDES
        util
    SOURCES
        components/ConfigServer/src/ConfigServer.c
        util/init_lib_with_fs_backend.c
        util/create_parameters.c
    C_FLAGS
        -Wall
        -Werror
        -DOS_CONFIG_SERVICE_CAMKES_SERVER
        -DOS_CONFIG_SERVICE_BACKEND_FILESYSTEM
    LIBS
        system_config
        lib_debug
        os_core_api
        os_configuration
        os_filesystem
)

DeclareCAmkESComponent(
    ConfigServerNoInit
    INCLUDES
        util
    SOURCES
        util/create_parameters.c
    C_FLAGS
        -Wall
        -Werror
        -DOS_CONFIG_SERVICE_CAMKES_SERVER
        -DOS_CONFIG_SERVICE_BACKEND_FILESYSTEM
    LIBS
        system_config
        lib_debug
        os_core_api
        os_configuration
        os_filesystem
)

# contains an additional local configServer as lib
DeclareCAmkESComponent(
    TestApp1
    INCLUDES
        util
        tests
    SOURCES
        components/TestApp/src/TestRunnerApp1.c
        util/init_lib_with_fs_backend.c
        util/create_parameters.c
        util/helper_func.c
        tests/test_create_handle.c
        tests/test_access_rights.c
        tests/test_domain_enumerator.c
        tests/test_multiclient_env.c
        tests/test_parameter_enumerator.c
        tests/test_parameter_get_functions.c
        tests/test_parameter_set_functions.c
    C_FLAGS
        -Wall
        -Werror
        -DOS_CONFIG_SERVICE_BACKEND_FILESYSTEM
        -DOS_CONFIG_SERVICE_CAMKES_CLIENT
    LIBS
        system_config
        lib_debug
        lib_macros
        os_core_api
        os_configuration
        os_filesystem
)

DeclareCAmkESComponent(
    TestApp2
    INCLUDES
        util
        tests
    SOURCES
        components/TestApp/src/TestRunnerApp2.c
        util/helper_func.c
        tests/test_create_handle.c
        tests/test_domain_enumerator.c
        tests/test_multiclient_env.c
        tests/test_parameter_enumerator.c
        tests/test_parameter_get_functions.c
        tests/test_parameter_set_functions.c
    C_FLAGS
        -Wall
        -Werror
        -DOS_CONFIG_SERVICE_CAMKES_CLIENT
    LIBS
        system_config
        lib_debug
        lib_macros
        os_core_api
        os_configuration
)

DeclareCAmkESComponent(
    TestApp3
    INCLUDES
        util
        tests
    SOURCES
        components/TestApp/src/TestRunnerApp3.c
        util/helper_func.c
        tests/test_create_handle.c
        tests/test_domain_enumerator.c
        tests/test_multiclient_env.c
        tests/test_parameter_enumerator.c
        tests/test_parameter_get_functions.c
        tests/test_parameter_set_functions.c
    C_FLAGS
        -Wall
        -Werror
        -DOS_CONFIG_SERVICE_CAMKES_CLIENT
    LIBS
        system_config
        lib_debug
        lib_macros
        os_core_api
        os_configuration
)

DeclareCAmkESComponent(
    TestApp4
    INCLUDES
        util
        tests
    SOURCES
        components/TestApp/src/TestRunnerApp4.c
        util/helper_func.c
        tests/test_create_handle.c
        tests/test_domain_enumerator.c
        tests/test_multiclient_env.c
        tests/test_parameter_enumerator.c
        tests/test_parameter_get_functions.c
        tests/test_parameter_set_functions.c
    C_FLAGS
        -Wall
        -Werror
        -DOS_CONFIG_SERVICE_CAMKES_CLIENT
    LIBS
        system_config
        lib_debug
        lib_macros
        os_core_api
        os_configuration
)

DeclareCAmkESComponent(
    TestAppNoServerInit
    INCLUDES
        util
        tests
    SOURCES
        components/TestApp/src/TestRunnerAppNoServerInit.c
        util/helper_func.c
        tests/test_domain_enumerator.c
        tests/test_parameter_enumerator.c
        tests/test_parameter_get_functions.c
        tests/test_parameter_set_functions.c
    C_FLAGS
        -Wall
        -Werror
        -DOS_CONFIG_SERVICE_CAMKES_CLIENT
    LIBS
        system_config
        lib_debug
        lib_macros
        os_core_api
        os_configuration
)

RamDisk_DeclareCAmkESComponent(
    RamDisk
)

os_sdk_create_CAmkES_system("ConfigServerTests.camkes")
