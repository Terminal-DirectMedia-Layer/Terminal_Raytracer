#pragma once

#include "core/env/object/ISurface.hpp"

namespace RayTracer
{
    class PerlinNoiseSurface : public ISurface
    {
    protected:
        static const std::array<int, 256> PERMUTATIONS;

    public:
        PerlinNoiseSurface(Color pit, Color peak, double scale);

    protected:
        static int perm(int i);
        static double fade(double t);
        static double lerp(double t, double a, double b);
        static double grad(int hash, double x, double y);
        static double noise(double x, double y);

        Color colorAt(double u, double v) override;

    protected:
        Color _pit;
        Color _peak;
        double _scale;
    };
};
