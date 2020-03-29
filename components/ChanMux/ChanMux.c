/*
 *  Channel MUX
 *
 *  Copyright (C) 2019, Hensoldt Cyber GmbH
 */


#include "ChanMux/ChanMux.h"
#include "SeosError.h"
#include "assert.h"

#include "system_config.h"

#include <camkes.h>

static uint8_t client_FifoBuf[PAGE_SIZE];

#define ARRAY_ELEMENTS(_array_)     ( sizeof(_array_)/sizeof(_array_[0]) )

#define NO_CHANMUX_FIFO         { .buffer = NULL, .len = 0 }
#define NO_CHANMUX_DATA_PORT    { .io = NULL, .len = 0 }


static const ChanMuxConfig_t cfgChanMux =
{
    .numChannels = CHANMUX_NUM_CHANNELS,
    .outputDataport = {
        .io  = (void**) &outputDataPort,
        .len = PAGE_SIZE
    },
    .channelsFifos = {
        NO_CHANMUX_FIFO,
        NO_CHANMUX_FIFO,
        NO_CHANMUX_FIFO,
        NO_CHANMUX_FIFO,
        NO_CHANMUX_FIFO,
        NO_CHANMUX_FIFO,
        { .buffer = client_FifoBuf, .len = sizeof(client_FifoBuf) },
        NO_CHANMUX_FIFO,
        NO_CHANMUX_FIFO
    }
};


typedef struct
{
    ChannelDataport_t  read;
    ChannelDataport_t  write;
} dataport_rw_t;

#define CHANMUX_DATA_PORT( _pBuf_, _len_ )     { .io = _pBuf_, .len = _len_ }

#define CHANMUX_DATA_PORT_RW_SHARED(_pBuf_, _len_) \
            { \
                .read = CHANMUX_DATA_PORT(_pBuf_, _len_), \
                .write = CHANMUX_DATA_PORT(_pBuf_, _len_) \
            }

#define NO_CHANMUX_DATA_PORT_RW     CHANMUX_DATA_PORT_RW_SHARED(NULL, 0)


static const dataport_rw_t dataports[CHANMUX_NUM_CHANNELS] =
{
    NO_CHANMUX_DATA_PORT_RW,
    NO_CHANMUX_DATA_PORT_RW,
    NO_CHANMUX_DATA_PORT_RW,
    NO_CHANMUX_DATA_PORT_RW,
    NO_CHANMUX_DATA_PORT_RW,
    NO_CHANMUX_DATA_PORT_RW,
    CHANMUX_DATA_PORT_RW_SHARED( (void**)&client_dataport_buf, PAGE_SIZE ),
    NO_CHANMUX_DATA_PORT_RW,
    NO_CHANMUX_DATA_PORT_RW
};

// sender IDs are basically the endpoint badges of the RPC connector. They are
// defined in the main CAmkES file's configuration block as
//   <component>.<interface>_attributes = <badge ID>
#define SENDER_PM           101

#define INVALID_CHANNEL     ((unsigned int)(-1))


typedef struct
{
    ChanMux*               chanMux;
    unsigned int           chanNum_global;
    const dataport_rw_t*   dataport_rw;
} chanMux_channel_ctx_t;


//------------------------------------------------------------------------------
static void
ChanMux_dataAvailable_emit(
    unsigned int chanNum)
{
    switch (chanNum)
    {
    //---------------------------------
    case CHANMUX_CHANNEL_NVM:
        dataAvailable_client_emit();
        break;

    //---------------------------------
    default:
        Debug_LOG_ERROR("[channel %u] invalid channel to signal data available",
                        chanNum);

        break;
    }
}


