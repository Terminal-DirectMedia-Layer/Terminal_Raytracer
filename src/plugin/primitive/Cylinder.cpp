/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-edgar.maurel
** File description:
** Cylinder.cpp
*/

#include "plugin/primitive/Cylinder.hpp"

namespace RayTracer
{
    Color Cylinder::colorAt(Point3d &intersect)
    {
        return _surface->colorAt(intersect.x(), intersect.y());
    }

    Vector3d Cylinder::getNormal(Point3d &intersect)
    {
        return (intersect);
    }

/*     std::optional<Ray3d> Cylinder::hits(Ray3d &ray, Transformation3d &trans)
    {
        Vector3d origin = ray.getOrigin() - trans.translation();
        Vector3d D = ray.getDirection();
        double R = this->radius;
        double t = (origin.y()) / (1 - D.y());
        //std::cout << t << std::endl;
        double theta = acos((D.x()*t + origin.x())/R);
        if (R * sin(theta) != D.z()*t + origin.z()) {
            std::cout << "no hit" << std::endl;
            return std::nullopt;
        }
        std::cout << theta << std::endl;
        Vector3d P = Vector3d(R * cos(theta), t, R * sin(theta));
        return Ray3d(P, P - Vector3d(0, 0, 0));

    } */

    std::optional<Ray3d> Cylinder::hits(Ray3d &ray, Transformation3d &trans)
    {
        Point3d origin = trans.translation();
        Vector3d D = ray.getDirection().normalize();
        Vector3d N = trans.rotation().normalize();
        Vector3d O = ray.getOrigin() - origin;
        double ND = D.dot(N);
        double NO = O.dot(N);
        double OD = O.dot(D);
        double r = this->radius;
        double a = 1 - pow(ND, 2);
        double b = 2 * (OD - NO * ND);
        double c = O.dot(O) - pow(r, 2) - pow(NO, 2);
        double delta = pow(b, 2) - 4 * a * c;
        if (delta < 0)
            return std::nullopt;
        double t1 = (-b - sqrt(delta)) / (2 * a);
        double t2 = (-b + sqrt(delta)) / (2 * a);
        if (t1 < 0 && t2 < 0)
            return std::nullopt;
        double t = t1;
        Point3d intersect = ray.at(t);
        Vector3d P =  N * N.dot(intersect);
        Vector3d V = P - intersect;
        return Ray3d(intersect, V);
    }
}