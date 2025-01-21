#include "display/sfml/SFMLDisplay.hpp"

#include "display/sfml/SFML.hpp"

extern "C"
{
    void display_init()
    {

    }

    void display_end()
    {

    }

    RayTracer::SFMLDisplay * display_create(std::size_t width, std::size_t height, const std::string &name)
    {
        RayTracer::SFMLDisplay *display = new RayTracer::SFMLDisplay(width, height, name);

        RayTracer::SFML::displays.push_back(display);
        return display;
    }

    void display_delete(RayTracer::SFMLDisplay *display)
    {
        RayTracer::SFML::displays.erase(
            std::remove(RayTracer::SFML::displays.begin(), RayTracer::SFML::displays.end(), display),
                        RayTracer::SFML::displays.end()
        );

        delete display;
    }
};
