#pragma once

#include "core/math/Tuple.hpp"
#include "core/math/SquareMatrix.hpp"

#include <libconfig.h++>

#include <variant>

#include <cmath>

namespace RayTracer
{
    template<typename T, int N>
    struct Vector : public Tuple<T, N>
    {
        static std::array<Vector<T, N>, N> basis()
        {
            std::array<Vector<T, N>, N> basisVectors;

            for (int i = 0; i < N; i++) {
                Vector<T, N> &basisVector = basisVectors.at(i);

                basisVector = Vector<T, N>();

                for (int j = 0; j < N; j++)
                    basisVector.values.at(j) = i == j ? 1 : 0;
            }

            return basisVectors;
        }

        using Tuple<T, N>::values;
        
        Vector(const Tuple<T, N> &tuple) :
            Tuple<T, N>(tuple)
        {}

        template<typename... Args>
        Vector(T first, Args&&... args) :
            Tuple<T, N>(first, args...)
        {}
        
        Vector(T value) :
            Tuple<T, N>(value)
        {}

        Vector() :
            Tuple<T, N>()
        {}

        T dot(const Vector<T, N> &other) const
        {
            T result = 0;

            for (int i = 0; i < N; i++)
                result += this->values.at(i) * other.values.at(i);

            return result;
        }

        Vector<T, N> cross(const Vector<T, N> &other, const std::array<Vector<T, N>, N> &basis) const
        {
            Vector<T, N> result;

            // Calculate wedge cross product with other and basis vectors
            for (int i = 0; i < N; i++)
                result += basis.at((i + 2) % N) * this->values.at(i) * other.values.at((i + 1) % N)
                        - basis.at((i + 1) % N) * this->values.at(i) * other.values.at((i + 2) % N);

            return result;
        }

        Vector<T, N> cross(const Vector<T, N> &other, std::enable_if<N <= 3> * = nullptr) const
        {
            return this->cross(other, Vector::basis());
        }

        T norm() const
        {
            return std::sqrt(this->dot(*this));
        }

        T squaredNorm() const
        {
            return this->dot(*this);
        }

        Vector<T, N> normalize() const
        {
            return *this / this->norm();
        }

        Vector<T, N> operator+(const Vector<T, N> &other) const
        {
            return Tuple<T, N>::operator+(other);
        }

        Vector<T, N> operator-(const Vector<T, N> &other) const
        {
            return Tuple<T, N>::operator-(other);
        }

        Vector<T, N> operator*(const T &scalar) const
        {
            return Tuple<T, N>::operator*(scalar);
        }

        Vector<T, N> operator/(const T &scalar) const
        {
            return Tuple<T, N>::operator/(scalar);
        }

        void operator+=(const Vector<T, N> &other)
        {
            Tuple<T, N>::operator+=(other);
        }

        void operator-=(const Vector<T, N> &other)
        {
            Tuple<T, N>::operator-=(other);
        }

        void operator*=(const T &scalar)
        {
            Tuple<T, N>::operator*=(scalar);
        }

        void operator/=(const T &scalar)
        {
            Tuple<T, N>::operator/=(scalar);
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

    using Vector3f = Vector<float, 3>;
    using Vector3d = Vector<double, 3>;
    using Vector4f = Vector<float, 4>;
    using Vector4d = Vector<double, 4>;
};

template<typename T, int N>
std::ostream & operator<<(std::ostream &os, const RayTracer::Vector<T, N> &vector)
{
    os << "Vector" << N << "(";

    for (int i = 0; i < N; i++)
        os << vector.values.at(i) << (i == N - 1 ? "" : ", ");

    os << ")";

    return os;
}
