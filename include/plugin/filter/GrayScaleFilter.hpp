/*
** EPITECH PROJECT, 2024
** BlackAndWhiteFilter
** File description:
** file for BlackAndWhiteFilter functions
*/


#pragma once

#include "core/env/object/IFilter.hpp"
#include "core/env/Color.hpp"

namespace RayTracer
{
    class GrayScaleFilter : public IFilter
    {
    public:
        Color apply(Color &color) override;
    };
} // RayTracer
