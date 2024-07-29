// MidiEventDecoder.h - Declares the MidiEventDecoder class.
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

#ifndef MIDI_EVENT_DECODER_H
#define MIDI_EVENT_DECODER_H

#include "MidiDataDecoder.h"
#include "MidiEventType.h"

class MidiEventDecoder : public MidiDataDecoder
{
public:
    MidiEventDecoder() : 
        size{ 0 }, 
        bytesDecoded{ 0 },
        type{ MidiEventType::Unknown },
        typeText{ "" }, 
        details{ "" }, 
        dataText{ "" },
        hasDecoded{ false },
        subDecoder{ nullptr }
    { }

    /// @brief The amount of bytes the decoder is expected to decode.
    /// @return The number of bytes. 
    virtual size_t Size() override;

    /// @brief Determines whether or not the decoder has already decoded data.
    /// @return Returns true if decoding has completed, otherwise false.
    virtual bool HasDecoded() override;

    /// @brief Provides a string representation of the decoded data.
    /// @return The string representing the decoded data.
    virtual std::string ToString() override;

    virtual std::string Details();

    virtual std::string TypeText();

    virtual MidiEventType Type();
protected:
    size_t size;
    size_t bytesDecoded;
    MidiEventType type;
    std::string typeText;
    std::string details;
    std::string dataText;
    bool hasDecoded;
    std::unique_ptr<MidiEventDecoder> subDecoder;

    virtual bool HasSubDecoders() override { return false; }

    virtual std::shared_ptr<MidiDataDecoder> NextSubDecoder() override
    { 
        return nullptr; 
    }

    virtual size_t BytesDecoded() override;

    virtual void DecodeSelf(BinData::FileStream* s);
};

#endif