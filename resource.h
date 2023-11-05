#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "UI.h"
#include "beingindex.h"

const unsigned SPRITE_TILE_W = 32;
const unsigned SPRITE_TILE_H = 32;

const std::map<unsigned,unsigned>resourceBeingNumSpriteVariants
{
    // In total. Not counting from zero.
    {ANCESTRY_VERIT, 4},
    {ANCESTRY_YETI, 2},
    {ANCESTRY_MAKHI, 3},
    {ANCESTRY_BEYU, 2},
    {ANCESTRY_MESERA, 2},
    {ANCESTRY_ORDON, 2},
    {ANCESTRY_HAPHAE, 2}
};
const unsigned resourceBeingNumWalkFrames = 2;

extern ALLEGRO_FONT *builtin8;
//extern ALLEGRO_BITMAP *builtin16Tga;
//extern ALLEGRO_FONT *builtin16;
//extern ALLEGRO_FONT *spaceMono16;

extern ALLEGRO_BITMAP *overworldPlacePng;

extern ALLEGRO_BITMAP *beingsPng;
extern ALLEGRO_BITMAP *beingPng[NUM_ANCESTRIES];

extern ALLEGRO_BITMAP *expertiseIconPng;

extern ALLEGRO_BITMAP *miniCargoPng;
extern ALLEGRO_BITMAP *cargoPng;

extern ALLEGRO_BITMAP *redArrowPng;
extern ALLEGRO_BITMAP *redTransparentXPng;

/*
enum enumBackgroundTracks
{
    TRACK_MACLEOD_COTTAGES = 0,
    TRACK_MACLEOD_MANOR    = 1
};
*/

extern ALLEGRO_SAMPLE *cottagesMacLeodMp3;
extern ALLEGRO_SAMPLE *manorMacLeodMp3;

extern ALLEGRO_SAMPLE_INSTANCE *cottagesSampleInstance;
extern ALLEGRO_SAMPLE_INSTANCE *manorSampleInstance;

//extern std::map<int, *ALLEGRO_SAMPLE_INSTANCE>allegroSampleInstances;

void LoadFontResources();
void LoadImageResources();
void LoadAudioResources();

void UnloadFontResources();
void UnloadImageResources();
void UnloadAudioResources();

#endif // RESOURCE_H_INCLUDED
