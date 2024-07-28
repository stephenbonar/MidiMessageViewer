// MidiTrack.cpp - Defines the MidiTrack class.
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

#include "MidiTrack.h"

bool MidiTrack::HasSubDecoders()
{
    if (BytesDecoded() < Size())
    {
        if (events.size() > 0)
        {
            if (events.back()->Type() == MidiEvent::EventType::Unknown)
                return false;
            else if (events.back()->Type() == MidiEvent::EventType::EndOfTrack)
                return false;
            else
                return true;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}

std::shared_ptr<MidiDataDecoder> MidiTrack::NextSubDecoder()
{
    auto nextEvent = std::make_shared<MidiEvent>();
    events.push_back(nextEvent);
    return nextEvent;
}

size_t MidiTrack::BytesDecoded()
{
    size_t bytesDecoded = 0;

    for (std::shared_ptr<MidiEvent> event : events)
        bytesDecoded += event->Size();

    return bytesDecoded;
}

void MidiTrack::DecodeSelf(BinData::FileStream* s)
{
    if (events.back()->Type() != MidiEvent::EventType::Unknown)
    {
        if (BytesDecoded() == Size())
            hasDecoded = true;
    }
}