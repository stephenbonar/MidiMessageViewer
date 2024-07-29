// MidiConstants.h - Declares constants associated with MIDI files.
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

#ifndef MIDI_CONSTANTS_H
#define MIDI_CONSTANTS_H

inline constexpr int StatusCodeTypeBitShift{ 4 };
inline constexpr int StatusCodeDataMask{ 0x0F };
inline constexpr int StatusCodeValidationMask{ 0x80 };

inline constexpr int EventNoteOffMessage{ 0x8 };
inline constexpr int EventNoteOnMessage{ 0x9 };
inline constexpr int EventPolyphonicKeyPressureMessage{ 0x9 };
inline constexpr int EventControlChangeMessage{ 0xB };
inline constexpr int EventProgramChangeMessage{ 0xC };
inline constexpr int EventChannelPressureMessage{ 0xD };
inline constexpr int EventPitchWheelChangeMessage{ 0xE };
inline constexpr int EventSystemMessage{ 0xF };

inline constexpr int SystemMessageExclusive{ 0x0 };
inline constexpr int SystemMessageSongPositionPointer{ 0x2 };
inline constexpr int SystemMessageSongSelect{ 0x3 };
inline constexpr int SystemMessageTuneSelect{ 0x6 };
inline constexpr int SystemMessageExclusiveEnd{ 0x7 };
inline constexpr int SystemMessageTimingClock{ 0x8 };
inline constexpr int SystemMessageStart{ 0xA };
inline constexpr int SystemMessageContinue{ 0xB };
inline constexpr int SystemMessageStop{ 0xC };
inline constexpr int SystemMessageActiveSensing{ 0xE };
inline constexpr int SystemMessageReset{ 0xF };

inline constexpr int MetaEventTempo{ 0x51 };
inline constexpr int MetaEventTempoPrefix{ 0x3 };
inline constexpr int MetaEventEndOfTrack{ 0x2F };
inline constexpr int MetaEventEndOfTrackSuffix{ 0x0 };

#endif