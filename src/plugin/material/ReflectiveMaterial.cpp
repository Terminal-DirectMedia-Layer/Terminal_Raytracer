/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-edgar.maurel
** File description:
** BasicMaterial.cpp
*/

#include "plugin/material/ReflectiveMaterial.hpp"

namespace RayTracer {
    std::optional<Vector3d> ReflectiveMaterial::reflect(const Ray3d &ray, const Vector3d &normal)
    {
        Vector3d direction = ray.getDirection();
        Vector3d N = normal.normalize();
        double dot = direction.dot(N);
        return (direction - N * 2 * dot).normalize();
    }

    Color ReflectiveMaterial::tranform(const Ray3d &ray, const Ray3d &intersect, Color &surfaceColor,
                                       SceneContext &context, int calls)
    {
        if (calls > 10)
            return surfaceColor;
        std::optional<Vector3d> reflection = reflect(ray, intersect.getDirection());
        if (!reflection.has_value())
            return surfaceColor;
        Ray3d reflectedRay(intersect.getOrigin(), reflection.value());

        std::optional<Ray3d> nearestHit;
        std::optional<TransformedPrimitive> nearestObject;
        for (auto &obj : context.primitives) {
            std::optional<Ray3d> hit = obj.object->hits(reflectedRay, obj.transformation);
            if (hit.has_value() && std::abs((hit.value().getOrigin() - reflectedRay.getOrigin()).norm()) < 0.1)
                continue;
            if (hit.has_value() && (!nearestObject.has_value() ||
                    std::abs((hit.value().getOrigin() - reflectedRay.getOrigin()).norm()) <
                    std::abs((nearestHit.value().getOrigin() - reflectedRay.getOrigin()).norm()))) {
                nearestObject = obj;
                nearestHit = hit;
            }
        }
        Color objColor = {0, 0, 0};
        if (nearestHit.has_value()) {
            Point3d hitPoint = nearestHit.value().getOrigin();
            objColor = nearestObject.value().object->colorAt(hitPoint);
            for (auto &material : nearestObject.value().object->getMaterials())
                objColor = material->tranform(reflectedRay, nearestHit.value(), objColor, context, calls + 1);
        }
        return {
            surfaceColor.r * (1.0 - _reflectivity) + objColor.r * _reflectivity,
            surfaceColor.g * (1.0 - _reflectivity) + objColor.g * _reflectivity,
            surfaceColor.b * (1.0 - _reflectivity) + objColor.b * _reflectivity
        };
    }
}
