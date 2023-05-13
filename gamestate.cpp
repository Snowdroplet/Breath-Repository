#include "gamestate.h"

/// Exit state
bool gameExit = false;

/// Drawing
bool redraw = true;

/*
/// Location
bool playerAtPlace = true;
int playerLocation = PL_ERICENNES;

/// Barter Control
bool barterKeyInputNPCSide = false;
int barterItemQuantity = 1;
int barterItemType;
*/


/// Allegro
ALLEGRO_TIMER *FPSTimer;
ALLEGRO_EVENT_QUEUE *eventQueue;
ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT event;
