#ifndef FLYINGTEXT_H_INCLUDED
#define FLYINGTEXT_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

#include "overworld.h"

class FlyingText
{
public:
    bool active;
    bool queued; // Queued text does not gain distanceFlown while queued.

    bool hasIcon;
    int itemIcon;

    std::string text;

    const float scrollUpSpeed = 0.4;
    const float scrollUpXDisplacement = 0;
    const float scrollUpYDisplacement = TILE_H*(-1.5);
    const float scrollDownSpeed = 0.32;
    const float scrollDownXDisplacement = TILE_W*(-1);
    const float scrollDownYDisplacement = TILE_H*(-2);

    bool scrollUp;
    float overworldXPosition, overworldYPosition;

    const int distanceFlownLimit = TILE_H*1.5;
    int distanceFlown;

    FlyingText(int ic, std::string t, float x, float y, bool up);
    ~FlyingText();

    void Progress();
    void DrawOnOverworld();

};


#endif // FLYINGTEXT_H_INCLUDED
