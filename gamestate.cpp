#include "gamestate.h"

//float executionTime = 0;

/// Exit state
bool gameExit = false;

/// Drawing
bool redraw = true;



/// Events and event sources
ALLEGRO_TIMER *FPSTimer;
ALLEGRO_DISPLAY *display;
