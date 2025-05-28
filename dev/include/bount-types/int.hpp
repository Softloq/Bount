#pragma once

#include <cstdint>

namespace bount
{
    // int size aliases

    using int8 = std::int8_t;
    static_assert(sizeof(int8) == 1, "bount::int8 must be 1 byte.");

    using int16 = std::int16_t;
    static_assert(sizeof(int16) == 2, "bount::int16 must be 2 bytes.");

    using int32 = std::int32_t;
    static_assert(sizeof(int32) == 4, "bount::int32 must be 4 bytes.");

    using int64 = std::int64_t;
    static_assert(sizeof(int64) == 8, "bount::int64 must be 8 bytes.");
}
