#include "overworld.h"

/// Mouse

/// Camera
bool overworldCameraMousePanningDisabled = false;

bool overworldCameraLocked = false;
bool overworldCameraLockedOnPlace = false;
Place *overworldCameraPlace = nullptr;
bool overworldCameraLockedOnCaravan = false;
Caravan *overworldCameraCaravan = nullptr;

/**

float overworldCameraXPosition = 0;
float overworldCameraYPosition = 0;

bool overworldCameraApproachingDestination = false;
float overworldCameraXDestination;
float overworldCameraYDestination;

int overworldCameraXSensitivity = 16;
int overworldCameraYSensitivity = 16;
*/

/// Audio
//extern ALLEGRO_SAMPLE_INSTANCE *overworldParallelSampleInstance;
int overworldParallelSampleInstanceCurrentPart = OPS_COTTAGES;
//unsigned int overworldParallelSampleInstancePosition = 0;

/// Draw grid underlay functions
void OverworldDrawGridUnderlay()
{

    for(int x = 0; x <= Display::WIDTH/Tile::WIDTH; x++) //Columns
    {
        int cxp = Camera::xPosition;
        int tw = Tile::WIDTH;

        al_draw_line(x*Tile::WIDTH - cxp%tw,
                     0,
                     x*Tile::WIDTH - cxp%tw,
                     Display::HEIGHT,
                     COLKEY_DEBUG_GRID_UNDERLAY,1);
    }

    for(int y = 0; y <= Display::HEIGHT/Tile::WIDTH; y++) //Rows
    {
        int cyp = Camera::yPosition;
        int th = Tile::HEIGHT;

        al_draw_line(0,
                     y*Tile::HEIGHT - cyp%th,
                     Display::WIDTH,
                     y*Tile::HEIGHT - cyp%th,
                     COLKEY_DEBUG_GRID_UNDERLAY,1);
    }
}

void OverworldDrawGridCameraCrosshair()
{
    if(!overworldCameraLocked)
    {
        al_draw_line(Display::WIDTH/2,0,Display::WIDTH/2,Display::HEIGHT,COLKEY_CAMERA_CROSSHAIR_FREE,1);
        al_draw_line(0,Display::HEIGHT/2,Display::WIDTH,Display::HEIGHT/2,COLKEY_CAMERA_CROSSHAIR_FREE,1);
    }
    else
    {
        al_draw_line(Display::WIDTH/2,0,Display::WIDTH/2,Display::HEIGHT,COLKEY_CAMERA_CROSSHAIR_LOCKED,1);
        al_draw_line(0,Display::HEIGHT/2,Display::WIDTH,Display::HEIGHT/2,COLKEY_CAMERA_CROSSHAIR_LOCKED,1);
    }
}

/*
void OverworldDrawGridMouseCrosshair(float mouseDisplayX, float mouseDisplayY)
{
    al_draw_line(mouseDisplayX, 0, mouseDisplayX, Display::HEIGHT, COLKEY_MOUSE_CROSSHAIR,1);
    al_draw_line(0, mouseDisplayY, Display::WIDTH, mouseDisplayY, COLKEY_MOUSE_CROSSHAIR,1);
}
*/

