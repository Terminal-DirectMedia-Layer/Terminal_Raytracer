#pragma once

#include "core/env/tree/SceneNode.hpp"

#include "core/env/object/Camera.hpp"
#include "core/env/object/APrimitive.hpp"

#include "core/env/scene/SceneContext.hpp"

#include <functional>
#include <memory>

namespace RayTracer
{
    class SceneTransformer
    {
    public:
        using ContextHandler = std::function<void(SceneContext &, std::shared_ptr<IDisplay> &)>;

        SceneTransformer(std::shared_ptr<SceneNode> sceneNode);

        void process(ContextHandler &&callback);

        template<typename T>
        void process(T *self, void(T::*callback)(SceneContext &, std::shared_ptr<IDisplay> &))
        {
            this->process(std::bind(callback, self, std::placeholders::_1, std::placeholders::_2));
        }

    private:
        void fillContext(SceneContext &context);

    protected:
        std::shared_ptr<SceneNode> _sceneNode;
    };
};
