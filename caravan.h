#ifndef CARAVAN_H_INCLUDED
#define CARAVAN_H_INCLUDED

#include <iostream>
#include <vector>

#include "being.h"
#include "inventory.h"
#include "placeconsts.h"
#include "road.h"
#include "place.h"

class Caravan
{
    bool active;

    bool atPlace;
    int whichPlace;

    bool onRoad; // As opposed to at a city or other landmark, for overworld drawing purposes.
    int whichRoad;
    bool reverseRoad;
    unsigned currentWaypoint;
    unsigned nextWaypoint;
    float distanceToWaypoint;

    //std::vector<float>xPosition;
    //std::vector<float>yPosition;

    float weight, maxWeight;

    int overworldXPosition;
    int overworldYPosition;

public:
    Caravan();
    ~Caravan();

    Inventory inventory;

    std::vector<Being*>members;
    Being*caravanLeader;


    void SetActive(bool a);
    void MoveToPlace(Place *p);
    void MoveToRoad(Road *r, bool isEndpointA);
    void DrawToOverworld();

    bool IsActive();

    void AddMember(Being *b);
    //void SetLeader(Being *b);

};

#endif // CARAVAN_H_INCLUDED
