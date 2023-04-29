#ifndef CARAVAN_H_INCLUDED
#define CARAVAN_H_INCLUDED

#include <iostream>
#include <vector>
#include <random>

#include "being.h"
#include "inventory.h"
#include "placeindex.h"
#include "road.h"
#include "place.h"
#include "worldgraph.h"

/// Dependencies
class Place; // Circular

class Caravan
{
public:
    static std::vector<Caravan*>caravans;

/// State
    bool active;
/// Roster
    std::vector<Being*>members;
    Being*caravanLeader;
/// Pathfinding
    WorldGraph worldGraph;
    int pathfindingDestination; /// Later modify to support multiple objectives in a priority queue.


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
    int roadDestination;
    float distanceFromNextWaypoint; // How much travel remains to reach next waypoint.
    float timeToNextWaypoint; // How much travel time remains to reach next waypoint.
    float distanceFromRoadsEnd;
    float roadSegmentLength;
    float overworldXPosition, overworldYPosition;
    float overworldXDestination, overworldYDestination;

    float travelSpeed;

/// Place activities
    int currentTimeAtPlace, thresholdTimeAtPlace;
    const int MIN_TIME_AT_PLACE = 100;
    const int MAX_TIME_AT_PLACE = 500;


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

    void OverworldLogic();
/// Inventory functions

/// Drawing functions
    void DrawSpriteOnOverworld();
    void DrawActivity(float x, float y);
};

#endif // CARAVAN_H_INCLUDED
