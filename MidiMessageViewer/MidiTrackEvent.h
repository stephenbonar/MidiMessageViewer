// MidiTrackEvent.h - Declares the MidiTrackEvent class.
//
// Copyright (C) 2024 Stephen Bonar
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http ://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef MIDI_TRACK_EVENT_H
#define MIDI_TRACK_EVENT_H

#include <string>
#include <sstream>
#include "BinData.h"
#include "VariableLengthQuantity.h"
#include "MidiConstants.h"
#include "MidiEventType.h"
#include "MidiEvent.h"
#include "MidiEventDecoder.h"
#include "MidiControlChangeMessage.h"
#include "MidiProgramChangeMessage.h"
#include "MidiSystemMessage.h"
#include "StatusByte.h"

class MidiTrackEvent : public MidiEventDecoder
{
public:
    std::string DeltaTime() { return std::to_string(deltaTime.Value()); }
protected:
    virtual void DecodeSelf(BinData::FileStream* s) override;
private:
    VariableLengthQuantity deltaTime;
};

#endif