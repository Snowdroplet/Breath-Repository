#include "resource.h"

ALLEGRO_FONT *builtin;

ALLEGRO_BITMAP *overworldPlacePng;

ALLEGRO_BITMAP *beingsPng;
ALLEGRO_BITMAP *beingPng[NUM_ANCESTRIES];

ALLEGRO_BITMAP *expertiseIconPng;

ALLEGRO_BITMAP *miniCargoPng;
ALLEGRO_BITMAP *cargoPng;

ALLEGRO_BITMAP *redArrowPng;
ALLEGRO_BITMAP *redTransparentXPng;

void LoadResources()
{
    builtin = al_create_builtin_font();

    overworldPlacePng = al_load_bitmap("placeholderOverworldPlace.png");

    beingsPng = al_load_bitmap("placeholderBeings.png");

    for(unsigned i = ANCESTRY_MARKER_FIRST; i <= ANCESTRY_MARKER_LAST; i++)
    {
        beingPng[i] = al_create_sub_bitmap(beingsPng,
                                           0,
                                           i*SPRITE_TILE_H,
                                           SPRITE_TILE_W * resourceBeingNumWalkFrames * resourceBeingNumSpriteVariants.at(i),
                                           SPRITE_TILE_H);
    }

    expertiseIconPng = al_load_bitmap("placeholderExpertiseIcon.png");

    miniCargoPng = al_load_bitmap("placeholderMiniCargo.png");
    cargoPng = al_load_bitmap("placeholderCargo.png");

    redArrowPng = al_load_bitmap("placeholderRedArrow.png");
    redTransparentXPng = al_load_bitmap("placeholderRedTransparentX.png");
}

void UnloadResources()
{
    al_destroy_font(builtin);

    al_destroy_bitmap(overworldPlacePng);

    for(int i = 0; i <= ANCESTRY_MARKER_LAST; i++)
        al_destroy_bitmap(beingPng[i]);

    al_destroy_bitmap(beingsPng);

    al_destroy_bitmap(expertiseIconPng);

    al_destroy_bitmap(miniCargoPng);
    al_destroy_bitmap(cargoPng);

    al_destroy_bitmap(redArrowPng);
    al_destroy_bitmap(redTransparentXPng);

}
