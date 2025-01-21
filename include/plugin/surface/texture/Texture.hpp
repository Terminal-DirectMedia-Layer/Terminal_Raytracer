/*
** EPITECH PROJECT, 2024
** Texture
** File description:
** file for Texture functions
*/

#pragma once

#include "core/env/Color.hpp"

#include <cstdint>
#include <functional>
#include <memory>

namespace RayTracer
{
    using FrameBuffer = std::unique_ptr<uint32_t[]>;

    class Texture
    {
    public:
        Texture(uint32_t w, uint32_t h);
        ~Texture() = default;

        FrameBuffer &getFrameBuffer() { return _frameBuffer; }
        [[nodiscard]] uint32_t getRawPixel(uint32_t x, uint32_t y) const { return _frameBuffer[x + y * _w]; }
        [[nodiscard]] Color getPixel(uint32_t x, uint32_t y) const { return Color(getRawPixel(x % _w, y % _h)); }

        void access(std::function<void(uint32_t *)> &&callback);

        [[nodiscard]] uint32_t getWidth() const { return _w; }
        [[nodiscard]] uint32_t getHeight() const { return _h; }

    protected:
        uint32_t _w;
        uint32_t _h;
        FrameBuffer _frameBuffer;
    };
} // RayTracer
