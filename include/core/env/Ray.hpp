#pragma once

#include "core/math/Point.hpp"
#include "core/math/Vector.hpp"

namespace RayTracer
{
    template<typename T, int N>
    struct Ray
    {
        Point<T, N> origin;
        Vector<T, N> direction;

        Ray(const Point<T, N> &origin, const Vector<T, N> &direction) :
            origin(origin),
            direction(direction.normalize())
        {}

        Vector<T, N> getDirection() const
        {
            return direction;
        }

        Point<T, N> getOrigin() const
        {
            return origin;
        }

        template<typename U>
        Ray<U, N> cast() const
        {
            return Ray<U, N>(
                origin.template cast<U>(),
                direction.template cast<U>()
            );
        }

        Point<T, N> at(T t) const
        {
            return origin + direction * t;
        }
    };

    using Ray3f = Ray<float, 3>;
    using Ray3d = Ray<double, 3>;
    using Ray4f = Ray<float, 4>;
    using Ray4d = Ray<double, 4>;
};
