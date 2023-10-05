#include "being.h"

std::vector<Being*> Being::people;

Being::Being()
{
    SetActive(true);

    SetActivity(ACT_WALKING);
    spriteWidth = SPRITE_TILE_W;
    spriteHeight = SPRITE_TILE_H;
    spriteVariant = rand()%beingSpriteNumVariants;

    travelSpeed = 1.0;

    //std::cout << "Being created." << std::endl;
}

Being::~Being()
{
    //std::cout << "Being deleted." << std::endl;
}

void Being::SetActive(bool a)
{
    active = a;
}

void Being::SetActivity(int act)
{
    activity = act;
    currentFrame = 0;
    frameDelayCount = 0;
    frameDelayThreshold = 6;

    switch(activity)
    {
    case ACT_WALKING:
        maxFrame = 1;
        break;
    }
}

void Being::SetName(std::string n)
{
    name = n;
}
void Being::SetAncestry(int a)
{
    ancestry = a;
}

void Being::SetHometown(int h)
{
    hometown = h;
}


bool Being::IsActive()
{
    return active;
}

void Being::Progress()
{
    ProgressAnimation();
}

void Being::DrawName(float x, float y, int flags)
{
    al_draw_text(builtin, al_map_rgb(0,0,0), x, y, flags, name.c_str());
}

void Being::DrawActivity(float x, float y)
{
    if(x > OVERWORLD_MIN_DRAW_X && x < OVERWORLD_MAX_DRAW_X
            && y > OVERWORLD_MIN_DRAW_Y && y < OVERWORLD_MAX_DRAW_Y)
    {
        int f = 0;
        if(!facingLeft)
            f = ALLEGRO_FLIP_HORIZONTAL;

        if(activity == ACT_WALKING)
            al_draw_bitmap_region(beingPng[ancestry],
                                  spriteVariant*resourceBeingNumWalkFrames*spriteWidth + spriteWidth*currentFrame,
                                  spriteHeight*activity,
                                  spriteWidth,
                                  spriteHeight,
                                  x - (spriteWidth/2),
                                  y - (spriteHeight/2),
                                  f);
    }
}

void Being::ProgressAnimation()
{
    if(maxFrame > 0)
    {
        frameDelayCount++;
        if(frameDelayCount >= frameDelayThreshold)
        {
            frameDelayCount = 0;
            currentFrame++;
            if(currentFrame > maxFrame)
                currentFrame = 0;
        }
    }
}

