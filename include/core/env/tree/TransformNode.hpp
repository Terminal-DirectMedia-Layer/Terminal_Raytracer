/*
** EPITECH PROJECT, 2024
** TransformNode
** File description:
** file for TransformNode functions
*/

#pragma once

#include "core/env/tree/ParentNode.hpp"

#include "core/math/Transformation3.hpp"

namespace RayTracer
{
    struct TransformNode : public ParentNode
    {
        TransformNode(const libconfig::Setting &node) :
            transformation(node)
        {}

        Transformation3d transformation;
    };
} // RayTracer
