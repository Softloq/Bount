#pragma once
#include "bount-gpu/shader/resource.hpp"
#include <initializer_list>

namespace bount::gpu::shader
{
    class program final
    {
    public:
        BOUNT_GPU_API program(const std::initializer_list<resource_interface>& shader_resources);

        BOUNT_GPU_API void use() noexcept;

        // Integer Uniforms

        BOUNT_GPU_API void set_uniform_int(const string& id, int32 x) noexcept;
        BOUNT_GPU_API void set_uniform_int(const string& id, int32 x, int32 y) noexcept;
        BOUNT_GPU_API void set_uniform_int(const string& id, int32 x, int32 y, int32 z) noexcept;
        BOUNT_GPU_API void set_uniform_int(const string& id, int32 x, int32 y, int32 z, int32 w) noexcept;

        // Unsigned Integer Uniforms

        BOUNT_GPU_API void set_uniform_uint(const string& id, uint32 x) noexcept;
        BOUNT_GPU_API void set_uniform_uint(const string& id, uint32 x, uint32 y) noexcept;
        BOUNT_GPU_API void set_uniform_uint(const string& id, uint32 x, uint32 y, uint32 z) noexcept;
        BOUNT_GPU_API void set_uniform_uint(const string& id, uint32 x, uint32 y, uint32 z, uint32 w) noexcept;

        // Floating-Point Uniforms

        BOUNT_GPU_API void set_uniform_float(const string& id, float32 x) noexcept;
        BOUNT_GPU_API void set_uniform_float(const string& id, float32 x, float32 y) noexcept;
        BOUNT_GPU_API void set_uniform_float(const string& id, float32 x, float32 y, float32 z) noexcept;
        BOUNT_GPU_API void set_uniform_float(const string& id, float32 x, float32 y, float32 z, float32 w) noexcept;

        // Double-Precision Floating-Point Uniforms

        BOUNT_GPU_API void set_uniform_double(const string& id, float64 x) noexcept;
        BOUNT_GPU_API void set_uniform_double(const string& id, float64 x, float64 y) noexcept;
        BOUNT_GPU_API void set_uniform_double(const string& id, float64 x, float64 y, float64 z) noexcept;
        BOUNT_GPU_API void set_uniform_double(const string& id, float64 x, float64 y, float64 z, float64 w) noexcept;

    private:
        uint32 m_program;
    };
}