/*
** EPITECH PROJECT, 2024
** ObjectNode
** File description:
** file for ObjectNode functions
*/


#pragma once

#include <memory>
#include "core/env/object/Object.hpp"
#include "core/env/tree/Node.hpp"

namespace RayTracer
{
    struct ObjectNode : public Node
    {
        std::shared_ptr<Object> object;
    };
} // RayTracer
