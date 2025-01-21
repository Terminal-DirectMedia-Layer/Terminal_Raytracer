#pragma once

#include <numbers>

namespace RayTracer
{
    template<typename T>
    class UnitConverter
    {
    public:
        UnitConverter() = delete;

        static T toRadians(T degrees)
        {
            return degrees * std::numbers::pi / 180.0;
        }

        static T toDegrees(T radians)
        {
            return radians * 180.0 / std::numbers::pi;
        }
    };
}
