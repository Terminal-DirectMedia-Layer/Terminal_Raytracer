/*
** EPITECH PROJECT, 2024
** BlackAndWhiteFilter
** File description:
** file for BlackAndWhiteFilter functions
*/

#include "plugin/filter/GrayScaleFilter.hpp"

namespace RayTracer
{
    Color GrayScaleFilter::apply(Color &color)
    {
        double average = color.r * 0.299 + color.g * 0.587 + color.b * 0.114;
        return {average, average, average, color.a};
    }
} // RayTracer
