/*
** EPITECH PROJECT, 2024
** NegativeFilter
** File description:
** file for NegativeFilter functions
*/

#include "include/plugin/filter/NegativeFilter.hpp"

namespace RayTracer
{
    Color NegativeFilter::apply(Color &color)
    {
        return {1 - color.r, 1 - color.g, 1 - color.b, color.a};
    }
} // RayTracer