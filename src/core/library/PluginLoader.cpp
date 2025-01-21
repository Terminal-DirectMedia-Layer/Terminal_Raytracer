/*
** EPITECH PROJECT, 2024
** PluginLoader
** File description:
** file for PluginLoader functions
*/

#include "core/library/PluginLoader.hpp"

#include "core/RayTracer.hpp"

#include <filesystem>
#include <format>

namespace RayTracer
{
    void PluginLoader::load()
    {
        if (!std::filesystem::exists(_path))
            throw Error(std::format("Invalid plugin directory path '{}'", _path));

        for (const auto &entry : std::filesystem::directory_iterator(_path)) {
            std::string path = entry.path().string();
            std::string name = entry.path().filename().string();
            if (name.ends_with(".so") && std::filesystem::is_regular_file(entry.path()))
                _plugins.emplace(name, path);
        }
    }
} // RayTracer
