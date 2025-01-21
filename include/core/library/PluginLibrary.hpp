/*
** EPITECH PROJECT, 2024
** PluginLibrary
** File description:
** file for PluginLibrary functions
*/

#pragma once

#include "core/library/DLLoader.hpp"

namespace RayTracer
{
    class PluginLibrary : public DLLoader
    {
    public:
        explicit PluginLibrary(const std::string &path);
        ~PluginLibrary();
    };
} // RayTracer
