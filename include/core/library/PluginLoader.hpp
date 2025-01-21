/*
** EPITECH PROJECT, 2024
** PluginLoader
** File description:
** file for PluginLoader functions
*/

#pragma once

#include "core/library/PluginLibrary.hpp"

#include <stdexcept>
#include <string>
#include <unordered_map>

namespace RayTracer
{
    class PluginLoader
    {
    public:
        class Error : public std::exception
        {
        public:
            explicit Error(std::string message) : _message(std::move(message)) {};
            ~Error() override = default;

            [[nodiscard]] const char *what() const noexcept override { return _message.c_str(); }

        private:
            std::string _message;
        };

        explicit PluginLoader(std::string path = "plugins") :
            _path(std::move(path))
        {}
        ~PluginLoader() = default;

        void load();

    protected:
        std::string _path;
        std::unordered_map<std::string, PluginLibrary> _plugins;
    };
}; // RayTracer
