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
#include "MidiDataDecoder.h"
#include "BinData.h"

class StatusByte : public MidiDataDecoder
{
public:
    StatusByte() : isRunning{ false }, hasDecoded{ false }
    { 
        byte = std::make_shared<BinData::UInt8Field>();
    }

    /// @brief The amount of bytes the decoder is expected to decode.
    /// @return The number of bytes. 
    virtual size_t Size() override { return 1; }

    /// @brief Determines whether or not the decoder has already decoded data.
    /// @return Returns true if decoding has completed, otherwise false.
    virtual bool HasDecoded() override { return hasDecoded; }

    /// @brief Determines the number of bytes that have been decoded so far. 
    /// @return The number of bytes. 
    virtual size_t BytesDecoded() override;

    /// @brief Provides a string representation of the decoded data.
    /// @return The string representing the decoded data.
    virtual std::string ToString() override;

    MidiEventType EventType();

    int Data() { return byte->Value() & StatusCodeDataMask; }

    std::shared_ptr<BinData::UInt8Field> Value() { return byte; }

    bool IsValid();

    bool IsRunning() { return isRunning; };

    void SetIsRunning(bool value) { isRunning = value; }
protected:
    /// @brief Determines if there are any more child decoders to decode.
    ///
    /// This method is called internally by the Decode() method, so it should
    /// be implemented with this purpose in mind.
    ///
    /// @return Returns true if there are any remaining decoders, else false.
    virtual bool HasSubDecoders() override { return false; }

    /// @brief Provides the next child decoder to decode.
    ///
    /// This method is called internally by the Decode() method to retrieve
    /// the next child decoder and decode the remainng data with it. This 
    /// method should be implemented with this purpose in mind.
    ///
    /// @return A shared pointer to the next decoder, or nullptr if no more.
    virtual std::shared_ptr<MidiDataDecoder> NextSubDecoder() override 
    {
        return nullptr; 
    }

    virtual void FinishDecoding(BinData::FileStream* s) override;
private:
    bool isRunning;
    bool hasDecoded;
    std::shared_ptr<BinData::UInt8Field> byte;
};

#endif