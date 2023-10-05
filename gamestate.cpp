#include "gamestate.h"

/// Exit state
bool gameExit = false;

/// Drawing
bool redraw = true;

ALLEGRO_TRANSFORM cameraZoom;
float cameraZoomScale = 1.0;
float cameraZoomTranslateX = 0;
float cameraZoomTranslateY = 0;

/// Events and event sources
ALLEGRO_TIMER *FPSTimer;
ALLEGRO_EVENT_QUEUE *eventQueue;
ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT event;
