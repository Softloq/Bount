#pragma once

#include "bount-lib/standard/macros.hpp"

namespace bount
{
    class system_interface
    {
    public:
        [[nodiscard]] virtual bool8 startup() = 0;
        virtual void shutdown() = 0;
    };
}