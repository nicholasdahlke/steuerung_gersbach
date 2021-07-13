#include <wx/wx.h>
class MainWindow : public wxFrame {
public:
    MainWindow();


private:
    void OnSettings(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnButton(wxCommandEvent& event);
};