#include "overworld.h"

bool overworldCameraMousePanningDisabled = false;

bool overworldCameraLocked = false;
bool overworldCameraLockedOnPlace = false;
Place *overworldCameraPlace = nullptr;
bool overworldCameraLockedOnCaravan = false;
Caravan *overworldCameraCaravan = nullptr;

float overworldCameraXPosition = 0;
float overworldCameraYPosition = 0;

bool overworldCameraApproachingDestination = false;
float overworldCameraXDestination;
float overworldCameraYDestination;

int overworldCameraXSensitivity = 16;
int overworldCameraYSensitivity = 16;

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
                             COLKEY_DEBUG_GRID_UNDERLAY,1);
    }

    for(int y = 0; y <= SCREEN_H/TILE_W; y++) //Rows
    {
        int owcyp = overworldCameraYPosition;
        int th = TILE_H;

                al_draw_line(0,
                             y*TILE_H - owcyp%th,
                             SCREEN_W,
                             y*TILE_H - owcyp%th,
                             COLKEY_DEBUG_GRID_UNDERLAY,1);
    }
}

void OverworldDrawGridCameraCrosshair()
{
    if(!overworldCameraLocked)
    {
        al_draw_line(SCREEN_W/2,0,SCREEN_W/2,SCREEN_H,COLKEY_CAMERA_CROSSHAIR_FREE,1);
        al_draw_line(0,SCREEN_H/2,SCREEN_W,SCREEN_H/2,COLKEY_CAMERA_CROSSHAIR_FREE,1);
    }
    else
    {
        al_draw_line(SCREEN_W/2,0,SCREEN_W/2,SCREEN_H,COLKEY_CAMERA_CROSSHAIR_LOCKED,1);
        al_draw_line(0,SCREEN_H/2,SCREEN_W,SCREEN_H/2,COLKEY_CAMERA_CROSSHAIR_LOCKED,1);
    }
}

void OverworldDrawGridMouseCrosshair(float mouseX, float mouseY)
{
    al_draw_line(mouseX, 0, mouseX, SCREEN_H, COLKEY_MOUSE_CROSSHAIR,1);
    al_draw_line(0, mouseY, SCREEN_W, mouseY, COLKEY_MOUSE_CROSSHAIR,1);
}

void OverworldDrawGridText(float mouseX, float mouseY)
{
    int cameraCrosshairXPosition = overworldCameraXPosition+SCREEN_W/2;
    int cameraCrosshairYPosition = overworldCameraYPosition+SCREEN_H/2;

    int cameraCrosshairXPositionCell = cameraCrosshairXPosition/TILE_W;
    int cameraCrosshairYPositionCell = cameraCrosshairYPosition/TILE_H;

    int mouseCrosshairXPosition = overworldCameraXPosition+mouseX;
    int mouseCrosshairYPosition = overworldCameraYPosition+mouseY;

    int mouseCrosshairXPositionCell = mouseCrosshairXPosition/TILE_W;
    int mouseCrosshairYPositionCell = mouseCrosshairYPosition/TILE_H;

    int zoomPercentage = cameraZoomScale*100;

    std::string cameraCrosshairPositionString = "CAMERA: (" + std::to_string(cameraCrosshairXPosition) + ", " + std::to_string(cameraCrosshairYPosition) + ") : ("
    + std::to_string(cameraCrosshairXPositionCell) + ", " + std::to_string(cameraCrosshairYPositionCell) + ") "
    + std::to_string(zoomPercentage) + "%";

    std::string mouseCrosshairPositionString = "MOUSE:  (" + std::to_string(mouseCrosshairXPosition) + ", " + std::to_string(mouseCrosshairYPosition) + ") : ("
    + std::to_string(mouseCrosshairXPositionCell) + ", " + std::to_string(mouseCrosshairYPositionCell) + ") "
    + std::to_string(zoomPercentage) + "%";

    if(!overworldCameraLocked)
        string_al_draw_text(builtin8,COLKEY_CAMERA_CROSSHAIR_FREE,0,0,ALLEGRO_ALIGN_LEFT,cameraCrosshairPositionString);
    else
        string_al_draw_text(builtin8,COLKEY_CAMERA_CROSSHAIR_LOCKED,0,0,ALLEGRO_ALIGN_LEFT,cameraCrosshairPositionString);

    string_al_draw_text(builtin8,COLKEY_MOUSE_CROSSHAIR,0,TEXT_HEIGHT_8,ALLEGRO_ALIGN_LEFT,mouseCrosshairPositionString);

}

void OverworldApproachCameraDestination()
{
    if(overworldCameraXPosition != overworldCameraXDestination)
        overworldCameraXPosition += (overworldCameraXDestination - overworldCameraXPosition)/2;

    if(overworldCameraYPosition != overworldCameraYDestination)
        overworldCameraYPosition += (overworldCameraYDestination - overworldCameraYPosition)/2;

}

void OverworldLockCameraPlace(Place *whichPlace)
{
    OverworldUnlockCameraCaravan();

    overworldCameraPlace = whichPlace;
    overworldCameraLockedOnPlace = true;
    overworldCameraLocked = true;

    bubbleViewPlace = whichPlace;
    //OpenAllPlaceBubbles();
}

void OverworldLockCameraCaravan(Caravan *whichCaravan)
{
    OverworldUnlockCameraPlace();

    overworldCameraCaravan = whichCaravan;
    overworldCameraLockedOnCaravan = true;
    overworldCameraLocked = true;


    bubbleViewCaravan = whichCaravan;
    //OpenAllCaravanBubbles();
}

void OverworldUnlockCameraCaravan()
{
    overworldCameraCaravan = nullptr;
    overworldCameraLockedOnCaravan = false;

    //CloseAllCaravanBubbles();
}

void OverworldUnlockCameraPlace()
{
    overworldCameraPlace = nullptr;
    overworldCameraLockedOnPlace = false;

    //CloseAllPlaceBubbles();
}

void OverworldUnlockCamera()
{
    OverworldUnlockCameraPlace();
    OverworldUnlockCameraCaravan();
    overworldCameraLocked = false;

    /*
    overworldCameraXPosition = overworldCameraXPosition/8*8; // rounds down to nearest 8 (truncates decimal)
    overworldCameraYPosition = overworldCameraYPosition/8*8;
    */
}
