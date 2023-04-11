#include "gamestate.h"

/// Exit state
bool gameExit = false;

/// Drawing
bool redraw = true;

/// UI
bool UIChangeDelay = false;

int activeUI = UI_OVERWORLD;
int previousActiveUI = UI_OVERWORLD;

int activeSubUI = SUB_OVERWORLD_NONE;
int previousActiveSubUI = SUB_OVERWORLD_NONE;

int activeTab = TAB_OVERWORLD_NONE;
int previousActiveTab = TAB_OVERWORLD_NONE;

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
