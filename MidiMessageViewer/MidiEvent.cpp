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

    s->Read(&statusCode);
    bytesDecoded += 1;

    switch (statusCode.Value() >> StatusCodeTypeBitShift)
    {
        case EventSystemMessage:
            eventType = EventType::SystemMessage;
            dataText << "System ";
            DecodeSystemMessage(s);
            break;
        default:
            eventType = EventType::Unknown;
            return;
    }
}

void MidiEvent::DecodeSystemMessage(BinData::FileStream* s)
{
    switch (statusCode.Value() & StatusCodeDataMask)
    {
        case SystemMessageReset:
            dataText << "Meta Event ";
            
    }
}
