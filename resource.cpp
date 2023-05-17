#include "resource.h"

ALLEGRO_FONT *builtin;

ALLEGRO_BITMAP *overworldPlacePng;

/*
ALLEGRO_BITMAP *backgroundPng;
ALLEGRO_BITMAP *placePng[3];

ALLEGRO_BITMAP *UIPlaceButtonPng;
ALLEGRO_BITMAP *UIBarterTabPng[2];
ALLEGRO_BITMAP *UICrewTabPng[2];
*/

ALLEGRO_BITMAP *beingPng[NUM_RACES];

/*
ALLEGRO_BITMAP *beingPortraitPng;

ALLEGRO_BITMAP *skillSquarePng;
*/
ALLEGRO_BITMAP *miniCargoPng;
ALLEGRO_BITMAP *cargoPng;

ALLEGRO_BITMAP *industryRedArrowPng;

void LoadResources()
{
    builtin = al_create_builtin_font();

    overworldPlacePng = al_load_bitmap("placeholderOverworldPlace.png");

    /*
    backgroundPng = al_load_bitmap("placeholderBackground.png");
    placePng[0] = al_load_bitmap("placeholderEricennes.png");
    placePng[1] = al_load_bitmap("placeholderKethentweir.png");
    placePng[2] = al_load_bitmap("placeholderKethketer.png");

    UIPlaceButtonPng = al_load_bitmap("placeholderUIPlaceButton.png");

    UIBarterTabPng[0] = al_load_bitmap("placeholderUIBarterTabInactive.png");
    UIBarterTabPng[1] = al_load_bitmap("placeholderUIBarterTabActive.png");

    UICrewTabPng[0] = al_load_bitmap("placeholderUICrewTabInactive.png");
    UICrewTabPng[1] = al_load_bitmap("placeholderUICrewTabActive.png");
    */

    beingPng[RACE_VERIT] = al_load_bitmap("placeholderVerit.png");
    beingPng[RACE_YETI] = al_load_bitmap("placeholderYeti.png");
    beingPng[RACE_MAKHI] = al_load_bitmap("placeholderMakhi.png");
    beingPng[RACE_BEYU] = al_load_bitmap("placeholderBeyu.png");
    beingPng[RACE_HAPHAE] = al_load_bitmap("placeholderHaphae.png");
    beingPng[RACE_MESERA] = al_load_bitmap("placeholderMesera.png");
    beingPng[RACE_ORDON] = al_load_bitmap("placeholderOrdon.png");
    /*
    beingPortraitPng = al_load_bitmap("placeholderBeingPortrait.png");

    skillSquarePng = al_load_bitmap("placeholderSkillSquare.png");
    */
    cargoPng = al_load_bitmap("placeholderMiniCargo.png");
    cargoPng = al_load_bitmap("placeholderCargo.png");

    industryRedArrowPng = al_load_bitmap("placeholderIndustryRedArrow.png");
}

void UnloadResources()
{
    al_destroy_font(builtin);

    al_destroy_bitmap(overworldPlacePng);

    /*

    al_destroy_bitmap(backgroundPng);

    for(int i = 0; i < 3; i++)
        al_destroy_bitmap(placePng[i]);

    al_destroy_bitmap(UIPlaceButtonPng);

    for(int i = 0; i < 2; i++)
    {
        al_destroy_bitmap(UIBarterTabPng[i]);
        al_destroy_bitmap(UICrewTabPng[i]);
    }
    */

    for(int i = 0; i < NUM_RACES; i++)
        al_destroy_bitmap(beingPng[i]);
    /*

    al_destroy_bitmap(beingPortraitPng);

    al_destroy_bitmap(skillSquarePng);

    */
    al_destroy_bitmap(miniCargoPng);
    al_destroy_bitmap(cargoPng);

    al_destroy_bitmap(industryRedArrowPng);

}
