/*
** EPITECH PROJECT, 2024
** TransformedLight
** File description:
** file for TransformedLight functions
*/

#pragma once

#include "core/env/object/IPrimitive.hpp"
#include "core/env/object/Camera.hpp"

#include "core/math/Transformation3.hpp"
#include "core/env/tree/Node.hpp"
#include <memory>

namespace RayTracer
{
    class ILight;

    template<typename T>
    class TransformedObject
    {
    public:
        TransformedObject(const Transformation3d &transformation,
            const std::shared_ptr<T> &object)
            : transformation(transformation), object(object)
        {}

        Transformation3d transformation;
        std::shared_ptr<T> object;
    };

    using TransformedPrimitive = TransformedObject<IPrimitive>;
    using TransformedLight = TransformedObject<ILight>;
    using TransformedCamera = TransformedObject<Camera>;
    using TransformedNode = TransformedObject<Node>;
} // RayTracer
