// MidiDataDecoder.h - Declares the MidiDataDecoder class.
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

#ifndef MIDI_DATA_DECODER_H
#define MIDI_DATA_DECODER_H

#include <string>
#include <vector>
#include <memory>
#include "BinData.h"

/// @brief Abstract base class for all classes that need to decode MIDI data.
///
/// Defines the common functionality for all classes that need to decode MIDI
/// data from a file stream. A class that derives from MidiDataDecoder can
/// also maintain and decode sub-decoders (child MidiDataDecoder instances). 
/// Although most methods are pure-virtual, the Decode() method has a default 
/// implementation that will decode all sub-decoders, as well as the current
/// decoder instance. 
class MidiDataDecoder
{
public:
    /// @brief Virtual destructor; ensures proper cleanup via inheritance.
    virtual ~MidiDataDecoder() = default;

    /// @brief The amount of bytes the decoder is expected to decode.
    /// @return The number of bytes. 
    virtual size_t Size() = 0;

    /// @brief Determines whether or not the decoder has already decoded data.
    /// @return Returns true if decoding has completed, otherwise false.
    virtual bool HasDecoded() = 0;

    /// @brief Determines the number of bytes that have been decoded so far. 
    /// @return The number of bytes. 
    virtual size_t BytesDecoded() = 0;

    /// @brief Provides a string representation of the decoded data.
    /// @return The string representing the decoded data.
    virtual std::string ToString() = 0;

    /// @brief Decodes the data at the current position in the file stream.
    ///
    /// The default implementation of this method calls NextSubDecoder() 
    /// repeatedly to obtain and decode each sub-decoder (child instances of
    /// types derived from MidiDataDecoder) until HasSubDecoders() returns
    /// false. Finally, it calls DecodeSelf() to decode itself. This 
    /// functionality can be adjusted by overriding this method in a derived
    /// class, but it is not required to do so if this implementation is
    /// sufficient.
    ///
    /// It is important for derived types to define HasSubDecoders(),
    /// NextSubDecoder(), and DecodeSelf() with this implementation in mind.
    /// They are protected methods and will thus only be used internally by
    /// this method. But this method (Decode) is the one exposed publically.
    ///
    /// @param s The file stream from which to decode data.
    virtual void Decode(BinData::FileStream* s);
protected:
    /// @brief Determines if there are any more child decoders to decode.
    ///
    /// This method is called internally by the Decode() method, so it should
    /// be implemented with this purpose in mind.
    ///
    /// @return Returns true if there are any remaining decoders, else false.
    virtual bool HasSubDecoders() = 0;

    /// @brief Provides the next child decoder to decode.
    ///
    /// This method is called internally by the Decode() method to retrieve
    /// the next child decoder and decode the remainng data with it. This 
    /// method should be implemented with this purpose in mind.
    ///
    /// @return A shared pointer to the next decoder, or nullptr if no more.
    virtual std::shared_ptr<MidiDataDecoder> NextSubDecoder() = 0;

    virtual void StartDecoding(BinData::FileStream* s) { }

    virtual void FinishDecoding(BinData::FileStream* s) { }
};

#endif