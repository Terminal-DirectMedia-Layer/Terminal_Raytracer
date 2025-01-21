/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-edgar.maurel
** File description:
** cylinder.hpp
*/

#include <utility>

#include "core/env/object/APrimitive.hpp"

namespace RayTracer
{
    class Cylinder : public APrimitive
    {
        public:
            Cylinder(std::vector<std::shared_ptr<IMaterial>> materials, std::shared_ptr<ISurface> surface, double radius, double height, Vector3d direction) :
                APrimitive(std::move(materials), std::move(surface)), radius(radius), height(height), direction(direction.normalize()) {};
            Color colorAt(Point3d &intersect) override;
            std::optional<Ray3d> hits(Ray3d &ray, Transformation3d &trans) override;
            Vector3d getNormal(Point3d &intersect) override;
        private:
            double radius;
            double height;
            Vector3d direction;
    };
} // namespace RayTracer