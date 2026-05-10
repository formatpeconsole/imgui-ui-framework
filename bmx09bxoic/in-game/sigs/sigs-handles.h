#pragma once
#include <memory>
#include <Windows.h>

#include "../../mem/ptr.h"

struct ModuleHandles
{
    HANDLE gameoverlayrenderer64;
    HANDLE client;
};

struct Signatures
{
    Ptr overlay_Present;
    Ptr overlay_ResizeBuffers;
    Ptr overlay_CreateSwapChain;
    Ptr client_FrameStageNotify;
};

extern Signatures& getSignaturesInstance();
extern ModuleHandles& getModuleHandlesInstance();
