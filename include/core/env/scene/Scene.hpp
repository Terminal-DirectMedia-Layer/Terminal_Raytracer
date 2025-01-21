/*
** EPITECH PROJECT, 2024
** Scene
** File description:
** file for Scene functions
*/

#pragma once

#include "core/env/Ray.hpp"

#include "core/env/tree/SceneNode.hpp"
#include "core/env/tree/ObjectNode.hpp"

#include "core/env/object/Camera.hpp"

#include "core/env/scene/SceneTransformer.hpp"

#include <memory>
#include <thread>
#include <random>

namespace RayTracer
{
    class Scene
    {
    public:
        explicit Scene(const std::shared_ptr<SceneNode> &sceneNode, int jobCount, bool fast);

    protected:
        void render(SceneContext &context, std::shared_ptr<IDisplay> &display);
        Color query(SceneContext &context, Ray3d &ray, std::mt19937 &generator);

    public:
        void render();

    protected:
        SceneTransformer _transformer;
        int _jobCount;
        bool _fast;
    };
} // RayTracing
