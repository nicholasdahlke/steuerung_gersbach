#include "wx/wxprec.h"
#include <iostream>
#include "settings.h"
#include "mainwindow.h"
#include <string>
#include "controller.h"
#ifndef WXWX_PRECOMP
#include <wx/wx.h>
#endif

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};



wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    MainWindow *frame = new MainWindow();
    frame->Show(true);
    return true;
}

