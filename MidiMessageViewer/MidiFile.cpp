// MidiFile.h - Defines the MidiFile class.
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

#include "MidiFile.h"

void MidiFile::Load()
{
    Open();

    Read(&fileHeader);
    Read(&headerData);

    std::shared_ptr<BinData::ChunkHeader> mtrkHeader;

    do
    {
        mtrkHeader = FindChunkHeader("MTrk", BinData::Endianness::Big);

        if (mtrkHeader != nullptr)
        {
            size_t beginning = mStream->Offset();
            size_t end = beginning + mtrkHeader->Size()->Value();

            MidiTrack track{ mtrkHeader };
            track.Decode(mStream.get());
            tracks.push_back(track);

            if (mStream->Offset() != end)
                mStream->SetOffset(end);
        }
    }
    while (mtrkHeader != nullptr);
}