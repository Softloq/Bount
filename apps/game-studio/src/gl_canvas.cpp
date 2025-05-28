#include "gl_canvas.hpp"
#include <bount-gl/system.hpp>

using namespace bount;

gl_canvas::gl_canvas(wxFrame *parent)
    : wxGLCanvas(parent)
    , m_initialized(false)
{
    m_context = new wxGLContext(this);
    
    Bind(wxEVT_PAINT, &gl_canvas::on_paint, this, wxID_ANY);
    Bind(wxEVT_SIZE, &gl_canvas::on_size, this, wxID_ANY);
}


void gl_canvas::on_paint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    SetCurrent(*m_context);

    if (!m_initialized) m_initialized = gl::system::get().startup();

    render();
}

void gl_canvas::on_size(wxSizeEvent& event)
{
    SetCurrent(*m_context);
    event.Skip();
}

void gl_canvas::render()
{
}
