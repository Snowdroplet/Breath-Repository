#ifndef BEING_H_INCLUDED
#define BEING_H_INCLUDED

#include <iostream>
#include <string>
#include <map>
#include <iterator>

#include <allegro5/allegro_image.h>

#include "beingconsts.h"
#include "overworld.h"

#include "gamestate.h"
#include "resource.h"

#include "inventory.h"

const std::string skillNames[NUM_SKILLS] =
{

};

class Being
{
public:
/// State
    bool active;
    int activity;

/// Biography
    std::string name;
    int race;
    int hometown;

    int skillProfile; // Read skills from file.
    std::map <int, int> skills;// Expertise from 1 to 5.

    float travelSpeed;

/// Drawing
    bool facingLeft;
    int spriteWidth, spriteHeight;
    int currentFrame, maxFrame;
    int frameDelayCount;     // Meant to iterate from zero.
    int frameDelayThreshold; // Higher value increases time between frame update

    //int portraitRow, portraitCol;

    Inventory inventory;

    Being();
    ~Being();

    void SetActive(bool a);
    void SetActivity(int act);

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

    void DrawOverworldActivity(float x, float y);
    void ProgressAnimation();

};

#endif // BEING_H_INCLUDED

