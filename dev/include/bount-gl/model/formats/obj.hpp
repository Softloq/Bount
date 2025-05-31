#pragma once

#include "bount-lib\gl\api.hpp"
#include <vector>

namespace bount::gl::model::format
{
    struct obj_vertex
    {
        union
        {
            float32 pos[4];
            struct { float32 x, y, z, w; };
        };
    };

    struct obj_tex_coords
    {
        union
        {
            float32 coords[3];
            struct { float32 u, v, w; };
        };
    };

    class obj_res_interface
    {
    public:
        
    protected:
        std::vector<obj_vertex> m_vertices;
    };

    class obj_file_res : public obj_res_interface
    {
    public:
        BOUNT_GL_API obj_file_res(const string& path);
    };

    class obj_text_res : public obj_res_interface
    {
    public:
        BOUNT_GL_API obj_text_res(const string& text);
    };

    /**
     * OBJ (.obj) Wavefront Object Format
     */
    class obj
    {
    public:
        BOUNT_GL_API obj(const obj_res_interface& res);

    private:
    };
}