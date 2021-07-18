#include <wx/wx.h>
#include <string>
#include <vector>
#include <filesystem>

class Settings : public wxDialog {
public:
    Settings(const wxString& title);
    Settings();
    wxString server = "";
    wxString port = "443";
    std::string getIp(){return std::string(server);};
    std::string getPort(){return std::string(port);};


private:
    wxTextCtrl* server_ptr;
    wxTextCtrl* port_ptr;
    void OnClose(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    bool ReadText(wxTextCtrl *textCtrl, wxString *content);
    bool writeSettings(std::vector<std::vector<wxString>> content);
    std::string readToml(std::string content);
    std::string getConfFile();
};