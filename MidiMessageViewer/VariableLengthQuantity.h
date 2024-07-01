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
#include "BinData.h"

class VariableLengthQuantity
{
public:
    VariableLengthQuantity() { }

    size_t Length() { return bytes.size(); }

    int Value();

    void Load(BinData::FileStream* s);
private:
    std::vector<BinData::UInt8Field> bytes;
};

#endif