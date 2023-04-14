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
public:
/// State
    bool active;

/// Roster
    std::vector<Being*>members;
    Being*caravanLeader;

/// Location
    bool atPlace;
    //int whichPlace;
    Place *whichPlace;

    bool onRoad; // As opposed to at a city or other landmark, for overworld drawing purposes.
    //int whichRoad;
    Road *whichRoad;
    bool reverseRoad;
    bool atRoadsEnd;
    unsigned currentWaypoint;
    unsigned nextWaypoint;
    unsigned finalWaypoint;
    float distanceFromNextWaypoint; // How much travel remains to reach next waypoint.

    float overworldXPosition;
    float overworldYPosition;

    float travelSpeed;

    Caravan();
    ~Caravan();

    void UpdateOverworldPosition();

/// Inventory
    Inventory inventory;
    float weight, maxWeight;

    void SetActive(bool a);
    void MoveToPlace(Place *p);
    void MoveToRoad(Road *r, bool isEndpointA);

/// Manipulate roster
    void AddMember(Being *b);
    //void SwapLeader(Being *b);
    void UpdateTravelSpeed();

/// Drawing
    void DrawOnOverworld();

    bool IsActive();

};

#endif // CARAVAN_H_INCLUDED
