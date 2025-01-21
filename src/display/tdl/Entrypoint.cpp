/*
** EPITECH PROJECT, 2024
** Raymenteur
** File description:
** Entrypoint.cpp
*/

#include "display/tdl/TDLDisplay.hpp"
#include "display/tdl/TDL.hpp"

#include "core/library/IDisplay.hpp"
#include "core/env/scene/RenderEvent.hpp"

#include <string>

#include <cstddef>
#include <memory>

extern "C"
{
    void display_init()
    {
        RayTracer::TDL::init();
    }

    void display_end()
    {
        RayTracer::TDL::destroy();
    }

    RayTracer::TDLDisplay *display_create(std::size_t width, std::size_t height, const std::string &name)
    {
        RayTracer::TDLDisplay *display = new RayTracer::TDLDisplay(width, height, name);
        RayTracer::TDL::displays.push_back(display);
        return display;
    }

    void display_delete(RayTracer::TDLDisplay *display)
    {
        RayTracer::TDL::displays.erase(std::remove(RayTracer::TDL::displays.begin(), RayTracer::TDL::displays.end(), display), RayTracer::TDL::displays.end());
    }

    bool display_update()
    {
        if (RayTracer::TDL::displays.empty())
            return false;
        return RayTracer::TDL::update();
    }

    void display_onevent(const RayTracer::RenderEvent &event)
    {
        for (RayTracer::TDLDisplay *display : RayTracer::TDL::displays)
            display->onEvent(event, tdl::Vector2u(display->getViewport().width(), display->getViewport().height()));
    }

}
