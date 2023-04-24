#include "place.h"

Place::Place(int id)
{
    identity = id;
    //std::cout << "Place created with ID " << id << std::endl;

    /// Replace with read from external file later
    switch(identity)
    {
    case PL_ERICENNES:
        name = "Ericennes";
        epithet = ", Capital of Verus";
        overworldXPosition = TILE_W*20;
        overworldYPosition = TILE_H*20;
        break;

    case PL_CHORAS:
        name = "Choras";
        overworldXPosition = TILE_W*24;
        overworldYPosition = TILE_H*12;
        break;

    case PL_KETH_KETHER:
        name = "Keth Kether";
        overworldXPosition = TILE_W*12;
        overworldYPosition = TILE_H*24;
        break;

    case PL_KETH_ENTWEIR:
        name = "Keth Entweir";
        overworldXPosition = TILE_W*11;
        overworldYPosition = TILE_H*18;
        break;

    case PL_VIELLEICHT:
        name = "Vielleicht";
        overworldXPosition = TILE_W*1;
        overworldYPosition = TILE_H*28;
        break;

    case PL_QUELLUDE:
        name = "Quellude";
        overworldXPosition = TILE_W*6;
        overworldYPosition = TILE_H*32;
        break;

    case PL_AMBLEFORTH:
        name = "Ambleforth";
        overworldXPosition = TILE_W*4;
        overworldYPosition = TILE_H*14;
        break;
    }

    bubbleActive = false;
}

Place::~Place()
{
    //std::cout << "Place deleted." << std::endl;

    for(std::vector<Being*>::iterator it = availableCrew.begin(); it != availableCrew.end();)
    {
        availableCrew.erase(it);
    }
}

void Place::AddAvailableCrew(Being *b)
{
    availableCrew.push_back(b);
}

void Place::RemoveAvailableCrew(Being *b)
{

}

void Place::AddCitizen(Being *b)
{
    citizens.push_back(b);
}

void Place::AddVisitorCaravan(Caravan *c)
{
    visitors.push_back(c);
    AdjustBubbleDimensions();
}

void Place::AdjustBubbleDimensions()
{
    if(visitors.size() > 0)
    {
        bubbleActive = true;
        bubbleWidth = TILE_W*visitors.size() + TILE_W/2;
        bubbleHeight = TILE_H *1.5;
    }
    else
        bubbleActive = false;

    std::cout << "bubbleWidth adjusted to: " << bubbleWidth << std::endl;
}

void Place::DrawSpriteOnOverworld()
{
    int drawX = overworldXPosition - overworldCameraXPosition - OVERWORLD_SPRITE_W/2;
    int drawY = overworldYPosition - overworldCameraYPosition - OVERWORLD_SPRITE_H/2;

    if(drawX > OVERWORLD_MIN_DRAW_X && drawX < OVERWORLD_MAX_DRAW_X
            && drawY > OVERWORLD_MIN_DRAW_Y && drawY < OVERWORLD_MAX_DRAW_Y)
    {
        int nameDrawX = overworldXPosition - overworldCameraXPosition;
        int nameDrawY = overworldYPosition - overworldCameraYPosition + OVERWORLD_SPRITE_H/2;

        al_draw_bitmap_region(overworldPlacePng,
                              0 + identity*64, 0,
                              64,64,
                              drawX,
                              drawY,
                              0);

        string_al_draw_text(builtin, COL_BLACK, nameDrawX, nameDrawY, ALLEGRO_ALIGN_CENTER, name);
    }
}

void Place::DrawBubbleOnOverworld()
{
    if(bubbleActive)
    {
        /// To do: Adjust for sprites that are not TILE_W in size.

        float drawX = overworldXPosition - overworldCameraXPosition;
        float drawY = overworldYPosition - overworldCameraYPosition - OVERWORLD_SPRITE_H;

        if(drawX > OVERWORLD_MIN_DRAW_X && drawX < OVERWORLD_MAX_DRAW_X
                && drawY > OVERWORLD_MIN_DRAW_Y && drawY < OVERWORLD_MAX_DRAW_Y)
        {


            al_draw_filled_rounded_rectangle(drawX - bubbleWidth/2,
                                             drawY - bubbleHeight/2,
                                             drawX + bubbleWidth/2,
                                             drawY + bubbleHeight/2,
                                             bubbleCornerRadius,
                                             bubbleCornerRadius,
                                             COL_DARK_WHITE);


            al_draw_rounded_rectangle(drawX - bubbleWidth/2,
                                      drawY - bubbleHeight/2,
                                      drawX + bubbleWidth/2,
                                      drawY + bubbleHeight/2,
                                      bubbleCornerRadius,
                                      bubbleCornerRadius,
                                      COL_INDIGO,
                                      4);


            for(unsigned i = 0; i < visitors.size(); i++)
            {
                visitors[i]->DrawActivity(drawX - bubbleWidth/2 + i*TILE_W + TILE_W*3/4,
                                          drawY);
            }

        }
    }
}
