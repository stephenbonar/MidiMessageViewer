// VariableLengthQuantity.h - Declares the VariableLengthQuantity class.
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

#ifndef VARIABLE_LENGTH_QUANTITY_H
#define VARIABLE_LENGTH_QUANTITY_H

#include <vector>
#include <sstream>
#include "BinData.h"
#include "MidiConstants.h"
#include "MidiDataDecoder.h"

class VariableLengthQuantity : public MidiDataDecoder
{
public:
    VariableLengthQuantity() : hasDecoded{ false } { }

    virtual size_t Size() override { return bytes.size(); }

    virtual bool HasDecoded() override { return hasDecoded; }

    virtual std::string ToString() override;

    int Value();
protected:
    virtual bool HasSubDecoders() override { return false; }

    virtual std::shared_ptr<MidiDataDecoder> NextSubDecoder() override 
    {
        return nullptr;
    };

    virtual size_t BytesDecoded() override 
    { 
        return hasDecoded ? bytes.size() : 0; 
    }

    virtual void FinishDecoding(BinData::FileStream* s) override;
private:
    bool hasDecoded;
    std::vector<BinData::UInt8Field> bytes;
};

#endif