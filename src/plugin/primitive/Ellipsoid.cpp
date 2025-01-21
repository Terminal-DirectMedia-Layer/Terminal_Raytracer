/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-edgar.maurel
** File description:
** Ellipsoid.cpp
*/

#include "plugin/primitive/Ellipsoid.hpp"

namespace RayTracer
{
    Color Ellipsoid::colorAt(Point3d &intersect)
    {
        return _surface->colorAt(intersect.x(), intersect.y());
    }

    Vector3d Ellipsoid::getNormal(Point3d &intersect)
    {
        return Vector3d(intersect.x() / pow(dimensions.x(), 2),
                        intersect.y() / pow(dimensions.y(), 2),
                        intersect.z() / pow(dimensions.z(), 2)) * 2;
    }

    std::optional<Ray3d> Ellipsoid::hits(Ray3d &ray, Transformation3d &trans)
    {
        //seting up values
        //std::cout << ray.getDirection() << std::endl;
        Point3d intersection;
        double t1;
        double t2;
        Vector3d center = trans.rotationMatrix() * trans.translation();
        Vector3d dir = trans.rotationMatrix() * ray.getDirection();
        Vector3d O = ray.getOrigin();
        double ox = center.x();
        double oy = center.y();
        double oz = center.z();
        double dx = dir.x();
        double dy = dir.y();
        double dz = dir.z();
        Vector3d new_dimensions = trans.scale() * trueDimensions;
        this->dimensions = new_dimensions;

        double d1 = new_dimensions.x();
        double d2 = new_dimensions.y();
        double d3 = new_dimensions.z();
        /* double a = pow(dx, 2) / pow(d1, 2) +
                   pow(dy, 2) / pow(d2, 2) +
                   pow(dz, 2) / pow(d3, 2);
        double b = 2 * (dx * ox / pow(d1, 2) +
                        dy * oy / pow(d2, 2) +
                        dz * oz / pow(d3, 2));
        double c = pow(ox, 2) / pow(d1, 2) +
                   pow(oy, 2) / pow(d2, 2) +
                   pow(oz, 2) / pow(d3, 2) - pow(radius, 2); */
        double a = pow(dx, 2) / pow(d1, 2) +
                   pow(dy, 2) / pow(d2, 2) +
                   pow(dz, 2) / pow(d3, 2);
        double b = 2* ((dx * (O.x() - ox) / pow(d1, 2)) +
                        (dy * (O.y() - oy) / pow(d2, 2)) +
                        (dz * (O.z() - oz) / pow(d3, 2)));
        double c = (pow(O.x() - ox, 2) / pow(d1, 2)) +
                   (pow(O.y() - oy, 2) / pow(d2, 2)) +
                   (pow(O.z() - oz, 2) / pow(d3, 2)) - pow(radius, 2);

        //intersection
        double delta = pow(b, 2) - 4 * a * c;
        if (delta < 0) {
            return std::nullopt;
        }
        t1 = (-b - sqrt(delta)) / (2 * a);
        t2 = (-b + sqrt(delta)) / (2 * a);
        if (t1 < 0 && t2 < 0) {
            return std::nullopt;
        }
        if (t1 < t2 || t2 < 0) {
            intersection = ray.at(t1);
        } else {
            intersection = ray.at(t2);
        }
        intersection = ray.at(t1);
        //std::cout << intersection + trans.translation() * 2 << std::endl;
        //refraction
        Vector3d normal = getNormal(intersection);
        Ray3d resRay(intersection, normal);
        return resRay;
    }
} // RayTracer
