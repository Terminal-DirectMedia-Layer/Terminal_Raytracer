/*
** EPITECH PROJECT, 2024
** TextureLoader
** File description:
** file for TextureLoader functions
*/


#pragma once

#include <string>
#include <utility>
#include "Texture.hpp"

namespace RayTracer
{
    class TextureLoader
    {
    public:
        explicit TextureLoader(std::string path) : _path(std::move(path)) {};
        ~TextureLoader() = default;

        std::shared_ptr<Texture> loadTexture();
    protected:
        std::string _path;
    };
} // RayTracer
