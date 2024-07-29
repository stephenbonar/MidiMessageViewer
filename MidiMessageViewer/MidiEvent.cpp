// MidiEvent.cpp - Defines the MidiEvent class.
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

StatusByte MidiEvent::lastStatusByte{ };

void MidiEvent::DecodeSelf(BinData::FileStream* s)
{
    s->Read(statusByte.Value().get());
    bytesDecoded++;
    typeText = "Event";

    if (!statusByte.IsValid())
    {
        statusByte = MidiEvent::lastStatusByte;
        statusByte.SetIsRunning(true);
        typeText = "(Running)";

        // Go back one because we just consumed a data byte instead of a status
        // byte. The next decoder will need to consume this same byte.
        s->SetOffset(s->Offset() - 1);
    }
    else
    {
        dataText = statusByte.Value()->ToString(BinData::Format::Hex);
        MidiEvent::lastStatusByte = statusByte;
    }

    switch (statusByte.EventType())
    {
        case MidiEventType::ControlChangeMessage:
            subDecoder = std::make_unique<MidiControlChangeMessage>(statusByte);
            break;
        case MidiEventType::ProgramChangeMessage:
            subDecoder = std::make_unique<MidiProgramChangeMessage>(statusByte);
            break;
        case MidiEventType::SystemMessage:
            subDecoder = std::make_unique<MidiSystemMessage>(statusByte);
            break;
        default:
            typeText += " unknown";
    }

    MidiEventDecoder::DecodeSelf(s);
}