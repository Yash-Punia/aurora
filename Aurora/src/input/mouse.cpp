#include "input/mouse.h"
#include "log.h"

#include <algorithm>
#include <array>

#include "sdl2/SDL_mouse.h"

namespace aurora::input
{
    // since they are static, so need to initialize early
    int Mouse::x = 0;
    int Mouse::y = 0;
    int Mouse::xLast = 0;
    int Mouse::yLast = 0;

    std::array<bool, Mouse::ButtonCount> Mouse::buttons;
    std::array<bool, Mouse::ButtonCount> Mouse::buttonsLast;

    void Mouse::Update()
    {
        std::fill(buttonsLast.begin(), buttonsLast.end(), false);

        xLast = x;
        yLast = y;
        buttonsLast = buttons; // TOOD: is memcpy better?

        Uint32 state = SDL_GetMouseState(&x, &y);
        for(int i=0; i<ButtonCount; i++)
        {
            buttons[i] = state & SDL_BUTTON(i+1);
        }
    }

    void Mouse::Initialize()
    {
        std::fill(buttons.begin(), buttons.end(), false);
        std::fill(buttonsLast.begin(), buttonsLast.end(), false);
    }

    bool Mouse::Button(int button)
    {
        // AURORA_ASSERT(button >= AURORA_INPUT_MOUSE_FIRST && button < AURORA_INPUPT_MOUSE_LAST, "Invalid Mouse Button");
        if (button >= AURORA_INPUT_MOUSE_FIRST && button < AURORA_INPUT_MOUSE_LAST)
        {
            return buttons[button - 1];
        }
        return false;
    }

    bool Mouse::ButtonDown(int button)
    {
        if (button >= AURORA_INPUT_MOUSE_FIRST && button < AURORA_INPUT_MOUSE_LAST)
        {
            // if down now and wasn't down before, then it means buttonDown should be true
            return buttons[button - 1] && !buttonsLast[button-1];
        }
        return false;
    }

    bool Mouse::ButtonUp(int button)
    {
        if (button >= AURORA_INPUT_MOUSE_FIRST && button < AURORA_INPUT_MOUSE_LAST)
        {
            return !buttons[button - 1] && buttonsLast[button-1];
        }
        return false;
    }
}