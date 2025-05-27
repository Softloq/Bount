#pragma once

#include <wx/wx.h>

enum
{
    ID_COMPILE_MENUITEM = wxID_HIGHEST + 1
};

class AppFrame final : public wxFrame
{
public:
    AppFrame(const wxString &title);

private:
    void OnExit(wxCommandEvent &event);
    void OnCompileMenuClicked(wxCommandEvent &event);
};

class App final : public wxApp
{
public:
    virtual bool OnInit() override;
};
