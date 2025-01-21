/*
** EPITECH PROJECT, 2024
** ParentNode
** File description:
** file for ParentNode functions
*/

#pragma once

#include "core/env/tree/Node.hpp"

#include <memory>
#include <vector>

namespace RayTracer
{
    struct ParentNode : public Node
    {
        std::vector<std::shared_ptr<Node>> children{};
    };
} // RayTracer
