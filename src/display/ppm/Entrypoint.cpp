#include "display/ppm/PPMDisplay.hpp"

#include <string>

#include <cstddef>

extern "C"
{
    void display_init()
    {

    }

    void display_end()
    {

    }

    RayTracer::PPMDisplay * display_create(std::size_t width, std::size_t height, const std::string &name)
    {
        return new RayTracer::PPMDisplay(width, height, name);
    }

    void display_delete(RayTracer::PPMDisplay *display)
    {
        delete display;
    }
};
