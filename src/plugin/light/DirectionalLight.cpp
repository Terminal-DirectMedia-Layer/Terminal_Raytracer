/*
** EPITECH PROJECT, 2024
** Raymenteur
** File description:
** DirectionalLight.cpp
*/

#include "plugin/light/DirectionalLight.hpp"
#include "core/math/Point.hpp"
#include "core/env/Ray.hpp"

namespace RayTracer
{

    DirectionalLight::DirectionalLight(Color color, double angle, double radius, double luminance)
    {
        _color = color;
        _angle = angle;
        _radius = radius;
        _luminance = luminance;
    }

    double DirectionalLight::getIntensity(const Ray3d &ray, SceneContext &context, Transformation3d &trans)
    {
        Vector3d diff = (ray.getOrigin() - trans.translation());
        Vector3d direction = trans.rotationMatrix() * trans.translation() + trans.translation();
        if (trans.rotation().x() == 0 && trans.rotation().y() == 0 && trans.rotation().z() == 0)
            direction = trans.translation() * -1;
        direction = direction.normalize();
        std::vector<Ray3d> hits;
        double minDist = 1000000;

        double angle = acos(diff.normalize().dot(direction.normalize()));
        if (angle > UnitConverter<double>::toRadians(_angle))
        {
            return 0.0;
        }


        // std::cout << "1: " << diff.normalize() << "\t2: " << diff.normalize().normalize() << std::endl;
        Ray3d lightRay = Ray3d(trans.translation(), diff.normalize());
        for (auto &obj : context.primitives)
        {
            auto hit = obj.object->hits(lightRay, obj.transformation);
            if (hit.has_value())
            {
                hits.push_back(hit.value());
            }
        }
        if (hits.size() == 0)
        {
            return 0.0;
        }

        for (int i = 0; i < hits.size(); i++)
        {
            if (hits[i].getOrigin().distanceFrom(trans.translation()) < minDist)
            {
                minDist = hits[i].getOrigin().distanceFrom(trans.translation());
            }
        }
        // std::cout << minDist << "\t" << diff.norm() << std::endl;

        if ((diff.norm() - minDist) > 0.1 || diff.norm() - minDist < -0.1)
        {
            // std::cout << "diff: " << diff.norm() << "\t" << minDist << std::endl;
            return 0.0;
        }
        // std::cout << "intensity: " << _luminance << std::endl;
        /* double cosAngle = std::cos(UnitConverter<double>::toRadians(_angle));
        double cosAngleSq = std::pow(cosAngle, 2);

        Vector3d V = ray.getDirection();
        Vector3d VA = V - trans.rotation() * V.dot(trans.rotation());
        Vector3d COA = diff - trans.rotation() * (diff.dot(trans.rotation()));

        double a = VA.dot(VA) * cosAngleSq;
        double b = 2 * (VA.dot(COA) - V.dot(trans.rotation()) * cosAngleSq);
        double c = COA.dot(COA) - cosAngleSq;

        double delta = b * b - 4 * a * c;

        if (delta < 0)
            return 0.0; */
        double intensity = 1 / std::pow(minDist, 2);
        // std::cout << angle << std::endl;
        // std::cout << minDist << std::endl;
        // std::cout << std::clamp(intensity, 0.0, 1.0) * _luminance << std::endl;
        return std::clamp(intensity, 0.0, 1.0) * _luminance;
    }
}
