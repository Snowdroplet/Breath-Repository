#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

#include <allegro5/allegro5.h>

#include "UI.h"

/// Exit state
extern bool gameExit;

/// Drawing
const int SCREEN_W = 1280;
const int SCREEN_H = 800;

const int TILE_W = 32; // Standard width of sprites meant to be arranged in grids.
const int TILE_H = 32;

const float FPS = 30.0;
extern bool redraw;

extern ALLEGRO_COLOR currentClearColor;


/// UI
extern bool UIChangeDelay;

extern int activeUI;
extern int previousActiveUI;

extern int activeSubUI;
extern int previousActiveSubUI;

extern int activeTab;
extern int previousActiveTab;



/*
extern bool playerAtPlace;
extern int playerLocation;

/// Barter Control
extern bool barterKeyInputNPCSide;
extern int barterItemQuantity;
extern int barterItemType;
*/

/// Allegro
extern ALLEGRO_TIMER *FPSTimer;
extern ALLEGRO_EVENT_QUEUE *eventQueue;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_EVENT event;


#endif // GAMESTATE_H_INCLUDED
