#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

#include <allegro5/allegro5.h>

struct Event
{
    static ALLEGRO_EVENT_QUEUE* eventQueue;
    static ALLEGRO_EVENT event;

    static bool keyInput[];
    static int keyHoldTicks[];
    static bool mouseInput[];
    static bool mousewheelInput[];
    static int mouseButtonHoldTicks[];

    static float mouseDisplayX;
    static float mouseDisplayY;

    static void InputKeydown();
    static void InputKeyup();

    static void InputKeyHold();

    static void InputMouseXY();
    static void InputMouseDown();
    static void InputMouseUp();
    static void InputMousewheel();

    static void InputMouseButtonHold();

    enum enumInputKeys
    {
        KEY_A = 0,  KEY_B = 1,  KEY_C = 2,
        KEY_D = 3,  KEY_E = 4,  KEY_F = 5,
        KEY_G = 6,  KEY_H = 7,  KEY_I = 8,
        KEY_J = 9,  KEY_K = 10, KEY_L = 11,
        KEY_M = 12, KEY_N = 13, KEY_O = 14,
        KEY_P = 15, KEY_Q = 16, KEY_R = 17,
        KEY_S = 18, KEY_T = 19, KEY_U = 20,
        KEY_V = 21, KEY_W = 22, KEY_X = 23,
        KEY_Y = 24, KEY_Z = 25,

        KEY_PAD_1, KEY_PAD_2, KEY_PAD_3,
        KEY_PAD_4, KEY_PAD_5, KEY_PAD_6,
        KEY_PAD_7, KEY_PAD_8, KEY_PAD_9,
        KEY_PAD_0,
        KEY_0, KEY_1, KEY_2, KEY_3, KEY_4,
        KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,
        KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT,
        KEY_SPACE,
        KEY_ENTER,
        KEY_LSHIFT, KEY_RSHIFT,

        KEY_ESC

    };

    enum enumInputMouseButtons
    {
        MOUSE_NOTHING = 0, // Allegro mouse buttons start counting from 1 for some reason, so this really is just filler.

        MOUSE_LEFT = 1,
        MOUSE_RIGHT = 2,
        MOUSE_MIDDLE = 3
    };

    enum enumInputMouseWheel
    {
        MOUSEWHEEL_UP = 0,
        MOUSEWHEEL_DOWN = 1
    };

};

#endif // EVENT_H_INCLUDED