void OverworldDrawGridText(float mouseTransformedX, float mouseTransformedY)
{
    int cameraCrosshairXPosition = Camera::xPosition+Display::WIDTH/2;
    int cameraCrosshairYPosition = Camera::yPosition+Display::HEIGHT/2;

    int cameraCrosshairXPositionCell = cameraCrosshairXPosition/Tile::WIDTH;
    int cameraCrosshairYPositionCell = cameraCrosshairYPosition/Tile::HEIGHT;

    int mouseCrosshairXPosition = Camera::xPosition+mouseTransformedX;
    int mouseCrosshairYPosition = Camera::yPosition+mouseTransformedY;

    int mouseCrosshairXPositionCell = mouseCrosshairXPosition/Tile::WIDTH;
    int mouseCrosshairYPositionCell = mouseCrosshairYPosition/Tile::HEIGHT;

    int zoomPercentage = Camera::zoomScale*100;

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

/*
/// Overworld mouse functions
void OverworldUpdateTransformedMouseCoords(float mX, float mY)
{

    mouseTransformedX = mX - cameraZoomScale*0.1*Display::WIDTH;
    mouseTransformedY = mY + cameraZoomScale*0.1*Display::HEIGHT;
}
*/


/// Camera control functions
/**
void OverworldApproachCameraDestination()
{
    if(overworldCameraXPosition != overworldCameraXDestination)
        overworldCameraXPosition += (overworldCameraXDestination - overworldCameraXPosition)/2;

    if(overworldCameraYPosition != overworldCameraYDestination)
        overworldCameraYPosition += (overworldCameraYDestination - overworldCameraYPosition)/2;

}
*/

void OverworldLockCameraPlace(Place *whichPlace)
{
    OverworldUnlockCameraCaravan();

    overworldCameraPlace = whichPlace;
    overworldCameraLockedOnPlace = true;
    overworldCameraLocked = true;

    bubbleViewPlace = whichPlace;

    OverworldSwapParallelBackgroundAudioToPlace();
}

void OverworldLockCameraCaravan(Caravan *whichCaravan)
{
    OverworldUnlockCameraPlace();

    overworldCameraCaravan = whichCaravan;
    overworldCameraLockedOnCaravan = true;
    overworldCameraLocked = true;

    bubbleViewCaravan = whichCaravan;

    OverworldSwapParallelBackgroundAudioToField();
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
}


/// Audio functions
void OverworldAudioUpdate()
{

    if(overworldParallelSampleInstanceCurrentPart == OPS_COTTAGES)
    {
        if(al_get_sample_instance_gain(cottagesSampleInstance) < 1.0)
            al_set_sample_instance_gain(cottagesSampleInstance, al_get_sample_instance_gain(cottagesSampleInstance) + 0.05);

        if(al_get_sample_instance_gain(manorSampleInstance) > 0.0)
            al_set_sample_instance_gain(manorSampleInstance, al_get_sample_instance_gain(manorSampleInstance) - 0.05);
    }

    if(overworldParallelSampleInstanceCurrentPart == OPS_MANOR) // Don't else if
    {
        if(al_get_sample_instance_gain(manorSampleInstance) < 1.0)
            al_set_sample_instance_gain(manorSampleInstance, al_get_sample_instance_gain(manorSampleInstance) + 0.05);

        if(al_get_sample_instance_gain(cottagesSampleInstance) > 0.0)
            al_set_sample_instance_gain(cottagesSampleInstance, al_get_sample_instance_gain(cottagesSampleInstance) - 0.05);
    }

}

void OverworldBeginParallelBackgroundAudio()
{
    al_set_sample_instance_playmode(cottagesSampleInstance, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_playmode(manorSampleInstance, ALLEGRO_PLAYMODE_LOOP);

    al_set_sample_instance_gain(cottagesSampleInstance, 0.0);
    al_set_sample_instance_gain(manorSampleInstance, 0.0);

    al_play_sample_instance(cottagesSampleInstance);
    al_play_sample_instance(manorSampleInstance);

    overworldParallelSampleInstanceCurrentPart = OPS_COTTAGES;
}

void OverworldEndParallelBackgroundAudio()
{
    al_stop_sample_instance(cottagesSampleInstance);
    al_stop_sample_instance(manorSampleInstance);
}

void OverworldSwapParallelBackgroundAudioToPlace()
{
    overworldParallelSampleInstanceCurrentPart = OPS_MANOR;
}

void OverworldSwapParallelBackgroundAudioToField()
{
    overworldParallelSampleInstanceCurrentPart = OPS_COTTAGES;
}
