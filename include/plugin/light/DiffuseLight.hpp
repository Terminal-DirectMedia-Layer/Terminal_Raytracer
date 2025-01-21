/*
** EPITECH PROJECT, 2024
** Raymenteur
** File description:
** DiffuseLight.hpp
*/

#ifndef RAYMENTEUR_DIFFUSELIGHT_HPP
    #define RAYMENTEUR_DIFFUSELIGHT_HPP

#include "core/env/object/ALight.hpp"

#include "core/math/Point.hpp"
#include "core/math/Transformation3.hpp"

namespace RayTracer
{
    class DiffuseLight : public ALight
    {
    public:
        DiffuseLight(Color color, double luminance);
        ~DiffuseLight() = default;

        double getIntensity(const Ray3d &ray, SceneContext &context, Transformation3d &trans) override;

    protected:
        double _luminance;
    };
}

#endif //RAYMENTEUR_DIFFUSELIGHT_HPP
