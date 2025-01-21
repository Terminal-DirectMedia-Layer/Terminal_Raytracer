/*
** EPITECH PROJECT, 2024
** Raymenteur
** File description:
** TDLDisplay.cpp
*/

#include "display/tdl/TDLDisplay.hpp"
#include "core/library/IDisplay.hpp"

#include "3rd/TDL_Terminal-DirectMedia-Library/include/TDL/Graphics/Display/Display.hpp"
#include "3rd/TDL_Terminal-DirectMedia-Library/include/TDL/Graphics/Window/Window.hpp"
#include "3rd/TDL_Terminal-DirectMedia-Library/include/TDL/Graphics/Drawable/Sprite/Sprite.hpp"
#include "3rd/TDL_Terminal-DirectMedia-Library/include/TDL/Utils/Math/Vector.hpp"
#include "3rd/TDL_Terminal-DirectMedia-Library/include/TDL/Utils/Math/Rect.hpp"
#include <vector>
#include <algorithm>




namespace RayTracer
{
    TDLDisplay::TDLDisplay(std::size_t width, std::size_t height, const std::string &name) : _framebuffer(width, height), _size(static_cast<int>(width), static_cast<int>(height))
    {
        tdl::Pixel *pixels = new tdl::Pixel[width * height] {tdl::Pixel(0, 0, 0, 255)};
        _framebuffer.access([&](Color *framebufferPtr) {
            for (std::size_t i = 0; i <_size.width() * _size.height(); i++) {
                Color &framebufferPixel = framebufferPtr[i];
                pixels[i] = tdl::Pixel(static_cast<u_int8_t>(framebufferPixel.r * 255),
                                       static_cast<u_int8_t>(framebufferPixel.g * 255),
                                       static_cast<u_int8_t>(framebufferPixel.b * 255), 255);
            }
        });
        tdl::Vector2u size = tdl::Vector2u(width, height);
        tdl::Vector2u pos = tdl::Vector2u(100, 100);
        tdl::Vector2u pos2 = tdl::Vector2u(0, 0);
        _texture = new tdl::Texture(pixels, size);
        _sprite = new tdl::Sprite(_texture, pos2);
        _window = new tdl::Window(name, size, pos, tdl::Pixel(0, 0, 0, 255));
        _window->addDrawable(_sprite);
        tdl::Display::getInstance().addWindow(_window);
    }

    TDLDisplay::~TDLDisplay()
    {
        delete _sprite;
        delete _texture;
        delete _window;
    }

    void TDLDisplay::update()
    {
        _sprite->setTexture(_texture);
        _window->addDrawable(_sprite);
    }

    void TDLDisplay::clear(Color color)
    {
    }

    Rectangle2i TDLDisplay::getViewport() const
    {
        return _size;
    }

    Framebuffer &TDLDisplay::getFramebuffer()
    {
        return _framebuffer;
    }

    void TDLDisplay::updateLoadingBar(tdl::Vector2u winSize, int fill)
    {
        /*
        if (_loadingBar[0].size() != tdl::x(winSize) * 3) {
            _loadingBar[0].resize(tdl::x(winSize) * 3, {tdl::Pixel(0, 0, 0, 255)});
        }
        for (int i = 0; i < tdl::x(winSize) * 3; i++) {
            if (i < fill * tdl::x(winSize) * 3 / 100)
                _loadingBar[0][i] = tdl::Pixel(255, 255, 255, 255);
            else
                _loadingBar[0][i] = tdl::Pixel(255, 255, 255, 0);
        }
        _loadingTexture->SetPixelVector(_loadingBar);
        _loadingSprite->setTexture(_loadingTexture);
        _loadingTexture->setRect(tdl::RectU(0, 0, tdl::x(winSize) * 3, 1));
        _loadingSprite->setPos(tdl::Vector2u(0,  tdl::y(winSize) - 2));
        _loadingSprite->setRect(tdl::RectU(0, 0, tdl::x(winSize) * 3, 1));
        */
    }

    void TDLDisplay::onEvent(const RayTracer::RenderEvent &event, tdl::Vector2u winSize) {
        if (event.type == RenderEvent::Type::RENDER_PROGRESS) {
            int percentToFill = static_cast<int>((event.data.render_progress.progress * 100));
            updateLoadingBar(winSize, percentToFill);
            tdl::Matrix<tdl::Pixel> pixels = _texture->getTextureData();
            tdl::Vector2u s = tdl::Vector2u(_size.width(), _size.height());
            pixels.resize(s);
            _framebuffer.access([&](Color *framebufferPtr) {
                for (std::size_t y = 0; y < _size.height(); y++) {
                    for (std::size_t x = 0; x < _size.width(); x++) {
                        Color &framebufferPixel = framebufferPtr[y * _size.width() + x];
                        tdl::Pixel p = tdl::Pixel(std::clamp(static_cast<int>(framebufferPixel.r * 255), 0, 255),
                                                  std::clamp(static_cast<int>(framebufferPixel.g * 255), 0, 255),
                                                  std::clamp(static_cast<int>(framebufferPixel.b * 255), 0, 255), 255);
                        pixels.setElement(tdl::Vector2u(x, y), p);
                    }
                }
            });
            _texture->setTextureData(pixels);
        }
        if (event.type == RenderEvent::Type::RENDER_END) {
            updateLoadingBar(winSize, 0);
        }
    }
}
