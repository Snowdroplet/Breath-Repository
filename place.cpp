#include "place.h"

Place::Place(int id)
{
    identity = id;
    std::cout << "Place created with ID " << id << std::endl;

    /// Replace with read from external file later
    switch(identity)
    {
    case PL_ERICENNES:
        name = "Ericennes";
        epithet = ", Capital of Verus";
        xPosition = TILE_W*20;
        yPosition = TILE_H*20;
    break;

    case PL_CHORAS:
        name = "Choras";
        xPosition = TILE_W*24;
        yPosition = TILE_H*12;
    break;

    case PL_KETH_KETHER:
        name = "Keth Kether";
        xPosition = TILE_W*12;
        yPosition = TILE_H*24;
    break;

    case PL_KETH_ENTWEIR:
        name = "Keth Entweir";
        xPosition = TILE_W*11;
        yPosition = TILE_H*18;
    break;

    case PL_VIELLEICHT:
        name = "Vielleicht";
        xPosition = TILE_W*1;
        yPosition = TILE_H*28;
    break;

    case PL_QUELLUDE:
        name = "Quellude";
        xPosition = TILE_W*6;
        yPosition = TILE_H*32;
    break;

    case PL_AMBLEFORTH:
        name = "Ambleforth";
        xPosition = TILE_W*4;
        yPosition = TILE_H*14;
    break;
    }
}

Place::~Place()
{
    std::cout << "Place deleted." << std::endl;

    for(std::vector<Being*>::iterator it = availableCrew.begin(); it != availableCrew.end();)
    {
        availableCrew.erase(it);
    }
}

void Place::AddAvailableCrew(Being *b)
{
    availableCrew.push_back(b);
}

void Place::DrawOnOverworld()
{
    int drawX = xPosition - overworldCameraXPosition - OVERWORLD_SPRITE_W/2;
    int drawY = yPosition - overworldCameraYPosition - OVERWORLD_SPRITE_H/2;
    int nameDrawX = xPosition - overworldCameraXPosition;
    int nameDrawY = yPosition - overworldCameraYPosition + OVERWORLD_SPRITE_H/2;

    al_draw_bitmap_region(overworldPlacePng,
                          0 + identity*64, 0,
                          64,64,
                          drawX,
                          drawY,
                          0);

    string_al_draw_text(builtin, COL_BLACK, nameDrawX, nameDrawY, ALLEGRO_ALIGN_CENTER, name);
}
