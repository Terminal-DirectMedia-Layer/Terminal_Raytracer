/*
** EPITECH PROJECT, 2024
** IFilter
** File description:
** file for IFilter functions
*/

#pragma once

#include "core/env/Color.hpp"

namespace RayTracer
{
    class IFilter
    {
    public:
        virtual Color apply(Color &color) = 0;
    };
} // RayTracer
