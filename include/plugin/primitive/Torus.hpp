/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-edgar.maurel
** File description:
** Torus.hpp
*/

#include "core/env/object/APrimitive.hpp"

namespace RayTracer
{
    class Torus : public APrimitive
    {
        public:
            Torus(std::vector<std::shared_ptr<IMaterial>> materials, std::shared_ptr<ISurface> surface, double majorRadius, double minorRadius) : APrimitive(materials, surface), majorRadius(majorRadius), minorRadius(minorRadius) {};
            Color colorAt(Point3d &intersect) override;
            std::optional<Ray3d> hits(Ray3d &ray, Transformation3d &trans) override;
            Vector3d getNormal(Point3d &intersect) override;
        private:
            double majorRadius;
            double minorRadius;
    };
} // namespace RayTracer