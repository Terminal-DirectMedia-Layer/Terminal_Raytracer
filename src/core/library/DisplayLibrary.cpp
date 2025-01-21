#include "core/library/DisplayLibrary.hpp"

namespace RayTracer
{
    DisplayLibrary::DisplayLibrary(const std::string &path) :
        DLLoader(path)
    {
        // Library initialization callback
        this->getMethod<void(*)()>("display_init")();
    }

    DisplayLibrary::~DisplayLibrary()
    {
        // Library destruction callback
        this->getMethod<void (*)()>("display_end")();
    }

    DisplayEntity DisplayLibrary::createDisplay(std::size_t width, std::size_t height, const std::string &name)
    {
        auto createCallback =
            this->getMethod<IDisplay *(*)(std::size_t, std::size_t, const std::string &)>("display_create");

        return std::shared_ptr<IDisplay>(
            createCallback(width, height, name),
            DisplayLibraryDeleter(*this)
        );
    }

    void DisplayLibrary::deleteDisplay(IDisplay *display)
    {
        auto deleteCallback = this->getMethod<void (*)(IDisplay *)>("display_delete");

        deleteCallback(display);
    }

    bool DisplayLibrary::update()
    {
        return this->getMethod<bool (*)()>("display_update")();
    }

    void DisplayLibrary::pushEvent(RenderEvent &&event)
    {
        std::lock_guard<std::mutex> lock(this->_eventQueueMutex);

        this->_eventQueue.push(std::move(event));
    }

    void DisplayLibrary::flushEvents()
    {
        if (!this->_eventQueue.empty()) {
            std::lock_guard<std::mutex> lock(this->_eventQueueMutex);

            while (!this->_eventQueue.empty()) {
                RenderEvent event = this->_eventQueue.front();
                this->_eventQueue.pop();

                this->getMethod<void (*)(const RenderEvent &)>("display_onevent")(event);
            }
        }
    }
}
