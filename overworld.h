#ifndef OVERWORLD_H_INCLUDED
#define OVERWORLD_H_INCLUDED

#include <string>
#include <cmath>

#include "allegrocustom.h"
#include <allegro5/allegro_primitives.h>

#include "colorindex.h"

#include "gamestate.h"
#include "resource.h"

#include "placeindex.h"
#include "roadindex.h"

/// Forward declaration
class Place;
class Caravan;

/// Camera
extern bool overworldCameraMousePanningDisabled;

extern bool overworldCameraLocked;
extern bool overworldCameraLockedOnPlace;
extern Place*overworldCameraPlace;
extern bool overworldCameraLockedOnCaravan;
extern Caravan* overworldCameraCaravan;

extern float overworldCameraXPosition;
extern float overworldCameraYPosition;

extern bool overworldCameraApproachingDestination; // When camera is not locked, rather than warping the camera instantly to location, approach it
extern float overworldCameraXDestination;
extern float overworldCameraYDestination;

extern int overworldCameraXSensitivity;
extern int overworldCameraYSensitivity;

const int OVERWORLD_MIN_DRAW_X = 0 - TILE_W*2; // Save drawing resources by not drawing places and beings outside this boundary
const int OVERWORLD_MIN_DRAW_Y = 0 - TILE_H*2;
const int OVERWORLD_MAX_DRAW_X = SCREEN_W + TILE_W*2;
const int OVERWORLD_MAX_DRAW_Y = SCREEN_H + TILE_H*2;


/// Audio
extern unsigned int parallelSampleInstancesPosition;

/// Draw grid underlay functions
void OverworldDrawGridUnderlay();
void OverworldDrawGridCameraCrosshair();
void OverworldDrawGridMouseCrosshair(float mouseX, float mouseY);
void OverworldDrawGridText(float mouseX, float mouseY);

/// Camera control functions
void OverworldApproachCameraDestination();
void OverworldLockCameraPlace(Place *whichPlace);
void OverworldLockCameraCaravan(Caravan *whichCaravan);
void OverworldUnlockCamera();
void OverworldUnlockCameraCaravan();
void OverworldUnlockCameraPlace();

/// Audio control functions
void OverworldSwapParallelBackgroundAudioToPlace();
void OverworldSwapParallelBackgroundAudioToField();

#endif // OVERWORLD_H_INCLUDED
