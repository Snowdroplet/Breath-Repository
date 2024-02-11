#include "event.h"

ALLEGRO_EVENT_QUEUE* Event::eventQueue;
ALLEGRO_EVENT Event::event;

///
///ALLEGRO_EVENT_QUEUE* Event::eventQueueExperimental;
///ALLEGRO_EVENT Event::eventExperimental;
///

bool Event::keyInput[] =
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
    false, false,                               //LSHIFT RSHIFT

    false                                      //Esc

};

int Event::keyHoldTicks[] =
{
    0, 0, 0,                        //ABC
    0, 0, 0,                        //DEF
    0, 0, 0,                        //GHI
    0, 0, 0,                        //JKL
    0, 0, 0,                        //MNO
    0, 0, 0,                        //PQR
    0, 0, 0,                        //STU
    0, 0, 0,                        //VWX
    0, 0,                           //YZ

    0, 0, 0,                        //numpad123
    0, 0, 0,                        //numpad456
    0, 0, 0,                        //numpad789
    0,                              //numpad0
    0, 0, 0, 0, 0,                  //01234
    0, 0, 0, 0, 0,                  //56789
    0, 0, 0, 0,                     //ULDR
    0,                              //Enter
    0,                              //Space
    0,0,                            //LSHIFT RSHIFT

    0,                              //Esc
};

bool Event::mouseInput[] =
{
    false, // nothing

    false, // LEFT
    false, // RIGHT
    false  // MIDDLE
};

bool Event::mousewheelInput[] =
{
    false, // Wheel up
    false  // Wheel down
};

int Event::mouseButtonHoldTicks[] =
{
    0, // Nothing (due to Allegro buttons counting from 1 instead of 0

    0, // LEFT
    0, // RIGHT
    0  // MIDDLE
};

float Event::mouseDisplayX;
float Event::mouseDisplayY;

void Event::InputKeydown()
{
    switch(Event::event.keyboard.keycode)
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
    case ALLEGRO_KEY_SPACE:
        keyInput[KEY_SPACE] = true;
        break;
    case ALLEGRO_KEY_ENTER:
        keyInput[KEY_ENTER] = true;
        break;
    case ALLEGRO_KEY_LSHIFT:
        keyInput[KEY_LSHIFT] = true;
        break;
    case ALLEGRO_KEY_RSHIFT:
        keyInput[KEY_RSHIFT] = true;
        break;
    case ALLEGRO_KEY_ESCAPE:
        keyInput[KEY_ESC] = true;
        break;
    }
}

/*
void Event::InputKeydownModifiers()
{
}
*/

