#ifndef PLACE_H_INCLUDED
#define PLACE_H_INCLUDED

#include <string>
#include <vector>

#include "allegrocustom.h"

#include "placeindex.h"

#include "overworld.h"

#include "caravan.h"

#include "economy.h"

#include "resource.h"

/// Dependencies
class Caravan; // Circular

class Place
{
    const int OVERWORLD_SPRITE_W = 64;
    const int OVERWORLD_SPRITE_H = 64;

public:
    static std::map <int, Place*>places;

/// Identity
    int identity;
    Place *selfPointer;

    std::string name; // Just the simple name for identification on the overworld map.
    std::string epithet; // e.g. ", City of Dreaming Spires"

/// Population
    std::vector<Being*>availableCrew;
    std::vector<Being*>citizens;
    std::vector<Caravan*>visitors;

/// Economy
    Inventory inventory;

/// Inventory

/// Location
    int overworldXPosition, overworldYPosition; // Absolute position on the overworld.

    std::vector<Road*>connections;

/// Bubble
    bool bubbleActive;
    float bubbleWidth, bubbleHeight;
    const float bubbleCornerRadius = 8;

/// Constructor
    Place(int id);
    ~Place();

/// Population functions
    void AddAvailableCrew(Being *b);
    void RemoveAvailableCrew(Being *b);

    void AddCitizen(Being *b);
    void RemoveCitizen(Being *b);

    void AddVisitorCaravan(Caravan *c);
    void RemoveVisitorCaravan(Caravan *c);

/// Bubble functions
    void AdjustBubbleDimensions();

/// Overworld drawing functions
    void DrawSpriteOnOverworld();
    void DrawBubbleOnOverworld();

};

#endif // PLACE_H_INCLUDED
