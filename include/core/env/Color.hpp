#pragma once

#include <algorithm>
#include <string>
#include <cmath>
#include <stdexcept>
#include <cstdint>

namespace RayTracer
{
    struct Color
    {
        double r;
        double g;
        double b;
        double a;

        Color(const std::string &hex)
        {
            // FIXME: Add optional alpha support

            if (hex[0] != '#' || hex.size() != 7)
                throw std::invalid_argument("Invalid hex color");

            r = std::stoi(hex.substr(1, 2), 0, 16) / 255.0;
            g = std::stoi(hex.substr(3, 2), 0, 16) / 255.0;
            b = std::stoi(hex.substr(5, 2), 0, 16) / 255.0;
            a = 1.0;
        }

        Color(double r, double g, double b, double a = 1.0) :
            r(r), g(g), b(b), a(a)
        {}

        explicit Color(uint32_t color) :
            Color(
                static_cast<uint8_t>((color >>  0) & 0xff) / 255.0,
                static_cast<uint8_t>((color >>  8) & 0xff) / 255.0,
                static_cast<uint8_t>((color >> 16) & 0xff) / 255.0,
                static_cast<uint8_t>((color >> 24) & 0xff) / 255.0
            )
        {}

        Color() :
            Color(.0, .0, .0) 
        {}

        Color blend(const Color &other) const
        {
            // Blend colors with alpha
            
            double alpha = other.a;

            return Color(
                this->r * (1 - alpha) + other.r * alpha,
                this->g * (1 - alpha) + other.g * alpha,
                this->b * (1 - alpha) + other.b * alpha,
                std::clamp(this->a + other.a, 0.0, 1.0)
            );
        }

        Color blend(const Color &other, double k) const
        {
            // Additive blending

            return Color(
                this->r + other.r * k * other.a,
                this->g + other.g * k * other.a,
                this->b + other.b * k * other.a,
                std::clamp(this->a + other.a, 0.0, 1.0)
            );
        }

        Color grayscale() const
        {
            double gray = (this->r + this->g + this->b) / 3;

            return Color(gray, gray, gray, this->a);
        }

        Color gamma(double gamma) const
        {
            return Color(
                std::pow(this->r, gamma),
                std::pow(this->g, gamma),
                std::pow(this->b, gamma),
                this->a
            );
        }
    };
};
