#pragma once

#include <wx/wx.h>
#include <wx/glcanvas.h>

class gl_canvas: public wxGLCanvas
{
public:
    gl_canvas(wxFrame* parent);
    void paint(wxPaintEvent& event);

private:
    void render();
};