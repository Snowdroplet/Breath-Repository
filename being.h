#ifndef BEING_H_INCLUDED
#define BEING_H_INCLUDED

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iterator>

#include <allegro5/allegro_image.h>

#include "beingindex.h"
#include "overworld.h"

#include "gamestate.h"
#include "resource.h"

#include "inventory.h"

class Being
{
public:
    static std::vector<Being*>people;

/// State
    bool active;
    int activity;

/// Biography
    std::string name;
    int ancestry;
    int hometown;

    float travelSpeed;

/// Drawing
    bool facingLeft;
    //const int beingSpriteNumVariants = 2; // In total. Not counting from zero.
    int spriteVariant;
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
    void SetAncestry(int a);

    void SetHometown(int h);

    bool IsActive();

/// Progress
    void Progress();

    void DrawName(float x, float y, int flags);

    void DrawActivity(float x, float y);
    void ProgressAnimation();

};

#endif // BEING_H_INCLUDED

