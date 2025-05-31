#pragma once
#include "bount-gpu/shader/type.hpp"

namespace bount::gpu::shader
{
    class resource_interface
    {
    public:
        virtual [[nodiscard]] type get_type() const = 0;
        virtual [[nodiscard]] string get_source() const = 0;
    };

    class file_resource : public resource_interface
    {
    public:
        BOUNT_GPU_API file_resource(const string& path, type res_type);
        [[nodiscard]] inline type get_type() const override { return m_type; }
        [[nodiscard]] inline string get_source() const override { return m_source; }
    
    private:
        string m_source;
        type m_type;
    };

    class text_resource : public resource_interface
    {
    public:
        inline text_resource(const string& source, type res_type) : m_source(source), m_type(res_type) {}
        [[nodiscard]] inline type get_type() const override { return m_type; }
        [[nodiscard]] inline string get_source() const override { return m_source; }
        
    private:
        string m_source;
        type m_type;
    };
}