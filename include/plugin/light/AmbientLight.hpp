/*
** EPITECH PROJECT, 2024
** Raymenteur
** File description:
** AmbiantLight.hpp
*/

#ifndef RAYMENTEUR_AMBIANTLIGHT_HPP
    #define RAYMENTEUR_AMBIANTLIGHT_HPP


#include "core/env/object/ALight.hpp"

#include "core/math/Point.hpp"
#include "core/math/Transformation3.hpp"

namespace RayTracer
{
    class AmbientLight : public ALight
    {
    public:
        AmbientLight(Color color, double intensity);
        ~AmbientLight() override = default;

        double getIntensity(const Ray3d &ray, SceneContext &context, Transformation3d &trans) override;
    protected:
        double _intensity = 0.1;
    };
}
#endif //RAYMENTEUR_AMBIANTLIGHT_HPP
