#pragma once

#include "gl_canvas.hpp"
#include <wx/aui/aui.h>

enum
{
    ID_OPEN_3D_MODEL_MENUITEM = wxID_HIGHEST + 1,
    ID_COMPILE_MENUITEM = wxID_HIGHEST + 2
};

class app_frame final : public wxFrame
{
public:
    app_frame(const wxString& title);

private:
    wxAuiManager m_aui_mgr;

    void on_exit(wxCommandEvent& event);
    void on_open_3d_model_clicked(wxCommandEvent& event);
    void on_compile_menu_clicked(wxCommandEvent& event);
};

class app final : public wxApp
{
public:
    virtual bool OnInit() override;
};
