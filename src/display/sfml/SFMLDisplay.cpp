#include "display/sfml/SFMLDisplay.hpp"
#include "display/sfml/SFML.hpp"

#include <algorithm>
#include <chrono>

#include <cstdint>

namespace RayTracer
{
    SFMLDisplay::SFMLDisplay(std::size_t width, std::size_t height, const std::string &name) :
        _framebuffer(width, height)
    {
        this->_window.create(sf::VideoMode(width, height), name, sf::Style::Titlebar | sf::Style::Close);

        this->_framebufferTexture.create(width, height);
        this->_framebufferSprite.setTexture(this->_framebufferTexture.getTexture());
        
        this->_font.loadFromFile("share/font/hd44780_variable.ttf");
        this->_font.setSmooth(true);

        this->_statusText.setFont(this->_font);
        this->_statusText.setCharacterSize(16);
        this->_statusText.setPosition(4, 4);
        
        this->_statusText.setString("Waiting for rendering...");
    }

    SFMLDisplay::~SFMLDisplay()
    {
        this->_window.close();
    }

    void SFMLDisplay::update()
    {
        sf::Event event;

        while (this->_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                this->_window.close();
            }
        }

        this->_window.clear();
        this->_window.draw(this->_framebufferSprite);
        this->_window.draw(this->_statusText);
        this->_window.display();
    }
    
    void SFMLDisplay::onEvent(const RayTracer::RenderEvent &event)
    {
        switch (event.type) {
        case RayTracer::RenderEvent::Type::RENDER_BEGIN:
            this->_startRenderTime = event.data.render_begin.time;

            this->_statusText.setString("Started rendering...");
            break;

        case RayTracer::RenderEvent::Type::RENDER_PROGRESS:
            {
                sf::Image   image;
                Rectangle2i imageSize = this->_framebuffer.getSize();
                
                image.create(imageSize.width(), imageSize.height());

                this->_framebuffer.access([&imageSize, &image](Color *framebufferPtr) {
                    for (std::size_t i = 0; i < 1ul * imageSize.width() * imageSize.height(); i++) {
                        Color &color = framebufferPtr[i];

                        image.setPixel(i % imageSize.width(), i / imageSize.width(),
                            {
                                static_cast<std::uint8_t>(std::clamp(color.r, 0.0, 1.0) * 255),
                                static_cast<std::uint8_t>(std::clamp(color.g, 0.0, 1.0) * 255),
                                static_cast<std::uint8_t>(std::clamp(color.b, 0.0, 1.0) * 255)
                            });
                    }
                });

                sf::Texture imageTexture;
                imageTexture.loadFromImage(image);
                sf::Sprite imageSprite;
                imageSprite.setTexture(imageTexture);

                this->_framebufferTexture.draw(imageSprite);
                this->_framebufferTexture.display();

                this->_statusText.setString(
                    std::format("{:.2f}% done ({}/{} sections, {:.2f} s elapsed)",
                        event.data.render_progress.progress * 100.0f,
                        event.data.render_progress.sections_calculated,
                        event.data.render_progress.sections_total,
                        std::chrono::duration<double>(
                            std::chrono::system_clock::now().time_since_epoch() - this->_startRenderTime).count())
                );
            }
            break;

        case RayTracer::RenderEvent::Type::RENDER_END:
            this->_statusText.setString(
                std::format("Done ({:.2f} s)",
                    std::chrono::duration<double>(event.data.render_end.time - this->_startRenderTime).count())
            );
            break;

        default:
            break;
        }
    }

    void SFMLDisplay::clear(Color color)
    {
        this->_framebufferTexture.clear({
            static_cast<std::uint8_t>(color.r * 255),
            static_cast<std::uint8_t>(color.g * 255),
            static_cast<std::uint8_t>(color.b * 255)
        });
    }

    Rectangle2i SFMLDisplay::getViewport() const
    {
        sf::Vector2u size = this->_framebufferTexture.getSize();

        return {{}, {static_cast<int>(size.x), static_cast<int>(size.y)}};
    }

    Framebuffer & SFMLDisplay::getFramebuffer()
    {
        return this->_framebuffer;
    }
};
