#ifndef OVERWORLD_H_INCLUDED
#define OVERWORLD_H_INCLUDED

#include <string>
#include <cmath>

#include "allegrocustom.h"
#include <allegro5/allegro_primitives.h>

#include "gamestate.h"
#include "resource.h"

#include "placeindex.h"
#include "roadindex.h"

class Place;
class Caravan;

extern bool overworldCameraLocked;
extern bool overworldCameraLockedOnPlace;
extern Place*overworldCameraPlace;
extern bool overworldCameraLockedOnCaravan;
extern Caravan* overworldCameraCaravan;

extern float overworldCameraXPosition;
extern float overworldCameraYPosition;

extern int overworldCameraXSensitivity;
extern int overworldCameraYSensitivity;

const float OVERWORLD_W = 10240;
const float OVERWORLD_H = 10240;

const int OVERWORLD_MIN_DRAW_X = 0 - TILE_W*2;
const int OVERWORLD_MIN_DRAW_Y = 0 - TILE_H*2;
const int OVERWORLD_MAX_DRAW_X = SCREEN_W + TILE_W*2;
const int OVERWORLD_MAX_DRAW_Y = SCREEN_H + TILE_H*2;

void OverworldDrawGridUnderlay();

void OverworldLockCameraPlace(Place *whichPlace);
void OverworldLockCameraCaravan(Caravan *whichCaravan);
void OverworldUnlockCamera();
void OverworldUnlockCameraCaravan();
void OverworldUnlockCameraPlace();

#endif // OVERWORLD_H_INCLUDED
