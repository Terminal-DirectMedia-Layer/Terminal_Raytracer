/*
** EPITECH PROJECT, 2024
** PluginLibrary
** File description:
** file for PluginLibrary functions
*/

#include "core/library/PluginLibrary.hpp"

#include "core/RayTracer.hpp"

namespace RayTracer
{
    PluginLibrary::PluginLibrary(const std::string &path) : DLLoader(path)
    {
        auto constructor = getMethod<void (*)(RayTracer &)>("plugin_init");
        constructor(RT());
    }

    PluginLibrary::~PluginLibrary()
    {
        auto destructor = getMethod<void (*)(RayTracer &)>("plugin_end");
        destructor(RT());
    }
} // RayTracer
