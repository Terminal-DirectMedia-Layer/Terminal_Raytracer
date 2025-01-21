/*
** EPITECH PROJECT, 2024
** SquareMatrix
** File description:
** file for SquareMatrix functions
*/


#pragma once

#include "core/math/Tuple.hpp"

#include "core/math/MathError.hpp"

#include <array>
#include <string>
#include <iostream>
#include <format>
#include <sstream>

namespace RayTracer
{
    template <typename T, int N>
    class SquareMatrix
    {
    private:
        template<typename... Args>
        void init(std::array<std::array<T, N>, N> &m, int i, int j, T v, Args... args)
        {
            m[i][j] = v;
            if constexpr (sizeof...(args) > 0)
                init(m, (j == N - 1) ? i + 1 : i, (j == N - 1) ? 0 : j + 1, args...);
        }

        template<typename... Args>
        static void initDiag(std::array<std::array<T, N>, N> &m, int i, T v, Args... args)
        {
            m[i][i] = v;
            if constexpr (sizeof...(args) > 0)
                initDiag(m, i + 1, args...);
        }

    public:
        SquareMatrix()
        {
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    _m[i][j] = (i == j) ? 1 : 0;
        }

        explicit SquareMatrix(const T mat[N][N])
        {
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    _m[i][j] = mat[i][j];
        }

        template<typename... Args>
        explicit SquareMatrix(T v, Args... args)
        {
            static_assert(1 + sizeof...(Args) == N * N,
                          "Incorrect number of values provided to SquareMatrix constructor");
            init(_m, 0, 0, v, args...);
        }

        static SquareMatrix Zero()
        {
            SquareMatrix m;
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    m._m[i][j] = 0;
            return m;
        }

        template<typename... Args>
        static SquareMatrix Diag(T v, Args... args)
        {
            static_assert(1 + sizeof...(Args) == N,
                          "Incorrect number of values provided to SquareMatrix::Diag");
            SquareMatrix m;
            initDiag(m._m, 0, v, args...);
            return m;
        }

        SquareMatrix operator+(const SquareMatrix &m) const
        {
            SquareMatrix r = *this;
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    r._m[i][j] += m._m[i][j];
            return r;
        }

        SquareMatrix operator-(const SquareMatrix &m) const
        {
            SquareMatrix r = *this;
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    r._m[i][j] -= m._m[i][j];
            return r;
        }

        SquareMatrix operator*(const SquareMatrix &m) const
        {
            SquareMatrix r = Zero();
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    for (int k = 0; k < N; ++k)
                        r._m[i][j] += _m[i][k] * m._m[k][j];
            return r;
        }

        SquareMatrix operator/(const SquareMatrix &m) const
        {
            SquareMatrix r = Zero();
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    for (int k = 0; k < N; ++k)
                        r._m[i][j] += _m[i][k] / m._m[k][j];
            return r;
        }

        SquareMatrix operator+(T s) const
        {
            SquareMatrix r = *this;
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    r._m[i][j] += s;
            return r;
        }

        SquareMatrix operator-(T s) const
        {
            SquareMatrix r = *this;
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    r._m[i][j] -= s;
            return r;
        }

        SquareMatrix operator*(T s) const
        {
            SquareMatrix r = *this;
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    r._m[i][j] *= s;
            return r;
        }

        SquareMatrix operator/(T s) const
        {
            if (s == 0)
                throw MathError(MathError::Type::DIVIDE_BY_ZERO);
            SquareMatrix r = *this;
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    r._m[i][j] /= s;
            return r;
        }

        void operator+=(const SquareMatrix &m)
        {
            *this = *this + m;
        }

        void operator-=(const SquareMatrix &m)
        {
            *this = *this - m;
        }

        void operator*=(const SquareMatrix &m)
        {
            *this = *this * m;
        }

        void operator/=(const SquareMatrix &m)
        {
            *this = *this / m;
        }

        const std::array<T, N> & operator[](int i) const
        {
            return _m.at(i);
        }

