#include "overworld.h"

bool overworldCameraLocked = false;
bool overworldCameraLockedOnPlace = false;
Place *overworldCameraPlace = nullptr;
bool overworldCameraLockedOnCaravan = false;
Caravan *overworldCameraCaravan = nullptr;

float overworldCameraXPosition = 0;
float overworldCameraYPosition = 0;

int overworldCameraXSensitivity = 8;
int overworldCameraYSensitivity = 8;

void OverworldDrawGridUnderlay()
{

    for(int x = 0; x <= SCREEN_W/TILE_W; x++) //Columns
    {
        int owcxp = overworldCameraXPosition;
        int tw = TILE_W;

                al_draw_line(x*TILE_W - owcxp%tw,
                             0,
                             x*TILE_W - owcxp%tw,
                             SCREEN_H,
                             COL_DARK_GRAY,1);
    }

    for(int y = 0; y <= SCREEN_H/TILE_W; y++) //Rows
    {
        int owcyp = overworldCameraYPosition;
        int th = TILE_H;

                al_draw_line(0,
                             y*TILE_H - owcyp%th,
                             SCREEN_W,
                             y*TILE_H - owcyp%th,
                             COL_DARK_GRAY,1);
    }


    int crosshairXPosition = overworldCameraXPosition+SCREEN_W/2;
    int crosshairYPosition = overworldCameraYPosition+SCREEN_H/2;

    int crosshairXPositionCell = crosshairXPosition/TILE_W;
    int crosshairYPositionCell = crosshairYPosition/TILE_H;

    std::string positionString = "(" + std::to_string(crosshairXPosition) + ", " + std::to_string(crosshairYPosition) + ") : (" + std::to_string(crosshairXPositionCell) + ", " + std::to_string(crosshairYPositionCell) + ")";
    if(!overworldCameraLocked)
    {
        string_al_draw_text(builtin,COL_BLUE,0,0,ALLEGRO_ALIGN_LEFT,positionString);
        al_draw_line(SCREEN_W/2,0,SCREEN_W/2,SCREEN_H,COL_BLUE,1);
        al_draw_line(0,SCREEN_H/2,SCREEN_W,SCREEN_H/2,COL_BLUE,1);
    }
    else
    {
        string_al_draw_text(builtin,COL_ORANGE,0,0,ALLEGRO_ALIGN_LEFT,positionString);
        al_draw_line(SCREEN_W/2,0,SCREEN_W/2,SCREEN_H,COL_ORANGE,1);
        al_draw_line(0,SCREEN_H/2,SCREEN_W,SCREEN_H/2,COL_ORANGE,1);
    }
}

void OverworldLockCameraPlace(Place *whichPlace)
{
    OverworldUnlockCameraCaravan();

    overworldCameraPlace = whichPlace;
    overworldCameraLockedOnPlace = true;
    overworldCameraLocked = true;
}

void OverworldLockCameraCaravan(Caravan *whichCaravan)
{
    OverworldUnlockCameraPlace();

    overworldCameraCaravan = whichCaravan;
    overworldCameraLockedOnCaravan = true;
    overworldCameraLocked = true;
}

void OverworldUnlockCameraCaravan()
{
    overworldCameraCaravan = nullptr;
    overworldCameraLockedOnCaravan = false;
}

void OverworldUnlockCameraPlace()
{
    overworldCameraPlace = nullptr;
    overworldCameraLockedOnPlace = false;
}

void OverworldUnlockCamera()
{
    OverworldUnlockCameraPlace();
    OverworldUnlockCameraCaravan();
    overworldCameraLocked = false;

    overworldCameraXPosition = overworldCameraXPosition/8*8; // rounds down to nearest 8 (truncates decimal)
    overworldCameraYPosition = overworldCameraYPosition/8*8;
}
