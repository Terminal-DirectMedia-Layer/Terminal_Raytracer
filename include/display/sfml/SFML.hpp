#pragma once

#include "display/sfml/SFMLDisplay.hpp"

#include <vector>

namespace RayTracer
{
    class SFML
    {
    public:
        static std::vector<SFMLDisplay *> displays;
    };
};
