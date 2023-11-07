#include "resource.h"

ALLEGRO_FONT *builtin8;
//ALLEGRO_BITMAP *builtin16Tga;
//ALLEGRO_FONT *builtin16;
//ALLEGRO_FONT *spaceMono16;

ALLEGRO_BITMAP *overworldPlacePng;

ALLEGRO_BITMAP *beingsPng;
ALLEGRO_BITMAP *beingPng[NUM_ANCESTRIES];

ALLEGRO_BITMAP *expertiseIconPng;

ALLEGRO_BITMAP *miniCargoPng;
ALLEGRO_BITMAP *cargoPng;

ALLEGRO_BITMAP *redArrowPng;
ALLEGRO_BITMAP *redTransparentXPng;

ALLEGRO_SAMPLE *cottagesMacLeodMp3;
ALLEGRO_SAMPLE *manorMacLeodMp3;

ALLEGRO_SAMPLE_INSTANCE *cottagesSampleInstance;
ALLEGRO_SAMPLE_INSTANCE *manorSampleInstance;

//std::map<int, *ALLEGRO_SAMPLE_INSTANCE>allegro_sample_instances>;

void LoadFontResources()
{
    /*
    int fontRanges[] =
    {
       0x0020, 0x007F,  // ASCII
       0x00A1, 0x00FF,  // Latin 1
       0x0100, 0x017F,  // Extended-A
       0x20AC, 0x20AC   // Euro
    };
    */

    builtin8 = al_create_builtin_font();
    //builtin16Tga = al_load_bitmap("a4_font_16.tga");
    //builtin16 = al_grab_font_from_bitmap(builtin16Tga, 4, fontRanges);
    //builtin16 = al_create_builtin_font();
    //spaceMono16 = al_load_ttf_font("SpaceMono-Regular.ttf",16,0);

}

void LoadImageResources()
{
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

void LoadAudioResources()
{
    al_reserve_samples(10);
    cottagesMacLeodMp3 = al_load_sample("Magic Scout - Cottages.mp3");
    manorMacLeodMp3    = al_load_sample("Magic Scout - Manor.mp3");

    cottagesSampleInstance = al_create_sample_instance(cottagesMacLeodMp3);
    manorSampleInstance    = al_create_sample_instance(manorMacLeodMp3);
    al_attach_sample_instance_to_mixer(cottagesSampleInstance, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(manorSampleInstance,    al_get_default_mixer());
}

void UnloadFontResources()
{
    al_destroy_font(builtin8);
    //al_destroy_bitmap(builtin16Tga);
    //al_destroy_font(builtin16);
    //al_destroy_font(spaceMono16);
}

void UnloadImageResources()
{
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

void UnloadAudioResources()
{
    al_destroy_sample_instance(cottagesSampleInstance);
    al_destroy_sample_instance(manorSampleInstance);

    al_destroy_sample(cottagesMacLeodMp3);
    al_destroy_sample(manorMacLeodMp3);
}
