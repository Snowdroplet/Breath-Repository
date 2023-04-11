#ifndef PLACE_H_INCLUDED
#define PLACE_H_INCLUDED

#include <string>
#include <vector>

#include "allegrocustom.h"

#include "placeconsts.h"

#include "overworld.h"
#include "being.h"
#include "inventory.h"

#include "resource.h"

class Place
{
public:
    int identity;

    std::string name; // Just the simple name for identification on the overworld map.
    std::string epithet; // e.g. ", City of Dreaming Spires"

    const int OVERWORLD_SPRITE_W = 64;
    const int OVERWORLD_SPRITE_H = 64;

    std::vector<float>demand;
    std::vector<float>consumption; // per day
    std::vector<float>production;  // per day

    int xPosition, yPosition; // Absolute position on the overworld.

    Inventory inventory;

    std::vector<Being*>availableCrew;
    std::vector<Place*>connections;

    Place(int id);
    ~Place();

    void AddAvailableCrew(Being *b);
    void DrawOnOverworld();


};

#endif // PLACE_H_INCLUDED
