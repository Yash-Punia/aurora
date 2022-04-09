#pragma once

#include <array>

namespace aurora::input
{
    class Mouse
    {
    public:
        static void Initialize();
        static void Update();
        
        inline static int X() {return x;}
        inline static int Y() {return y;}

        // Delta mouse position
        inline static int DX() {return (x - xLast);}
        inline static int DY() {return (y - yLast);}

        static bool Button(int button);
        static bool ButtonDown(int button);
        static bool ButtonUp(int button);

    private:
        constexpr static const int ButtonCount = 5; // SDL supports upto 5 buttons

        // I prefer using s as prefix for static variables but this will work for x, y coords
        static int x, xLast;
        static int y, yLast;

        // Use only buttonsLast and remove the need for three arrays
        static std::array<bool, Mouse::ButtonCount> buttons;       // current state
        static std::array<bool, Mouse::ButtonCount> buttonsLast;   // whether button was just pressed
        // static std::array<bool, Mouse::ButtonCount> buttonsUp;     // whether buttons was just released


    };
} 

// use un-named enum so that client can write better code
enum 
{
    AURORA_INPUT_MOUSE_FIRST = 1,
    AURORA_INPUT_MOUSE_LEFT = AURORA_INPUT_MOUSE_FIRST,
    AURORA_INPUT_MOUSE_MIDDLE = 2,
    AURORA_INPUT_MOUSE_RIGHT = 3,
    AURORA_INPUT_MOUSE_X1 = 4,
    AURORA_INPUT_MOUSE_X2 = 5,
    AURORA_INPUT_MOUSE_LAST = 5
};