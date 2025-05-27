#include "gl_canvas.hpp"

gl_canvas::gl_canvas(wxFrame *parent)
    : wxGLCanvas(parent)
{
    Bind(wxEVT_PAINT, &gl_canvas::paint, this, wxID_ANY);
    int argc = 1;
    char* argv[1] = { wxString((wxTheApp->argv)[0]).char_str() };
}


void gl_canvas::paint(wxPaintEvent& WXUNUSED(event))
{
    std::cout << "Hello" << std::endl;
    render();
}

void gl_canvas::render()
{
}
