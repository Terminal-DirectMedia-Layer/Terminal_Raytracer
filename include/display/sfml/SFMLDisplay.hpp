#pragma once

#include "core/library/IDisplay.hpp"

#include "core/env/scene/RenderEvent.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace RayTracer
{
    class SFMLDisplay : public IDisplay
    {
    public:
        SFMLDisplay(std::size_t width, std::size_t height, const std::string &name);
        ~SFMLDisplay() override;

        void update() override;
        void onEvent(const RayTracer::RenderEvent &event);

        bool isClosed() const { return !this->_window.isOpen(); }

        void clear(Color color) override;
        Rectangle2i getViewport() const override;
        Framebuffer & getFramebuffer() override;

    protected:
        sf::RenderWindow _window;
        sf::Font _font;

        std::chrono::microseconds _startRenderTime;

        Framebuffer _framebuffer;
        sf::RenderTexture _framebufferTexture;
        sf::Sprite  _framebufferSprite;

        sf::Text _statusText;
    };
};
