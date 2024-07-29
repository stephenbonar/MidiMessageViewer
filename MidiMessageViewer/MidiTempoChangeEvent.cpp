// MidiTempoChangeEvent.cpp - Defines the MidiTempoChangeEvent class.
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

#include "MidiTempoChangeEvent.h"

void MidiTempoChangeEvent::DecodeSelf(BinData::FileStream* s)
{
    BinData::UInt8Field param;
    BinData::UInt24Field tempo;

    //ReadData(s, &param);
    s->Read(&param);

    if (param.Value() != MetaEventTempoPrefix)
    {
        typeText = "Tempo Change Invalid";
        return;
    }

    s->Read(&tempo);
    type = MidiEventType::TempoChangeEvent;
    typeText = "Tempo Change";
    dataText = param.ToString(BinData::Format::Hex) 
        + " " 
        + tempo.ToString(BinData::Format::Hex);
    details = "Tempo " + tempo.ToString() + " microseconds per quarter note";
}