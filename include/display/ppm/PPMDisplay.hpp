#pragma once

#include "core/library/IDisplay.hpp"

#include "core/math/Rectangle.hpp"

namespace RayTracer
{
    class PPMDisplay : public IDisplay
    {
    public:
        PPMDisplay(std::size_t width, std::size_t height, const std::string &name);
        ~PPMDisplay();

        void update() override;

        void clear(Color color) override;
        Rectangle2i getViewport() const override;
        Framebuffer & getFramebuffer() override;
    
    protected:
        std::string _name;
        Rectangle2i _size;

        Framebuffer _framebuffer;
    };
};
