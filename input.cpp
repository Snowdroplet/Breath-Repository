#include "input.h"

bool keyInput[] =
{
    false, false, false,                        //ABC
    false, false, false,                        //DEF
    false, false, false,                        //GHI
    false, false, false,                        //JKL
    false, false, false,                        //MNO
    false, false, false,                        //PQR
    false, false, false,                        //STU
    false, false, false,                        //VWX
    false, false,                               //YZ

    false,                                      //Enter
    false,                                      //Space
    false, false, false,                        //numpad123
    false, false, false,                        //numpad456
    false, false, false,                        //numpad789
    false,                                      //numpad0
    false, false, false, false, false,          //01234
    false, false, false, false, false,          //56789
    false, false, false, false,                 //ULDR

    false                                       //Esc

};

bool mouseInput[] =
{
    false, // nothing

    false, // LEFT
    false, // RIGHT
    false  // MIDDLE
};

bool mousewheelInput[] =
{
    false, // Wheel up
    false  // Wheel down
};



float mouseDisplayX;
float mouseDisplayY;

unsigned keyESCDelay = 0;
unsigned mouseLeftDelay = 0;

void InputKeydown()
{
    switch(event.keyboard.keycode)
    {
        case ALLEGRO_KEY_A:
            keyInput[KEY_A] = true;
            break;
        case ALLEGRO_KEY_B:
            keyInput[KEY_B] = true;
            break;
        case ALLEGRO_KEY_C:
            keyInput[KEY_C] = true;
            break;
        case ALLEGRO_KEY_D:
            keyInput[KEY_D] = true;
            break;
        case ALLEGRO_KEY_E:
            keyInput[KEY_E] = true;
            break;
        case ALLEGRO_KEY_F:
            keyInput[KEY_F] = true;
            break;
        case ALLEGRO_KEY_G:
            keyInput[KEY_G] = true;
            break;
        case ALLEGRO_KEY_H:
            keyInput[KEY_H] = true;
            break;
        case ALLEGRO_KEY_I:
            keyInput[KEY_I] = true;
            break;
        case ALLEGRO_KEY_J:
            keyInput[KEY_J] = true;
            break;
        case ALLEGRO_KEY_K:
            keyInput[KEY_K] = true;
            break;
        case ALLEGRO_KEY_L:
            keyInput[KEY_L] = true;
            break;
        case ALLEGRO_KEY_M:
            keyInput[KEY_M] = true;
            break;
        case ALLEGRO_KEY_N:
            keyInput[KEY_N] = true;
            break;
        case ALLEGRO_KEY_O:
            keyInput[KEY_O] = true;
            break;
        case ALLEGRO_KEY_P:
            keyInput[KEY_P] = true;
            break;
        case ALLEGRO_KEY_Q:
            keyInput[KEY_Q] = true;
            break;
        case ALLEGRO_KEY_R:
            keyInput[KEY_R] = true;
            break;
        case ALLEGRO_KEY_S:
            keyInput[KEY_S] = true;
            break;
        case ALLEGRO_KEY_T:
            keyInput[KEY_T] = true;
            break;
        case ALLEGRO_KEY_U:
            keyInput[KEY_U] = true;
            break;
        case ALLEGRO_KEY_V:
            keyInput[KEY_V] = true;
            break;
        case ALLEGRO_KEY_W:
            keyInput[KEY_W] = true;
            break;
        case ALLEGRO_KEY_X:
            keyInput[KEY_X] = true;
            break;
        case ALLEGRO_KEY_Y:
            keyInput[KEY_Y] = true;
            break;
        case ALLEGRO_KEY_Z:
            keyInput[KEY_Z] = true;
            break;
        case ALLEGRO_KEY_SPACE:
            keyInput[KEY_SPACE] = true;
            break;
        case ALLEGRO_KEY_ENTER:
            keyInput[KEY_ENTER] = true;
            break;
        case ALLEGRO_KEY_PAD_1:
            keyInput[KEY_PAD_1] = true;
            break;
        case ALLEGRO_KEY_PAD_2:
            keyInput[KEY_PAD_2] = true;
            break;
        case ALLEGRO_KEY_PAD_3:
            keyInput[KEY_PAD_3] = true;
            break;
        case ALLEGRO_KEY_PAD_4:
            keyInput[KEY_PAD_4] = true;
            break;
        case ALLEGRO_KEY_PAD_5:
            keyInput[KEY_PAD_5] = true;
            break;
        case ALLEGRO_KEY_PAD_6:
            keyInput[KEY_PAD_6] = true;
            break;
        case ALLEGRO_KEY_PAD_7:
            keyInput[KEY_PAD_7] = true;
            break;
        case ALLEGRO_KEY_PAD_8:
            keyInput[KEY_PAD_8] = true;
            break;
        case ALLEGRO_KEY_PAD_9:
            keyInput[KEY_PAD_9] = true;
            break;
        case ALLEGRO_KEY_PAD_0:
            keyInput[KEY_PAD_0] = true;
            break;
        case ALLEGRO_KEY_1:
            keyInput[KEY_1] = true;
            break;
        case ALLEGRO_KEY_2:
            keyInput[KEY_2] = true;
            break;
        case ALLEGRO_KEY_3:
            keyInput[KEY_3] = true;
            break;
        case ALLEGRO_KEY_4:
            keyInput[KEY_4] = true;
            break;
        case ALLEGRO_KEY_5:
            keyInput[KEY_5] = true;
            break;
        case ALLEGRO_KEY_6:
            keyInput[KEY_6] = true;
            break;
        case ALLEGRO_KEY_7:
            keyInput[KEY_7] = true;
            break;
        case ALLEGRO_KEY_8:
            keyInput[KEY_8] = true;
            break;
        case ALLEGRO_KEY_9:
            keyInput[KEY_9] = true;
            break;
        case ALLEGRO_KEY_0:
            keyInput[KEY_0] = true;
            break;
        case ALLEGRO_KEY_UP:
            keyInput[KEY_UP] = true;
            break;
        case ALLEGRO_KEY_DOWN:
            keyInput[KEY_DOWN] = true;
            break;
        case ALLEGRO_KEY_LEFT:
            keyInput[KEY_LEFT] = true;
            break;
        case ALLEGRO_KEY_RIGHT:
            keyInput[KEY_RIGHT] = true;
            break;

        case ALLEGRO_KEY_ESCAPE:
            if(keyESCDelay == 0)
            {
                keyInput[KEY_ESC] = true;
                keyESCDelay = keyESCCooldown;
            }
            break;
    }
}

