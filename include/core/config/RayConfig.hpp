/*
** EPITECH PROJECT, 2024
** RayConfig
** File description:
** file for RayConfig functions
*/

#pragma once

#include "core/RayTracer.hpp"

#include "core/env/tree/SceneNode.hpp"
#include "core/env/tree/ObjectNode.hpp"
#include "core/env/tree/TransformNode.hpp"

#include <string>
#include <utility>
#include <filesystem>
#include <format>

#include <omp.h>

#include <libconfig.h++>

namespace RayTracer
{
    class RayConfig
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

        explicit RayConfig() = default;

        [[nodiscard]] const std::string &pluginsPath() const;
        [[nodiscard]] const std::string &displaysPath() const;

        [[nodiscard]] int jobCount() const;
        [[nodiscard]] bool fast() const;

        [[nodiscard]] const std::string &sceneFile() const;
        [[nodiscard]] const std::string &displayLibrary() const;

        void setPluginsPath(const std::string &pluginPath);
        void setDisplaysPath(const std::string &displayPath);

        void setJobCount(int jobCount);
        void setFast(bool fast);

        void setSceneFile(const std::string &sceneFile);
        void setDisplayLibrary(const std::string &displayLibrary);

        std::shared_ptr<SceneNode> loadScene();
        static std::shared_ptr<SceneNode> loadScene(const std::string &sceneFile);

    private:
        static std::shared_ptr<Node> loadNode(libconfig::Setting &setting);
        static std::vector<std::shared_ptr<Node>> loadNodes(libconfig::Setting &setting);

    protected:
        std::string _sceneFile;

        std::string _pluginsPath = RayTracer::PATH_LIBRARY_PLUGINS;
        std::string _displaysPath = RayTracer::PATH_LIBRARY_DISPLAYS;

        int _jobCount = ::omp_get_max_threads();
        bool _fast = false;

        std::string _displayLibrary = "ppm";
    };
} // RayTracer
