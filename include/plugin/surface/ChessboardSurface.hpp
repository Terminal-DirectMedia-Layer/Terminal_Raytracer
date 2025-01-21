/*
** EPITECH PROJECT, 2024
** ChessboardSurface
** File description:
** file for ChessboardSurface functions
*/

#pragma once

#include "core/env/object/ISurface.hpp"

namespace RayTracer
{
    class ChessboardSurface : public ISurface
    {
    public:
        explicit ChessboardSurface(int cells) : _cells(cells) {};
        ~ChessboardSurface() = default;

        Color colorAt(double u, double v) override;

    protected:
        int _cells;
    };
} // RayTracer
