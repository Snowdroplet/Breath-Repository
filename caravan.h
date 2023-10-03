#ifndef CARAVAN_H_INCLUDED
#define CARAVAN_H_INCLUDED

#include <iostream>
#include <vector>
#include <random>

#include "colorindex.h"

#include "being.h"
#include "inventory.h"
#include "placeindex.h"
#include "road.h"
#include "place.h"
#include "worldgraph.h"
#include "traderecord.h"


/// Dependencies
class Place; // Circular

class Caravan
{
public:
    static std::vector<Caravan*>caravans;

/// State
    bool active;
    int hometownID;
    Place*hometownPointer;

/// Roster
    std::vector<Being*>members;
    Being*caravanLeader;

/// Objectives: Pathfinding
    WorldGraph worldGraph;
    int pathfindingDestination; /// Later modify to support multiple objectives in a priority queue.
/// Objectives: Recruiting
    //RecruitingMission recruitingMission;
/// Objectives: Trading

/// Location
    bool atPlace;
    Place *whichPlace;
    bool atHome;
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
    int currentHoursAtPlace, thresholdHoursAtPlace;
    const int MIN_HOURS_AT_PLACE = 4;
    const int MAX_HOURS_AT_PLACE = 10;

/// Inventory
    Inventory inventory;
    float cargoWeight, cargoWeightMax; // Just have everything weigh 1 for now.

/// Trade records
    std::vector<TradeRecord*>tradeRecords;
    const unsigned tradeRecordsMaxRows = 9;

/// Bubbles
    const float bubblePadding = TILE_W/4;
    const float bubbleCornerRadius = 8;

    const float inventoryBubbleDrawX = SCREEN_W*1/40;
    const float inventoryBubbleDrawY = SCREEN_H*8/40;
    const float inventoryBubbleRowSpacing = BUILTIN_TEXT_HEIGHT;
    const float inventoryBubbleBaseCols = 7;
    const float inventoryBubbleBaseRows = 1;
    unsigned inventoryBubbleNumCols;
    unsigned inventoryBubbleNumRows;
    float inventoryBubbleWidth, inventoryBubbleHeight;

    const float tradeRecordsBubbleDrawX = SCREEN_W*1/40;
    const float tradeRecordsBubbleDrawY = SCREEN_H*14/40;
    const float tradeRecordsBubbleRowSpacing = BUILTIN_TEXT_HEIGHT;
    const unsigned tradeRecordsBubbleBaseRows = 1;
    const float tradeRecordsBubbleWidth = TILE_W*7;
    unsigned tradeRecordsBubbleNumRows;
    const float tradeRecordsBubbleNumIconCols = 4;
    float tradeRecordsBubbleHeight;
    const float tradeRecordsBubblePlaceNameWidth = TILE_W*3;

    const float pathfindingBubbleColSpacing = TILE_W;
    const float pathfindingBubbleRowSpacing = BUILTIN_TEXT_HEIGHT;
    const float pathfindingBubbleDrawX = SCREEN_W*1/40;
    const float pathfindingBubbleDrawY = SCREEN_H*35/40;
    const unsigned pathfindingBubbleBaseCols = 1;
    const unsigned pathfindingBubbleBaseRows = 1;
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
    void SetHometown(int which);

/// Mission, trade and movement functions
    int SelectRandomTradeDestination();

    void OverworldLogic();

/// Location functions
    void UpdateTravelSpeed();
    void MoveToPlace(Place *p);
    void MoveToRoad(Road *r, bool isReverseRoad);
    void MoveToRoadSegment(int a, bool isReverseRoad); // Must first have index of waypoints set in MoveToRoad();

    void UpdateOverworldPosition();

/// Inventory functions
    void UpdateCargoWeight();
    void UpdateCargoWeightMax();

    void AddInventoryStock(int a, float b);
    void RemoveInventoryStock(int a, float b);
    void SetInventoryStock(int a, float b);

/// Trade record functions

    void AddTradeRecord(int location);
    void UpdateTradeRecordQuantities(int whichItem, int change);

    void CheckTradeRecordsRowLimit();

/// Bubble functions
    void UpdateInventoryBubble();
    void UpdatePathfindingBubble();
    void UpdateTradeRecordsBubble();

/// Drawing functions
    void DrawSpriteOnOverworld();
    void DrawActivity(float x, float y);
    void DrawInventoryBubble();
    void DrawTradeRecordsBubble();
    void DrawPathfindingBubble();
};

#endif // CARAVAN_H_INCLUDED
