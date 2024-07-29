// StatusByte.h - Declares the StatusByte class.
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

#ifndef STATUS_BYTE_H
#define STATUS_BYTE_H

#include <memory>
#include "MidiConstants.h"
#include "MidiEventType.h"
#include "BinData.h"

class StatusByte
{
public:
    StatusByte() : isRunning{ false }
    {
        byte = std::make_shared<BinData::UInt8Field>();
    }

    MidiEventType EventType();

    int Data() { return byte->Value() & StatusCodeDataMask; }

    std::shared_ptr<BinData::UInt8Field> Value() { return byte; }

    bool IsValid();

    bool IsRunning() { return isRunning; };

    void SetIsRunning(bool value) { isRunning = value; }
private:
    bool isRunning;
    std::shared_ptr<BinData::UInt8Field> byte;
};

#endif