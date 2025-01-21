#include "display/ppm/PPMDisplay.hpp"

#include "core/env/scene/RenderEvent.hpp"

extern "C"
{
    bool display_update()
    {
        return false;
    }

    void display_onevent(const RayTracer::RenderEvent &event)
    {
        std::cout << "Event received: " << static_cast<int>(event.type) << " on " << event.display << std::endl;
    }
};
