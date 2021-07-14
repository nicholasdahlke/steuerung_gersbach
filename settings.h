#include <wx/wx.h>
#include <string>
#include <vector>
#include <filesystem>

class Settings : public wxDialog {
public:
    Settings(const wxString& title);
    wxString server = "";
    wxString port = "";


private:
    wxTextCtrl* server_ptr;
    wxTextCtrl* port_ptr;
    void OnClose(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    bool ReadText(wxTextCtrl *textCtrl, wxString *content);
    bool writeSettings(std::vector<std::vector<wxString>> content);

    void readToml(std::string content, wxTextCtrl *textCtrl);
    std::string getConfFile();
};