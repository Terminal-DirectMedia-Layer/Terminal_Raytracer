/*
** EPITECH PROJECT, 2024
** Raymenteur
** File description:
** AmbiantLight.cpp
*/

#include "plugin/light/AmbientLight.hpp"

#include "core/math/Transformation3.hpp"

namespace RayTracer
{
    AmbientLight::AmbientLight(Color color, double intensity)
        : _intensity(intensity)
    {
        _color = color;
    }

    double AmbientLight::getIntensity(const Ray3d &ray, SceneContext &context, Transformation3d &trans)
    {
        return _intensity;
    }
} // RayTracer
