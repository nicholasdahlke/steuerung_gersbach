#include <wx/wx.h>
#include <string>
#include <vector>
#include <filesystem>

class Settings : public wxDialog {
public:
    Settings(const wxString& title);
    std::string config_path;
    wxString server = "";
    wxString port = "";
    wxTextCtrl* server_ptr;
    wxTextCtrl* port_ptr;

private:
    void OnClose(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnTextEditChange(wxCommandEvent& event);
    bool ReadText(wxTextCtrl *textCtrl, wxString *content);
    bool writeSettings(std::string section,std::vector<std::vector<wxString>> content);
    bool checkIllegalCharacters(wxTextCtrl *textCtrl, std::vector<int> characters, wxCommandEvent *event);
    bool returnIllegalPosition(int (*callbackFunc)(int), wxString string, wxTextCtrl *text);
};