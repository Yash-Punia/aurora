#include "input/keyboard.h"
#include "log.h"

#include <algorithm>
#include <array>

#include "sdl2/SDL_keyboard.h"

namespace aurora::input
{
    std::array<bool, Keyboard::KeyCount> Keyboard::keys;
    std::array<bool, Keyboard::KeyCount> Keyboard::keysLast;

    void Keyboard::Update()
    {
        std::fill(keysLast.begin(), keysLast.end(), false);

        // we don't need to know how big array is, so we use nullptr     
        const Uint8* state = SDL_GetKeyboardState(nullptr);
        for(int i=AURORA_INPUT_KEY_FIRST; i<KeyCount; i++)
            keys[i] = state[i];
    }

    void Keyboard::Initialize()
    {
        std::fill(keys.begin(), keys.end(), false);
        std::fill(keysLast.begin(), keysLast.end(), false);
    }

    bool Keyboard::Key(int key)
    {
        // AURORA_ASSERT(Key >= AURORA_INPUT_Keyboard_FIRST && Key < AURORA_INPUPT_Keyboard_LAST, "Invalid Keyboard Key");
        if (key >= AURORA_INPUT_KEY_FIRST && key < Keyboard::KeyCount)
        {
            return keys[key];
        }
        return false;
    }

    bool Keyboard::KeyDown(int key)
    {
        if (key >= AURORA_INPUT_KEY_FIRST && key < Keyboard::KeyCount)
        {
            return keys[key] && !keysLast[key];
        }
        return false;
    }

    bool Keyboard::KeyUp(int key)
    {
        if (key >= AURORA_INPUT_KEY_FIRST && key < Keyboard::KeyCount)
        {
            return !keys[key] && keysLast[key];
        }
        return false;
    }
}