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
    Open = 1,
    TrackSelect = 2
};

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "MidiMessageViewer")
{
    wxPanel* topPanel = new wxPanel{ this, wxID_ANY, wxDefaultPosition };

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

    wxStaticText *trackLabel = new wxStaticText{ topPanel, wxID_ANY, "Track" };
    trackComboBox = new wxComboBox{ topPanel, ID::TrackSelect, "-" };

    messageListView = new wxListView{ this, wxID_ANY, 
                                   wxDefaultPosition, wxSize{600, 400} };
    messageListView->AppendColumn("Track Event Data", wxLIST_FORMAT_LEFT, 300);
    messageListView->AppendColumn("Delta Time");
    messageListView->AppendColumn("Type");
    messageListView->AppendColumn("Details");

    SetMenuBar(menuBar);
 
    CreateStatusBar();
    SetStatusText("Ready");

    topSizer->Add(trackLabel);
    topSizer->Add(trackComboBox, 0, wxALL, 5);
    topPanel->SetSizerAndFit(topSizer);

    frameSizer->Add(topPanel, 0, wxEXPAND);
    frameSizer->Add(messageListView, 1, wxEXPAND);
    SetSizerAndFit(frameSizer);

    Bind(wxEVT_MENU, &MainWindow::OnOpen, this, ID::Open);
    Bind(wxEVT_MENU, &MainWindow::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainWindow::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMBOBOX, &MainWindow::OnTrackSelect, this, ID::TrackSelect);
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
        currentFile = std::make_unique<MidiFile>(dialog.GetPath().ToStdString());
        currentFile->Load();

        std::stringstream status;
        status << "Chunk Header: " << currentFile->Header().ID()->ToString() 
               << ", Chunk Size: " << currentFile->Header().Size()->Value()
               << ", Format: " << currentFile->HeaderData().Format()->Value()
               << ", Num Tracks: " << currentFile->HeaderData().NumTracks()->Value()
               << ", Division: " << currentFile->HeaderData().NumTracks()->Value();
        SetStatusText(wxString{ status.str() });

        int trackNumber{ 0 };

        for (auto track : currentFile->Tracks())
        {
            trackComboBox->AppendString(std::to_string(trackNumber));
            trackNumber++;
        }
    }
}

void MainWindow::OnTrackSelect(wxCommandEvent& event)
{
    int trackNumber{ 0 };
    int selectedTrack{ 0 };
    trackComboBox->GetValue().ToInt(&selectedTrack);

    for (auto track : currentFile->Tracks())
    {
        if (trackNumber == selectedTrack)
        {
            int index{ 0 };
            messageListView->DeleteAllItems();

            for (auto event : track.Events())
            {
                messageListView->InsertItem(index, event->ToString());
                messageListView->SetItem(index, 1, event->DeltaTime());
                messageListView->SetItem(index, 2, event->TypeText());
                messageListView->SetItem(index, 3, event->Details());
                index++;
            }
        }

        trackNumber++;
    }
}