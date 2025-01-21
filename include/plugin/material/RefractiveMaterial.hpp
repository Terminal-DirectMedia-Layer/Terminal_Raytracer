/*
** EPITECH PROJECT, 2024
** RefractionMaterial
** File description:
** file for RefractionMaterial functions
*/


#pragma once

#include "core/env/object/IMaterial.hpp"

namespace RayTracer
{
    class RefractiveMaterial : public IMaterial
    {
    public:
        RefractiveMaterial(double refractionIndex, double transparency):
            _refractionIndex(refractionIndex), _transparency(transparency) {}
        ~RefractiveMaterial() = default;

        Color tranform(const Ray3d &ray, const Ray3d &intersect, Color &surfaceColor, SceneContext &context, int calls = 0) override;

    private:
        double _refractionIndex;
        double _transparency;
    };
} // RayTracer
