#pragma once

#include <stdexcept>

namespace RayTracer
{
    class MathRepresentationError : public std::runtime_error
    {
    public:
        explicit MathRepresentationError(const std::string &message) :
            std::runtime_error(message) {}
    };
};
