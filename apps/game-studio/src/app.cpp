#include "app.hpp"
#include <bount-filesystem/path.hpp>
#include <wx/dirctrl.h>
#include <cstdlib>

using namespace bount;

app_frame::app_frame(const wxString &title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(600, 480))
{
    // Create a menu bar
    wxMenuBar *menuBar = new wxMenuBar;
    wxMenu *fileMenu = new wxMenu;
    fileMenu->Append(ID_COMPILE_MENUITEM, "Compile", "Compile your project");
    fileMenu->Append(wxID_SEPARATOR);
    fileMenu->Append(wxID_EXIT, "&Exit\tCtrl+Q", "Quit the application");
    menuBar->Append(fileMenu, "&File");
    SetMenuBar(menuBar);

    // Create a status bar
    CreateStatusBar();
    SetStatusText("Welcome to Bount Game Studio!");

    Bind(wxEVT_MENU, &app_frame::on_compile_menu_clicked, this, ID_COMPILE_MENUITEM);
    Bind(wxEVT_MENU, &app_frame::on_exit, this, wxID_EXIT);
}

void app_frame::on_exit(wxCommandEvent &event)
{
    Close(true);
}

void app_frame::on_compile_menu_clicked(wxCommandEvent &event)
{
    wxDirDialog dialog(this, "Choose a directory",
                       wxEmptyString, // Default path (can be set)
                       wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

    if (dialog.ShowModal() != wxID_OK)
        return;
    wxString path = dialog.GetPath();
    string cmake_exe_path = (filesystem::path::program_dir()/filesystem::path("cmake/bin/cmake")).to_string();
    wxMessageBox(wxString::Format("You selected: %s", path), "Folder Selected", wxOK | wxICON_INFORMATION, this);
    string cmake_build_cmd = cmake_exe_path + " --version";
    int result = std::system(cmake_build_cmd.c_str());
}

bool app::OnInit()
{
    app_frame *frame = new app_frame("Bount Game Studio");
    wxGLAttributes attribs;
    attribs.PlatformDefaults().RGBA().MinRGBA(8, 8, 8, 8).DoubleBuffer().Stencil(8).Depth(24).EndList();
    m_canvas = std::make_unique<gl_canvas>(frame, attribs);
    frame->Show(true);
    return true;
}