
// MidiMessage.cpp - Defines the MidiMessage class.
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

#include "MidiMessage.h"

BinData::UInt8Field MidiMessage::ReadDataByte(BinData::FileStream* s)
{
    BinData::UInt8Field byte;
    s->Read(&byte);
    dataText += byte.ToString(BinData::Format::Hex) + " ";
    return byte;
}

void MidiMessage::DecodeDataByte(std::string label, BinData::FileStream* s)
{
    BinData::UInt8Field byte = ReadDataByte(s);
    details += " " + label + " " + byte.ToString();
}

void MidiMessage::DecodeSelf(BinData::FileStream* s)
{
    details = statusDataLabel;
    details += " " + std::to_string(statusByte.Data());
}