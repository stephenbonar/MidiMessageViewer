// MainWindow.h - Defines the MainWindow class
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

#include "MainWindow.h"

enum ID
{
    Open = 1
};

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "MidiMessageViewer")
{
    wxPanel* topPanel = new wxPanel{ this, wxID_ANY, wxDefaultPosition };
    //wxPanel* bottomPanel = new wxPanel{ this, wxID_ANY, wxDefaultPosition };
    //bottomPanel->SetBackgroundColour(wxColour{ *wxBLUE });

    wxBoxSizer* topSizer = new wxBoxSizer{ wxHORIZONTAL };
    wxBoxSizer* frameSizer = new wxBoxSizer{ wxVERTICAL };

    wxMenu *fileMenu = new wxMenu;
    fileMenu->Append(ID::Open, "&Open...\tCtrlO",
                     "Open a MIDI file");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT);
 
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(wxID_ABOUT);
 
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(helpMenu, "&Help");

    trackComboBox = new wxComboBox{ topPanel, wxID_ANY, "Track" };

    messageListView = new wxListView{ this, wxID_ANY, 
                                   wxDefaultPosition, wxSize{600, 400} };
    messageListView->AppendColumn("Delta Time", wxLIST_FORMAT_LEFT, 300);
    messageListView->AppendColumn("Status Code");
    messageListView->AppendColumn("Channel");
    messageListView->AppendColumn("Data");

    SetMenuBar(menuBar);
 
    CreateStatusBar();
    SetStatusText("Ready");

    topSizer->Add(trackComboBox, 0, wxALL, 5);
    topPanel->SetSizerAndFit(topSizer);

    frameSizer->Add(topPanel, 0, wxEXPAND);
    frameSizer->Add(messageListView, 1, wxEXPAND);
    SetSizerAndFit(frameSizer);

    Bind(wxEVT_MENU, &MainWindow::OnOpen, this, ID::Open);
    Bind(wxEVT_MENU, &MainWindow::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainWindow::OnExit, this, wxID_EXIT);
}

void MainWindow::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MainWindow::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This function is not yet implemented.",
                 "MidiMessageViewer", wxOK | wxICON_INFORMATION);
}

void MainWindow::OnOpen(wxCommandEvent& event)
{
     wxFileDialog dialog(this, _("Open MIDI file"), "", "",
                        "Media files (*.mid)|*.mid", 
                        wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (dialog.ShowModal() == wxID_OK)
    {
        MidiFile file{ dialog.GetPath().ToStdString() };
        file.Load();
        std::stringstream status;
        status << "Chunk Header: " << file.Header().ID()->ToString() 
               << ", Chunk Size: " << file.Header().Size()->Value()
               << ", Format: " << file.HeaderData().Format()->Value()
               << ", Num Tracks: " << file.HeaderData().NumTracks()->Value()
               << ", Division: " << file.HeaderData().NumTracks()->Value();
        SetStatusText(wxString{ status.str() });
    }
}