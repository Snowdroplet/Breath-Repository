#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include "gamestate.h"

enum enumInputKeys // use KEYMODs instead of putting alt, Lshift, Rshift, Lctrl, Rctrl, ect. here
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

    KEY_SPACE,
    KEY_ENTER,
    KEY_PAD_1, KEY_PAD_2, KEY_PAD_3,
    KEY_PAD_4, KEY_PAD_5, KEY_PAD_6,
    KEY_PAD_7, KEY_PAD_8, KEY_PAD_9,
    KEY_PAD_0,
    KEY_0, KEY_1, KEY_2, KEY_3, KEY_4,
    KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,
    KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT,


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

extern float mouseX;
extern float mouseY;

extern bool keyInput[];
extern bool mouseInput[];
extern bool mousewheelInput[];

void InputKeydown();
void InputKeyup();
void InputMouseXY();
void InputMouseDown();
void InputMouseUp();
void InputMousewheel();

#endif // INPUT_H_INCLUDED
