/*
** EPITECH PROJECT, 2024
** Texture
** File description:
** file for Texture functions
*/

#include "plugin/surface/texture/Texture.hpp"

namespace RayTracer
{
    Texture::Texture(uint32_t w, uint32_t h) : _w(w), _h(h),
        _frameBuffer(std::make_unique_for_overwrite<uint32_t[]>(w * h))
    {
    }

    void Texture::access(std::function<void(uint32_t *)> &&callback)
    {
        callback(this->_frameBuffer.get());
    }
} // RayTracer
