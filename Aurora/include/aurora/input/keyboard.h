#pragma once

#include <array>

namespace aurora::input
{
    class Keyboard
    {
    public:
        static void Initialize();
        static void Update();

        static bool Key(int key);
        static bool KeyDown(int key);
        static bool KeyUp(int key);

    private:
        // SDL_SCANCODE provides the bindings to keyboard keys
        constexpr static const int KeyCount = 287; // SDL supports upto index 286 SDL_NUM_SCANCODES

        static std::array<bool, Keyboard::KeyCount> keys;     // current state
        static std::array<bool, Keyboard::KeyCount> keysLast; // whether key was just pressed
    };
}

// use un-named enum so that client can write better code
enum
{
    AURORA_INPUT_KEY_FIRST = 4,
    AURORA_INPUT_KEY_A = AURORA_INPUT_KEY_FIRST,
    AURORA_INPUT_KEY_B = 5,
    AURORA_INPUT_KEY_C = 6,
    AURORA_INPUT_KEY_D = 7,
    AURORA_INPUT_KEY_E = 8,
    AURORA_INPUT_KEY_F = 9,
    AURORA_INPUT_KEY_G = 10,
    AURORA_INPUT_KEY_H = 11,
    AURORA_INPUT_KEY_I = 12,
    AURORA_INPUT_KEY_J = 13,
    AURORA_INPUT_KEY_K = 14,
    AURORA_INPUT_KEY_L = 15,
    AURORA_INPUT_KEY_M = 16,
    AURORA_INPUT_KEY_N = 17,
    AURORA_INPUT_KEY_O = 18,
    AURORA_INPUT_KEY_P = 19,
    AURORA_INPUT_KEY_Q = 20,
    AURORA_INPUT_KEY_R = 21,
    AURORA_INPUT_KEY_S = 22,
    AURORA_INPUT_KEY_T = 23,
    AURORA_INPUT_KEY_U = 24,
    AURORA_INPUT_KEY_V = 25,
    AURORA_INPUT_KEY_W = 26,
    AURORA_INPUT_KEY_X = 27,
    AURORA_INPUT_KEY_Y = 28,
    AURORA_INPUT_KEY_Z = 29,
    AURORA_INPUT_KEY_1 = 30,
    AURORA_INPUT_KEY_2 = 31,
    AURORA_INPUT_KEY_3 = 32,
    AURORA_INPUT_KEY_4 = 33,
    AURORA_INPUT_KEY_5 = 34,
    AURORA_INPUT_KEY_6 = 35,
    AURORA_INPUT_KEY_7 = 36,
    AURORA_INPUT_KEY_8 = 37,
    AURORA_INPUT_KEY_9 = 38,
    AURORA_INPUT_KEY_0 = 39,
    AURORA_INPUT_KEY_RETURN = 40,
    AURORA_INPUT_KEY_ESCAPE = 41,
    AURORA_INPUT_KEY_BACKSPACE = 42,
    AURORA_INPUT_KEY_TAB = 43,
    AURORA_INPUT_KEY_SPACE = 44,
    AURORA_INPUT_KEY_MINUS = 45,
    AURORA_INPUT_KEY_EQUALS = 46,
    AURORA_INPUT_KEY_LEFTBRACKET = 47,
    AURORA_INPUT_KEY_RIGHTBRACKET = 48,
    AURORA_INPUT_KEY_BACKSLASH = 49,
    AURORA_INPUT_KEY_NONUSHASH = 50,
    AURORA_INPUT_KEY_SEMICOLON = 51,
    AURORA_INPUT_KEY_APOSTROPHE = 52,
    AURORA_INPUT_KEY_GRAVE = 53,
    AURORA_INPUT_KEY_COMMA = 54,
    AURORA_INPUT_KEY_PERIOD = 55,
    AURORA_INPUT_KEY_SLASH = 56,
    AURORA_INPUT_KEY_CAPSLOCK = 57,
    AURORA_INPUT_KEY_F1 = 58,
    AURORA_INPUT_KEY_F2 = 59,
    AURORA_INPUT_KEY_F3 = 60,
    AURORA_INPUT_KEY_F4 = 61,
    AURORA_INPUT_KEY_F5 = 62,
    AURORA_INPUT_KEY_F6 = 63,
    AURORA_INPUT_KEY_F7 = 64,
    AURORA_INPUT_KEY_F8 = 65,
    AURORA_INPUT_KEY_F9 = 66,
    AURORA_INPUT_KEY_F10 = 67,
    AURORA_INPUT_KEY_F11 = 68,
    AURORA_INPUT_KEY_F12 = 69,
    AURORA_INPUT_KEY_PRINTSCREEN = 70,
    AURORA_INPUT_KEY_SCROLLLOCK = 71,
    AURORA_INPUT_KEY_PAUSE = 72,
    AURORA_INPUT_KEY_INSERT = 73,
    AURORA_INPUT_KEY_HOME = 74,
    AURORA_INPUT_KEY_PAGEUP = 75,
    AURORA_INPUT_KEY_DELETE = 76,
    AURORA_INPUT_KEY_END = 77,
    AURORA_INPUT_KEY_PAGEDOWN = 78,
    AURORA_INPUT_KEY_RIGHT = 79,
    AURORA_INPUT_KEY_LEFT = 80,
    AURORA_INPUT_KEY_DOWN = 81,
    AURORA_INPUT_KEY_UP = 82,
    AURORA_INPUT_KEY_NUMLOCKCLEAR = 83,
    AURORA_INPUT_KEY_KP_DIVIDE = 84,
    AURORA_INPUT_KEY_KP_MULTIPLY = 85,
    AURORA_INPUT_KEY_KP_MINUS = 86,
    AURORA_INPUT_KEY_KP_PLUS = 87,
    AURORA_INPUT_KEY_KP_ENTER = 88,
    AURORA_INPUT_KEY_KP_1 = 89,
    AURORA_INPUT_KEY_KP_2 = 90,
    AURORA_INPUT_KEY_KP_3 = 91,
    AURORA_INPUT_KEY_KP_4 = 92,
    AURORA_INPUT_KEY_KP_5 = 93,
    AURORA_INPUT_KEY_KP_6 = 94,
    AURORA_INPUT_KEY_KP_7 = 95,
    AURORA_INPUT_KEY_KP_8 = 96,
    AURORA_INPUT_KEY_KP_9 = 97,
    AURORA_INPUT_KEY_KP_0 = 98,
    AURORA_INPUT_KEY_KP_PERIOD = 99,
    AURORA_INPUT_KEY_NONUSBACKSLASH = 100,
    AURORA_INPUT_KEY_APPLICATION = 101,
    AURORA_INPUT_KEY_POWER = 102,
    AURORA_INPUT_KEY_KP_EQUALS = 103,
    AURORA_INPUT_KEY_F13 = 104,
    AURORA_INPUT_KEY_F14 = 105,
    AURORA_INPUT_KEY_F15 = 106,
    AURORA_INPUT_KEY_F16 = 107,
    AURORA_INPUT_KEY_F17 = 108,
    AURORA_INPUT_KEY_F18 = 109,
    AURORA_INPUT_KEY_F19 = 110,
    AURORA_INPUT_KEY_F20 = 111,
    AURORA_INPUT_KEY_F21 = 112,
    AURORA_INPUT_KEY_F22 = 113,
    AURORA_INPUT_KEY_F23 = 114,
    AURORA_INPUT_KEY_F24 = 115,
    AURORA_INPUT_KEY_EXECUTE = 116,
    AURORA_INPUT_KEY_HELP = 117,
    AURORA_INPUT_KEY_MENU = 118,
    AURORA_INPUT_KEY_SELECT = 119,
    AURORA_INPUT_KEY_STOP = 120,
    AURORA_INPUT_KEY_AGAIN = 121,
    AURORA_INPUT_KEY_UNDO = 122,
    AURORA_INPUT_KEY_CUT = 123,
    AURORA_INPUT_KEY_COPY = 124,
    AURORA_INPUT_KEY_PASTE = 125,
    AURORA_INPUT_KEY_FIND = 126,
    AURORA_INPUT_KEY_MUTE = 127,
    AURORA_INPUT_KEY_VOLUMEUP = 128,
    AURORA_INPUT_KEY_VOLUMEDOWN = 129,
    AURORA_INPUT_KEY_KP_COMMA = 133,
    AURORA_INPUT_KEY_KP_EQUALSAS400 = 134,
    AURORA_INPUT_KEY_INTERNATIONAL1 = 135,
    AURORA_INPUT_KEY_INTERNATIONAL2 = 136,
    AURORA_INPUT_KEY_INTERNATIONAL3 = 137,
    AURORA_INPUT_KEY_INTERNATIONAL4 = 138,
    AURORA_INPUT_KEY_INTERNATIONAL5 = 139,
    AURORA_INPUT_KEY_INTERNATIONAL6 = 140,
    AURORA_INPUT_KEY_INTERNATIONAL7 = 141,
    AURORA_INPUT_KEY_INTERNATIONAL8 = 142,
    AURORA_INPUT_KEY_INTERNATIONAL9 = 143,
    AURORA_INPUT_KEY_LANG1 = 144,
    AURORA_INPUT_KEY_LANG2 = 145,
    AURORA_INPUT_KEY_LANG3 = 146,
    AURORA_INPUT_KEY_LANG4 = 147,
    AURORA_INPUT_KEY_LANG5 = 148,
    AURORA_INPUT_KEY_LANG6 = 149,
    AURORA_INPUT_KEY_LANG7 = 150,
    AURORA_INPUT_KEY_LANG8 = 151,
    AURORA_INPUT_KEY_LANG9 = 152,
    AURORA_INPUT_KEY_ALTERASE = 153,
    AURORA_INPUT_KEY_SYSREQ = 154,
    AURORA_INPUT_KEY_CANCEL = 155,
    AURORA_INPUT_KEY_CLEAR = 156,
    AURORA_INPUT_KEY_PRIOR = 157,
    AURORA_INPUT_KEY_RETURN2 = 158,
    AURORA_INPUT_KEY_SEPARATOR = 159,
    AURORA_INPUT_KEY_OUT = 160,
    AURORA_INPUT_KEY_OPER = 161,
    AURORA_INPUT_KEY_CLEARAGAIN = 162,
    AURORA_INPUT_KEY_CRSEL = 163,
    AURORA_INPUT_KEY_EXSEL = 164,
    AURORA_INPUT_KEY_KP_00 = 176,
    AURORA_INPUT_KEY_KP_000 = 177,
    AURORA_INPUT_KEY_THOUSANDSSEPARATOR = 178,
    AURORA_INPUT_KEY_DECIMALSEPARATOR = 179,
    AURORA_INPUT_KEY_CURRENCYUNIT = 180,
    AURORA_INPUT_KEY_CURRENCYSUBUNIT = 181,
    AURORA_INPUT_KEY_KP_LEFTPAREN = 182,
    AURORA_INPUT_KEY_KP_RIGHTPAREN = 183,
    AURORA_INPUT_KEY_KP_LEFTBRACE = 184,
    AURORA_INPUT_KEY_KP_RIGHTBRACE = 185,
    AURORA_INPUT_KEY_KP_TAB = 186,
    AURORA_INPUT_KEY_KP_BACKSPACE = 187,
    AURORA_INPUT_KEY_KP_A = 188,
    AURORA_INPUT_KEY_KP_B = 189,
    AURORA_INPUT_KEY_KP_C = 190,
    AURORA_INPUT_KEY_KP_D = 191,
    AURORA_INPUT_KEY_KP_E = 192,
    AURORA_INPUT_KEY_KP_F = 193,
    AURORA_INPUT_KEY_KP_XOR = 194,
    AURORA_INPUT_KEY_KP_POWER = 195,
    AURORA_INPUT_KEY_KP_PERCENT = 196,
    AURORA_INPUT_KEY_KP_LESS = 197,
    AURORA_INPUT_KEY_KP_GREATER = 198,
    AURORA_INPUT_KEY_KP_AMPERSAND = 199,
    AURORA_INPUT_KEY_KP_DBLAMPERSAND = 200,
    AURORA_INPUT_KEY_KP_VERTICALBAR = 201,
    AURORA_INPUT_KEY_KP_DBLVERTICALBAR = 202,
    AURORA_INPUT_KEY_KP_COLON = 203,
    AURORA_INPUT_KEY_KP_HASH = 204,
    AURORA_INPUT_KEY_KP_SPACE = 205,
    AURORA_INPUT_KEY_KP_AT = 206,
    AURORA_INPUT_KEY_KP_EXCLAM = 207,
    AURORA_INPUT_KEY_KP_MEMSTORE = 208,
    AURORA_INPUT_KEY_KP_MEMRECALL = 209,
    AURORA_INPUT_KEY_KP_MEMCLEAR = 210,
    AURORA_INPUT_KEY_KP_MEMADD = 211,
    AURORA_INPUT_KEY_KP_MEMSUBTRACT = 212,
    AURORA_INPUT_KEY_KP_MEMMULTIPLY = 213,
    AURORA_INPUT_KEY_KP_MEMDIVIDE = 214,
    AURORA_INPUT_KEY_KP_PLUSMINUS = 215,
    AURORA_INPUT_KEY_KP_CLEAR = 216,
    AURORA_INPUT_KEY_KP_CLEARENTRY = 217,
    AURORA_INPUT_KEY_KP_BINARY = 218,
    AURORA_INPUT_KEY_KP_OCTAL = 219,
    AURORA_INPUT_KEY_KP_DECIMAL = 220,
    AURORA_INPUT_KEY_KP_HEXADECIMAL = 221,
    AURORA_INPUT_KEY_LCTRL = 224,
    AURORA_INPUT_KEY_LSHIFT = 225,
    AURORA_INPUT_KEY_LALT = 226,
    AURORA_INPUT_KEY_LGUI = 227,
    AURORA_INPUT_KEY_RCTRL = 228,
    AURORA_INPUT_KEY_RSHIFT = 229,
    AURORA_INPUT_KEY_RALT = 230,
    AURORA_INPUT_KEY_RGUI = 231,
    AURORA_INPUT_KEY_MODE = 257,
    AURORA_INPUT_KEY_AUDIONEXT = 258,
    AURORA_INPUT_KEY_AUDIOPREV = 259,
    AURORA_INPUT_KEY_AUDIOSTOP = 260,
    AURORA_INPUT_KEY_AUDIOPLAY = 261,
    AURORA_INPUT_KEY_AUDIOMUTE = 262,
    AURORA_INPUT_KEY_MEDIASELECT = 263,
    AURORA_INPUT_KEY_WWW = 264,
    AURORA_INPUT_KEY_MAIL = 265,
    AURORA_INPUT_KEY_CALCULATOR = 266,
    AURORA_INPUT_KEY_COMPUTER = 267,
    AURORA_INPUT_KEY_AC_SEARCH = 268,
    AURORA_INPUT_KEY_AC_HOME = 269,
    AURORA_INPUT_KEY_AC_BACK = 270,
    AURORA_INPUT_KEY_AC_FORWARD = 271,
    AURORA_INPUT_KEY_AC_STOP = 272,
    AURORA_INPUT_KEY_AC_REFRESH = 273,
    AURORA_INPUT_KEY_AC_BOOKMARKS = 274,
    AURORA_INPUT_KEY_BRIGHTNESSDOWN = 275,
    AURORA_INPUT_KEY_BRIGHTNESSUP = 276,
    AURORA_INPUT_KEY_DISPLAYSWITCH = 277,
    AURORA_INPUT_KEY_KBDILLUMTOGGLE = 278,
    AURORA_INPUT_KEY_KBDILLUMDOWN = 279,
    AURORA_INPUT_KEY_KBDILLUMUP = 280,
    AURORA_INPUT_KEY_EJECT = 281,
    AURORA_INPUT_KEY_SLEEP = 282,
    AURORA_INPUT_KEY_APP1 = 283,
    AURORA_INPUT_KEY_APP2 = 284,
    AURORA_INPUT_KEY_AUDIOREWIND = 285,
    AURORA_INPUT_KEY_AUDIOFASTFORWARD = 286
};