void InputKeyup()
{
    switch(event.keyboard.keycode)
    {
        case ALLEGRO_KEY_A:
            keyInput[KEY_A] = false;
            break;
        case ALLEGRO_KEY_B:
            keyInput[KEY_B] = false;
            break;
        case ALLEGRO_KEY_C:
            keyInput[KEY_C] = false;
            break;
        case ALLEGRO_KEY_D:
            keyInput[KEY_D] = false;
            break;
        case ALLEGRO_KEY_E:
            keyInput[KEY_E] = false;
            break;
        case ALLEGRO_KEY_F:
            keyInput[KEY_F] = false;
            break;
        case ALLEGRO_KEY_G:
            keyInput[KEY_G] = false;
            break;
        case ALLEGRO_KEY_H:
            keyInput[KEY_H] = false;
            break;
        case ALLEGRO_KEY_I:
            keyInput[KEY_I] = false;
            break;
        case ALLEGRO_KEY_J:
            keyInput[KEY_J] = false;
            break;
        case ALLEGRO_KEY_K:
            keyInput[KEY_K] = false;
            break;
        case ALLEGRO_KEY_L:
            keyInput[KEY_L] = false;
            break;
        case ALLEGRO_KEY_M:
            keyInput[KEY_M] = false;
            break;
        case ALLEGRO_KEY_N:
            keyInput[KEY_N] = false;
            break;
        case ALLEGRO_KEY_O:
            keyInput[KEY_O] = false;
            break;
        case ALLEGRO_KEY_P:
            keyInput[KEY_P] = false;
            break;
        case ALLEGRO_KEY_Q:
            keyInput[KEY_Q] = false;
            break;
        case ALLEGRO_KEY_R:
            keyInput[KEY_R] = false;
            break;
        case ALLEGRO_KEY_S:
            keyInput[KEY_S] = false;
            break;
        case ALLEGRO_KEY_T:
            keyInput[KEY_T] = false;
            break;
        case ALLEGRO_KEY_U:
            keyInput[KEY_U] = false;
            break;
        case ALLEGRO_KEY_V:
            keyInput[KEY_V] = false;
            break;
        case ALLEGRO_KEY_W:
            keyInput[KEY_W] = false;
            break;
        case ALLEGRO_KEY_X:
            keyInput[KEY_X] = false;
            break;
        case ALLEGRO_KEY_Y:
            keyInput[KEY_Y] = false;
            break;
        case ALLEGRO_KEY_Z:
            keyInput[KEY_Z] = false;
            break;
        case ALLEGRO_KEY_SPACE:
            keyInput[KEY_SPACE] = false;
            break;
        case ALLEGRO_KEY_PAD_1:
            keyInput[KEY_PAD_1] = false;
            break;
        case ALLEGRO_KEY_PAD_2:
            keyInput[KEY_PAD_2] = false;
            break;
        case ALLEGRO_KEY_PAD_3:
            keyInput[KEY_PAD_3] = false;
            break;
        case ALLEGRO_KEY_PAD_4:
            keyInput[KEY_PAD_4] = false;
            break;
        case ALLEGRO_KEY_PAD_5:
            keyInput[KEY_PAD_5] = false;
            break;
        case ALLEGRO_KEY_PAD_6:
            keyInput[KEY_PAD_6] = false;
            break;
        case ALLEGRO_KEY_PAD_7:
            keyInput[KEY_PAD_7] = false;
            break;
        case ALLEGRO_KEY_PAD_8:
            keyInput[KEY_PAD_8] = false;
            break;
        case ALLEGRO_KEY_PAD_9:
            keyInput[KEY_PAD_9] = false;
            break;
        case ALLEGRO_KEY_PAD_0:
            keyInput[KEY_PAD_0] = false;
            break;
        case ALLEGRO_KEY_1:
            keyInput[KEY_1] = false;
            break;
        case ALLEGRO_KEY_2:
            keyInput[KEY_2] = false;
            break;
        case ALLEGRO_KEY_3:
            keyInput[KEY_3] = false;
            break;
        case ALLEGRO_KEY_4:
            keyInput[KEY_4] = false;
            break;
        case ALLEGRO_KEY_5:
            keyInput[KEY_5] = false;
            break;
        case ALLEGRO_KEY_6:
            keyInput[KEY_6] = false;
            break;
        case ALLEGRO_KEY_7:
            keyInput[KEY_7] = false;
            break;
        case ALLEGRO_KEY_8:
            keyInput[KEY_8] = false;
            break;
        case ALLEGRO_KEY_9:
            keyInput[KEY_9] = false;
            break;
        case ALLEGRO_KEY_0:
            keyInput[KEY_0] = false;
            break;
        case ALLEGRO_KEY_UP:
            keyInput[KEY_UP] = false;
            break;
        case ALLEGRO_KEY_DOWN:
            keyInput[KEY_DOWN] = false;
            break;
        case ALLEGRO_KEY_LEFT:
            keyInput[KEY_LEFT] = false;
            break;
        case ALLEGRO_KEY_RIGHT:
            keyInput[KEY_RIGHT] = false;
            break;
        case ALLEGRO_KEY_ENTER:
            keyInput[KEY_ENTER] = false;
            break;

        case ALLEGRO_KEY_ESCAPE:
            keyInput[KEY_ESC] = false;
            break;
    }
}

