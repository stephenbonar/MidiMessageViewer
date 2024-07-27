// MidiEvent.h - Declares the MidiEvent class.
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

#ifndef MIDI_EVENT_H
#define MIDI_EVENT_H

#include <string>
#include <sstream>
#include "BinData.h"
#include "MidiDataDecoder.h"
#include "VariableLengthQuantity.h"

class MidiEvent : public MidiDataDecoder
{
public:
    inline static constexpr int StatusCodeTypeBitShift{ 4 };
    inline static constexpr int StatusCodeDataMask{ 0x0F };

    inline static constexpr int EventNoteOff{ 0x8 };
    inline static constexpr int EventNoteOn{ 0x9 };
    inline static constexpr int EventPolyphonicKeyPressure{ 0x9 };
    inline static constexpr int EventControlChange{ 0xB };
    inline static constexpr int EventProgramChange{ 0xC };
    inline static constexpr int EventChannelPressure{ 0xD };
    inline static constexpr int EventPitchWheelChange{ 0xE };
    inline static constexpr int EventSystemMessage{ 0xF };

    inline static constexpr int SystemMessageExclusive{ 0x0 };
    inline static constexpr int SystemMessageSongPositionPointer{ 0x2 };
    inline static constexpr int SystemMessageSongSelect{ 0x3 };
    inline static constexpr int SystemMessageTuneSelect{ 0x6 };
    inline static constexpr int SystemMessageExclusiveEnd{ 0x7 };
    inline static constexpr int SystemMessageTimingClock{ 0x8 };
    inline static constexpr int SystemMessageStart{ 0xA };
    inline static constexpr int SystemMessageContinue{ 0xB };
    inline static constexpr int SystemMessageStop{ 0xC };
    inline static constexpr int SystemMessageActiveSensing{ 0xE };
    inline static constexpr int SystemMessageReset{ 0xF };

    inline static constexpr int MetaEventTempo{ 0x51 };
    inline static constexpr int MetaEventTempoPrefix{ 0x3 };

    enum class EventType
    {
        Unknown,
        NoteOff,
        NoteOn,
        PolyphonicKeyPressure,
        ControlChange,
        ProgramChange,
        ChannelPressure,
        PitchWheelChange,
        SystemMessage
    };

    MidiEvent() : hasDecoded{ false },
                  bytesDecoded{ 0 },
                  statusCode{ 0 }, 
                  channel{ -1 },
                  eventType{ EventType::Unknown } 
    { }

    virtual bool HasDecoded() override { return hasDecoded; }

    virtual size_t Size() override;

    virtual std::string ToString() override { return "Event"; }

    std::string DeltaTime() { return deltaTime.ToString(); }

    std::string StatusCode() 
    { 
        return statusCode.ToString(BinData::Format::Hex); 
    }

    std::string Data() { return dataText.str(); }

    EventType Type() { return eventType; }
protected:
    virtual bool HasSubDecoders() override { return false; }

    virtual std::shared_ptr<MidiDataDecoder> NextSubDecoder() override
    { 
        return nullptr; 
    }

    virtual size_t BytesDecoded() override { return bytesDecoded; }

    virtual void DecodeSelf(BinData::FileStream* s) override;
private:
    bool hasDecoded;
    size_t bytesDecoded;
    VariableLengthQuantity deltaTime;
    BinData::UInt8Field statusCode;
    int channel;
    std::unique_ptr<MidiDataDecoder> data;
    EventType eventType;
    std::stringstream dataText;

    void DecodeSystemMessage(BinData::FileStream* s);

    void DecodeMetaEvent(BinData::FileStream* s);
};

#endif