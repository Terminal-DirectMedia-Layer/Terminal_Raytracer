/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-edgar.maurel
** File description:
** Cuboid.hpp
*/

#pragma once

#include "core/env/object/APrimitive.hpp"

namespace RayTracer {
    class Cuboid : public APrimitive {
        using Face = std::tuple<Point3d, Point3d, Point3d, Point3d>;
    public:
        Cuboid(Vector3d dimensions, std::vector<std::shared_ptr<IMaterial>> materials, std::shared_ptr<ISurface> surface);

        Vector3d getDimension() {return dimensions; };
        std::array<Face, 6> getFaces() {return faces; };
        std::array<Vector3d, 8> getPoints() {return points; };

        std::optional<Ray3d> hits(Ray3d &ray, Transformation3d &trans) override;
        Color colorAt(Point3d &intersect) override;
        Vector3d getNormal(Point3d &intersect) override;
        Vector3d normalFace(Face face);
        void setupPoints(Transformation3d &trans);

    protected:
        Vector3d dimensions;
        std::array<Face, 6> faces; // front, back, top, right, bottom, left
        std::array<Vector3d, 8> points;
        bool isSetup;
    };
}
