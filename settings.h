#include <wx/wx.h>
#include <string>
#include <vector>
#include <filesystem>

class Settings : public wxDialog {
public:
    Settings(const wxString& title);
    wxString server = "";
    wxString port = "";
    wxTextCtrl* server_ptr;
    wxTextCtrl* port_ptr;

private:
    void OnClose(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    bool ReadText(wxTextCtrl *textCtrl, wxString *content);
    bool writeSettings(std::string section,std::vector<std::vector<wxString>> content);

    bool readToml(std::string path, std::string section, std::string content);
    std::string getConfFile(std::string a);
};