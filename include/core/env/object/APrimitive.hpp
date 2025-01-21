/*
** EPITECH PROJECT, 2024
** APrimitive
** File description:
** file for APrimitive functions
*/


#pragma once

#include <utility>

#include "core/env/object/IPrimitive.hpp"
#include "core/math/Transformation3.hpp"

namespace RayTracer
{
    class APrimitive : public IPrimitive
    {
    public:
        APrimitive(std::vector<std::shared_ptr<IMaterial>> materials, std::shared_ptr<ISurface> surface)
            : _materials(std::move(materials)), _surface(std::move(surface))
        {}
        ~APrimitive() = default;

        std::vector<std::shared_ptr<IMaterial>> &getMaterials() override
        {
            return _materials;
        }

        Color colorAt(Point3d &intersect) override = 0;
        std::optional<Ray3d> hits(Ray3d &ray, Transformation3d &trans) override = 0;
        Vector3d getNormal(Point3d &intersect) override = 0;

    protected:
        std::shared_ptr<ISurface> _surface;
        std::vector<std::shared_ptr<IMaterial>> _materials;
    };
} // RayTracer
