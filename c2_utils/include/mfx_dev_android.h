/********************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2017-2018 Intel Corporation. All Rights Reserved.

*********************************************************************************/

#pragma once

#include "mfx_dev.h"

class MfxDevAndroid : public MfxDev
{
public:
    MfxDevAndroid();
    virtual ~MfxDevAndroid();
    MFX_CLASS_NO_COPY(MfxDevAndroid)

public:
    virtual mfxStatus Init() override;
    virtual mfxStatus Close() override;

    virtual std::shared_ptr<MfxFrameAllocator> GetFrameAllocator() override { return nullptr; }
    virtual std::shared_ptr<MfxFrameConverter> GetFrameConverter() override { return nullptr; }
    virtual std::shared_ptr<MfxFramePoolAllocator> GetFramePoolAllocator() override { return nullptr; }

    virtual mfxStatus InitMfxSession(MFXVideoSession* session) override;
};
