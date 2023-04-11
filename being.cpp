#include "being.h"

Being::Being()
{
    SetActive(true);

    std::cout << "Being created." << std::endl;
}

Being::~Being()
{
    std::cout << "Being deleted." << std::endl;
}

void Being::SetActive(bool a)
{
    active = a;
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

void Being::DrawOverworldActivity()
{
    /*
    al_draw_bitmap(

                   );
                   */
}

