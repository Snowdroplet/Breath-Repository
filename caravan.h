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

/// Objectives: Pathfinding
    WorldGraph worldGraph;
    int pathfindingDestination; /// Later modify to support multiple objectives in a priority queue.
/// Objectives: Recruiting
    std::map<int,int>recruitingQualifications;
/// Objectives: Purchasing

/// Objectives:
    bool onReturnTrip;

/// Objectives: Investment

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
    const int MIN_TIME_AT_PLACE = 50;
    const int MAX_TIME_AT_PLACE = 100;

/// Inventory
    Inventory inventory;
    float weight, maxWeight;

/// Bubbles
    const float bubblePadding = TILE_W/4;
    const float bubbleCornerRadius = 8;

    const float inventoryBubbleDrawX = SCREEN_W*8/40;
    const float inventoryBubbleDrawY = SCREEN_H*10/40;
    const float inventoryBubbleRowSpacing = BUILTIN_TEXT_HEIGHT;
    const float inventoryBubbleBaseCols = 5;
    const float inventoryBubbleBaseRows = 1;
    unsigned inventoryBubbleNumCols;
    unsigned inventoryBubbleNumRows;
    float inventoryBubbleWidth, inventoryBubbleHeight;

    const float pathfindingBubbleColSpacing = TILE_W;
    const float pathfindingBubbleRowSpacing = BUILTIN_TEXT_HEIGHT;
    const float pathfindingBubbleDrawX = TILE_W;
    const float pathfindingBubbleDrawY = SCREEN_H - 2*TILE_H - 2*pathfindingBubbleRowSpacing - TILE_H;
    const float pathfindingBubbleBaseCols = 1;
    const float pathfindingBubbleBaseRows = 1;
    unsigned pathfindingBubbleNumCols;
    unsigned pathfindingBubbleNumRows;
    float pathfindingBubbleWidth, pathfindingBubbleHeight;

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
    void AddInventoryStock(int a, float b);
    void RemoveInventoryStock(int a, float b);
    void SetInventoryStock(int a, float b);

/// Bubble functions
    void UpdateInventoryBubble();
    void UpdatePathfindingBubble();

/// Drawing functions
    void DrawSpriteOnOverworld();
    void DrawActivity(float x, float y);
    void DrawInventoryBubble();
    void DrawPathfindingBubble();
};

#endif // CARAVAN_H_INCLUDED
