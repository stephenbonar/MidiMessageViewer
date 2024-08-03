// MidiMessage.h - Declares the MidiMessage class.
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

#ifndef MIDI_MESSAGE_H
#define MIDI_MESSAGE_H

#include <string>
#include <memory>
#include "MidiDataDecoder.h"
#include "MidiEventDecoder.h"
#include "MidiConstants.h"
#include "StatusByte.h"
#include "BinData.h"

class MidiMessage : public MidiEventDecoder
{
public:
    MidiMessage(std::shared_ptr<StatusByte> statusByte) 
        : statusByte{ statusByte }
    {
        size = 1;
    }
protected:
    std::shared_ptr<StatusByte> statusByte;
    std::shared_ptr<MidiEventDecoder> subDecoder;

    virtual void DecodeStatusData(std::string label, BinData::FileStream* s);

    template <typename T>
    void InitializeSubDecoderWithStatusByte()
    {
        subDecoder = std::make_shared<T>(statusByte);
        subDecoders.push_back(subDecoder);
        decodeQueue.push_back(subDecoder);
    }

    template <typename T>
    void InitializeSubDecoder()
    {
        subDecoder = std::make_shared<T>();
        subDecoders.push_back(subDecoder);
        decodeQueue.push_back(subDecoder);
    }
};

#endif