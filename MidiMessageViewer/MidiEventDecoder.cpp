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
    for (std::shared_ptr<MidiDataDecoder> subDecoder : subDecoders)
    {
        if (!subDecoder->HasDecoded())
            return false;
    }

    return hasDecoded;
}

size_t MidiEventDecoder::Size()
{   
    size_t subDecoderSize{ 0 };

    for (std::shared_ptr<MidiDataDecoder> subDecoder : subDecoders)
        subDecoderSize += subDecoder->Size();
    
    return size + subDecoderSize;
}

std::string MidiEventDecoder::ToString()
{
    return dataText; 
}

std::string MidiEventDecoder::Details()
{
    return details;
}

std::string MidiEventDecoder::TypeText()
{
    return typeText;
}

MidiEventType MidiEventDecoder::Type()
{
    return type;
}

std::shared_ptr<MidiDataDecoder> MidiEventDecoder::NextSubDecoder()
{
    if (!decodeQueue.empty())
    {
        std::shared_ptr<MidiDataDecoder> subDecoder = decodeQueue.front();
        decodeQueue.pop_front();
        return subDecoder;
    }
    else
    {
        return nullptr;
    }
}

bool MidiEventDecoder::HasSubDecoders()
{
    if (!decodeQueue.empty())
    {
        return true;
    }
    else
    {
        return false;
    }
}

size_t MidiEventDecoder::BytesDecoded()
{
    size_t subDecoderBytesDecoded{ 0 };

    if (subDecoders.size() > 0)
    {
        for (std::shared_ptr<MidiDataDecoder> subDecoder : subDecoders)
            subDecoderBytesDecoded += subDecoder->BytesDecoded();
    }

    return bytesDecoded + subDecoderBytesDecoded;
}

BinData::UInt8Field MidiEventDecoder::ReadDataByte(BinData::FileStream* s)
{
    BinData::UInt8Field byte;
    s->Read(&byte);
    dataText += byte.ToString(BinData::Format::Hex) + " ";
    return byte;
}

void MidiEventDecoder::DecodeDataByte(std::string label, BinData::FileStream* s)
{
    BinData::UInt8Field byte = ReadDataByte(s);
    details += " " + label + " " + byte.ToString();
}

void MidiEventDecoder::DecodeDataField(std::string label, 
                                       BinData::Field* f, 
                                       BinData::FileStream* s)
{
    s->Read(f);
    dataText += f->ToString(BinData::Format::Hex) + " ";
    details += " " + label + " " + f->ToString();
}

void MidiEventDecoder::UpdateTypeInfo(MidiEventDecoder* subDecoder)
{
    type = subDecoder->Type();
    typeText += " " + subDecoder->TypeText();
    dataText += " " + subDecoder->ToString();
    details += " " + subDecoder->Details();
}

/*
void MidiEventDecoder::FinishDecoding(BinData::FileStream* s)
{
    if (subDecoder != nullptr)
        subDecoder->Decode(s);
}*/