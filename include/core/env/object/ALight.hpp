/*
** EPITECH PROJECT, 2024
** Raymenteur
** File description:
** ALight.hpp
*/

#ifndef RAYMENTEUR_ALIGHT_HPP
    #define RAYMENTEUR_ALIGHT_HPP

#include "core/env/object/ILight.hpp"

#include "core/math/Point.hpp"
#include "core/math/Transformation3.hpp"

namespace RayTracer
{
    class ALight : public ILight
    {
    public:
        [[nodiscard]] Color getColor() const override { return _color;}
        [[nodiscard]] double getIntensity(const Ray3d &ray, SceneContext &context, Transformation3d &trans) override = 0;

    protected:
        Color _color;
    };
}

#endif //RAYMENTEUR_ALIGHT_HPP
