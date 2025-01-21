/*
** EPITECH PROJECT, 2024
** ILight
** File description:
** file for ILight functions
*/

#pragma once

#include "core/env/Color.hpp"

#include "core/math/Vector.hpp"
#include "core/math/Point.hpp"
#include "core/math/Transformation3.hpp"
#include "core/env/Ray.hpp"

#include "core/env/object/Object.hpp"
#include "core/env/scene/SceneTransformer.hpp"

namespace RayTracer
{
    class ILight : public Object
    {
    public:
        [[nodiscard]] virtual Color getColor() const = 0;
        [[nodiscard]] virtual double getIntensity(const Ray3d &ray, SceneContext &context, Transformation3d &trans) = 0;
    };
} // RayTracer
