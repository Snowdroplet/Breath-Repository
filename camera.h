#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

//#include <iostream> // debug only
#include <cmath> // abs

#include <allegro5/allegro5.h>

#include "display.h"
#include "tile.h"

/// Note: The camera should try to follow tiles, not follow actors

struct Camera
{
    ///static ALLEGRO_BITMAP* cameraBuffer;

    static constexpr float SCALE_MIN = 1.0;
    static constexpr float SCALE_MAX = 2.0;

    static ALLEGRO_TRANSFORM noTransform; // identity transform
    static ALLEGRO_TRANSFORM zoomTransform;

    static float zoomScale;
    static float zoomTranslateX;
    static float zoomTranslateY;

    static bool overworldCameraMousePanningDisabled;
    static float mouseTransformedX;
    static float mouseTransformedY;

    static bool atDestination;
    static bool approachingDestination;
    static int xCell, yCell;
    static float xPosition, yPosition;
    static float xDestination, yDestination;
    static constexpr float xSensitivity = 16;
    static constexpr float ySensitivity = 16;

    static constexpr float OVERWORLD_MIN_DRAW_X = 0 - Tile::WIDTH*2; // Save drawing resources by not drawing places and beings outside this boundary
    static constexpr float OVERWORLD_MIN_DRAW_Y = 0 - Tile::HEIGHT*2;
    static constexpr float OVERWORLD_MAX_DRAW_X = Display::WIDTH + Tile::WIDTH*2;
    static constexpr float OVERWORLD_MAX_DRAW_Y = Display::HEIGHT + Tile::HEIGHT*2;



    static void Initialize()
    {
        atDestination = true;
        approachingDestination = false;

        al_identity_transform(&noTransform);
        ///cameraBuffer = al_create_bitmap(UI::MAIN_W, UI::MAIN_H);

        zoomScale = SCALE_MIN;
        zoomTranslateX = 0; // At 1.0 scale
        zoomTranslateY = 0;

        SetCell(0,0);
    }

    static void SetPosition(float x, float y){atDestination = true; xDestination = xPosition = x; yDestination = yPosition = y;}
    static void SetCell(int x, int y){xCell = x; yCell = y; SetDestination(xCell*Tile::WIDTH, yCell*Tile::HEIGHT);}
    static void SetDestination(float x, float y){atDestination = false; approachingDestination = true; xDestination = x; yDestination = y;}
    static void SetDestinationCell(int x, int y){SetDestination(x*/*UI::*/Tile::WIDTH, y*/*UI::*/Tile::HEIGHT);}

    static void ApproachDestination();
    static void WarpToDestination();

};

#endif // CAMERA_H_INCLUDED
