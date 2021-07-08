#include <wx/wx.h>
#include <string>

class Settings : public wxDialog {
public:
    Settings(const wxString& title);
    std::string config_path;
    wxString server;
    wxString port;

private:
    void OnClose(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    bool ReadSettings(wxTextCtrl *textCtrl, wxString *content);
    wxTextCtrl *tc;
};