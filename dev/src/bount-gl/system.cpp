#include "bount-lib/gl/precompiled.hpp"
#include "bount-gl/system.hpp"
#include <GL/glew.h>

namespace bount::gl
{
    BOUNT_SINGLETON_CLASS_IMPL(bount::gl::system)

    bool8 system::startup()
    {
        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            shutdown();
            return false;
        }
        return true;
    }

    void system::shutdown()
    {
        
    }
}