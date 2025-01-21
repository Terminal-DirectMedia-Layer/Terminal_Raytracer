#pragma once

#include "core/math/Tuple.hpp"
#include "core/math/Point.hpp"

#include <format>

namespace RayTracer
{
    template<typename T, int N>
    struct Rectangle
    {
        Point<T, N> position;
        Tuple<T, N> size;

        Rectangle(Point<T, N> position, Tuple<T, N> size)
            : position(position), size(size)
        {}

        template<typename... Args>
        Rectangle(T firstSize, Args&&... args)
            : Rectangle(Tuple<T, N>(0), Tuple<T, N>(firstSize, args...))
        {}

        Rectangle(const libconfig::Setting &node)
        {
            this->load(node);
        }

        void load(const libconfig::Setting &node)
        {
            if (this->size.tryLoad(node))
                return;

            switch (node.getType()) {
            case libconfig::Setting::Type::TypeList:
            case libconfig::Setting::Type::TypeArray:
                {
                    if (node.getLength() != N)
                        throw MathRepresentationError(
                            std::format("Invalid Rectangle{} description", N)
                        );

                    position.load(node);
                }
                break;

            case libconfig::Setting::Type::TypeGroup:
                {
                    if constexpr (N == 2) {
                        if (node.exists("width") && node.exists("height")) {
                            this->size[0] = node["width"];
                            this->size[1] = node["height"];

                            return;
                        }
                    }

                    if (node.exists("position"))
                        this->position.load(node["position"]);
                    if (!node.exists("size"))
                        throw MathRepresentationError("Rectangle must have a size");

                    this->size.load(node["size"]);
                }
                break;

            default:
                throw MathRepresentationError(
                    std::format("Invalid Rectangle{} description", N)
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

        Point<T, N> center() const
        {
            return this->position + Vector<T, N>(this->size / 2);
        }

        Point<T, N> at(const Point<T, N> &coeffs) const
        {
            return this->position + Vector<T, N>(this->size * coeffs);
        }

        Point<T, N> at(T u, T v) const
        {
            return this->at(Point<T, N>(u, v));
        }

        template<typename... Args>
        Point<T, N> at(T c, Args&&... args) const
        {
            return this->at(Point<T, N>(c, args...));
        }

        bool contains(const Point<T, N> &point) const
        {
            for (int i = 0; i < N; i++)
                if (point[i] < position[i] || point[i] > position[i] + size[i])
                    return false;

            return true;
        }

        template<typename... Args>
        bool contains(T a, Args&&... args) const
        {
            return contains(Point<T, N>(a, args...));
        }

    private:
        template<int M>
        using declare_if_n =
            typename std::conditional_t<N >= M, T &, std::monostate>;

        template<int M>
        using declare_if_n_const =
            typename std::conditional_t<N >= M, T, std::monostate>;

    public:
        declare_if_n<2> x() { return this->position.at(0); };
        declare_if_n<2> y() { return this->position.at(1); };

        declare_if_n<2> width() { return this->size.at(0); };
        declare_if_n<2> height() { return this->size.at(1); };

        declare_if_n_const<2> x() const { return this->position.at(0); };
        declare_if_n_const<2> y() const { return this->position.at(1); };

        declare_if_n_const<2> width() const { return this->size.at(0); };
        declare_if_n_const<2> height() const { return this->size.at(1); };
    };

    using Rectangle2f = Rectangle<float, 2>;
    using Rectangle2d = Rectangle<double, 2>;
    using Rectangle2i = Rectangle<int, 2>;

    using Rectangle3f = Rectangle<float, 3>;
    using Rectangle3d = Rectangle<int, 3>;
};

template<typename T, int N>
std::ostream &operator<<(std::ostream &os, const RayTracer::Rectangle<T, N> &rectangle)
{
    os << "Rectangle" << N << "(pos=" << rectangle.position << ", size=" << rectangle.size << ")";
    return os;
}
