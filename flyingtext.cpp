#include "flyingtext.h"

//std::vector<FlyingText*>FlyingText::flyingTexts;

FlyingText::FlyingText(int ic, std::string t, float x, float y, bool up)
{
    active = true;
    queued = true;

    distanceFlown = 0;

    hasIcon = true;
    itemIcon = ic;
    text = t;
    scrollUp = up;
    overworldXPosition = x;

    if(scrollUp)
        overworldYPosition = y - yPositionDisplacement;
    else
        overworldYPosition = y + yPositionDisplacement;

    std::cout << "Item #" << ic << " " << t << " " << x << "/" << y << std::endl;

}

FlyingText::~FlyingText()
{
    std::cout << "Deletion test" << std::endl;
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
            overworldYPosition -= scrollSpeed;
        else
            overworldYPosition += scrollSpeed;
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

        string_al_draw_text(builtin,COL_BLACK,drawX+MINI_TILE_W,drawY,ALLEGRO_ALIGN_LEFT,text);
    }
}

/*
void FlyingText::Output(int ic, std::string t, float x, float y, bool up)
{
    flyingTexts.push_back(new FlyingText(ic, t, x, y, up));
}
*/
