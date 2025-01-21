/*
** EPITECH PROJECT, 2024
** Surface
** File description:
** file for Surface functions
*/

#include "core/RayTracer.hpp"

#include "plugin/surface/TextureSurface.hpp"
#include "plugin/surface/ColorSurface.hpp"
#include "plugin/surface/ChessboardSurface.hpp"
#include "plugin/surface/PerlinNoiseSurface.hpp"

extern "C"
{
    void plugin_init(RayTracer::RayTracer &rt)
    {
        RayTracer::SurfaceFactory &sf = rt.getSurfaceFactory();

        sf.registerObject("texture", [&](libconfig::Setting &setting) {
            std::string texture;
            if (!setting.lookupValue("texture", texture))
                throw RayTracer::Factory<RayTracer::Object>::Error("Texture surface must have a texture");
            RayTracer::Tuple<double, 2> ratio;
            try {
                if (!setting.exists("ratio"))
                    throw RayTracer::MathRepresentationError("Ratio not found");
                ratio = RayTracer::Tuple<double, 2>(setting["ratio"]);
            } catch (RayTracer::MathRepresentationError &e) {
                ratio = {1.0, 1.0};
            }
            return std::make_shared<RayTracer::TextureSurface>(texture, ratio);
        });

        sf.registerObject("color", [&](libconfig::Setting &setting) {
            std::string color;
            if (!setting.lookupValue("color", color))
                throw RayTracer::Factory<RayTracer::Object>::Error("Color surface must have a color");
            return std::make_shared<RayTracer::ColorSurface>(color);
        });

        sf.registerObject("chessboard", [&](libconfig::Setting &setting) {
            int cells;
            if (!setting.lookupValue("cells", cells))
                throw RayTracer::Factory<RayTracer::Object>::Error("Chessboard surface must have a cells");
            return std::make_shared<RayTracer::ChessboardSurface>(cells);
        });

        sf.registerObject("perlin_noise", [&](libconfig::Setting &setting) {
            RayTracer::Color pit = {0.0, 0.0, 0.0};
            RayTracer::Color peak = {1.0, 1.0, 1.0};
            double scale = 1.0;

            if (setting.exists("pit"))
                pit = RayTracer::Color(std::string(setting["pit"]));
            if (setting.exists("peak"))
                peak = RayTracer::Color(std::string(setting["peak"]));
            if (!setting.lookupValue("scale", scale))
                scale = 1.0;

            return std::make_shared<RayTracer::PerlinNoiseSurface>(
                pit, peak, scale);
        });
    }

    void plugin_end(RayTracer::RayTracer &rt)
    {
        RayTracer::SurfaceFactory &sf = rt.getSurfaceFactory();

        sf.unregisterObject("texture");
        sf.unregisterObject("color");
        sf.unregisterObject("chessboard");
    }
}
