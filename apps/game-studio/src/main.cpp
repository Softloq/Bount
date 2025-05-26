#include <wx/wx.h>

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title)
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
        Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    }

private:
    void OnExit(wxCommandEvent &event)
    {
        Close(true);
    }
};

class MyApp : public wxApp
{
public:
    virtual bool OnInit() override
    {
        MyFrame *frame = new MyFrame("Bount Game Studio");
        frame->Show(true);
        return true;
    }
};
#define WinMain main
wxIMPLEMENT_APP(MyApp);