#include "gamestate.h"

//float executionTime = 0;

/// Exit state
bool gameExit = false;

/// Drawing
bool redraw = true;

ALLEGRO_TRANSFORM cameraZoom;
float cameraZoomScale = 1.0;
float cameraZoomTranslateX = 0; // At 1.0 scale
float cameraZoomTranslateY = 0;

float mouseZoomTranslateX = 0;  // At 1.0 scale
float mouseZoomTranslateY = 0;

/// Events and event sources
ALLEGRO_TIMER *FPSTimer;
ALLEGRO_EVENT_QUEUE *eventQueue;
ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT event;
