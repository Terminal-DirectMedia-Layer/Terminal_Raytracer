/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-edgar.maurel
** File description:
** Torus.cpp
*/

#include "plugin/primitive/Torus.hpp"

namespace RayTracer
{
    Color Torus::colorAt(Point3d &intersect)
    {
        return _surface->colorAt(intersect.x(), intersect.y());
    }

    Vector3d Torus::getNormal(Point3d &intersect)
    {
        return (intersect);
    }

    std::optional<Ray3d> Torus::hits(Ray3d &ray, Transformation3d &trans)
    {
        Vector3d origin = trans.translation();
        Vector3d H0 = Vector3d(trans.rotationMatrix() * Vector3d(0.0, 0.0, 1.0));
        Vector3d H1 = Vector3d(trans.rotationMatrix() * Vector3d(0.0, 1.0, 0.0));
        Vector3d H2 = Vector3d(trans.rotationMatrix() * Vector3d(1.0, 0.0, 0.0));
        
        return ray;
    }
}