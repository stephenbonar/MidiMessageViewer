// VariableLengthQuantity.cpp - Defines the VariableLengthQuantity class.
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

#include "VariableLengthQuantity.h"

void VariableLengthQuantity::DecodeSelf(BinData::FileStream* s)
{
    BinData::UInt8Field nextByte{ 0, BinData::Endianness::Big };
    bytes.clear();

    do
    {
        s->Read(&nextByte);
        bytes.push_back(nextByte);
    } 
    while ((nextByte.Value() & 0x80) == 0x80);

    hasDecoded = true;
}

int VariableLengthQuantity::Value()
{
    // We will need to shift the value of each byte to the left by multiples of
    // 7 bits because only the last 7 bits of the byte represent the value.
    constexpr int bitsToShift{ 7 };

    // The first byte will be the most significant byte, so it will need to be
    // shifted by the number of bytes - 1 when it is combined into the value.
    size_t numberOfShifts{ bytes.size() - 1 };

    int value{ 0 };

    for (int i = 0; i < bytes.size(); i++)
    {
        BinData::UInt8Field currentByte = bytes.at(i);
        size_t bits{ bitsToShift * numberOfShifts };
        value = value & (currentByte.Value() << bits);
        numberOfShifts--;
    }

    return value;
}

std::string VariableLengthQuantity::ToString()
{
    std::stringstream byteString;

    for (BinData::UInt8Field byte : bytes)
        byteString << byte.ToString(BinData::Format::Hex) << " ";
    
    return byteString.str();
}