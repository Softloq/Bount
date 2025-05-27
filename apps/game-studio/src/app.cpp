#include "app.hpp"
#include <bount-filesystem/path.hpp>
#include <wx/dirctrl.h>
#include <cstdlib>

using namespace bount;

AppFrame::AppFrame(const wxString &title)
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

    Bind(wxEVT_MENU, &AppFrame::OnCompileMenuClicked, this, ID_COMPILE_MENUITEM);
    Bind(wxEVT_MENU, &AppFrame::OnExit, this, wxID_EXIT);
}

void AppFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}

void AppFrame::OnCompileMenuClicked(wxCommandEvent &event)
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

bool App::OnInit()
{
    AppFrame *frame = new AppFrame("Bount Game Studio");
    frame->Show(true);
    return true;
}