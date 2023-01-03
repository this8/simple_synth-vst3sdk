//------------------------------------------------------------------------
// Copyright(c) 2023 Musiola.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace Musiola {
//------------------------------------------------------------------------
static const Steinberg::FUID kMusynthProcessorUID (0x5B309FE3, 0x29065435, 0x92B9A5A3, 0x9B2C39D6);
static const Steinberg::FUID kMusynthControllerUID (0xF4BAA20E, 0xF4CC5B63, 0xB3A5213E, 0x45D23129);

#define MusynthVST3Category "Instrument"

//------------------------------------------------------------------------
} // namespace Musiola
