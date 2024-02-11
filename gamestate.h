#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

#include <allegro5/allegro5.h>

#include "UI.h"

//extern float executionTime; // not literal, since the timer doesn't begin until after loading resources

/// Exit state
extern bool gameExit;

/// Drawing
const float FPS = 30.0;
extern bool redraw;

extern ALLEGRO_COLOR currentClearColor;

/**
extern ALLEGRO_TRANSFORM cameraNoTransform; // identity transform
extern ALLEGRO_TRANSFORM cameraZoom;
extern float cameraZoomScale;
extern float cameraZoomTranslateX;
extern float cameraZoomTranslateY;

extern float mouseTransformedX;
extern float mouseTransformedY;

const float CAMERA_SCALE_MIN = 1.0;
const float CAMERA_SCALE_MAX = 2.0;
*/

/// Events and event sources
extern ALLEGRO_TIMER *FPSTimer;
extern ALLEGRO_DISPLAY *display;

#endif // GAMESTATE_H_INCLUDED
