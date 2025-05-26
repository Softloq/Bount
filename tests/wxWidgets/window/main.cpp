/**
 * wxWidgets Window Unit Test.
 * Expected: Start a wxApp that creates an empty wxFrame then closes it.
 */

#include <wx/wx.h>

class TestFrame : public wxFrame
{
public:
    TestFrame(const wxString &title)
        : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(300, 200))
    {
    }
};

class TestApp : public wxApp
{
public:
    virtual bool OnInit() override
    {
        TestFrame *frame = new TestFrame("Test Window");
        frame->Close(true);
        return true;
    }
};

#define WinMain main
wxIMPLEMENT_APP(TestApp);
