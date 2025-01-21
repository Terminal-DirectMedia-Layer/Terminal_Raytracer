#pragma once

#include "core/math/Tuple.hpp"
#include "core/math/Vector.hpp"

#include <libconfig.h++>

#include <variant>

namespace RayTracer
{
    template<typename T, int N>
    struct Point : public Tuple<T, N>
    {
        using Tuple<T, N>::values;

        Point() :
            Tuple<T, N>()
        {}

        template<typename... Args>
        Point(T first, Args&&... args) :
            Tuple<T, N>(first, args...)
        {}

        Point(const Tuple<T, N> &tuple) :
            Tuple<T, N>(tuple)
        {}

        T distanceFrom(const Vector<T, N> &vector) const
        {
            T result = 0;

            for (int i = 0; i < N; i++)
                result += std::pow(this->values.at(i) - vector.values.at(i), 2);

            return std::sqrt(result);
        }

        Point<T, N> operator+(const Vector<T, N> &vector) const
        {
            return Tuple<T, N>::operator+(vector);
        }

        Vector<T, N> operator+(const Point<T, N> &point) const
        {
            return Tuple<T, N>::operator+(point);
        }

        Point<T, N> operator-(const Vector<T, N> &vector) const
        {
            return Tuple<T, N>::operator-(vector);
        }

        Vector<T, N> operator-(const Point<T, N> &point) const
        {
            return Tuple<T, N>::operator-(point);
        }

        void operator+=(const Vector<T, N> &vector)
        {
            Tuple<T, N>::operator+=(vector);
        }

        void operator-=(const Vector<T, N> &vector)
        {
            Tuple<T, N>::operator-=(vector);
        }

    private:
        template<int M>
        using declare_if_n = typename std::conditional_t<N >= M, T &, std::monostate>;

    public:
        declare_if_n<1> x() { return this->values.at(0); }
        declare_if_n<2> y() { return this->values.at(1); }
        declare_if_n<3> z() { return this->values.at(2); }
        declare_if_n<4> w() { return this->values.at(3); }
    };

    using Point2f = Point<float, 2>;
    using Point2d = Point<double, 2>;
    using Point2i = Point<int, 2>;

    using Point3f = Point<float, 3>;
    using Point3d = Point<double, 3>;
    using Point3i = Point<int, 3>;

    using Point4f = Point<float, 4>;
    using Point4d = Point<double, 4>;
    using Point4i = Point<int, 4>;
};

template<typename T, int N>
std::ostream &operator<<(std::ostream &os, const RayTracer::Point<T, N> &point)
{
    os << "Point" << N << "(";

    for (int i = 0; i < N; i++)
        os << point.values.at(i) << (i == N - 1 ? "" : ", ");

    os << ")";

    return os;
}
