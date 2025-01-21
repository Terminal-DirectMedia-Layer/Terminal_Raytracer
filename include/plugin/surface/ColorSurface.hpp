/*
** EPITECH PROJECT, 2024
** Raymenteur
** File description:
** ColorSurface.hpp
*/

#pragma once

#include "core/env/Color.hpp"

#include "core/env/object/ISurface.hpp"

namespace RayTracer
{
    class ColorSurface : public ISurface
    {
    public:
        ColorSurface(Color color);
        Color colorAt(double u, double v) override;

    private:
        Color _color;
    };
} // namespace RayTracer
