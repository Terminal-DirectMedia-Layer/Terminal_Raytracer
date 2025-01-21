/*
** EPITECH PROJECT, 2024
** SepiaFilter
** File description:
** file for SepiaFilter functions
*/


#pragma once

#include "core/env/object/IFilter.hpp"

namespace RayTracer
{
    class SepiaFilter : public IFilter
    {
    public:
        Color apply(Color &color) override;
    };
} // RayTracer
