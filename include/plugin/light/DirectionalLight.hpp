/*
** EPITECH PROJECT, 2024
** Raymenteur
** File description:
** DirectionalLight.hpp
*/

#pragma once

#include "core/env/object/ALight.hpp"

#include "core/math/Point.hpp"
#include "core/math/Transformation3.hpp"

namespace RayTracer
{
    class DirectionalLight : public ALight
    {
    public:

        DirectionalLight(Color color, double angle, double radius, double luminance);
        ~DirectionalLight() override = default;
        [[nodiscard]] double getAngle() const { return _angle;}
        [[nodiscard]] double getRadius() const { return _radius;}
 
        double getIntensity(const Ray3d &ray, SceneContext &context, Transformation3d &trans) override;

    protected:
        double _angle;
        double _radius;
        double _luminance;
    };
}
