/*
** EPITECH PROJECT, 2024
** PhongMaterial
** File description:
** file for PhongMaterial functions
*/

#include "include/plugin/material/PhongMaterial.hpp"
#include "include/core/env/object/ILight.hpp"

namespace RayTracer
{
    Color PhongMaterial::tranform(const Ray3d &ray, const Ray3d &intersect, Color &surfaceColor,
                                  SceneContext &context, int calls)
    {
        double illuminance = _ka;
        for (TransformedLight &light : context.lights)
        {
            Transformation3d trans = light.transformation;
            Vector3d direction = trans.rotationMatrix() * trans.translation() + trans.translation();
            if (trans.rotation().x() == 0 && trans.rotation().y() == 0 && trans.rotation().z() == 0)
                direction = trans.translation() * -1;
            direction = direction.normalize();
            Vector3d Lm = intersect.getOrigin() - trans.translation();
            Vector3d N = intersect.getDirection().normalize();
            Vector Rm = (N * 2 * (Lm.dot(N)) - Lm) * -1;
            Vector V = ray.getOrigin() - intersect.getOrigin();
            V = V.normalize();
            double it = light.object->getIntensity(intersect, context, trans);
            if (it > 0)
            {
                illuminance = _ka;
                if (Lm.normalize().dot(N) > 0)
                    illuminance += _kd * (Lm.normalize().dot(N)) * it;
                if (Rm.normalize().dot(V) > 0)
                    illuminance += _ks * pow(Rm.normalize().dot(V), _shininess);
                surfaceColor.r += light.object->getColor().r * illuminance;
                surfaceColor.g += light.object->getColor().g * illuminance;
                surfaceColor.b += light.object->getColor().b * illuminance;
            }
        }
        return surfaceColor;

    }
}