void Event::InputKeyup()
{
    switch(Event::event.keyboard.keycode)
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
        keyHoldTicks[KEY_E] = 0;
        break;
    case ALLEGRO_KEY_F:
        keyInput[KEY_F] = false;
        keyHoldTicks[KEY_F] = 0;
        break;
    case ALLEGRO_KEY_G:
        keyInput[KEY_G] = false;
        keyHoldTicks[KEY_G] = 0;
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
        keyHoldTicks[KEY_Q] = 0;
        break;
    case ALLEGRO_KEY_R:
        keyInput[KEY_R] = false;
        break;
    case ALLEGRO_KEY_S:
        keyInput[KEY_S] = false;
        break;
    case ALLEGRO_KEY_T:
        keyInput[KEY_T] = false;
        keyHoldTicks[KEY_T] = 0;
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
    case ALLEGRO_KEY_PAD_1:
        keyInput[KEY_PAD_1] = false;
        keyHoldTicks[KEY_PAD_1] = 0;
        break;
    case ALLEGRO_KEY_PAD_2:
        keyInput[KEY_PAD_2] = false;
        keyHoldTicks[KEY_PAD_2] = 0;
        break;
    case ALLEGRO_KEY_PAD_3:
        keyInput[KEY_PAD_3] = false;
        keyHoldTicks[KEY_PAD_3] = 0;
        break;
    case ALLEGRO_KEY_PAD_4:
        keyInput[KEY_PAD_4] = false;
        keyHoldTicks[KEY_PAD_4] = 0;
        break;
    case ALLEGRO_KEY_PAD_5:
        keyInput[KEY_PAD_5] = false;
        keyHoldTicks[KEY_PAD_5] = 0;
        break;
    case ALLEGRO_KEY_PAD_6:
        keyInput[KEY_PAD_6] = false;
        keyHoldTicks[KEY_PAD_6] = 0;
        break;
    case ALLEGRO_KEY_PAD_7:
        keyInput[KEY_PAD_7] = false;
        keyHoldTicks[KEY_PAD_7] = 0;
        break;
    case ALLEGRO_KEY_PAD_8:
        keyInput[KEY_PAD_8] = false;
        keyHoldTicks[KEY_PAD_8] = 0;
        break;
    case ALLEGRO_KEY_PAD_9:
        keyInput[KEY_PAD_9] = false;
        keyHoldTicks[KEY_PAD_9] = 0;
        break;
    case ALLEGRO_KEY_PAD_0:
        keyInput[KEY_PAD_0] = false;
        break;
    case ALLEGRO_KEY_1:
        keyInput[KEY_1] = false;
        keyHoldTicks[KEY_1] = 0;
        break;
    case ALLEGRO_KEY_2:
        keyInput[KEY_2] = false;
        keyHoldTicks[KEY_2] = 0;
        break;
    case ALLEGRO_KEY_3:
        keyInput[KEY_3] = false;
        keyHoldTicks[KEY_3] = 0;
        break;
    case ALLEGRO_KEY_4:
        keyInput[KEY_4] = false;
        keyHoldTicks[KEY_4] = 0;
        break;
    case ALLEGRO_KEY_5:
        keyInput[KEY_5] = false;
        break;
    case ALLEGRO_KEY_6:
        keyInput[KEY_6] = false;
        break;
    case ALLEGRO_KEY_7:
        keyInput[KEY_7] = false;
        keyHoldTicks[KEY_7] = 0;
        break;
    case ALLEGRO_KEY_8:
        keyInput[KEY_8] = false;
        keyHoldTicks[KEY_8] = 0;
        break;
    case ALLEGRO_KEY_9:
        keyInput[KEY_9] = false;
        keyHoldTicks[KEY_9] = 0;
        break;
    case ALLEGRO_KEY_0:
        keyInput[KEY_0] = false;
        keyHoldTicks[KEY_0] = 0;
        break;
    case ALLEGRO_KEY_UP:
        keyInput[KEY_UP] = false;
        keyHoldTicks[KEY_UP] = 0;
        break;
    case ALLEGRO_KEY_DOWN:
        keyInput[KEY_DOWN] = false;
        keyHoldTicks[KEY_DOWN] = 0;
        break;
    case ALLEGRO_KEY_LEFT:
        keyInput[KEY_LEFT] = false;
        keyHoldTicks[KEY_LEFT] = 0;
        break;
    case ALLEGRO_KEY_RIGHT:
        keyInput[KEY_RIGHT] = false;
        keyHoldTicks[KEY_RIGHT] = 0;
        break;
    case ALLEGRO_KEY_SPACE:
        keyInput[KEY_SPACE] = false;
        keyHoldTicks[KEY_SPACE] = 0;
        break;
    case ALLEGRO_KEY_ENTER:
        keyInput[KEY_ENTER] = false;
        break;
    case ALLEGRO_KEY_LSHIFT:
        keyInput[KEY_LSHIFT] = false;
        keyHoldTicks[KEY_LSHIFT] = 0;
        break;
    case ALLEGRO_KEY_RSHIFT:
        keyInput[KEY_RSHIFT] = false;
        keyHoldTicks[KEY_RSHIFT] = 0;
        break;

    case ALLEGRO_KEY_ESCAPE:
        keyInput[KEY_ESC] = false;
        keyInput[KEY_ESC] = 0;
        break;
    }
}

