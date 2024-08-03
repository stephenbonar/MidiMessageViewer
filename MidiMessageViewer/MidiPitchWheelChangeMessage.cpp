// MidiPitchWheelChangeMessage.cpp - Defines the MidiPitchWheelChangeMessage class.
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

#include "MidiPitchWheelChangeMessage.h"

void MidiPitchWheelChangeMessage::FinishDecoding(BinData::FileStream* s)
{
    type = MidiEventType::PitchWheelChangeMessage;
    typeText += "Pitch Wheel Change";
    //MidiChannelMessage::FinishDecoding(s);

    // The pitch wheel value is comprised of two 7-bit values that we need
    // to combine.
    BinData::UInt8Field leastSignificantBits = ReadDataByte(s);
    BinData::UInt8Field mostSignificantBits = ReadDataByte(s);

    // First, copy the least significant bits into an int.
    int combinedBits = leastSignificantBits.Value();

    // Then, left-bit shift the most significant bits to the left by 7
    // because it is a 7-bit value, and bitwise or it to the least
    // significatn bits to combine them. 
    combinedBits |= mostSignificantBits.Value() << 7;

    details += " pitch wheel value " + std::to_string(combinedBits);
}