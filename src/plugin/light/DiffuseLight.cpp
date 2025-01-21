/*
** EPITECH PROJECT, 2024
** Raymenteur
** File description:
** DiffuseLight.cpp
*/

#include "core/math/Point.hpp"
#include "core/math/Transformation3.hpp"

#include "plugin/light/DiffuseLight.hpp"

namespace RayTracer
{
    DiffuseLight::DiffuseLight(Color color, double luminance)
    {
        _color = color;
        _luminance = luminance;
    }

    double DiffuseLight::getIntensity(const Ray3d &ray, SceneContext &context, Transformation3d &trans)
    {
        Vector3d diff = ray.getOrigin() - trans.translation();
        Ray3d lightRay = Ray3d(trans.translation(), diff);
        for (auto &obj : context.primitives) {
            auto hit = obj.object->hits(lightRay, obj.transformation);
            if (hit.has_value() && (hit.value().getOrigin() - ray.getOrigin()).norm() < 0.001)
                return 0;
        }
        double intensity = 1 / std::pow(diff.norm(), 2);
        return std::clamp(intensity, 0.0, 1.0);
    }
} // RayTracer