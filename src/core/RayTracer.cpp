/*
** EPITECH PROJECT, 2024
** Raymenteur
** File description:
** RayTracer.cpp
*/

#include "core/RayTracer.hpp"

#include "core/factory/Factory.hpp"

#include "core/env/object/Camera.hpp"

#include <memory>
#include <format>

namespace RayTracer
{
    RayTracer::RayTracer() :
        _displayLoader(RayTracer::PATH_LIBRARY_DISPLAYS),
        _pluginLoader(RayTracer::PATH_LIBRARY_PLUGINS)
    {
        this->registerCamera();
    }

    void RayTracer::load()
    {
        if (this->isLoaded())
            throw std::runtime_error("Attempt to load subsystems more than once");

        this->_pluginLoader.load();
        this->_displayLoader.load();

        this->_loaded = true;
    }

    void RayTracer::registerCamera()
    {
        _objectFactory.registerObject("camera", [this](libconfig::Setting &node) -> std::shared_ptr<Object> {
            return std::make_shared<Camera>(node, std::format("Camera Render {}", this->_cameraInstanceNo++));
        });
    }

    RayTracer &RT()
    {
        static RayTracer instance;

        return instance;
    }
} // namespace RayTracer
