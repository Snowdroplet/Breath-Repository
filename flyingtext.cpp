#include "flyingtext.h"

FlyingText::FlyingText(int ic, std::string t, float x, float y, bool up)
{
    active = true;
    queued = true;

    distanceFlown = 0;

    hasIcon = true;
    itemIcon = ic;
    text = t;
    scrollUp = up;

    if(scrollUp)
    {
        overworldXPosition = x + scrollUpXDisplacement;
        overworldYPosition = y + scrollUpYDisplacement;
    }
    else
    {
        overworldXPosition = x + scrollDownXDisplacement;
        overworldYPosition = y + scrollDownYDisplacement;
    }

    //std::cout << "Item #" << ic << " " << t << " " << x << "/" << y << std::endl;

}

FlyingText::~FlyingText()
{
    //std::cout << "Deletion test" << std::endl;
}

void FlyingText::Progress()
{
    if(!queued)
    {
        distanceFlown++;
        if(distanceFlown >= distanceFlownLimit)
        {
            active = false;
        }
        if(scrollUp)
            overworldYPosition -= scrollUpSpeed;
        else
            overworldYPosition += scrollDownSpeed;
    }

}

void FlyingText::DrawOnOverworld()
{
    if(!queued)
    {
        float drawX = overworldXPosition - Camera::xPosition;
        float drawY = overworldYPosition - Camera::yPosition;

        al_draw_bitmap_region(Resource::miniCargoPng,
                              itemIcon*Tile::MINI_WIDTH, 0,
                              Tile::MINI_WIDTH, Tile::MINI_HEIGHT,
                              drawX,
                              drawY,
                              0);

        if(scrollUp)
            AllegroCustom::string_al_draw_text(Resource::builtin8,COLKEY_TEXT,drawX+Tile::MINI_WIDTH,drawY,ALLEGRO_ALIGN_LEFT,text);
        else //scroll down
            AllegroCustom::string_al_draw_text(Resource::builtin8,COLKEY_FLYINGTEXT_DOWN,drawX+Tile::MINI_WIDTH,drawY,ALLEGRO_ALIGN_LEFT,text);
    }
}
