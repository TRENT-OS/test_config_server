/*
   *  Partition manager init file for the use of the partition manager as a component.
   *
   *  Copyright (C) 2019, Hensoldt Cyber GmbH
*/


#include "LibDebug/Debug.h"
#include "ChanMuxNvmDriver.h"
#include "api_pm.h"

#include <camkes.h>


//------------------------------------------------------------------------------
void
api_pm_component__init(void)
{
    static ChanMuxNvmDriver chanMuxNvmDriver;

    if (!ChanMuxNvmDriver_ctor(
            &chanMuxNvmDriver,
            CHANMUX_CHANNEL_NVM,
            chanMuxDataPort))
    {
        Debug_LOG_ERROR("Failed to construct ChanMuxNvmDriver");
        return;
    }

    seos_err_t ret = api_pm_partition_manager_init(
                        ChanMuxNvmDriver_get_nvm(&chanMuxNvmDriver));
    if (ret != SEOS_SUCCESS)
    {
        Debug_LOG_DEBUG("Fail to init partition manager, code %d", ret);
        return;
    }
}
