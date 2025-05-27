#pragma once

namespace bount
{
    static_assert(sizeof(bool) == 1, "bool must be 1 byte.");

    // bool size alias

    using bool8 = bool;
    static_assert(sizeof(bool8) == 1, "bount::bool8 must be 1 byte.");
}