void Event::InputKeyHold()
{
    if(keyInput[KEY_E])
        keyHoldTicks[KEY_E] ++;
    if(keyInput[KEY_F])
        keyHoldTicks[KEY_F] ++;
    if(keyInput[KEY_G])
        keyHoldTicks[KEY_G] ++;
    if(keyInput[KEY_Q])
        keyHoldTicks[KEY_Q] ++;
    if(keyInput[KEY_T])
        keyHoldTicks[KEY_T] ++;

    if(keyInput[KEY_PAD_1])
        keyHoldTicks[KEY_PAD_1] ++;
    if(keyInput[KEY_PAD_2])
        keyHoldTicks[KEY_PAD_2] ++;
    if(keyInput[KEY_PAD_3])
        keyHoldTicks[KEY_PAD_3] ++;
    if(keyInput[KEY_PAD_4])
        keyHoldTicks[KEY_PAD_4] ++;
    if(keyInput[KEY_PAD_5])
        keyHoldTicks[KEY_PAD_5] ++;
    if(keyInput[KEY_PAD_6])
        keyHoldTicks[KEY_PAD_6] ++;
    if(keyInput[KEY_PAD_7])
        keyHoldTicks[KEY_PAD_7] ++;
    if(keyInput[KEY_PAD_8])
        keyHoldTicks[KEY_PAD_8] ++;
    if(keyInput[KEY_PAD_9])
        keyHoldTicks[KEY_PAD_9] ++;

    if(keyInput[KEY_1])
        keyHoldTicks[KEY_1] ++;
    if(keyInput[KEY_2])
        keyHoldTicks[KEY_2] ++;
    if(keyInput[KEY_3])
        keyHoldTicks[KEY_3] ++;
    if(keyInput[KEY_4])
        keyHoldTicks[KEY_4] ++;

    if(keyInput[KEY_7])
        keyHoldTicks[KEY_7] ++;
    if(keyInput[KEY_8])
        keyHoldTicks[KEY_8] ++;
    if(keyInput[KEY_9])
        keyHoldTicks[KEY_9] ++;
    if(keyInput[KEY_0])
        keyHoldTicks[KEY_0] ++;

    if(keyInput[KEY_UP])
        keyHoldTicks[KEY_UP] ++;
    if(keyInput[KEY_DOWN])
        keyHoldTicks[KEY_DOWN] ++;
    if(keyInput[KEY_LEFT])
        keyHoldTicks[KEY_LEFT] ++;
    if(keyInput[KEY_RIGHT])
        keyHoldTicks[KEY_RIGHT] ++;

    if(keyInput[KEY_LSHIFT])
        keyHoldTicks[KEY_LSHIFT] ++;
    if(keyInput[KEY_RSHIFT])
        keyHoldTicks[KEY_RSHIFT] ++;

    if(keyInput[KEY_SPACE])
        keyHoldTicks[KEY_SPACE] ++;

    if(keyInput[KEY_ESC])
        keyHoldTicks[KEY_ESC] ++;
}

void Event::InputMouseXY()
{
    mouseDisplayX = Event::event.mouse.x;
    mouseDisplayY = Event::event.mouse.y;
}

void Event::InputMouseDown()
{
    switch(Event::event.mouse.button)
    {
    case MOUSE_LEFT:
        mouseInput[MOUSE_LEFT] = true;
        break;
    case MOUSE_RIGHT:
        mouseInput[MOUSE_RIGHT] = true;
        break;
    case MOUSE_MIDDLE:
        mouseInput[MOUSE_MIDDLE] = true;
        break;
    }
}

void Event::InputMouseUp()
{
    switch(Event::event.mouse.button)
    {
    case MOUSE_LEFT:
        mouseInput[MOUSE_LEFT] = false;
        mouseButtonHoldTicks[MOUSE_LEFT] = 0;
        break;
    case MOUSE_RIGHT:
        mouseInput[MOUSE_RIGHT] = false;
        mouseButtonHoldTicks[MOUSE_RIGHT] = 0;
        break;
    case MOUSE_MIDDLE:
        mouseInput[MOUSE_MIDDLE] = false;
        mouseButtonHoldTicks[MOUSE_MIDDLE] = 0;
        break;
    }
}

void Event::InputMousewheel()
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

void Event::InputMouseButtonHold()
{
    if(mouseInput[MOUSE_LEFT])
        mouseButtonHoldTicks[MOUSE_LEFT] ++;
    if(mouseInput[MOUSE_RIGHT])
        mouseButtonHoldTicks[MOUSE_RIGHT] ++;
    if(mouseInput[MOUSE_MIDDLE])
        mouseButtonHoldTicks[MOUSE_MIDDLE] ++;
}

/*

void Event::InputCooldown()
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

*/
