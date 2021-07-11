#include "settings.h"
#include <string>
#include "tomlcpp.hpp"
#include <vector>
#include <sys/stat.h>
#include <cstring>
#include <wx/textfile.h>
#include <wx/filefn.h>
#include <wx/wx.h>
#include <cctype>

struct stat info;

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
    ID_SERVER=5,
    ID_PORT=6
};
enum {
    ALNUM=1,
    ALPHA=2,
    DIGIT=3,
    SPACE=4
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

    wxStaticText *text_server = new wxStaticText(panel, -1, wxT("Server IP"), wxPoint(5,35));
    wxStaticText *text_port = new wxStaticText(panel, -1, wxT("Server Port"), wxPoint(5,75));

    wxTextCtrl *server_tc = new wxTextCtrl(panel, ID_SERVER, wxT(" "), wxPoint(100,35));
    wxTextCtrl *port_tc = new wxTextCtrl(panel, ID_PORT, wxT(" "), wxPoint(100,75));

    Settings::server_ptr = server_tc;
    Settings::port_ptr = port_tc;

    wxButton *okButton = new wxButton(this, ID_SAVE, wxT("Speichern"), wxDefaultPosition, wxSize(70,30));
    wxButton *closeButton = new wxButton(this, ID_CLOSE, wxT("Schließen"), wxDefaultPosition, wxSize(70,30));

    hbox->Add(okButton, 1);
    hbox->Add(closeButton, 1, wxLEFT, 5);

    vbox->Add(panel, 1);
    vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    SetSizer(vbox);

    Connect(ID_CLOSE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Settings::OnClose));
    Connect(ID_SAVE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Settings::OnSave));
    Bind(wxEVT_TEXT, &Settings::OnTextEditChange, this, ID_SERVER);
    Bind(wxEVT_TEXT, &Settings::OnTextEditChange, this, ID_PORT);


    Centre();
    ShowModal();

    Destroy();
}
bool Settings::ReadText(wxTextCtrl *textCtrl, wxString* content) {
    wxString text = textCtrl->GetValue();
    if(text == ""){
        return false;
    }
    *content = text;
    return true;
}

bool Settings::writeSettings(std::string section, std::vector<std::vector<wxString>> content) {
    std::string config_path = getConfigPath() + "/sternwarte_gersbach";
    wxString config_file(config_path + "/config.toml");
    wxString conf_path(config_path);


    if (!wxDirExists(conf_path) && !wxMkdir(conf_path,0777))
        return false;

    wxTextFile file(config_file);

    if (!wxFileExists(config_file))
        file.Create();

    if(!file.Open())
        return false;

    file.Clear();

    file.AddLine("title = \"Sternwarten Config\"");
    file.AddLine(wxT(""));
    file.AddLine("[" + section + "]");

    for (int i = 0; i < 2; ++i) {
        file.AddLine(content[i][0] + "=\"" + content[i][1] + "\"");
    }

    file.Write();
    file.Close();

    return true;
}

void Settings::OnSave(wxCommandEvent &event) {
    ReadText(Settings::server_ptr, &server);
    ReadText(Settings::port_ptr, &port);
    std::vector< std::vector<wxString> > settings(2, std::vector<wxString>(2));
    settings[0][0] = wxT("server");
    settings[1][0] = wxT("port");
    settings[0][1] = Settings::server;
    settings[1][1] = Settings::port;

    Settings::writeSettings("server", settings);

    Close(true);
}

void Settings::OnClose(wxCommandEvent &event) {
    Close(true);
}

void Settings::OnTextEditChange(wxCommandEvent &event) {

}

bool Settings::checkIllegalCharacters(wxTextCtrl *textCtrl, std::vector<int> characters, wxCommandEvent *event) {
    if (event == nullptr)
        return false;

    auto returnIllegalPosition = [](bool (*callbackFunc)(int), wxString string, wxTextCtrl *text) {
        for(int i = 0; i < string.size(); i++){
            if(!(*callbackFunc)(string[i]))
                text->Remove(i,i);
        }
    };

    wxString text = event->GetString();
    for (auto const& value: characters) {
        switch (value) {
            case ALNUM:
                if (!returnIllegalPosition(reinterpret_cast<bool (*)(int)>(isalnum), value, textCtrl));
                return false;
            case ALPHA:
                sd;

            case DIGIT:
                sd;

            case SPACE:
                sd;
        }
    }
}
