/*
** EPITECH PROJECT, 2024
** Filter
** File description:
** file for Filter functions
*/

#include "core/RayTracer.hpp"
#include "plugin/filter/SepiaFilter.hpp"
#include "plugin/filter/NegativeFilter.hpp"
#include "plugin/filter/GrayScaleFilter.hpp"

extern "C" {
    void plugin_init(RayTracer::RayTracer &rt)
    {
        RayTracer::FilterFactory &ff = rt.getFilterFactory();

        ff.registerObject("gray", [&](libconfig::Setting &setting) {
            return std::make_shared<RayTracer::GrayScaleFilter>();
        });

        ff.registerObject("sepia", [&](libconfig::Setting &setting) {
            return std::make_shared<RayTracer::SepiaFilter>();
        });

        ff.registerObject("negative", [&](libconfig::Setting &setting) {
            return std::make_shared<RayTracer::NegativeFilter>();
        });
    }

    void plugin_end(RayTracer::RayTracer &rt)
    {
        RayTracer::FilterFactory &ff = rt.getFilterFactory();

        ff.unregisterObject("gray");
        ff.unregisterObject("sepia");
        ff.unregisterObject("negative");
    }
}
