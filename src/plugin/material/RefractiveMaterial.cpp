/*
** EPITECH PROJECT, 2024
** RefractionMaterial
** File description:
** file for RefractionMaterial functions
*/

#include "include/plugin/material/RefractiveMaterial.hpp"
#include "core/env/scene/SceneContext.hpp"

namespace RayTracer
{
    Color
    RefractiveMaterial::tranform(const Ray3d &ray, const Ray3d &intersect, Color &surfaceColor,
                                 SceneContext &context, int calls)
    {
        if (calls > 15)
            return {0, 0, 0};
        Vector3d normal = intersect.getDirection().normalize();
        Vector3d incident = ray.getDirection().normalize();
        const double n = 1 / _refractionIndex;
        const double cosI = -normal.dot(incident);
        const double sinT2 = n * n * (1.0 - cosI * cosI);
        if(sinT2 > 1.0)
            return {0, 0, 0};
        const double cosT = sqrt(1.0 - sinT2);
        Vector3d refraction = incident * n + normal * (n * cosI - cosT);
        Point3d origin = intersect.getOrigin() + refraction * 0.1;
        Ray3d refractedRay = {origin, refraction};

        std::optional<Ray3d> nearestHit;
        std::optional<TransformedPrimitive> nearestObject;
        for (auto &obj : context.primitives) {
            std::optional<Ray3d> hit = obj.object->hits(refractedRay, obj.transformation);
            if (hit.has_value() && std::abs((hit.value().getOrigin() - refractedRay.getOrigin()).norm()) < 0.1)
                continue;
            if (hit.has_value() && (!nearestObject.has_value() ||
                    std::abs((hit.value().getOrigin() - refractedRay.getOrigin()).norm()) <
                    std::abs((nearestHit.value().getOrigin() - refractedRay.getOrigin()).norm()))) {
                nearestObject = obj;
                nearestHit = hit;
            }
        }
        Color objColor = {0, 0, 0};
        if (nearestHit.has_value()) {
            Point3d hitPoint = nearestHit.value().getOrigin();
            objColor = nearestObject.value().object->colorAt(hitPoint);
            for (auto &material : nearestObject.value().object->getMaterials())
                objColor = material->tranform(refractedRay, nearestHit.value(), objColor, context, calls + 1);
        }
        return {
                surfaceColor.r * (1.0 - _transparency) + objColor.r * _transparency,
                surfaceColor.g * (1.0 - _transparency) + objColor.g * _transparency,
                surfaceColor.b * (1.0 - _transparency) + objColor.b * _transparency
        };
    }
} // RayTracer
