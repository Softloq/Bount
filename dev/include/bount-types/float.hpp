#pragma once

namespace bount
{
    // float size aliases

    using float32 = float;
    static_assert(sizeof(float32) == 4, "bount::float32 must be 4 bytes.");

    using float64 = double;
    static_assert(sizeof(float64) == 8, "bount::float64 must be 8 bytes.");

    using float_max = long double;
    static_assert(sizeof(float_max) >= sizeof(float64), "bount::float_max must be greater than or equal to float64.");
}
