#pragma once

#include <cctype>

namespace bount
{
    static_assert(sizeof(char) == 1, "char must be 1 byte.");

    // unsigned char size aliases

    using char8 = char8_t;
    static_assert(sizeof(char8) == 1, "bount::char8 must be 1 byte.");

    using char16 = char16_t;
    static_assert(sizeof(char16) == 2, "bount::char16 must be 2 bytes.");

    using char32 = char32_t;
    static_assert(sizeof(char32) == 4, "bount::char32 must be 4 bytes.");
}
