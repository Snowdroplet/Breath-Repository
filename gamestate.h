#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

#include <allegro5/allegro5.h>

#include "UI.h"

/// Exit state
extern bool gameExit;

/// Drawing
const float SCREEN_W = 1280;
const float SCREEN_H = 800;

const float TILE_W = 32; // Standard width of sprites meant to be arranged in grids.
const float TILE_H = 32;

const float MINI_TILE_W = 16; // Width of half-sized versions of sprites meant to be arranged in grids.
const float MINI_TILE_H = 16;

const float FPS = 30.0;
extern bool redraw;

extern ALLEGRO_COLOR currentClearColor;

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
