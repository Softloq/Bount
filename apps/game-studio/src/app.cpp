#include "app.hpp"

AppFrame::AppFrame(const wxString &title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(300, 200))
{
    // Create a menu bar
    wxMenuBar *menuBar = new wxMenuBar;
    wxMenu *fileMenu = new wxMenu;
    fileMenu->Append(wxID_EXIT, "&Exit\tCtrl+Q", "Quit the application");
    menuBar->Append(fileMenu, "&File");
    SetMenuBar(menuBar);

    // Create a status bar
    CreateStatusBar();
    SetStatusText("Welcome to Bount Game Studio!");

    // Connect the "Exit" menu item to the OnExit event handler
    Bind(wxEVT_MENU, &AppFrame::OnExit, this, wxID_EXIT);
}

void AppFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}

bool App::OnInit()
{
    AppFrame *frame = new AppFrame("Bount Game Studio");
    frame->Show(true);
    return true;
}