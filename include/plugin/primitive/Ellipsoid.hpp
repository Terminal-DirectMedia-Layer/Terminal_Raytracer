/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-edgar.maurel
** File description:
** Ellipsoid.hpp
*/

#pragma once

#include "core/env/object/APrimitive.hpp"

#include <utility>

namespace RayTracer
{
    class Ellipsoid : public APrimitive
    {
        public:
            Ellipsoid(std::vector<std::shared_ptr<IMaterial>> materials, std::shared_ptr<ISurface> surface,
                      Vector3d dimensions, double radius)
                : APrimitive(std::move(materials), std::move(surface)), dimensions(dimensions), radius(radius)
            {
                trueDimensions = dimensions;
            }

            [[nodiscard]] Vector3d getDimensions() const { return dimensions; };
            [[nodiscard]] double getRadius() const { return radius; };

            Color colorAt(Point3d &intersect) override;
            std::optional<Ray3d> hits(Ray3d &ray, Transformation3d &trans) override;
            Vector3d getNormal(Point3d &intersect) override;

        protected:
            Vector3d dimensions;
            Vector3d trueDimensions;
            double radius;
    };
} // RayTracer
