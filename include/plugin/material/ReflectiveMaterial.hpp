/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-edgar.maurel
** File description:
** basicMaterial.hpp
*/

#pragma once

#include "core/env/object/IMaterial.hpp"
#include "core/env/scene/SceneContext.hpp"

namespace RayTracer
{
    class ReflectiveMaterial : public IMaterial {
        public:
            explicit ReflectiveMaterial(double reflectivity) : _reflectivity(reflectivity) {};

            Color tranform(const Ray3d &ray, const Ray3d &intersect, Color &surfaceColor,
                           SceneContext &context, int calls = 0) override;
            std::optional<Vector3d> reflect(const Ray3d &ray, const Vector3d &normal);
        protected:
            double _reflectivity;
    };
}
