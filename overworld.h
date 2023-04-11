#ifndef OVERWORLD_H_INCLUDED
#define OVERWORLD_H_INCLUDED

#include <string>
#include <cmath>

#include "allegrocustom.h"
#include <allegro5/allegro_primitives.h>

#include "gamestate.h"
#include "resource.h"

#include "placeconsts.h"
#include "roadconsts.h"

extern int overworldCameraXPosition;
extern int overworldCameraYPosition;

extern int overworldCameraXSensitivity;
extern int overworldCameraYSensitivity;

const int OVERWORLD_W = 1280;
const int OVERWORLD_H = 1280;

void DrawOverworldDebugOverlay();

#endif // OVERWORLD_H_INCLUDED
