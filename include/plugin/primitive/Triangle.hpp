#pragma once

#include "core/env/object/APrimitive.hpp"

#include "core/math/Point.hpp"

namespace RayTracer
{
    class Triangle : public APrimitive {
    public:
        Triangle(
            Vector3d a, Vector3d b, Vector3d c,
            std::vector<std::shared_ptr<IMaterial>> materials, std::shared_ptr<ISurface> surface
        );

        std::optional<Ray3d> hits(Ray3d &ray, Transformation3d &trans) override;
        Color colorAt(Point3d &intersect) override;
        Vector3d getNormal(Point3d &intersect) override;

    protected:
        Point3d _cOrigin;

        Vector3d _a;
        Vector3d _b;
        Vector3d _c;
    };
};
