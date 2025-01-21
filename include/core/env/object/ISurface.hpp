/*
** EPITECH PROJECT, 2024
** ISurface
** File description:
** file for ISurface functions
*/


#pragma once

#include "core/env/Color.hpp"

#include "core/math/Point.hpp"

namespace RayTracer
{
    class ISurface
    {
    public:
        virtual Color colorAt(double u, double v) = 0;
    };
} // RayTracer