//------------------------------------------------------------------------------
static ChanMux*
ChanMux_getInstanceOrCreate(
    unsigned int doCreate)
{
    // ToDo: actually, we need a mutex here to ensure all access and especially
    //       the creation is serialized. In the current implementation, the
    //       creation happens from the main thread before the interfaces are
    //       up and afterward we just try to get the instance, but never try to
    //       create it.

    // singleton
    static ChanMux* self = NULL;
    static ChanMux  theOne;
    static Channel_t channels[CHANMUX_NUM_CHANNELS];

    if ((NULL == self) && doCreate)
    {
        if (!ChanMux_ctor(&theOne,
                          channels,
                          &cfgChanMux,
                          NULL,
                          ChanMux_dataAvailable_emit,
                          Output_write))
        {
            Debug_LOG_ERROR("ChanMux_ctor() failed");
            return NULL;
        }

        self = &theOne;
    }

    return self;
}


//------------------------------------------------------------------------------
static ChanMux*
ChanMux_getInstance(void)
{
    return ChanMux_getInstanceOrCreate(0);
}


//------------------------------------------------------------------------------
static unsigned int
ChanMux_resolveChannel(
    unsigned int  sender_id,
    unsigned int  chanNum_local)
{
    unsigned int  chanNum_global = INVALID_CHANNEL;

    // ToDo: this function is supposed to map a "local" channel number passed
    //       by a sender to a "global" channel number used by the Proxy. Goal
    //       is, that only ChanMUX is aware of the global channel number that
    //       the proxy needs. All components should just use local channel
    //       numbers.

    switch (sender_id)
    {
    //----------------------------------
    case SENDER_PM:
        if (chanNum_local != 0)
        {
            Debug_LOG_ERROR("Invalid local channel number %d from PM", chanNum_local);
            return INVALID_CHANNEL;
        }
        chanNum_global = CHANMUX_CHANNEL_NVM;
        break;
    //----------------------------------
    default:
        break;
    }

    if (INVALID_CHANNEL == chanNum_global)
    {
        Debug_LOG_DEBUG("[channel %u.%u] invalid channel", sender_id, chanNum_local);
        return INVALID_CHANNEL;
    }

    Debug_LOG_TRACE("[channel %u.%u] mapped to Proxy channel %u",
                    sender_id, chanNum_local, chanNum_global);

    return chanNum_global;
}


//------------------------------------------------------------------------------
static seos_err_t
ChanMux_resolve_ctx(
    unsigned int             sender_id,
    unsigned int             chanNum_local,
    chanMux_channel_ctx_t*   ctx)
{
    Debug_ASSERT( NULL != ctx );

    ctx->chanMux = ChanMux_getInstance();
    if (NULL == ctx->chanMux)
    {
        Debug_LOG_ERROR("[Channel %u.%u] ChanMUX instance not available",
                        sender_id, chanNum_local);
        return SEOS_ERROR_GENERIC;
    }

    ctx->chanNum_global = ChanMux_resolveChannel(sender_id, chanNum_local);
    if (INVALID_CHANNEL == ctx->chanNum_global)
    {
        Debug_LOG_ERROR("[Channel %u.%u] invalid channel",
                        sender_id, chanNum_local);
        return SEOS_ERROR_ACCESS_DENIED;
    }

    Debug_ASSERT( ctx->chanNum_global < ARRAY_ELEMENTS(dataports) );
    ctx->dataport_rw = &dataports[ctx->chanNum_global];
    Debug_ASSERT( NULL != ctx->dataport_rw );

    return SEOS_SUCCESS;
}


//==============================================================================
// CAmkES component
//==============================================================================

//---------------------------------------------------------------------------
// called before any other init function is called. Full runtime support is not
// available, e.g. interfaces cannot be expected to be accessible.
void pre_init(void)
{
    Debug_LOG_DEBUG("create ChanMUX instance");
    ChanMux* chanMux = ChanMux_getInstanceOrCreate(1);
    if (NULL == chanMux)
    {
        Debug_LOG_ERROR("ChanMUX instance creation failed");
    }
}


// //---------------------------------------------------------------------------
// // called after everything has been initialized
// void post_init(void)
// {
//     Debug_LOG_TRACE("%s()", __func__);
// }


//==============================================================================
// CAmkES Interface "ChanMuxOut" (ChanMUX bottom)
//==============================================================================

