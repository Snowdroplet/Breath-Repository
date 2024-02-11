#ifndef OVERWORLD_H_INCLUDED
#define OVERWORLD_H_INCLUDED

#include <iostream>
#include <string>
#include <cmath>

#include "allegrocustom.h"
#include <allegro5/allegro_primitives.h>

#include "colorindex.h"
#include "camera.h"

#include "gamestate.h"
#include "resource.h"

#include "placeindex.h"
#include "roadindex.h"

/// Forward declaration
class Place;
class Caravan;

/// Overworld Mouse


/// Camera
extern bool overworldCameraMousePanningDisabled;

extern bool overworldCameraLocked;
extern bool overworldCameraLockedOnPlace;
extern Place*overworldCameraPlace;
extern bool overworldCameraLockedOnCaravan;
extern Caravan* overworldCameraCaravan;

/**
extern float overworldCameraXPosition;
extern float overworldCameraYPosition;

extern bool overworldCameraApproachingDestination; // When camera is not locked, rather than warping the camera instantly to location, approach it
extern float overworldCameraXDestination;
extern float overworldCameraYDestination;

extern int overworldCameraXSensitivity;
extern int overworldCameraYSensitivity;

const int OVERWORLD_MIN_DRAW_X = 0 - Tile::WIDTH*2; // Save drawing resources by not drawing places and beings outside this boundary
const int OVERWORLD_MIN_DRAW_Y = 0 - Tile::HEIGHT*2;
const int OVERWORLD_MAX_DRAW_X = Display::WIDTH + Tile::WIDTH*2;
const int OVERWORLD_MAX_DRAW_Y = Display::HEIGHT + Tile::HEIGHT*2;
*/


/// Audio
enum enumOverworldParallelSampleParts
{
    OPS_COTTAGES = 0,
    OPS_MANOR = 1
};

extern int overworldParallelSampleInstanceCurrentPart;
//extern unsigned int overworldParallelSampleInstancePosition;

/// Draw grid underlay functions
void OverworldDrawGridUnderlay();
void OverworldDrawGridCameraCrosshair();
//void OverworldDrawGridMouseCrosshair(float mouseZoomedX, float mouseZoomedY);
void OverworldDrawGridText(float mouseTransformedX, float mouseTransformedY);

/// Overworld mouse functions
//void OverworldUpdateTransformedMouseCoords(float mX, float mY);

/// Camera control functions
///void OverworldApproachCameraDestination();
void OverworldLockCameraPlace(Place *whichPlace);
void OverworldLockCameraCaravan(Caravan *whichCaravan);
void OverworldUnlockCamera();
void OverworldUnlockCameraCaravan();
void OverworldUnlockCameraPlace();

/// Audio control functions
void OverworldAudioUpdate();
void OverworldBeginParallelBackgroundAudio();
void OverworldEndParallelBackgroundAudio();
void OverworldSwapParallelBackgroundAudioToPlace();
void OverworldSwapParallelBackgroundAudioToField();

#endif // OVERWORLD_H_INCLUDED
