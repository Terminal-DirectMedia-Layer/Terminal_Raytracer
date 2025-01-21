/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** file for RayTracer functions
*/

#pragma once

#include "core/factory/Factory.hpp"

#include "core/library/PluginLibrary.hpp"
#include "core/library/PluginLoader.hpp"

#include "core/library/DisplayLibrary.hpp"
#include "core/library/DisplayLoader.hpp"

#include <map>

namespace RayTracer
{
    class RayConfig;

    class RayTracer
    {
        friend RayConfig;

    protected:
        static constexpr std::string PATH_LIBRARY_PLUGINS = "plugins";
        static constexpr std::string PATH_LIBRARY_DISPLAYS = "displays";

    public:
        RayTracer();

    public:
        bool isLoaded() { return _loaded; }
        void load();

        void setDisplayLibrary(const std::string &name) { _displayLoader.use(name); }
        DisplayLibrary & getDisplayLibrary() const { return _displayLoader.active(); }

        ObjectFactory &getObjectFactory() { return _objectFactory; }
        MaterialFactory &getMaterialFactory() { return _materialFactory; }
        FilterFactory &getFilterFactory() { return _filterFactory; }
        SurfaceFactory &getSurfaceFactory() { return _surfaceFactory; }

        void registerObject(const std::string &name, ObjectFactory::FactoryBuilder &&callback) { _objectFactory.registerObject(name, callback); }

    private:
        void registerCamera();

    protected:
        bool _loaded = false;

        ObjectFactory _objectFactory;
        MaterialFactory _materialFactory;
        FilterFactory _filterFactory;
        SurfaceFactory _surfaceFactory;

        DisplayLoader _displayLoader;
        PluginLoader _pluginLoader;

        std::size_t _cameraInstanceNo = 0;
    };

    RayTracer &RT();
} // RayTracer
