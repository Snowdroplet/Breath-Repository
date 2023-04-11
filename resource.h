#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

#include "UI.h"
#include "beingconsts.h"

/*
const int PNG_INACTIVE = 0;
const int PNG_ACTIVE = 1;
*/
extern ALLEGRO_FONT *builtin;

extern ALLEGRO_BITMAP *overworldPlacePng;

//extern ALLEGRO_BITMAP *backgroundPng;
//extern ALLEGRO_BITMAP *placePng[3];

/*
extern ALLEGRO_BITMAP *UIPlaceButtonPng;
extern ALLEGRO_BITMAP *UIBarterTabPng[2];
extern ALLEGRO_BITMAP *UICrewTabPng[2];
*/

extern ALLEGRO_BITMAP *beingPng[NUM_RACES];
/*
extern ALLEGRO_BITMAP *beingPortraitPng;
extern ALLEGRO_BITMAP *skillSquarePng;

extern ALLEGRO_BITMAP *cargoPng;
*/

void LoadResources();
void UnloadResources();

#endif // RESOURCE_H_INCLUDED
