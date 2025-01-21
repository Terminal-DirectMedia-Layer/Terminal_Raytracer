/*
** EPITECH PROJECT, 2024
** Raymenteur
** File description:
** TDL.hpp
*/

#ifndef RAYMENTEUR_TDL_HPP
    #define RAYMENTEUR_TDL_HPP


#include "core/library/IDisplay.hpp"

#include "3rd/TDL_Terminal-DirectMedia-Library/include/TDL/Graphics/Display/Display.hpp"
#include "3rd/TDL_Terminal-DirectMedia-Library/include/TDL/Graphics/Window/Window.hpp"
#include "display/tdl/TDLDisplay.hpp"

#include "core/math/Rectangle.hpp"

namespace RayTracer
{
    class TDL
    {
    public:
        static void init();
        static bool update();
        static void destroy();
        static void incrementPos();
        static void decrementPos();

        static std::vector<TDLDisplay *> displays;
        static tdl::Window *_window;
        static int pos;
    };
}

#endif //RAYMENTEUR_TDL_HPP
