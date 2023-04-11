#include "overworld.h"

int overworldCameraXPosition = OVERWORLD_W/2 - SCREEN_W/2;
int overworldCameraYPosition = OVERWORLD_H/2 - SCREEN_H/2;

int overworldCameraXSensitivity = 4;
int overworldCameraYSensitivity = 4;

void DrawOverworldDebugOverlay()
{

    for(int i = 0; i <= OVERWORLD_W; i+= TILE_W) //Columns
    {
                al_draw_line(i                -overworldCameraXPosition,
                             0                -overworldCameraYPosition,
                             i                -overworldCameraXPosition,
                             OVERWORLD_H      -overworldCameraYPosition,
                             COL_DARK_GRAY,1);
    }

    for(int i = 0; i <= OVERWORLD_H; i+= TILE_H) //Rows
    {
                al_draw_line(0              -overworldCameraXPosition,
                             i              -overworldCameraYPosition,
                             OVERWORLD_W    -overworldCameraXPosition,
                             i              -overworldCameraYPosition,
                             COL_DARK_GRAY,1);
    }

    int crosshairXPosition = overworldCameraXPosition+SCREEN_W/2;
    int crosshairYPosition = overworldCameraYPosition+SCREEN_H/2;

    int crosshairXPositionCell = crosshairXPosition/TILE_W;
    int crosshairYPositionCell = crosshairYPosition/TILE_H;

    std::string positionString = "(" + std::to_string(crosshairXPosition) + ", " + std::to_string(crosshairYPosition) + ") : (" + std::to_string(crosshairXPositionCell) + ", " + std::to_string(crosshairYPositionCell) + ")";
    string_al_draw_text(builtin,COL_ORANGE,0,0,ALLEGRO_ALIGN_LEFT,positionString);

    al_draw_line(SCREEN_W/2,0,SCREEN_W/2,SCREEN_H,COL_ORANGE,1);
    al_draw_line(0,SCREEN_H/2,SCREEN_W,SCREEN_H/2,COL_ORANGE,1);
}
