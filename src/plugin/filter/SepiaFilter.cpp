/*
** EPITECH PROJECT, 2024
** SepiaFilter
** File description:
** file for SepiaFilter functions
*/

#include "include/plugin/filter/SepiaFilter.hpp"

namespace RayTracer
{
    Color SepiaFilter::apply(Color &color)
    {
        double tr = 0.393 * color.r + 0.769 * color.g + 0.189 * color.b;
        double tg = 0.349 * color.r + 0.686 * color.g + 0.168 * color.b;
        double tb = 0.272 * color.r + 0.534 * color.g + 0.131 * color.b;

        return {tr, tg, tb, color.a};
    }
} // RayTracer
