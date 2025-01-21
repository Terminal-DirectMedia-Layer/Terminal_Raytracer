/*
** EPITECH PROJECT, 2024
** NegativeFilter
** File description:
** file for NegativeFilter functions
*/


#pragma once

#include "core/env/object/IFilter.hpp"

namespace RayTracer
{
    class NegativeFilter : public IFilter
    {
    public:
        Color apply(Color &color) override;
    };
} // RayTracer
