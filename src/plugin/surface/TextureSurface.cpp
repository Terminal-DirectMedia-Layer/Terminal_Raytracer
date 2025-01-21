/*
** EPITECH PROJECT, 2024
** TextureSurface
** File description:
** file for TextureSurface functions
*/

#include "plugin/surface/TextureSurface.hpp"

namespace RayTracer
{
    Color TextureSurface::colorAt(double u, double v)
    {
        return _texture->getPixel(u * _texture->getWidth() / _ratio.at(0), v * _texture->getHeight() / _ratio.at(1));
    }
} // RayTracer
