#include "display/sfml/SFML.hpp"

#include "core/env/scene/RenderEvent.hpp"

extern "C"
{
    bool display_update()
    {
        std::size_t closedCount = std::count_if(
            RayTracer::SFML::displays.begin(), RayTracer::SFML::displays.end(),
            [](RayTracer::SFMLDisplay *display) {
                return display->isClosed();
            });

        if (RayTracer::SFML::displays.size() == closedCount)
            return false;

        for (RayTracer::SFMLDisplay *display : RayTracer::SFML::displays)
            display->update();
        return true;
    }

    void display_onevent(const RayTracer::RenderEvent &event)
    {
        static_cast<RayTracer::SFMLDisplay *>(event.display)->onEvent(event);
    }
}
