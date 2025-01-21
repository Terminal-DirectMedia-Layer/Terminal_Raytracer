/*
** EPITECH PROJECT, 2024
** IPrimitive
** File description:
** file for IPrimitive functions
*/

#pragma once

#include "core/env/Ray.hpp"
#include "core/env/Color.hpp"
#include "core/env/object/Object.hpp"

#include "core/env/object/IMaterial.hpp"
#include "core/env/object/ISurface.hpp"

#include "core/math/Transformation3.hpp"
#include <vector>
#include <memory>
#include <optional>

namespace RayTracer
{
    class IPrimitive : public Object
    {
    public:
        [[maybe_unused]] virtual Color colorAt(Point3d &intersect) = 0;
        [[maybe_unused]] virtual std::optional<Ray3d> hits(Ray3d &ray, Transformation3d &trans) = 0;
        [[maybe_unused]] virtual Vector3d getNormal(Point3d &intersect) = 0;
        [[maybe_unused]] virtual std::vector<std::shared_ptr<IMaterial>> &getMaterials() = 0;
    };
} // RayTracer
