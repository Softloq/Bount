#include "bount-lib/gpu/precompiled.hpp"
#include "bount-gpu/shader/program.hpp"
#include <gl/glew.h>
#include <list>

namespace bount::gpu::shader
{
    [[nodiscard]] GLenum gl_shader_enum(bount::gpu::shader::type shader_type) noexcept
    {
        switch(shader_type)
        {
        case bount::gpu::shader::type::vert: return GL_VERTEX_SHADER;
        case bount::gpu::shader::type::geom: return GL_GEOMETRY_SHADER;
        case bount::gpu::shader::type::frag: return GL_FRAGMENT_SHADER;
        case bount::gpu::shader::type::tese: return GL_TESS_EVALUATION_SHADER;
        case bount::gpu::shader::type::tesc: return GL_TESS_CONTROL_SHADER;
        case bount::gpu::shader::type::comp: return GL_COMPUTE_SHADER;
        default: return GL_INVALID_ENUM;
        }
    }
    program::program(const std::initializer_list<resource_interface>& shader_resources)
    {
        std::list<GLuint> link_shaders;
        for (const auto& shader_resource : shader_resources)
        {
            GLuint gl_shader = glCreateShader(gl_shader_enum(shader_resource.get_type()));
            auto source = shader_resource.get_source().c_str();
            glShaderSource(gl_shader, 1, &source, NULL);
            glCompileShader(gl_shader);
            link_shaders.push_back(gl_shader);
        }

        GLuint program = glCreateProgram();
        for (auto compiled_shader : link_shaders) glAttachShader(program, compiled_shader);
        glLinkProgram(program);
        for (auto compiled_shader : link_shaders) glDeleteShader(compiled_shader);
        
        m_program = program;
    }

    void program::use() noexcept { glUseProgram(m_program); }

    // Integer Uniforms

    void program::set_uniform_int(const string& id, int32 x) noexcept { glUniform1i(glGetUniformLocation(m_program, id.c_str()), x); }
    void program::set_uniform_int(const string& id, int32 x, int32 y) noexcept { glUniform2i(glGetUniformLocation(m_program, id.c_str()), x, y); }
    void program::set_uniform_int(const string& id, int32 x, int32 y, int32 z) noexcept { glUniform3i(glGetUniformLocation(m_program, id.c_str()), x, y, z); }
    void program::set_uniform_int(const string& id, int32 x, int32 y, int32 z, int32 w) noexcept { glUniform4i(glGetUniformLocation(m_program, id.c_str()), x, y, z, w); }

    // Unsigned Integer Uniforms

    void program::set_uniform_uint(const string& id, uint32 x) noexcept { glUniform1ui(glGetUniformLocation(m_program, id.c_str()), x); }
    void program::set_uniform_uint(const string& id, uint32 x, uint32 y) noexcept { glUniform2ui(glGetUniformLocation(m_program, id.c_str()), x, y); }
    void program::set_uniform_uint(const string& id, uint32 x, uint32 y, uint32 z) noexcept { glUniform3ui(glGetUniformLocation(m_program, id.c_str()), x, y, z); }
    void program::set_uniform_uint(const string& id, uint32 x, uint32 y, uint32 z, uint32 w) noexcept { glUniform4ui(glGetUniformLocation(m_program, id.c_str()), x, y, z, w); }

    // Floating-Point Uniforms

    void program::set_uniform_float(const string& id, float32 x) noexcept { glUniform1f(glGetUniformLocation(m_program, id.c_str()), x); }
    void program::set_uniform_float(const string& id, float32 x, float32 y) noexcept { glUniform2f(glGetUniformLocation(m_program, id.c_str()), x, y); }
    void program::set_uniform_float(const string& id, float32 x, float32 y, float32 z) noexcept { glUniform3f(glGetUniformLocation(m_program, id.c_str()), x, y, z); }
    void program::set_uniform_float(const string& id, float32 x, float32 y, float32 z, float32 w) noexcept { glUniform4f(glGetUniformLocation(m_program, id.c_str()), x, y, z, w); }

    // Double-Precision Floating-Point Uniforms

    void program::set_uniform_double(const string& id, float64 x) noexcept { glUniform1d(glGetUniformLocation(m_program, id.c_str()), x); }
    void program::set_uniform_double(const string& id, float64 x, float64 y) noexcept { glUniform2d(glGetUniformLocation(m_program, id.c_str()), x, y); }
    void program::set_uniform_double(const string& id, float64 x, float64 y, float64 z) noexcept { glUniform3d(glGetUniformLocation(m_program, id.c_str()), x, y, z); }
    void program::set_uniform_double(const string& id, float64 x, float64 y, float64 z, float64 w) noexcept { glUniform4d(glGetUniformLocation(m_program, id.c_str()), x, y, z, w); }
}