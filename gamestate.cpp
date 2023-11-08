#include "gamestate.h"

//float executionTime = 0;

/// Exit state
bool gameExit = false;

/// Drawing
bool redraw = true;

ALLEGRO_TRANSFORM cameraNoTransform;
ALLEGRO_TRANSFORM cameraZoom;
float cameraZoomScale = 1.0;
float cameraZoomTranslateX = 0; // At 1.0 scale
float cameraZoomTranslateY = 0;

float mouseTransformedX;
float mouseTransformedY;

/// Events and event sources
ALLEGRO_TIMER *FPSTimer;
ALLEGRO_EVENT_QUEUE *eventQueue;
ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT event;
