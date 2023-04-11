#ifndef BEING_H_INCLUDED
#define BEING_H_INCLUDED

#include <iostream>
#include <string>
#include <map>
#include <iterator>

#include <allegro5/allegro_image.h>

#include "beingconsts.h"

#include "gamestate.h"
#include "resource.h"

#include "inventory.h"

const std::string skillNames[NUM_SKILLS] =
{

};

class Being
{
    bool active;

    int skillProfile; // Read skills from file.

    std::string name;
    int race;
    //int portraitRow, portraitCol;
    int spriteBase;


    int hometown;

    // Expertise from 1 to 5.
    std::map <int, int>skills;


public:

    Inventory inventory;

    Being();
    ~Being();

    void SetActive(bool a);

    void SetName(std::string n);
    void SetRace(int r);
    //void SetPortrait(int r, int c);

    void SetHometown(int h);

    void SetSkill(int s, int v);

    bool IsActive();

    //void DrawPortrait(float x, float y);
    void DrawName(float x, float y, int flags);
    //void DrawSkills(float x, float y);
    //void DrawSkillsDetailed(float x, float y);

    void DrawOverworldActivity();

};

#endif // BEING_H_INCLUDED

