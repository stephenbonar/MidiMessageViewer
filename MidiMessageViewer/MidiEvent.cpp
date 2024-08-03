// MidiEvent.cpp - Defines the MidiEvent class.
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

#include "MidiEvent.h"

std::shared_ptr<StatusByte> MidiEvent::lastStatusByte;

void MidiEvent::StartDecoding(BinData::FileStream* s)
{
    statusByte = std::make_shared<StatusByte>();
    subDecoders.push_back(statusByte);
    decodeQueue.push_back(statusByte);
}

void MidiEvent::FinishDecoding(BinData::FileStream* s)
{
    if (!statusByte->IsValid())
    {
        if (MidiEvent::lastStatusByte != nullptr)
        {
            statusByte = MidiEvent::lastStatusByte;
            statusByte->SetIsRunning(true);
            typeText += "(Running)";
        }
        else
        {
            typeText += "Unknown";
            type = MidiEventType::Unknown;
            dataText = statusByte->ToString();
            return;
        }
        

        // Go back one because we just consumed a data byte instead of a status
        // byte. The next decoder will need to consume this same byte.
        s->SetOffset(s->Offset() - 1);
    }
    else
    {
        dataText += statusByte->Value()->ToString(BinData::Format::Hex);
        MidiEvent::lastStatusByte = statusByte;
    }

    switch (statusByte->EventType())
    {
        case MidiEventType::NoteOnMessage:
            midiMessage = std::make_shared<MidiNoteOnMessage>(statusByte);
            break;
        case MidiEventType::ControlChangeMessage:
            midiMessage = std::make_shared<MidiControlChangeMessage>(statusByte);
            break;
        case MidiEventType::ProgramChangeMessage:
            midiMessage = std::make_shared<MidiProgramChangeMessage>(statusByte);
            break;
        case MidiEventType::PitchWheelChangeMessage:
            midiMessage = std::make_shared<MidiPitchWheelChangeMessage>(statusByte);
            break;
        case MidiEventType::SystemMessage:
            midiMessage = std::make_shared<MidiSystemMessage>(statusByte);
            break;
        default:
            typeText += "Unknown";
    }

    if (midiMessage != nullptr)
    {
        subDecoders.push_back(midiMessage);
        midiMessage->Decode(s);
        hasDecoded = true;
        UpdateTypeInfo(midiMessage.get());
    }

    //MidiEventDecoder::FinishDecoding(s);

    //midiEvent = std::make_shared<MidiEvent>();
    
    
    //decodeQueue.push_back(midiEvent);
    
    /*
    deltaTime.Decode(s);
    bytesDecoded += deltaTime.Size();
    dataText = deltaTime.ToString();

    subDecoder = std::make_unique<MidiEvent>();

    MidiEventDecoder::FinishDecoding(s);
    */
}