/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-edgar.maurel
** File description:
** Cone.hpp
*/

#pragma once

#include "core/env/object/APrimitive.hpp"

namespace RayTracer {
    class Cone : public APrimitive {
    public:
        Cone(double radius, double height, std::vector<std::shared_ptr<IMaterial>> materials, std::shared_ptr<ISurface> surface) : APrimitive(materials, surface), radius(radius), height(height) {};

        std::optional<Ray3d> hits(Ray3d &ray, Transformation3d &trans) override;
        Color colorAt(Point3d &intersect) override;
        Vector3d getNormal(Point3d &intersect) override;

    protected:
        double radius;
        double height;
    };
}