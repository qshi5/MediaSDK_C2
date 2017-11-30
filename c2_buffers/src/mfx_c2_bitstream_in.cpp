/********************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2017 Intel Corporation. All Rights Reserved.

*********************************************************************************/

#include "mfx_c2_bitstream_in.h"
#include "mfx_c2_utils.h"
#include "mfx_debug.h"
#include "mfx_c2_debug.h"
#include "mfx_msdk_debug.h"

using namespace android;

#undef MFX_DEBUG_MODULE_NAME
#define MFX_DEBUG_MODULE_NAME "mfx_c2_bitstream_in"

MfxC2BitstreamIn::MfxC2BitstreamIn(MfxC2FrameConstructorType fc_type)
{
    MFX_DEBUG_TRACE_FUNC;

    frame_constructor_ = MfxC2FrameConstructorFactory::CreateFrameConstructor(fc_type);
}

MfxC2BitstreamIn::~MfxC2BitstreamIn()
{
    MFX_DEBUG_TRACE_FUNC;
}

status_t MfxC2BitstreamIn::LoadC2BufferPack(C2BufferPack& buf_pack, nsecs_t timeout)
{
    MFX_DEBUG_TRACE_FUNC;

    C2Error res = C2_OK;
    const mfxU8* data = nullptr;
    mfxU32 filled_len = 0;

    do {
        std::unique_ptr<C2ConstLinearBlock> c_linear_block;
        res = GetC2ConstLinearBlock(buf_pack, &c_linear_block);
        if(C2_OK != res) break;

        const mfxU8* raw = nullptr;
        res = MapConstLinearBlock(*c_linear_block, timeout, &raw);
        if(C2_OK != res) break;

        MFX_DEBUG_TRACE_I64(buf_pack.ordinal.timestamp);

        data = raw + c_linear_block->offset();
        filled_len = c_linear_block->size();

        frame_constructor_->SetEosMode(buf_pack.flags & BUFFERFLAG_END_OF_STREAM);

        mfxStatus mfx_res = frame_constructor_->Load(data,
                                                     filled_len,
                                                     buf_pack.ordinal.timestamp,
                                                     buf_pack.flags & BUFFERFLAG_CODEC_CONFIG,
                                                     true);
        res = MfxStatusToC2(mfx_res);
        if(C2_OK != res) break;

    } while(false);

    MFX_DEBUG_TRACE__android_status_t(res);
    return res;
}