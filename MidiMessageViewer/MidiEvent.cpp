// MidiEvent.h - Defines the MidiEvent class.
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

#include "MidiEvent.h"

size_t MidiEvent::Size()
{
    size_t size{ deltaTime.Size() + 1 };
    
    if (data != nullptr)
        size += data->Size();

    return size;
}

void MidiEvent::DecodeSelf(BinData::FileStream* s)
{
    deltaTime.Decode(s);
    bytesDecoded += deltaTime.Size();

    ReadData(s, &statusCode);

    /*
    s->Read(&statusCode);
    dataText << statusCode.ToString(BinData::Format::Hex) << " ";
    bytesDecoded += 1;*/

    switch (statusCode.Value() >> StatusCodeTypeBitShift)
    {
        case EventSystemMessage:
            eventType = EventType::SystemMessage;
            typeText << "System ";
            DecodeSystemMessage(s);
            break;
        default:
            eventType = EventType::Unknown;
            typeText << "Unknown Event Type";
    }
}

void MidiEvent::DecodeSystemMessage(BinData::FileStream* s)
{
    switch (statusCode.Value() & StatusCodeDataMask)
    {
        case SystemMessageReset:
            typeText << "Meta Event ";
            DecodeMetaEvent(s);
            break;
        default:
            typeText << "Unknown Type";
            eventType = EventType::Unknown;
    }
}

void MidiEvent::DecodeMetaEvent(BinData::FileStream* s)
{
    BinData::UInt8Field opcode;
    BinData::UInt8Field param;
    BinData::UInt24Field tempo;
    //s->Read(&opcode);
    ReadData(s, &opcode);

    switch (opcode.Value())
    {
        case MetaEventTempo:
            ReadData(s, &param);
            //s->Read(&param);

            if (param.Value() != MetaEventTempoPrefix)
            {
                details << "Invalid Tempo Change";
                eventType = EventType::Unknown;
                return;
            }

            s->Read(&tempo);
            details << "Tempo " << tempo.ToString() 
                     << " microseconds per quarter note";
            break;
        case MetaEventEndOfTrack:
            ReadData(s, &param);
            //s->Read(&param);

            if (param.Value() != MetaEventEndOfTrackSuffix)
            {
                details << "Invalid End of Track";
                eventType = EventType::Unknown;
                return;
            }

            details << "End of Track";
            eventType = EventType::EndOfTrack;
            break;
        default:
            details << "Unknown Type";
            eventType = EventType::Unknown;
    }
}

void MidiEvent::ReadData(BinData::FileStream* s, BinData::Field* f)
{
    s->Read(f);
    dataText << f->ToString(BinData::Format::Hex) << " ";
    bytesDecoded += 1;
}
