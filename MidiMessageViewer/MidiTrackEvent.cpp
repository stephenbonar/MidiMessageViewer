// MidiTrackEvent.h - Defines the MidiTrackEvent class.
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

#include "MidiTrackEvent.h"

std::string MidiTrackEvent::DeltaTime()
{
    if (deltaTime != nullptr)
        return std::to_string(deltaTime->Value());
    else
        return "N/A";
}

void MidiTrackEvent::StartDecoding(BinData::FileStream* s)
{
    deltaTime = std::make_shared<VariableLengthQuantity>();
    subDecoders.push_back(deltaTime);
    decodeQueue.push_back(deltaTime);

    midiEvent = std::make_shared<MidiEvent>();
    subDecoders.push_back(midiEvent);
    decodeQueue.push_back(midiEvent);
}

void MidiTrackEvent::FinishDecoding(BinData::FileStream* s)
{
    dataText += deltaTime->ToString();
    UpdateTypeInfo(midiEvent.get());
}
