#pragma once

#include "core/library/IDisplay.hpp"

#include <chrono>

#include <cstddef>

namespace RayTracer
{
    struct RenderEvent
    {
        IDisplay *display;

        enum class Type
        {
            NONE,
            RENDER_BEGIN,
            RENDER_END,
            RENDER_PROGRESS
        } type;

        union {
            struct {
                std::chrono::microseconds time;
                std::size_t thread_count;
            } render_begin;
            struct {
                std::chrono::microseconds time;
            } render_end;
            struct {
                float progress;
                std::size_t sections_calculated;
                std::size_t sections_total;
            } render_progress;
        } data;        
    };
};
