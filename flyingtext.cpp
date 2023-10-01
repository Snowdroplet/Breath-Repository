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
        float drawX = overworldXPosition - overworldCameraXPosition;
        float drawY = overworldYPosition - overworldCameraYPosition;

        al_draw_bitmap_region(miniCargoPng,
                              itemIcon*MINI_TILE_W, 0,
                              MINI_TILE_W, MINI_TILE_H,
                              drawX,
                              drawY,
                              0);

        if(scrollUp)
            string_al_draw_text(builtin,COLKEY_TEXT,drawX+MINI_TILE_W,drawY,ALLEGRO_ALIGN_LEFT,text);
        else //scroll down
            string_al_draw_text(builtin,COLKEY_FLYINGTEXT_DOWN,drawX+MINI_TILE_W,drawY,ALLEGRO_ALIGN_LEFT,text);
    }
}
