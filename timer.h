#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <allegro5/allegro5.h>

struct Timer
{
    static constexpr float FPS = 30.0;
    static ALLEGRO_TIMER *FPSTimer;
};

#endif // TIMER_H_INCLUD ED
