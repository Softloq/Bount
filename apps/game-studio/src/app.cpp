#include "app.hpp"
#include <bount-filesystem/path.hpp>
#include <wx/dirctrl.h>
#include <wx/filedlg.h>
#include <wx/splitter.h>
#include <cstdlib>

using namespace bount;

app_frame::app_frame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1024, 800))
{
    // Create a menu bar
    wxMenuBar* menuBar = new wxMenuBar;

    wxMenu* fileMenu = new wxMenu;
    fileMenu->Append(ID_OPEN_3D_MODEL_MENUITEM, "Open 3D Model", "Open a 3D Model file");
    fileMenu->Append(ID_COMPILE_MENUITEM, "Compile", "Compile your project");
    fileMenu->Append(wxID_SEPARATOR);
    fileMenu->Append(wxID_EXIT, "&Exit\tCtrl+Q", "Quit the application");
    menuBar->Append(fileMenu, "&File");

    wxMenu* editMenu = new wxMenu;
    menuBar->Append(editMenu, "&Edit");

    wxMenu* windowMenu = new wxMenu;
    menuBar->Append(windowMenu, "&Window");

    wxMenu* helpMenu = new wxMenu;
    menuBar->Append(helpMenu, "&Help");

    SetMenuBar(menuBar);
    
    wxColor bg_color(25, 25, 25);
    wxPanel* properties = new wxPanel(this);
    properties->SetBackgroundColour(bg_color);
    wxPanel* scene_graph = new wxPanel(this);
    scene_graph->SetBackgroundColour(bg_color);
    wxPanel* viewport = new wxPanel(this);
    viewport->SetBackgroundColour(bg_color);
    wxBoxSizer* viewport_sizer = new wxBoxSizer(wxVERTICAL);
    viewport->SetSizer(viewport_sizer);
    wxPanel* resources = new wxPanel(this);
    resources->SetBackgroundColour(bg_color);

    m_aui_mgr.SetManagedWindow(this);
    m_aui_mgr.AddPane(scene_graph, wxAuiPaneInfo().Caption("Scene Graph").CloseButton(false).Left().Movable(false).Floatable(false).Dockable(false).BestSize(wxSize(200, -1)).MinSize(wxSize(200, -1)));
    m_aui_mgr.AddPane(viewport, wxAuiPaneInfo().Caption("Viewport").CloseButton(false).Center().Movable(false).Floatable(false).Dockable(false));
    m_aui_mgr.AddPane(properties, wxAuiPaneInfo().Caption("Properties").CloseButton(false).Right().Movable(false).Floatable(false).Dockable(false).BestSize(wxSize(200, -1)).MinSize(wxSize(200, -1)).Layer(1));
    m_aui_mgr.AddPane(resources, wxAuiPaneInfo().Caption("Resources").CloseButton(false).Bottom().Movable(false).Floatable(false).Dockable(false).BestSize(wxSize(-1, 200)).MinSize(wxSize(-1, 200)));
    m_aui_mgr.Update();

    wxGLAttributes attribs;
    attribs.PlatformDefaults().RGBA().MinRGBA(8, 8, 8, 8).DoubleBuffer().Stencil(8).Depth(24).EndList();
    gl_canvas* canvas = new gl_canvas(viewport, attribs);
    viewport_sizer->Add(canvas, 1, wxEXPAND);

    // Create a status bar

    CreateStatusBar();
    SetStatusText("Welcome to Bount Game Studio!");

    Bind(wxEVT_MENU, &app_frame::on_open_3d_model_clicked, this, ID_OPEN_3D_MODEL_MENUITEM);
    Bind(wxEVT_MENU, &app_frame::on_compile_menu_clicked, this, ID_COMPILE_MENUITEM);
    Bind(wxEVT_MENU, &app_frame::on_exit, this, wxID_EXIT);
}

void app_frame::on_exit(wxCommandEvent &event)
{
    Close(true);
}

void app_frame::on_open_3d_model_clicked(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(this, "Open file", "", "",
                                "Wavefront 3D file (*.obj)|*.obj",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL) return;

    SetStatusText(wxString::Format("Loaded '%s'", openFileDialog.GetFilename()));
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
    app_frame* frame = new app_frame("Bount Game Studio");
    frame->Show(true);
    return true;
}