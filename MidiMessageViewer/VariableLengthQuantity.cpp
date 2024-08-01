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
    BinData::UInt8Field currentByte{ 0, BinData::Endianness::Big };

    // Account for a situation where the VariableLengthQuantity is decoded
    // more than once (TODO: prevent multiple decodings).
    bytes.clear();

    // Assume each byte read from the file is part of the variable length 
    // quantity as long as the continuation bit is set on the currentByte.
    do
    {
        s->Read(&currentByte);
        bytes.push_back(currentByte);
    } 
    while ((currentByte.Value() & ContinuationBitMask) == ContinuationBitMask);

    hasDecoded = true;
}

int VariableLengthQuantity::Value()
{
    // We will need to shift the value of each byte to the left by multiples of
    // 7 bits because only the last 7 bits of the byte represent the value.
    constexpr int bitsPerByte{ 7 };

    // The first byte (most significant) will need to be shifted by bitsPerByte
    // times the bitShiftMultiplier to ensure each byte is shifted the correct
    // number of bits. 
    size_t bitShiftMultiplier{ bytes.size() - 1 };

    int value{ 0 };

    for (int i = 0; i < bytes.size(); i++)
    {
        BinData::UInt8Field currentByte = bytes.at(i);

        // If the continuation bit is set, we toggle it off using bitwise XOR
        // so it is not included in the value. 
        if ((currentByte.Value() & ContinuationBitMask) == ContinuationBitMask)
            currentByte.SetValue(currentByte.Value() ^ ContinuationBitMask);

        // Shift by 21, 14, 7, or 0 depending on the number of shifts we need.
        size_t bitsToShift{ bitsPerByte * bitShiftMultiplier };

        // Shift the bits and use bitwise OR to combine the newly shifted bits
        // with the ones already applied to the value.
        value |= (currentByte.Value() << bitsToShift);

        // Each subsequent byte needs to be shifted by 7 less bits.
        bitShiftMultiplier--;
    }

    return value;
}

std::string VariableLengthQuantity::ToString()
{
    std::stringstream byteString;

    // Bytes are output raw, including the continuation bits. That said,
    // this method does not return the hex values of the decoded number,
    // but rather the underlying encoded bytes. 
    for (BinData::UInt8Field byte : bytes)
        byteString << byte.ToString(BinData::Format::Hex) << " ";
    
    return byteString.str();
}