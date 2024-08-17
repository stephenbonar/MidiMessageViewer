# CMakeLists.txt - CMakeLists for building the project.
#
# Copyright (C) 2024 Stephen Bonar
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http ://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissionsand
# limitations under the License.

cmake_minimum_required(VERSION 3.5.0)
project(MidiMessageViewer VERSION 0.52.0 LANGUAGES C CXX)

# Specify the C++ standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Statically link wxWidgets.
set(wxBUILD_SHARED OFF)

add_subdirectory(MidiMessageViewer)

add_subdirectory(wxWidgets)

add_subdirectory(LibCppMidiData)
