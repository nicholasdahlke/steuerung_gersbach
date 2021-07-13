#include "wx/wxprec.h"
#include <iostream>
#include "settings.h"
#include <string>
#ifndef WXWX_PRECOMP
#include <wx/wx.h>
#endif

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

class MainWindow : public wxFrame {
public:
    MainWindow();


private:
    void OnSettings(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnButton(wxCommandEvent& event);
};

enum {
    ID_SETTINGS = 1,
    ID_BUTTON = 2
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    MainWindow *frame = new MainWindow();
    frame->Show(true);
    return true;
}

MainWindow::MainWindow() : wxFrame(NULL, wxID_ANY, "Sternwarte", wxDefaultPosition, wxSize(700, 700)) {
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_SETTINGS, "&Einstellungen","Ruft die Einstellungen auf");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&Datei");
    menuBar->Append(menuHelp, "&Hilfe");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("Steuerung Sternwarte Gersbach");

    wxPanel *panel = new wxPanel(this, wxID_ANY);

    wxButton *button = new wxButton(panel, ID_BUTTON, wxT("Button"), wxPoint(20,20));

    Connect(ID_BUTTON, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainWindow::OnButton));
    Bind(wxEVT_MENU, &MainWindow::OnSettings, this, ID_SETTINGS);
    Bind(wxEVT_MENU, &MainWindow::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainWindow::OnExit, this, wxID_EXIT);

    button->SetFocus();
    Centre();
}

void MainWindow::OnExit(wxCommandEvent &event) {
    Close(true);
}

void MainWindow::OnAbout(wxCommandEvent &event) {
    wxMessageBox("Geschrieben von Nicholas Dahlke \n nicholas.dahlke@gmx.de", "Über Sternwarten Steuerung Gersbach", wxOK | wxICON_INFORMATION);
}

void MainWindow::OnSettings(wxCommandEvent &event) {
    Settings *settings = new Settings(wxT("Custom Dialog"));
    settings->Show();

}

void MainWindow::OnButton(wxCommandEvent &event) {
    std::cout << "Button pressed" << std::endl;
}