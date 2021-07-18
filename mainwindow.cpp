#include "mainwindow.h"
#include <wx/wx.h>
#include "settings.h"
#include "controller.h"

enum {
    ID_SETTINGS = 1,
    ID_BUTTON1 = 2,
    ID_CONNECT = 3,
    ID_BUTTON2 = 4,
    ID_BUTTON3 = 5,
    ID_BUTTON4 = 6
};

MainWindow::MainWindow() : wxFrame(NULL, wxID_ANY, "Sternwarte", wxDefaultPosition, wxSize(700, 700)) {
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_SETTINGS, "&Einstellungen","Ruft die Einstellungen auf");
    menuFile->Append(ID_CONNECT, "&Verbinden", "Verbindung mit dem Server aufbauen");
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

    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    wxStaticBoxSizer *hbox1 = new wxStaticBoxSizer(wxHORIZONTAL, panel, "Steuerung 12V");
    wxStaticBoxSizer *hbox2 = new wxStaticBoxSizer(wxHORIZONTAL,panel, "Steuerung Montierung");

    wxStaticText *text1 = new wxStaticText(panel, -1, wxT("12V"));
    wxStaticText *text2 = new wxStaticText(panel, -1, wxT("Montierung"));

    wxButton *button1 = new wxButton(panel, ID_BUTTON1, wxT("Aus"));
    wxButton *button2 = new wxButton(panel, ID_BUTTON2, wxT("An"));
    wxButton *button3 = new wxButton(panel, ID_BUTTON3, wxT("An"));
    wxButton *button4 = new wxButton(panel, ID_BUTTON4, wxT("Aus"));

    hbox1->Add(text1, 1, wxEXPAND | wxALL, 20);
    hbox1->Add(button1, 1, wxEXPAND | wxALL, 20);
    hbox1->Add(button2, 1, wxEXPAND | wxALL, 20);
    hbox2->Add(text2, 1, wxEXPAND | wxALL, 20);
    hbox2->Add(button3, 1, wxEXPAND | wxALL, 20);
    hbox2->Add(button4, 1, wxEXPAND | wxALL, 20);
    topSizer->Add(hbox1, 1, wxEXPAND | wxALL, 20);
    topSizer->Add(hbox2, 1, wxEXPAND | wxALL, 20);

    panel->SetSizer(topSizer);

    Connect(ID_BUTTON1, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainWindow::OnButton));
    Bind(wxEVT_MENU, &MainWindow::OnSettings, this, ID_SETTINGS);
    Bind(wxEVT_MENU, &MainWindow::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainWindow::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MainWindow::OnConnect, this, ID_CONNECT);

    button1->SetFocus();
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

void MainWindow::OnConnect(wxCommandEvent &event) {
    Controller *connection = new Controller();
    Settings *settings = new Settings();

    connection->setIp(std::string(settings->getIp()));
    connection->setPort(std::string(settings->getPort()));
    connection->getConnectionStatus();


}