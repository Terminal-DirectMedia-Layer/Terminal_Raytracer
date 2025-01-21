/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-edgar.maurel
** File description:
** Cone.cpp
*/

#include "plugin/primitive/Cone.hpp"

namespace RayTracer
{
    Color Cone::colorAt(Point3d &intersect)
    {
        return _surface->colorAt(intersect.x(), intersect.y());
    }

    Vector3d Cone::getNormal(Point3d &intersect)
    {
        return Vector3d(intersect.x(), intersect.y(), -intersect.z());
    }

    std::optional<Ray3d> Cone::hits(Ray3d &ray, Transformation3d &trans)
    {
        Point3d origin = trans.translation();
        Vector3d D = (ray.getDirection()).normalize();
        Vector3d N = trans.rotation().normalize();
        Vector3d O = ray.getOrigin() + origin;
        double R = this->radius;
        double H = this->height;
        double ND = D.dot(N);
        double NO = O.dot(N);
        double OD = O.dot(D);
        double a = 1 - pow(ND, 2) - pow(R, 2) * pow(ND, 2);
        double b = 2 * (OD - NO * ND) - 2 * R * R * ND * (NO - H);
        double c = O.dot(O) - pow(NO, 2) - pow(R * (NO - H), 2);
        double delta = pow(b, 2) - 4 * a * c;
        if (delta < 0)
            return std::nullopt;
        double t1 = (-b - sqrt(delta)) / (2 * a);
        double t2 = (-b + sqrt(delta)) / (2 * a);
        double t = (t1 > t2) ? t1 : t2;
        Point3d intersection = O + D * t;
        Vector3d P =  N * N.dot(intersection);
        Point3d coneOrigin = (0, 0, 0);
        if (coneOrigin.distanceFrom(P) > H)
            return std::nullopt;
        return Ray3d(intersection - origin, intersection - P);
        
    }
}