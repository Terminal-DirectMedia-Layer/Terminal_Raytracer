#include "plugin/primitive/Triangle.hpp"

namespace RayTracer
{
    Triangle::Triangle(
        Vector3d a, Vector3d b, Vector3d c,
        std::vector<std::shared_ptr<IMaterial>> materials, std::shared_ptr<ISurface> surface
    ) :
        APrimitive(materials, surface),
        _a(a),
        _b(b),
        _c(c)
    {}

    std::optional<Ray3d> Triangle::hits(Ray3d &ray, Transformation3d &trans)
    {
        constexpr double epsilon = std::numeric_limits<double>::epsilon();

        this->_cOrigin = trans.translation();

        Vector3d edge1 = trans * (this->_b - this->_a);
        Vector3d edge2 = trans * (this->_c - this->_a);
        Vector3d crossEdge2 = ray.getDirection().cross(edge2);
        double determinant = edge1.dot(crossEdge2);

        if (std::abs(determinant) < epsilon)
            return std::nullopt;

        double   invDeterminant = 1.0 / determinant;
        Vector3d s = ray.getOrigin() - Vector3d{trans * this->_a};
        double   u = s.dot(crossEdge2) * invDeterminant;

        if (u < 0.0 || u > 1.0)
            return std::nullopt;

        Vector3d crossS = s.cross(edge1);
        double   v = ray.getDirection().dot(crossS) * invDeterminant;

        if (v < 0.0 || u + v > 1.0)
            return std::nullopt;

        double t = edge2.dot(crossS) * invDeterminant;

        if (t < epsilon)
            return std::nullopt;

        Point3d intersect = ray.at(t);
        return Ray3d{intersect, ray.getDirection().normalize()};
    }

    Color Triangle::colorAt(Point3d &intersect)
    {
        return _surface->colorAt(intersect.x(), intersect.y());
    }

    Vector3d Triangle::getNormal(Point3d &intersect)
    {
        return Vector3d{intersect}.normalize();
    }
};
