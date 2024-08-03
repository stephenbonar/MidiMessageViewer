// MidiSystemMessage.h - Declares the MidiSystemMessage class.
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

#ifndef MIDI_SYSTEM_MESSAGE_H
#define MIDI_SYSTEM_MESSAGE_H

#include <memory>
#include "MidiMessage.h"
#include "MidiConstants.h"
#include "MidiMetaEvent.h"
#include "StatusByte.h"
#include "BinData.h"

class MidiSystemMessage : public MidiMessage
{
public:
    MidiSystemMessage(std::shared_ptr<StatusByte> statusByte)
        : MidiMessage(statusByte)
    { }
protected:
    virtual void StartDecoding(BinData::FileStream* s) override;

    virtual void FinishDecoding(BinData::FileStream* s) override;
};

#endif