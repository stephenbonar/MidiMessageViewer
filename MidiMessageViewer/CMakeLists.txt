# CMakeLists.txt - CMakeLists for building the main program.
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

# Define the sources used to build the executable.
set(SOURCES MidiMessageViewer.cpp MainWindow.cpp)

# Define the additional libraries the GUI needs to link with. 
set(LIBRARIES wx::net wx::core wx::base)

# Define the Windows GUI executable target.
if(WIN32)
    add_executable(MidiMessageViewer WIN32 ${SOURCES})
else()
    add_executable(MidiMessageViewer ${SOURCES})
endif(WIN32)

# Links the executable with the libraries. 
target_link_libraries(MidiMessageViewer ${LIBRARIES})