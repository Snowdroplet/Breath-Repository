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
    Place *whichPlace;
    bool onRoad; // As opposed to at a city or other landmark, for overworld drawing purposes.
    Road *whichRoad;
    bool reverseRoad;
    bool atRoadsEnd;
    int currentWaypoint;
    int nextWaypoint;
    int finalWaypoint;
    float distanceFromNextWaypoint; // How much travel remains to reach next waypoint.
    float distanceFromRoadsEnd;
    float roadSegmentLength;
    float overworldXPosition;
    float overworldYPosition;
    float overworldXDestination;
    float overworldYDestination;

    float travelSpeed;
/// Inventory
    Inventory inventory;
    float weight, maxWeight;

/// Constructor
    Caravan();
    ~Caravan();
/// State functions
    bool IsActive();
/// Roster functions
    void AddMember(Being *b);
    //void SwapLeader(Being *b);
/// State functions
    void SetActive(bool a);
/// Location functions
    void UpdateTravelSpeed();
    void MoveToPlace(Place *p);
    void MoveToRoad(Road *r, bool isReverseRoad);
    void MoveToRoadSegment(int a, bool isReverseRoad); // Must first have index of waypoints set in MoveToRoad();

    void UpdateOverworldPosition();

    void Travel();
/// Inventory functions

/// Drawing functions
    void DrawOnOverworld();
};

#endif // CARAVAN_H_INCLUDED
