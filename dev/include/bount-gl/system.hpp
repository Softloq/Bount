#pragma once

#include "bount-lib\gl\api.hpp"
#include "bount-engine\interfaces\system.hpp"
#include "bount-design-patterns\singleton.hpp"

namespace bount::gl
{
    class system : public system_interface
    {
        BOUNT_SINGLETON_CLASS_FIELDS(BOUNT_GL_API, system)

    public:
        [[nodiscard]] bool8 startup() override;
        void shutdown() override;
    };
}