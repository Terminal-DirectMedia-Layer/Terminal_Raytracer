/*
** EPITECH PROJECT, 2024
** ChessboardSurface
** File description:
** file for ChessboardSurface functions
*/

#include "plugin/surface/ChessboardSurface.hpp"

namespace RayTracer
{
    Color ChessboardSurface::colorAt(double u, double v)
    {
        int x = (int)(u * _cells);
        int y = (int)(v * _cells);

        if ((x + y) % 2 == 0)
            return {0, 0, 0};
        return {1, 1, 1};
    }
} // namespace RayTracer
