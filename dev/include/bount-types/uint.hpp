#pragma once

#include <cstdint>

namespace bount
{
    using uint = unsigned int;
    static_assert(sizeof(uint) == 4, "bount::uint must be 4 bytes.");

    // unsigned int size aliases

    using uint8 = std::uint8_t;
    static_assert(sizeof(uint8) == 1, "bount::uint8 must be 1 byte.");

    using uint16 = std::uint16_t;
    static_assert(sizeof(uint16) == 2, "bount::uint16 must be 2 bytes.");

    using uint32 = std::uint32_t;
    static_assert(sizeof(uint32) == 4, "bount::uint32 must be 4 bytes.");

    using uint64 = std::uint64_t;
    static_assert(sizeof(uint64) == 8, "bount::uint64 must be 8 bytes.");
}
