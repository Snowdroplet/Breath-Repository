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

#include "resource.h"
#include "camera.h"

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

/// Stats
    int mood; // Emotion taking into account changes in vitality, purpose and happiness.

    float vitality;  // Depletes on the road. Depletes faster if unadapted to environment.
                     // Replenished at cities.
                     // Instant death at 0.

    float happiness; // Depletes slowly. Depletes faster if vitality is low. Depletes faster if purpose is low.
                     // Replenishes if both vitality and purpose are high.
                     // Becomes a bandit at 0 or less.

    float purpose;   // Depletes gradually. Depletes faster far from home.
                     // Greatly replenished by completing objectives.
                     // Creates new caravan to returns home if 0 or less.
/// Objectives
    int objectiveA;
    int objectiveB;
    int objectiveC;
/// Abilities
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

/// Status Bubble


/// Constructor and destructor
    Being();
    ~Being();

/// State functions
    void SetActive(bool a);
    void SetActivity(int act);
    bool IsActive();
/// Biography functions
    void SetName(std::string n);
    void SetAncestry(int a);

    void SetHometown(int h);

/// Progress
    void Progress();

/// Drawing
    void DrawActivity(float x, float y);
    void ProgressAnimation();
};

#endif // BEING_H_INCLUDED