        std::array<T, N> & operator[](int i)
        {
            return _m[i];
        }

        bool operator==(const SquareMatrix<T, N> &m2) const
        {
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    if (_m[i][j] != m2._m[i][j])
                        return false;
            return true;
        }

        bool operator!=(const SquareMatrix<T, N> &m2) const
        {
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    if (_m[i][j] != m2._m[i][j])
                        return true;
            return false;
        }

        bool operator<(const SquareMatrix<T, N> &m2) const
        {
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j) {
                    if (_m[i][j] < m2._m[i][j])
                        return true;
                    if (_m[i][j] > m2._m[i][j])
                        return false;
                }
            return false;
        }

        bool operator>(const SquareMatrix<T, N> &m2) const
        {
            return m2 < *this;
        }

        /* Applied transformation operators */

        Tuple<T, 3> operator *(const Tuple<T, 3> &tuple) const
        {
            return {
                this->_m[0][0] * tuple.at(0) + this->_m[0][1] * tuple.at(1) + this->_m[0][2] * tuple.at(2) + this->_m[0][3],
                this->_m[1][0] * tuple.at(0) + this->_m[1][1] * tuple.at(1) + this->_m[1][2] * tuple.at(2) + this->_m[1][3],
                this->_m[2][0] * tuple.at(0) + this->_m[2][1] * tuple.at(1) + this->_m[2][2] * tuple.at(2) + this->_m[2][3]
            };
        }

        T minor(int row, int col) const
        {
            SquareMatrix<T, N - 1> m;

            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    if (i != row && j != col)
                        m[i - (i > row)][j - (j > col)] = _m[i][j];

            return m.determinant();
        }
        
        T cofactor(int row, int col) const
        {
            return this->minor(row, col) * (((row + col) % 2 == 0) ? 1 : -1);
        }

        T determinant() const
        {
            if constexpr (N == 2)
                return _m[0][0] * _m[1][1] - _m[0][1] * _m[1][0];
            else {
                T det = 0;

                for (int i = 0; i < N; ++i)
                    det += _m[0][i] * cofactor(0, i);
                
                return det;
            }
        }

        template<int M>
        SquareMatrix<T, M> extend() const
        {
            static_assert(M > N, "Cannot extend to a smaller dimension");

            SquareMatrix<T, M> m;

            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    m[i][j] = _m[i][j];
            
            return m;
        }

        SquareMatrix<T, N> inverse() const
        {
            if (isIdentity())
                return *this;

            T det = determinant();
            if (det == 0)
                throw MathError(MathError::Type::INVALID_MATRIX_INVERSION);

            SquareMatrix<T, N> m;
            
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    m[i][j] = cofactor(j, i) / det;

            return m;
        }

        [[nodiscard]] bool isIdentity() const
        {
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    if ((i == j && _m[i][j] != 1) || (i != j && _m[i][j] != 0))
                        return false;

            return true;
        }

        [[nodiscard]] bool isDiagonal() const
        {
            int x = _m[0][0];
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++) 
                    if ((i == j && _m[i][j] != x) || (i != j && _m[i][j] != 0))
                        return false;

            return true;
        }

        [[nodiscard]] std::string toString() const
        {
            std::stringstream ss;

            std::cout << "┏" << std::string(N * 8 - 1, ' ') << "┓" << std::endl;

            for (int i = 0; i < N; i++) {
                ss << "┃";

                for (int j = 0; j < N; j++)
                    ss << std::format("{:6.2f}", _m[i][j])
                       << ((j == N - 1) ? "" : ", ");

                ss << " ┃" << std::endl;
            }

            ss << "┗" << std::string(N * 8 - 1, ' ') << "┛" << std::endl;
            return ss.str();
        }

    private:
        std::array<std::array<T, N>, N> _m;
    };
};

template<typename T, int N>
static std::ostream &operator<<(std::ostream &os, const RayTracer::SquareMatrix<T, N> &m)
{
    return os << m.toString();
}