void InputMouseXY()
{
    mouseDisplayX = event.mouse.x;
    mouseDisplayY = event.mouse.y;
}

void InputMouseDown()
{
    switch(event.mouse.button)
    {
    case MOUSE_LEFT:
        if(mouseLeftDelay == 0)
        {
            mouseInput[MOUSE_LEFT] = true;
            mouseLeftDelay = mouseLeftCooldown;
        }
        break;
    case MOUSE_RIGHT:
        mouseInput[MOUSE_RIGHT] = true;
        break;
    case MOUSE_MIDDLE:
        mouseInput[MOUSE_MIDDLE] = true;
        break;
    }
}

void InputMouseUp()
{
    switch(event.mouse.button)
    {
    case MOUSE_LEFT:
        mouseInput[MOUSE_LEFT] = false;
        break;
    case MOUSE_RIGHT:
        mouseInput[MOUSE_RIGHT] = false;
        break;
    case MOUSE_MIDDLE:
        mouseInput[MOUSE_MIDDLE] = false;
        break;
    }
}

void InputMousewheel()
{
    if(event.mouse.z > 0)
        mousewheelInput[MOUSEWHEEL_UP] = true;
    else
        mousewheelInput[MOUSEWHEEL_UP] = false;

    if(event.mouse.z < 0)
        mousewheelInput[MOUSEWHEEL_DOWN] = true;
    else
        mousewheelInput[MOUSEWHEEL_DOWN] = false;
}

void InputCooldown()
{
    if(keyESCDelay > 0)
    {
        keyESCDelay --;
    }
    if(mouseLeftDelay > 0)
    {
        mouseLeftDelay --;
    }
}
