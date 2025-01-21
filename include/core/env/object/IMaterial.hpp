/*
** EPITECH PROJECT, 2024
** IMaterial
** File description:
** file for IMaterial functions
*/

#pragma once

#include "core/env/Color.hpp"
#include "core/env/Ray.hpp"
#include <optional>

namespace RayTracer
{
    class SceneContext;
    class IMaterial
    {
        public:
            [[maybe_unused]] virtual Color tranform(const Ray3d &ray, const Ray3d &intersect, Color &surfaceColor,
                                                    SceneContext &context, int calls = 0) = 0;
    };
} // RayTracer
