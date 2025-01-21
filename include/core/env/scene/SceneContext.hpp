#pragma once

#include "core/env/scene/TransformedObject.hpp"

#include <vector>
#include <memory>

namespace RayTracer
{
    struct SceneContext
    {
        std::vector<TransformedPrimitive> primitives;
        std::vector<TransformedLight> lights;

        std::shared_ptr<Camera> camera;
        Transformation3d inverseCameraTransformation;
    };
};