// //---------------------------------------------------------------------------
// // initialize interface
// void
// ChanMuxOut__init(void)
// {
//     Debug_LOG_TRACE("%s()", __func__);
//     // nothing to do
// }


//------------------------------------------------------------------------------
// function takeByte() of interface
void
ChanMuxOut_takeByte(char byte)
{
    ChanMux* chanMux = ChanMux_getInstance();
    if (NULL == chanMux)
    {
        Debug_LOG_ERROR("ChanMUX instance not available");
        return;
    }

    // process the byte. May trigger the notifications defined in cfgChanMux if
    // there is data in the channel or the state of the channel changed
    ChanMux_takeByte(chanMux, byte);
}


//==============================================================================
// CAmkES Interface "ChanMuxIn" (ChanMUX top)
//==============================================================================

// this is missing in camkes.h
extern unsigned int ChanMuxIn_get_sender_id(void);


// //---------------------------------------------------------------------------
// // initialize interface
// void
// ChanMuxIn__init(void)
// {
//     Debug_LOG_TRACE("%s()", __func__);
//     // nothing to do
// }


//------------------------------------------------------------------------------
seos_err_t
ChanMuxIn_write(
    unsigned int  chanNum,
    size_t        len,
    size_t*       lenWritten)
{
    seos_err_t ret;

    // set defaults
    *lenWritten = 0;

    unsigned int sender_id = ChanMuxIn_get_sender_id();
    Debug_LOG_TRACE("[channel %u.%u] write len %u", sender_id, chanNum, len);

    chanMux_channel_ctx_t ctx = {0};
    ret = ChanMux_resolve_ctx(sender_id, chanNum, &ctx);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("[Channel %u.%u] ChanMux_resolve_ctx() failed, error %d",
                        sender_id, chanNum, ret);
        return SEOS_ERROR_ACCESS_DENIED;
    }

    Debug_ASSERT( NULL != ctx.chanMux );
    Debug_ASSERT( INVALID_CHANNEL != ctx.chanNum_global );
    Debug_ASSERT( NULL != ctx.dataport_rw );

    const ChannelDataport_t* dataport = &(ctx.dataport_rw->write);
    Debug_ASSERT( NULL != dataport );

    ret = ChanMux_write(ctx.chanMux, ctx.chanNum_global, dataport, &len);
    *lenWritten = len;

    Debug_LOG_TRACE("[Channel %u.%u] lenWritten %u", sender_id, chanNum, len);

    return ret;
}


//------------------------------------------------------------------------------
// function read() of interface
seos_err_t
ChanMuxIn_read(
    unsigned int  chanNum,
    size_t        len,
    size_t*       lenRead)
{
    seos_err_t ret;

    // set defaults
    *lenRead = 0;

    unsigned int sender_id = ChanMuxIn_get_sender_id();
    Debug_LOG_TRACE("[Channel %u.%u] read len %u", sender_id, chanNum, len);

    chanMux_channel_ctx_t ctx = {0};
    ret = ChanMux_resolve_ctx(sender_id, chanNum, &ctx);
    if (SEOS_SUCCESS != ret)
    {
        Debug_LOG_ERROR("[Channel %u.%u] ChanMux_resolve_ctx() failed, error %d",
                        sender_id, chanNum, ret);
        return SEOS_ERROR_ACCESS_DENIED;
    }

    Debug_ASSERT( NULL != ctx.chanMux );
    Debug_ASSERT( INVALID_CHANNEL != ctx.chanNum_global );
    Debug_ASSERT( NULL != ctx.dataport_rw );

    const ChannelDataport_t* dataport = &(ctx.dataport_rw->read);
    Debug_ASSERT( NULL != dataport );

    ret = ChanMux_read(ctx.chanMux, ctx.chanNum_global, dataport, &len);
    *lenRead = len;

    Debug_LOG_TRACE("[Channel %u.%u] lenRead %u", sender_id, chanNum, len);

    return ret;
}