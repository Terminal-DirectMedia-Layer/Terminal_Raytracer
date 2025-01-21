/*
** EPITECH PROJECT, 2024
** PhongMaterial
** File description:
** file for PhongMaterial functions
*/


#pragma once

#include "core/env/object/IMaterial.hpp"
#include "core/env/scene/SceneContext.hpp"

namespace RayTracer
{
    class PhongMaterial : public IMaterial
    {
    public:
        PhongMaterial(double ka, double kd, double ks, double shininess)
            : _ka(ka), _kd(kd), _ks(ks), _shininess(shininess)
        {}

        [[maybe_unused]] Color tranform(const Ray3d &ray, const Ray3d &intersect, Color &surfaceColor,
                                        SceneContext &context, int calls = 0) override;

    private:
        double _ka;
        double _kd;
        double _ks;
        double _shininess;
    };
} // RayTracer
