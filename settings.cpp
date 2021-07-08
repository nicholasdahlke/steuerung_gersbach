#include "settings.h"
#include <string>
#include "tomlcpp.hpp"
#include <vector>


#ifdef _WIN64
#define WINDOWS
}
#endif

#ifdef __linux__
#define LINUX
#endif

#ifdef __APPLE__
#define APPLE
#endif


enum {
    ID_SAVE=3,
    ID_CLOSE=4,
    ID_SERVER=5
};

std::string GetEnv( const std::string & var ) {
    const char * val = std::getenv( var.c_str() );
    if ( val == nullptr ) {
        return "";
    }
    else {
        return val;
    }
}


std::string getConfigPath(){
#ifdef WINDOWS
#endif
#ifdef LINUX
    if(GetEnv("XDG_CONFIG_HOME") == "") {
        return GetEnv("HOME") + "/.config";
    } else {
        return GetEnv("XDG_CONFIG_HOME");
    }
#endif

}

Settings::Settings(const wxString &title) : wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(400,240)) {
    wxPanel *panel = new wxPanel(this, -1);

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

    wxStaticBox *st = new wxStaticBox(panel, -1, wxT("Einstellungen"), wxPoint(5,5), wxSize(400,150));

    wxStaticText *text = new wxStaticText(panel, -1, wxT("Server IP"), wxPoint(5,35));

    wxTextCtrl *tc = new wxTextCtrl(panel, -1, wxT(" "), wxPoint(100,35));

    wxButton *okButton = new wxButton(this, ID_SAVE, wxT("Speichern"), wxDefaultPosition, wxSize(70,30));
    wxButton *closeButton = new wxButton(this, ID_CLOSE, wxT("Schließen"), wxDefaultPosition, wxSize(70,30));

    hbox->Add(okButton, 1);
    hbox->Add(closeButton, 1, wxLEFT, 5);

    vbox->Add(panel, 1);
    vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    SetSizer(vbox);

    Connect(ID_CLOSE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Settings::OnClose));
    Connect(ID_SAVE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Settings::OnSave));

    Centre();
    ShowModal();

    Destroy();
}
bool Settings::ReadSettings(wxTextCtrl *textCtrl, wxString* content) {
    wxString text = textCtrl->GetValue();
    if(text == ""){
        return false;
    }
    *content = text;
    return true;
}

void Settings::OnSave(wxCommandEvent &event) {
    std::cout << getConfigPath() << std::endl;
    wxString * serverPtr = &server;
    ReadSettings(tc,serverPtr);
    std::cout << Settings::server << std::endl;
    Close(true);
}

void Settings::OnClose(wxCommandEvent &event) {
    Close(true);
}
