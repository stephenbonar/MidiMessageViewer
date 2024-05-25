// MidiHeaderData.h - Declares the MidiHeaderData class.
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

#ifndef MIDI_HEADER_DATA_H
#define MIDI_HEADER_DATA_H

#include <vector>
#include <memory>
#include "BinData.h"

class MidiHeaderData : public BinData::FieldStruct
{
public:
    MidiHeaderData() : 
        fields
        {
            std::make_shared<BinData::UInt16Field>(BinData::Endianness::Big),
            std::make_shared<BinData::UInt16Field>(BinData::Endianness::Big),
            std::make_shared<BinData::UInt16Field>(BinData::Endianness::Big)
        }
    { }

    std::shared_ptr<BinData::UInt16Field> Format()
    { 
        return std::static_pointer_cast<BinData::UInt16Field>(fields.at(0));
    }

    std::shared_ptr<BinData::UInt16Field> NumTracks()
    { 
        return std::static_pointer_cast<BinData::UInt16Field>(fields.at(1));
    }

    std::shared_ptr<BinData::UInt16Field> Division()
    { 
        return std::static_pointer_cast<BinData::UInt16Field>(fields.at(2));
    }

    std::vector<std::shared_ptr<BinData::Field>> Fields() const override
    {
        return fields; 
    }
private:
    std::vector<std::shared_ptr<BinData::Field>> fields;
};

#endif