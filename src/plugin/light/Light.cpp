/*
** EPITECH PROJECT, 2024
** Light
** File description:
** file for Light functions
*/

#include "plugin/light/DirectionalLight.hpp"
#include "core/env/object/Object.hpp"
#include "core/RayTracer.hpp"
#include "plugin/light/DiffuseLight.hpp"
#include "plugin/light/AmbientLight.hpp"

extern "C" {
    void plugin_init(RayTracer::RayTracer &rt)
    {
        rt.getObjectFactory().registerObject("directional_light", [&](libconfig::Setting &setting) {
            double luminance, angle, radius;
            std::string color;
            if (!setting.lookupValue("luminance", luminance))
                throw RayTracer::Factory<RayTracer::Object>::Error("Directional light must have a luminance");
            if (!setting.lookupValue("angle", angle))
                throw RayTracer::Factory<RayTracer::Object>::Error("Directional light must have an angle");
            if (!setting.lookupValue("radius", radius))
                throw RayTracer::Factory<RayTracer::Object>::Error("Directional light must have a radius");
            if (!setting.lookupValue("color", color))
                throw RayTracer::Factory<RayTracer::Object>::Error("Directional light must have a color");
            return std::make_shared<RayTracer::DirectionalLight>(
                    RayTracer::Color(color), angle, radius, luminance);
        });
        rt.getObjectFactory().registerObject("diffuse_light", [&](libconfig::Setting &setting) {
            std::string color;
            double luminance;
            if (!setting.lookupValue("luminance", luminance))
                throw RayTracer::Factory<RayTracer::Object>::Error("Diffuse light must have a luminance");
            if (!setting.lookupValue("color", color))
                throw RayTracer::Factory<RayTracer::Object>::Error("Diffuse light must have a color");
            return std::make_shared<RayTracer::DiffuseLight>(RayTracer::Color(color), luminance);
        });
        rt.getObjectFactory().registerObject("ambient_light", [&](libconfig::Setting &setting) {
            std::string color;
            if (!setting.lookupValue("color", color))
                throw RayTracer::Factory<RayTracer::Object>::Error("Ambient light must have a color");
            double intensity;
            if (!setting.lookupValue("intensity", intensity))
                throw RayTracer::Factory<RayTracer::Object>::Error("Ambient light must have an intensity");
            return std::make_shared<RayTracer::AmbientLight>(RayTracer::Color(color), intensity);
        });
    }

    void plugin_end(RayTracer::RayTracer &rt)
    {
        rt.getObjectFactory().unregisterObject("directional_light");
        rt.getObjectFactory().unregisterObject("diffuse_light");
        rt.getObjectFactory().unregisterObject("ambient_light");
    }
}
