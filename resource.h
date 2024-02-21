#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "tile.h"
#include "beingindex.h"

struct Resource
{
    static constexpr float TEXT_HEIGHT_8 = 8;
    static constexpr float TEXT_HEIGHT_12 = 12;
    static constexpr float TEXT_HEIGHT_16 = 16;

    static ALLEGRO_FONT *builtin8;
    //static ALLEGRO_BITMAP *builtin16Tga;
    //static ALLEGRO_FONT *builtin16;
    //static ALLEGRO_FONT *spaceMono16;

    static ALLEGRO_BITMAP *overworldPlacePng;

    static const unsigned resourceBeingNumWalkFrames = 2;
    static ALLEGRO_BITMAP *beingsPng;
    static ALLEGRO_BITMAP *beingPng[NUM_ANCESTRIES];

    static ALLEGRO_BITMAP *expertiseIconPng;

    static ALLEGRO_BITMAP *miniCargoPng;
    static ALLEGRO_BITMAP *cargoPng;

    static ALLEGRO_BITMAP *redArrowPng;
    static ALLEGRO_BITMAP *redTransparentXPng;

    /*
    enum enumBackgroundTracks
    {
        TRACK_MACLEOD_COTTAGES = 0,
        TRACK_MACLEOD_MANOR    = 1
    };
    */

    static ALLEGRO_SAMPLE *cottagesMacLeodMp3;
    static ALLEGRO_SAMPLE *manorMacLeodMp3;

    static ALLEGRO_SAMPLE_INSTANCE *cottagesSampleInstance;
    static ALLEGRO_SAMPLE_INSTANCE *manorSampleInstance;

    static void LoadFontResources();
    static void LoadImageResources();
    static void LoadAudioResources();

    static void UnloadFontResources();
    static void UnloadImageResources();
    static void UnloadAudioResources();

};

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

#endif // RESOURCE_H_INCLUDED
