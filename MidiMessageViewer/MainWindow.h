// MainWindow.h - Declares the MainWindow class.
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

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <sstream>
#include <memory>
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/combobox.h>
#include "MidiData.h"

/// @brief Represents the application's main window. 
class MainWindow : public wxFrame
{
public:
    /// @brief Default constructor; creates a new instance of MainWindow. 
    MainWindow();
private:
    wxComboBox* trackComboBox;
    wxListView* messageListView;
    std::unique_ptr<MidiData::File> currentFile;

    /// @brief The event handler for the Open File menu item.
    /// @param event The event that fired.
    void OnOpen(wxCommandEvent& event);

    /// @brief The event handler for exiting the application.
    /// @param event The event that fired.
    void OnExit(wxCommandEvent& event);

    /// @brief The event handler for the About menu item. 
    /// @param event The event that fired.
    void OnAbout(wxCommandEvent& event);

    /// @brief The event handler for the track selection drop-down. 
    /// @param event The event that fired.
    void OnTrackSelect(wxCommandEvent& event);
};

#endif