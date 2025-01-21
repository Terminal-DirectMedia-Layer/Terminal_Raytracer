/*
** EPITECH PROJECT, 2024
** Raymenteur
** File description:
** TDL.cpp
*/

#include "display/tdl/TDL.hpp"
#include "3rd/TDL_Terminal-DirectMedia-Library/include/TDL/Graphics/Display/Display.hpp"
#include "3rd/TDL_Terminal-DirectMedia-Library/include/TDL/Utils/Math/Vector.hpp"
#include "3rd/TDL_Terminal-DirectMedia-Library/include/TDL/Utils/Math/Rect.hpp"

namespace RayTracer
{
    std::vector<TDLDisplay *> TDL::displays;
    tdl::Window *TDL::_window;
    int TDL::pos;

    void TDL::init()
    {
        tdl::Display::getInstance()._interruptManager.start();
        pos = 0;
    }

    void TDL::destroy() {
        tdl::Display::getInstance()._interruptManager.stop();
        for (TDLDisplay *display : displays)
            delete display;
        displays.clear();
    }

    bool TDL::update()
    {
        /*
        for(tdl::Event event; _window->pollEvent(event) ;)
        {
            if (event.type == tdl::Event::EventType::KeyPressed)
            {
                if (event.key.code == tdl::TDLKeyCodes::KEY_RIGHT){
                    incrementPos();
                }
                if (event.key.code =_window= tdl::TDLKeyCodes::KEY_LEFT) {
                    decrementPos();
                }
                if (event.key.code == tdl::TDLKeyCodes::KEY_ESC)
                    return false;
            }
        }
        */
        tdl::Display::getInstance().clear();
        for (TDLDisplay *display : displays) {
            display->update();
            tdl::RectU crop = tdl::RectU(0, 0, display->getSize().width(), display->getSize().height());
            display->getSprite()->setRect(crop);
        }
        tdl::Display::getInstance().draw();
        // displays[pos]->getSprite()->drawOn(_window);
        // displays[pos]->getLoadingSprite()->drawOn(_window);
        return true;
    }

    void TDL::incrementPos()
    {
        pos++;
        if (pos >= displays.size())
            pos = 0;
    }

    void TDL::decrementPos()
    {
        pos--;
        if (pos < 0)
            pos = displays.size() - 1;
    }
}