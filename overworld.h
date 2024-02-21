#ifndef OVERWORLD_H_INCLUDED
#define OVERWORLD_H_INCLUDED

#include <iostream>
#include <string>
#include <cmath>

#include "allegrocustom.h"
#include <allegro5/allegro_primitives.h>


//#include "bubbleview.h"
#include "resource.h"

//#include "placeindex.h"
//#include "roadindex.h"

/// Audio
enum enumOverworldParallelSampleParts
{
    OPS_COTTAGES = 0,
    OPS_MANOR = 1
};

extern int overworldParallelSampleInstanceCurrentPart;

/// Draw grid underlay functions

/// Overworld mouse functions
//void OverworldUpdateTransformedMouseCoords(float mX, float mY);

/// Audio control functions
void OverworldAudioUpdate();
void OverworldBeginParallelBackgroundAudio();
void OverworldEndParallelBackgroundAudio();
void OverworldSwapParallelBackgroundAudioToPlace();
void OverworldSwapParallelBackgroundAudioToField();

#endif // OVERWORLD_H_INCLUDED
