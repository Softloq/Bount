#pragma once

#include <wx/wx.h>

class AppFrame final : public wxFrame
{
public:
    AppFrame(const wxString &title);

private:
    void OnExit(wxCommandEvent &event);
};

class App final : public wxApp
{
public:
    virtual bool OnInit() override;
};
