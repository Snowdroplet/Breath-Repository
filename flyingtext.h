#ifndef FLYINGTEXT_H_INCLUDED
#define FLYINGTEXT_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

#include "overworld.h"

class FlyingText
{
public:
    //static std::vector<FlyingText*>flyingTexts;

    bool active;
    bool queued; // Queued text does not lose lifespan until queueTime is 0.
    const int distanceFlownLimit = 60;
    int distanceFlown;
    int queueTime;

    bool hasIcon;
    int itemIcon;

    std::string text;

    const float scrollSpeed = 1;
    const float yPositionDisplacement = TILE_H;
    bool scrollUp;
    float overworldXPosition, overworldYPosition;

    FlyingText(int ic, std::string t, float x, float y, bool up);
    ~FlyingText();

    //void static Output(int ic, std::string t, float x, float y, bool up);

    void Progress();
    void DrawOnOverworld();

};


#endif // FLYINGTEXT_H_INCLUDED
