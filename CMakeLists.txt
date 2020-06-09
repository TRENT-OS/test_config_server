cmake_minimum_required(VERSION 3.7.2)

project(system_config C)
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_LIST_DIR})

project(test_config_server C)

os_set_config_file(system_config.h)

os_use_libs(
    OS_LIBS
    OS_CHANMUX
    OS_PARTITION_MANAGER
    OS_FILESYSTEM_CORE
    OS_FILESYSTEM_FAT
    OS_FILESYSTEM_SPIFFS
    OS_CONFIGURATION
)


#-------------------------------------------------------------------------------
# Component ConfigFileInjector
#-------------------------------------------------------------------------------
DeclareCAmkESComponent(ConfigFileInjector
    INCLUDES
        util
    SOURCES
        components/ConfigFileInjector/src/ConfigFileInjector.c
        util/create_parameters.c
        util/create_fs_backend.c
    C_FLAGS
        -Wall
        -Werror
        # filesystem
        #-DOS_CONFIG_SERVICE_BACKEND_FILESYSTEM
        -DOS_FS_BUILD_AS_LIB_BASIC_HANDLE
        # partition manager
        -DOS_PARTITION_MANAGER_BUILD_AS_COMPONENT
    LIBS
        system_config
        os_libs
        os_core_api
        os_configuration
        os_partition_manager_api
        os_filesystem_core
        os_filesystem_fat
        os_filesystem_spiffs
)


#-------------------------------------------------------------------------------
# Component PartitionManager
#-------------------------------------------------------------------------------
DeclareCAmkESComponent(PartitionManager
    SOURCES
        components/PartitionManager/PartitionManager.c
    C_FLAGS
        -Wall
        -Werror
        -DOS_PARTITION_MANAGER_BUILD_AS_COMPONENT
    LIBS
        system_config
        os_libs
        proxy_nvm
        os_partition_manager
)


#-------------------------------------------------------------------------------
# Component ConfigServer
#-------------------------------------------------------------------------------
DeclareCAmkESComponent(ConfigServer
    INCLUDES
        util
    SOURCES
        components/ConfigServer/src/ConfigServer.c
        util/init_lib_with_fs_backend.c
        util/init_lib_with_mem_backend.c
        util/create_parameters.c
    C_FLAGS
        -Wall
        -Werror
        # filesystem
        #-DOS_CONFIG_SERVICE_BACKEND_FILESYSTEM
        -DOS_CONFIG_SERVICE_BACKEND_MEMORY
        -DOS_FS_BUILD_AS_LIB_BASIC_HANDLE
        # partition manager
        -DOS_PARTITION_MANAGER_BUILD_AS_COMPONENT
        # config server
        -DOS_CONFIG_SERVICE_CAMKES_SERVER     # indicates a camkes configuration server is being built
    LIBS
        system_config
        os_libs
        os_core_api
        os_configuration
        os_partition_manager_api
        os_filesystem_core
        os_filesystem_fat
        os_filesystem_spiffs
)

#-------------------------------------------------------------------------------
# Component TestApp1 (with additional local configServer as lib)
#-------------------------------------------------------------------------------
DeclareCAmkESComponent(TestApp1
    INCLUDES
        util
        tests
    SOURCES
        components/TestApp/src/TestRunnerApp1.c
	util/init_lib_with_fs_backend.c
        util/init_lib_with_mem_backend.c
        util/create_parameters.c
        util/helper_func.c
        tests/test_create_handle.c
        tests/test_access_rights.c
        tests/test_domain_enumerator.c
        tests/test_parameter_enumerator.c
        tests/test_parameter_get_functions.c
        tests/test_parameter_set_functions.c
    C_FLAGS
        -Wall
        -Werror
        # filesystem
        #-DOS_CONFIG_SERVICE_BACKEND_FILESYSTEM
        -DOS_CONFIG_SERVICE_BACKEND_MEMORY
        -DOS_FS_BUILD_AS_LIB_BASIC_HANDLE
        # partition manager
        -DOS_PARTITION_MANAGER_BUILD_AS_COMPONENT
        -DOS_CONFIG_SERVICE_CAMKES_CLIENT
    LIBS
        system_config
        os_libs
        os_core_api
        os_configuration
        os_partition_manager_api
        os_filesystem_core
        os_filesystem_fat
        os_filesystem_spiffs
)

#-------------------------------------------------------------------------------
# Component TestApp2
#-------------------------------------------------------------------------------
DeclareCAmkESComponent(TestApp2
    INCLUDES
        util
        tests
    SOURCES
        components/TestApp/src/TestRunnerApp2.c
        util/helper_func.c
        tests/test_create_handle.c
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
        os_libs
        os_core_api
        os_configuration
)

#-------------------------------------------------------------------------------
# Component TestApp3
#-------------------------------------------------------------------------------
DeclareCAmkESComponent(TestApp3
    INCLUDES
        util
        tests
    SOURCES
        components/TestApp/src/TestRunnerApp3.c
        util/helper_func.c
        tests/test_create_handle.c
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
        os_libs
        os_core_api
        os_configuration
)

#-------------------------------------------------------------------------------
# Component TestApp4
#-------------------------------------------------------------------------------
DeclareCAmkESComponent(TestApp4
    INCLUDES
        util
        tests
    SOURCES
        components/TestApp/src/TestRunnerApp4.c
        util/helper_func.c
        tests/test_create_handle.c
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
        os_libs
        os_core_api
        os_configuration
)

#-------------------------------------------------------------------------------
# Component UartDrv
#-------------------------------------------------------------------------------
DeclareCAmkESComponent_UART(
    UART
)

#-------------------------------------------------------------------------------
# Component ChanMux
#-------------------------------------------------------------------------------
DeclareCAmkESComponent_ChanMux(
    ChanMux
    components/ChanMux/ChanMux_config.c
    system_config
)

DeclareAndCreateCamkESSystem(ConfigServerTests.camkes)
GenerateSimulateScript()
