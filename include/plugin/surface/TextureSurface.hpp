/*
** EPITECH PROJECT, 2024
** TextureSurface
** File description:
** file for TextureSurface functions
*/


#pragma once

#include "core/env/object/ISurface.hpp"
#include "include/plugin/surface/texture/Texture.hpp"
#include "include/plugin/surface/texture/TextureLoader.hpp"

namespace RayTracer
{
    class TextureSurface : public ISurface
    {
    public:
        explicit TextureSurface(std::string &texturePath, Tuple<double, 2> &ratio)
            : _texturePath(texturePath), _texture(TextureLoader(texturePath).loadTexture()), _ratio(ratio) {};
        ~TextureSurface() = default;

        Color colorAt(double u, double v) override;

    protected:
        std::string _texturePath;
        std::shared_ptr<Texture> _texture;
        Tuple<double, 2> _ratio;
    };
} // RayTracer
