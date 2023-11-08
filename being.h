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

/// Status
    int mood; // Just some random emotion taking into account vitality, purpose and happiness.

    float vitality;  // Depletes on the road. Depletes faster if unadapted to environment.
                     // Replenished at cities.
                     // Instant death at 0.

    float purpose;   // Depletes gradually.
                     // Greatly replenished by completing objectives.
                     // Creates new caravan to returns home if 0 or less.

    float happiness; // Depletes slowly. Depletes faster if vitality is low. Depletes faster if purpose is low.
                     // Replenishes if both vitality and purpose are high.
                     // Becomes a bandit at 0 or less.

    int objectiveA;
    int objectiveB;
    int objectiveC;



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
    void DrawName(float x, float y, int flags);

    void DrawActivity(float x, float y);
    void ProgressAnimation();

};

#endif // BEING_H_INCLUDED

