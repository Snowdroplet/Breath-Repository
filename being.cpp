#include "being.h"

std::vector<Being*> Being::people;

Being::Being()
{
    SetActive(true);

    SetActivity(ACT_WALKING);
    spriteWidth = TILE_W;
    spriteHeight = TILE_H;

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
    frameDelayThreshold = 5;

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
void Being::SetRace(int r)
{
    race = r;
}

/*
void Being::SetPortrait(int r, int c)
{
    portraitRow = r;
    portraitCol = c;
}
*/

void Being::SetHometown(int h)
{
    hometown = h;
}

void Being::SetSkill(int s, int v)
{
    skills[s] = v;

    if(skills[s] <= 0)
        skills.erase(s);

}

bool Being::IsActive()
{
    return active;
}

/*

void Being::DrawPortrait(float x, float y)
{
    al_draw_bitmap_region(beingPortraitPng,
                          portraitCol*BEING_PORTRAIT_W,
                          portraitRow*BEING_PORTRAIT_H,
                          BEING_PORTRAIT_W,
                          BEING_PORTRAIT_H,
                          x,
                          y,
                          0);
}

*/

void Being::DrawName(float x, float y, int flags)
{
    al_draw_text(builtin, al_map_rgb(0,0,0), x, y, flags, name.c_str());
}

/*
void Being::DrawSkills(float x, float y)
{
    int i = 0;
    for(std::map<int,int>::iterator it = skills.begin(); it != skills.end(); ++it)
    {
        //int drawPosition = std::distance(skills.begin(),it);
        std::string value = std::to_string(it->second);

        al_draw_bitmap_region(skillSquarePng,
                              it->first * BEING_SKILL_SQUARE_W,
                              0,
                              BEING_SKILL_SQUARE_W,
                              BEING_SKILL_SQUARE_H,
                              x + i*BEING_SKILL_SQUARE_W,
                              y,
                              0);

        al_draw_text(builtin,
                     al_map_rgb(0,0,0),
                     x + UI_CREW_SKILL_VALUE_X_DISPLACEMENT + i*UI_CREW_SKILL_VALUE_X_SPACING,
                     y + UI_CREW_SKILL_VALUE_Y_DISPLACEMENT,
                     0,
                     value.c_str());

        i++;
    }
}
*/

/*
void Being::DrawSkillsDetailed(float x, float y)
{
    int i = 0;
    for(std::map<int, int>::iterator it = skills.begin(); it != skills.end(); ++it)
    {

        al_draw_bitmap_region(skillSquarePng,
                              it->first * BEING_SKILL_SQUARE_W,
                              0,
                              BEING_SKILL_SQUARE_W,
                              BEING_SKILL_SQUARE_H,
                              x,
                              y + i*UI_CREW_DETAILED_SKILL_SQUARE_Y_SPACING,
                              0);

        al_draw_text(builtin,
                     al_map_rgb(0,0,0),
                     x + UI_CREW_DETAILED_SKILL_TEXT_X_DISPLACEMENT,
                     y + i*UI_CREW_DETAILED_SKILL_TEXT_Y_SPACING,
                     ALLEGRO_ALIGN_LEFT,
                     skillNames[it->first].c_str());

        i++;
    }
}
*/

void Being::DrawActivity(float x, float y)
{
    int f = 0;
    if(facingLeft)
        f = ALLEGRO_FLIP_HORIZONTAL;

    al_draw_bitmap_region(beingPng[race],
                          spriteWidth*currentFrame,
                          spriteHeight*activity,
                          spriteWidth,
                          spriteHeight,
                          x - (spriteWidth/2),
                          y - (spriteHeight/2),
                          f);

    ProgressAnimation();
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

