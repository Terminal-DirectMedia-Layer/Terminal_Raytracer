/*
** EPITECH PROJECT, 2024
** Primitive
** File description:
** file for Primitive functions
*/

#include "plugin/primitive/Ellipsoid.hpp"
#include "plugin/primitive/Plane.hpp"
#include "plugin/primitive/Cuboid.hpp"
#include "plugin/primitive/Cylinder.hpp"
#include "plugin/primitive/Cone.hpp"
#include "plugin/primitive/Triangle.hpp"

#include "core/factory/ObjectPrimitiveWrapper.hpp"
#include "core/RayTracer.hpp"

extern "C"
{
    void plugin_init(RayTracer::RayTracer &rt)
    {
        RayTracer::ObjectFactory &of = rt.getObjectFactory();

        of.registerObject("ellipsoid", [&](libconfig::Setting &setting) {
            return RayTracer::ObjectPrimitiveWrapper::createFactory(
                [&](libconfig::Setting &node,
                    std::vector<std::shared_ptr<RayTracer::IMaterial>>
                        &materials,
                    std::shared_ptr<RayTracer::ISurface> &surface) {
                    RayTracer::Vector3d dimensions;
                    double radius;

                    try {
                        if (!node.exists("dimensions"))
                            throw RayTracer::MathRepresentationError("dimensions");
                        dimensions = RayTracer::Tuple<double, 3>(node["dimensions"]);
                    } catch (RayTracer::MathRepresentationError &e) {
                        dimensions = RayTracer::Vector3d{1.0, 1.0, 1.0};
                    }
                    
                    if (!node.lookupValue("radius", radius))
                        radius = 1.0;
                    
                    return std::make_shared<RayTracer::Ellipsoid>(materials, surface, dimensions, radius);
                })(setting);
        });

        of.registerObject("plane", [&](libconfig::Setting &setting) {
            return RayTracer::ObjectPrimitiveWrapper::createFactory(
                [&](libconfig::Setting &node,
                    std::vector<std::shared_ptr<RayTracer::IMaterial>>
                        &materials,
                    std::shared_ptr<RayTracer::ISurface> &surface) {
                    RayTracer::Vector3d normal;
                    
                    try {
                        if (!node.exists("normal"))
                            throw RayTracer::MathRepresentationError("normal");
                        normal = RayTracer::Tuple<double, 3>(node["normal"]);
                    } catch (RayTracer::MathRepresentationError &e) {
                        normal = RayTracer::Vector3d{0.0, 0.0, 1.0};
                    }

                    return std::make_shared<RayTracer::Plane>(materials, surface, normal);
                })(setting);
        });

        of.registerObject("cuboid", [&](libconfig::Setting &setting) {
            return RayTracer::ObjectPrimitiveWrapper::createFactory(
                [&](libconfig::Setting &node,
                    std::vector<std::shared_ptr<RayTracer::IMaterial>>
                        &materials,
                    std::shared_ptr<RayTracer::ISurface> &surface) {
                    RayTracer::Vector3d dimensions;

                    try {
                        if (!node.exists("dimensions"))
                            throw RayTracer::MathRepresentationError("dimensions");
                        dimensions = RayTracer::Tuple<double, 3>(node["dimensions"]);
                    } catch (RayTracer::MathRepresentationError &e) {
                        dimensions = RayTracer::Vector3d{1.0, 1.0, 1.0};
                    }

                    return std::make_shared<RayTracer::Cuboid>(dimensions, materials, surface);
                })(setting);
        });

        of.registerObject("cylinder", [&](libconfig::Setting &setting) {
            return RayTracer::ObjectPrimitiveWrapper::createFactory(
                [&](libconfig::Setting &node,
                    std::vector<std::shared_ptr<RayTracer::IMaterial>>
                        &materials,
                    std::shared_ptr<RayTracer::ISurface> &surface) {
                    double radius, height;
                    RayTracer::Vector3d dimensions;
                    
                    if (!node.lookupValue("radius", radius))
                        radius = 1.0;
                    if (!node.lookupValue("height", height))
                        height = 1.0;

                    try {
                        if (!node.exists("direction"))
                            throw RayTracer::MathRepresentationError("direction");
                        dimensions = RayTracer::Tuple<double, 3>(node["direction"]);
                    } catch (RayTracer::MathRepresentationError &e) {
                        dimensions = RayTracer::Vector3d{1.0, 1.0, 1.0};
                    }
                    return std::make_shared<RayTracer::Cylinder>(materials, surface, radius, height, dimensions);
                })(setting);
        });

        of.registerObject("cone", [&](libconfig::Setting &setting) {
            return RayTracer::ObjectPrimitiveWrapper::createFactory(
                [&](libconfig::Setting &node,
                    std::vector<std::shared_ptr<RayTracer::IMaterial>>
                        &materials,
                    std::shared_ptr<RayTracer::ISurface> &surface) {
                    double radius, height;

                    if (!node.lookupValue("radius", radius))
                        radius = 1.0;
                    if (!node.lookupValue("height", height))
                        height = 1.0;
                    return std::make_shared<RayTracer::Cone>(radius, height, materials, surface);
                })(setting);
        });

        of.registerObject("triangle", [](libconfig::Setting &node) {
            return RayTracer::ObjectPrimitiveWrapper::createFactory(
                [&](libconfig::Setting &node,
                    std::vector<std::shared_ptr<RayTracer::IMaterial>>
                        &materials,
                    std::shared_ptr<RayTracer::ISurface> &surface
                ) {
                    RayTracer::Vector3d a, b, c;

                    for (std::string_view point : {"a", "b", "c"})
                        if (!node.exists(point.data()))
                            throw RayTracer::MathRepresentationError("Missing " + std::string(point));
                    
                    a.load(node["a"]);
                    b.load(node["b"]);
                    c.load(node["c"]);

                    return std::make_shared<RayTracer::Triangle>(a, b, c, materials, surface);
                })(node);
        });
    }

    void plugin_end(RayTracer::RayTracer &rt)
    {
        RayTracer::ObjectFactory &of = rt.getObjectFactory();

        of.unregisterObject("ellipsoid");
        of.unregisterObject("plane");
        of.unregisterObject("cuboid");
        of.unregisterObject("cylinder");
        of.unregisterObject("cone");
        of.unregisterObject("triangle");
    }
}
