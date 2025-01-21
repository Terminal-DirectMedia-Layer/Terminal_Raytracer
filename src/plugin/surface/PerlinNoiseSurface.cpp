#include "plugin/surface/PerlinNoiseSurface.hpp"

namespace RayTracer
{
    const std::array<int, 256> PerlinNoiseSurface::PERMUTATIONS = {
        151, 160, 137,  91,  90,  15, 131,  13, 201,  95,  96,  53, 194, 233,   7, 225,
        140,  36, 103,  30,  69, 142,   8,  99,  37, 240,  21,  10,  23, 190,   6, 148,
        247, 120, 234,  75,   0,  26, 197,  62,  94, 252, 219, 203, 117,  35,  11,  32,
         57, 177,  33,  88, 237, 149,  56,  87, 174,  20, 125, 136, 171, 168,  68, 175,
         74, 165,  71, 134, 139,  48,  27, 166,  77, 146, 158, 231,  83, 111, 229, 122,
         60, 211, 133, 230, 220, 105,  92,  41,  55,  46, 245,  40, 244, 102, 143,  54,
         65,  25,  63, 161,   1, 216,  80,  73, 209,  76, 132, 187, 208,  89,  18, 169,
        200, 196, 135, 130, 116, 188, 159,  86, 164, 100, 109, 198, 173, 186,   3,  64,
         52, 217, 226, 250, 124, 123,   5, 202,  38, 147, 118, 126, 255,  82,  85, 212,
        207, 206,  59, 227,  47,  16,  58,  17, 182, 189,  28,  42, 223, 183, 170, 213,
        119, 248, 152,   2,  44, 154, 163,  70, 221, 153, 101, 155, 167,  43, 172,   9,
        129,  22,  39, 253,  19,  98, 108, 110,  79, 113, 224, 232, 178, 185, 112, 104,
        218, 246,  97, 228, 251,  34, 242, 193, 238, 210, 144,  12, 191, 179, 162, 241,
         81,  51, 145, 235, 249,  14, 239, 107,  49, 192, 214,  31, 181, 199, 106, 157,
        184,  84, 204, 176, 115, 121,  50,  45, 127,   4, 150, 254, 138, 236, 205,  93,
        222, 114,  67,  29,  24,  72, 243, 141, 128, 195,  78,  66, 215,  61, 156, 180
    };

    PerlinNoiseSurface::PerlinNoiseSurface(Color pit, Color peak, double scale) :
        _pit(pit),
        _peak(peak),
        _scale(scale)
    {}

    int PerlinNoiseSurface::perm(int i)
    {
        return PerlinNoiseSurface::PERMUTATIONS[i % PerlinNoiseSurface::PERMUTATIONS.size()];
    }

    double PerlinNoiseSurface::fade(double t)
    {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    double PerlinNoiseSurface::lerp(double t, double a, double b)
    {
        return a + t * (b - a);
    }

    double PerlinNoiseSurface::grad(int hash, double x, double y)
    {
        int h = hash & 7;
        double u = h < 4 ? x : -x;
        double v = h < 2 ? y : -y;

        return u + v;
    }

    double PerlinNoiseSurface::noise(double u, double v)
    {
        int X = static_cast<int>(std::floor(u));
        int Y = static_cast<int>(std::floor(v));

        double x_frac = u - std::floor(u);
        double y_frac = v - std::floor(v);

        double u_fade = PerlinNoiseSurface::fade(x_frac);
        double v_fade = PerlinNoiseSurface::fade(y_frac);

        int A = PerlinNoiseSurface::perm(X) + Y;
        int B = PerlinNoiseSurface::perm(X + 1) + Y;

        return PerlinNoiseSurface::lerp(v_fade,
            PerlinNoiseSurface::lerp(u_fade,
                PerlinNoiseSurface::grad(PerlinNoiseSurface::perm(A),         x_frac, y_frac),
                PerlinNoiseSurface::grad(PerlinNoiseSurface::PERMUTATIONS[B], x_frac - 1, y_frac)
            ),
            PerlinNoiseSurface::lerp(u_fade,
                PerlinNoiseSurface::grad(PerlinNoiseSurface::perm(A + 1),         x_frac, y_frac - 1),
                PerlinNoiseSurface::grad(PerlinNoiseSurface::PERMUTATIONS[B + 1], x_frac - 1, y_frac - 1)
            )
        );
    }

    Color PerlinNoiseSurface::colorAt(double u, double v)
    {
        double p = PerlinNoiseSurface::noise(u * this->_scale, v * this->_scale);

        return this->_pit.blend(this->_peak, p);
    }
};
