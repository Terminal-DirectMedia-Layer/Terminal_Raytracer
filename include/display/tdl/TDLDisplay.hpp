/*
** EPITECH PROJECT, 2024
** Raymenteur
** File description:
** TDLDisplay.hpp
*/

#ifndef RAYMENTEUR_TDLDISPLAY_HPP
    #define RAYMENTEUR_TDLDISPLAY_HPP

    #include "core/library/IDisplay.hpp"

    #include "3rd/TDL_Terminal-DirectMedia-Library/include/TDL/Graphics/Display/Display.hpp"
    #include "3rd/TDL_Terminal-DirectMedia-Library/include/TDL/Graphics/Window/Window.hpp"
    #include "3rd/TDL_Terminal-DirectMedia-Library/include/TDL/Graphics/Drawable/Sprite/Sprite.hpp"
    #include "core/env/scene/RenderEvent.hpp"

    #include "core/math/Rectangle.hpp"

#include <memory>

namespace RayTracer
{
    class TDLDisplay : public IDisplay
    {
    public:
        TDLDisplay(std::size_t width, std::size_t height, const std::string &name);
        ~TDLDisplay();

        void update() override;
        void onEvent(const RayTracer::RenderEvent &event, tdl::Vector2u winSize);

        void clear(Color color) override;
        Rectangle2i getViewport() const override;
        Framebuffer &getFramebuffer() override;
        void setSize(std::size_t width, std::size_t height);
        Rectangle2i getSize() const { return _size; }

        tdl::Sprite *getSprite() const { return _sprite; }
    protected:

        void updateLoadingBar(tdl::Vector2u winSize, int fill);
        tdl::Sprite *_sprite;
        tdl::Texture *_texture;
        Framebuffer _framebuffer;
        Rectangle2i _size;
        tdl::Window *_window;
    };

};

#endif //RAYMENTEUR_TDLDISPLAY_HPP
