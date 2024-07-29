// MidiEventDecoder.cpp - Defines the MidiEventDecoder class.
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

#include "MidiEventDecoder.h"

bool MidiEventDecoder::HasDecoded()
{
    if (subDecoder != nullptr)
        return hasDecoded && subDecoder->HasDecoded();
    else
        return hasDecoded;
}

size_t MidiEventDecoder::Size()
{   
    if (subDecoder != nullptr)
        return size + subDecoder->Size();
    else
        return size;
}

std::string MidiEventDecoder::ToString()
{
    if (subDecoder != nullptr)
        return dataText + " " + subDecoder->ToString();
    else 
        return dataText; 
}

std::string MidiEventDecoder::Details()
{
    if (subDecoder != nullptr)
        return details + " " + subDecoder->Details();
    else 
        return details;
}

std::string MidiEventDecoder::TypeText()
{
    if (subDecoder != nullptr)
        return typeText + " " + subDecoder->TypeText();
    else 
        return typeText; 
}

MidiEventType MidiEventDecoder::Type()
{
    if (subDecoder != nullptr)
        return subDecoder->Type();
    else 
        return type;
}

size_t MidiEventDecoder::BytesDecoded()
{
    if (subDecoder != nullptr)
        return bytesDecoded + subDecoder->BytesDecoded();
    else
        return bytesDecoded;
}

void MidiEventDecoder::DecodeSelf(BinData::FileStream* s)
{
    if (subDecoder != nullptr)
        subDecoder->Decode(s);
}