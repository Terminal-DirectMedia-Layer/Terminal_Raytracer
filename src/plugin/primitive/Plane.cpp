/*
** EPITECH PROJECT, 2024
** Raymenteur
** File description:
** Plane.cpp
*/

#include "plugin/primitive/Plane.hpp"
#include "core/env/object/ISurface.hpp"
#include "core/env/object/IMaterial.hpp"
#include "core/math/Point.hpp"

namespace RayTracer
{

    Plane::Plane(std::vector<std::shared_ptr<IMaterial>> materials, std::shared_ptr<ISurface> surface, Vector3d normal) : APrimitive(materials, surface), normal(normal)
    {
    }

    Color Plane::colorAt(Point3d &intersect)
    {
        
        return _surface->colorAt(intersect.x(), intersect.y());
    }

    std::optional<Ray3d> Plane::hits(Ray3d &ray, Transformation3d &trans)
    {
        Vector3d pointInPlane = trans.translation();
        Vector3d newNormal = trans.rotationMatrix() * normal;
        newNormal = normal - pointInPlane;
        Vector3d direction = ray.getDirection();
        Vector3d origin = ray.getOrigin();
        if (direction.dot(newNormal) == 0)
            return std::nullopt;
        double t = (pointInPlane - origin).dot(newNormal) / direction.dot(newNormal);
        if (t < 0)
            return std::nullopt;
        //std::cout << ray.at(t) << std::endl;
        return Ray3d(ray.at(t), normal);
    }

    Vector3d Plane::getNormal(Point3d &intersect)
    {
        (void)intersect;
        return normal;
    }
} // namespace RayTracer
