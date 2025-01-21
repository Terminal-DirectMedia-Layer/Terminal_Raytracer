/*
** EPITECH PROJECT, 2024
** DisplayLibrary
** File description:
** file for DisplayLibrary functions
*/

#pragma once

#include "core/env/scene/RenderEvent.hpp"

#include "core/library/DLLoader.hpp"
#include "core/library/IDisplay.hpp"

#include <filesystem>
#include <memory>
#include <queue>

namespace RayTracer
{
    using DisplayEntity = std::shared_ptr<IDisplay>;

    class DisplayLibrary : public DLLoader
    {
        friend struct DisplayLibraryDeleter;

    public:
        DisplayLibrary(const std::string &path);
        ~DisplayLibrary();

        // Create a display rendering window/texture/whatever is happening behind the hood
        DisplayEntity createDisplay(std::size_t width, std::size_t height, const std::string &name);

        void pushEvent(RenderEvent &&event);

    protected:
        // Dispose of the display created with the previous method
        void deleteDisplay(IDisplay *display);

    public:
        // Update the general state of the library
        bool update();
        void flushEvents();

    protected:
        std::mutex _eventQueueMutex;
        std::queue<RenderEvent> _eventQueue;
    };

    struct DisplayLibraryDeleter {
    public:
        DisplayLibraryDeleter(DisplayLibrary &library) :
            _library(library)
        {}

        void operator()(IDisplay *display) const
        {
            this->_library.deleteDisplay(display);
        }

    protected:
        DisplayLibrary &_library;
    };
} // RayTracer
