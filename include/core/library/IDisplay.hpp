/*
** EPITECH PROJECT, 2024
** IDisplay
** File description:
** file for IDisplay functions
*/

#pragma once

#include "core/env/Color.hpp"

#include "core/math/Vector.hpp"
#include "core/math/Rectangle.hpp"

#include <functional>
#include <mutex>

#include <cstddef>

namespace RayTracer
{
    class Framebuffer
    {
    public:
        Framebuffer(std::size_t width, std::size_t height) :
            _size(static_cast<int>(width), static_cast<int>(height)),
            _color(new Color[width * height])
        {}

        ~Framebuffer()
        {
            delete[] this->_color;
        }

        Rectangle2i getSize() const
        {
            return this->_size;
        }

        void access(std::function<void(Color *)> callback)
        {
            std::lock_guard<std::mutex> lock(this->_mutex);

            callback(this->_color);
        }

    protected:
        Rectangle2i _size;

        std::mutex _mutex;
        Color *_color;
    };

    class IDisplay
    {
    public:
        virtual ~IDisplay() = default;

        virtual void update() = 0;

        virtual void clear(Color color) = 0;
        virtual Rectangle2i getViewport() const = 0;
        virtual Framebuffer & getFramebuffer() = 0;
    };
} // RayTracer
