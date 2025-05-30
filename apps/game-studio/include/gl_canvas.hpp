#pragma once

#include <bount-lib/standard/macros.hpp>

#include <wx/wx.h>
#include <wx/glcanvas.h>

#include <memory>

class gl_canvas: public wxGLCanvas
{
public:
    gl_canvas(wxFrame* parent, const wxGLAttributes& attribs);

private:
    std::unique_ptr<wxGLContext> m_context;
    bount::bool8 m_initialized;

    void on_paint(wxPaintEvent& event);
    void on_size(wxSizeEvent& event);

    void render();
};