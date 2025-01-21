#include "core/RayTracer.hpp"
#include "plugin/material/ReflectiveMaterial.hpp"
#include "plugin/material/PhongMaterial.hpp"
#include "plugin/material/RefractiveMaterial.hpp"

extern "C" {
    void plugin_init(RayTracer::RayTracer &rt)
    {
        RayTracer::MaterialFactory &mf = rt.getMaterialFactory();

        mf.registerObject("phong", [&](libconfig::Setting &setting) {
            double ka, kd, ks, shininess;
            if (!setting.lookupValue("ka", ka))
                throw RayTracer::Factory<RayTracer::Object>::Error("Phong material must have a ka");
            if (!setting.lookupValue("kd", kd))
                throw RayTracer::Factory<RayTracer::Object>::Error("Phong material must have a kd");
            if (!setting.lookupValue("ks", ks))
                throw RayTracer::Factory<RayTracer::Object>::Error("Phong material must have a ks");
            if (!setting.lookupValue("shininess", shininess))
                throw RayTracer::Factory<RayTracer::Object>::Error("Phong material must have a shininess");
            return std::make_shared<RayTracer::PhongMaterial>(ka, kd, ks, shininess);
        });

        mf.registerObject("reflective", [&](libconfig::Setting &setting) {
            double reflectivity;
            if (!setting.lookupValue("reflectivity", reflectivity))
                throw RayTracer::Factory<RayTracer::Object>::Error("Reflective material must have a reflectivity");
            return std::make_shared<RayTracer::ReflectiveMaterial>(reflectivity);
        });

        mf.registerObject("refractive", [&](libconfig::Setting &setting) {
            double refractivity, transparency;
            if (!setting.lookupValue("refractivity", refractivity))
                throw RayTracer::Factory<RayTracer::Object>::Error("Refractive material must have a refractivity");
            if (!setting.lookupValue("transparency", transparency))
                throw RayTracer::Factory<RayTracer::Object>::Error("Refractive material must have a transparency");
            return std::make_shared<RayTracer::RefractiveMaterial>(refractivity, transparency);
        });

        mf.registerObject("transparent", [&](libconfig::Setting &setting) {
            double transparency;
            if (!setting.lookupValue("transparency", transparency))
                throw RayTracer::Factory<RayTracer::Object>::Error("Transparent material must have a transparency");
            return std::make_shared<RayTracer::RefractiveMaterial>(1.0, transparency);
        });
    }

    void plugin_end(RayTracer::RayTracer &rt)
    {
        RayTracer::MaterialFactory &mf = rt.getMaterialFactory();

        mf.unregisterObject("phong");
        mf.unregisterObject("reflective");
        mf.unregisterObject("refractive");
        mf.unregisterObject("transparent");
    }
};
