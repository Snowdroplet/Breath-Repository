#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

#include "UI.h"
#include "beingindex.h"

const unsigned SPRITE_TILE_W = 32;
const unsigned SPRITE_TILE_H = 32;

const std::map<unsigned,unsigned>resourceBeingNumSpriteVariants
{
    // In total. Not counting from zero.
    {ANCESTRY_VERIT, 2},
    {ANCESTRY_YETI, 2},
    {ANCESTRY_MAKHI, 2},
    {ANCESTRY_BEYU, 2},
    {ANCESTRY_MESERA, 2},
    {ANCESTRY_ORDON, 2},
    {ANCESTRY_HAPHAE, 2}
};
const unsigned resourceBeingNumWalkFrames = 2;

extern ALLEGRO_FONT *builtin;

extern ALLEGRO_BITMAP *overworldPlacePng;

extern ALLEGRO_BITMAP *beingsPng;
extern ALLEGRO_BITMAP *beingPng[NUM_ANCESTRIES];

extern ALLEGRO_BITMAP *expertiseIconPng;

extern ALLEGRO_BITMAP *miniCargoPng;
extern ALLEGRO_BITMAP *cargoPng;

extern ALLEGRO_BITMAP *redArrowPng;
extern ALLEGRO_BITMAP *redTransparentXPng;

void LoadResources();
void UnloadResources();

#endif // RESOURCE_H_INCLUDED
