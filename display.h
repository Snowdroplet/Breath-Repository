#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include <allegro5/allegro5.h>

struct Display
{
    static ALLEGRO_DISPLAY *display;

    static constexpr float WIDTH = 1280;
    static constexpr float HEIGHT = 800;
};

#endif // DISPLAY_H_INCLUDED
