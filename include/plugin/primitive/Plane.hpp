/*
** EPITECH PROJECT, 2024
** Raymenteur
** File description:
** Plane.hpp
*/

#ifndef RAYMENTEUR_PLANE_HPP
    #define RAYMENTEUR_PLANE_HPP

    #include "core/env/object/APrimitive.hpp"

namespace RayTracer
{
    class Plane : public APrimitive
    {
    public:
        Plane() : APrimitive({}, nullptr) {}
        Plane(std::vector<std::shared_ptr<IMaterial>> materials, std::shared_ptr<ISurface> surface, Vector3d normal);
        ~Plane() = default;

        Color colorAt(Point3d &intersect) override;
        std::optional<Ray3d> hits(Ray3d &ray, Transformation3d &trans) override;

        Vector3d getNormal(Point3d &intersect) override;
    protected :
        Vector3d normal;
    };
}

#endif //RAYMENTEUR_PLANE_HPP
