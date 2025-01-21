#pragma once

#include "core/math/MathRepresentationError.hpp"

#include <libconfig.h++>

#include <format>
#include <array>
#include <iostream>

namespace RayTracer
{
    template<typename T, int N>
    struct Tuple
    {
        std::array<T, N> values;

        Tuple(std::array<T, N> values)
            : values(std::move(values))
        {}

        template<typename... Args>
        Tuple(T first, Args&&... args) :
            values{first, args...}
        {}

        Tuple(T value)
        {
            std::fill(values.begin(), values.end(), value);
        }

        Tuple()
            : Tuple(0)
        {}

        Tuple(const libconfig::Setting &node)
        {
            this->load(node);
        }

        template<typename U>
        Tuple(Tuple<U, N> other)
        {
            for (int i = 0; i < N; i++)
                this->values.at(i) = static_cast<T>(other.values.at(i));
        }

    protected:
        static T grabValue(const libconfig::Setting &item, const std::string &propertyName)
        {
            /*
             * We need to do this stupid, convoluted, idiotic switch case because libconfig++ is dumb enough to care
             * about the rvalue type, consciously knowing that C++ has implicit-type conversion.
             *
             * Typical example of a library that tries to be too smart for its own good, and ends up being really dumb.
             */
            switch (item.getType()) {
            case libconfig::Setting::Type::TypeInt:
                {
                    int value;

                    value = item;
                    return static_cast<T>(value);
                }
                break;

            case libconfig::Setting::Type::TypeFloat:
                {
                    double value;

                    value = item;
                    return static_cast<T>(value);
                }
                break;

            default:
                throw MathRepresentationError(
                    std::format("Invalid Tuple{} description (element {} is not a number)", N, propertyName)
                );
                break;
            }
        }

    public:
        void load(const libconfig::Setting &node)
        {
            switch (node.getType()) {
            case libconfig::Setting::Type::TypeList:
            case libconfig::Setting::Type::TypeArray:
                {
                    if (node.getLength() != N)
                        throw MathRepresentationError(
                            std::format("Invalid Tuple{} description (got only {} elements)", N, node.getLength())
                        );

                    for (int i = 0; i < N; i++)
                        this->values.at(i) = this->grabValue(node[i], std::format("#{}", i));
                }
                break;

            case libconfig::Setting::Type::TypeGroup:
                {
                    if constexpr (N <= 4) {
                        static constexpr std::array<std::string_view, 4> names = {"x", "y", "z", "w"};

                        int i;
                        for (i = 0; i < N; i++) {
                            if (!node.exists(names.at(i).data()))
                                break;

                            libconfig::Setting &item = node[names.at(i).data()];
                            this->values.at(i) = this->grabValue(item, names.at(i).data());
                        }

                        if (i == N)
                            break;
                    }
                }

            default:
                throw MathRepresentationError(
                    std::format("Invalid description for Tuple{} (no matching pattern)", N)
                );
            }
        }

        bool tryLoad(const libconfig::Setting &node)
        {
            try {
                this->load(node);
            } catch (const MathRepresentationError &e) {
                return false;
            }

            return true;
        }

        Tuple<T, N> operator+(const Tuple<T, N> &other) const
        {
            Tuple<T, N> result;

            for (int i = 0; i < N; i++)
                result.values.at(i) = this->values.at(i) + other.values.at(i);

            return result;
        }

        Tuple<T, N> operator-(const Tuple<T, N> &other) const
        {
            Tuple<T, N> result;

            for (int i = 0; i < N; i++)
                result.values.at(i) = this->values.at(i) - other.values.at(i);

            return result;
        }

        Tuple<T, N> operator*(const Tuple<T, N> &other) const
        {
            Tuple<T, N> result;

            for (int i = 0; i < N; i++)
                result.values.at(i) = this->values.at(i) * other.values.at(i);

            return result;
        }

        Tuple<T, N> operator/(const Tuple<T, N> &other) const
        {
            Tuple<T, N> result;

            for (int i = 0; i < N; i++)
                result.values.at(i) = this->values.at(i) / other.values.at(i);

            return result;
        }

        Tuple<T, N> operator*(T scalar) const
        {
            Tuple<T, N> result;

            for (int i = 0; i < N; i++)
                result.values.at(i) = this->values.at(i) * scalar;

            return result;
        }

        Tuple<T, N> operator/(T scalar) const
        {
            Tuple<T, N> result;

            for (int i = 0; i < N; i++)
                result.values.at(i) = this->values.at(i) / scalar;

            return result;
        }

        void operator+=(const Tuple<T, N> &other)
        {
            for (int i = 0; i < N; i++)
                this->values.at(i) += other.values.at(i);
        }

        void operator-=(const Tuple<T, N> &other)
        {
            for (int i = 0; i < N; i++)
                this->values.at(i) -= other.values.at(i);
        }

        void operator*=(const T &scalar)
        {
            for (int i = 0; i < N; i++)
                this->values.at(i) *= scalar;
        }

        void operator/=(const T &scalar)
        {
            for (int i = 0; i < N; i++)
                this->values.at(i) /= scalar;
        }

        T & operator[](int index)
        {
            return this->values.at(index);
        }

        T at(int index) const
        {
            return this->values.at(index);
        }

        T & at(int index)
        {
            return this->values.at(index);
        }
    };
};

template<typename T, int N>
std::ostream & operator<<(std::ostream &os, const RayTracer::Tuple<T, N> &vector)
{
    os << "Tuple" << N << "(";

    for (int i = 0; i < N; i++)
        os << vector.values.at(i) << (i == N - 1 ? "" : ", ");

    os << ")";

    return os;
}
