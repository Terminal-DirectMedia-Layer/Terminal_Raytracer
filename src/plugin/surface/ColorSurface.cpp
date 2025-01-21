/*
** EPITECH PROJECT, 2024
** Raymenteur
** File description:
** ColorSurface.cpp
*/

#include "plugin/surface/ColorSurface.hpp"

namespace RayTracer
{
    ColorSurface::ColorSurface(Color color) : _color(color)
    {
    }

    Color ColorSurface::colorAt(double u, double v)
    {
        return _color;
    }
} // namespace RayTracer