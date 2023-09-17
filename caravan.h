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
#include "trademission.h"
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
    TradeMission tradeMission;

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
    int currentTimeAtPlace, thresholdTimeAtPlace;
    const int MIN_TIME_AT_PLACE = 50;
    const int MAX_TIME_AT_PLACE = 100;

/// Coins and Travel Supplies
    float coins;
    float travelSupplies;

/// Inventory
    Inventory inventory;
    float cargoWeight, cargoWeightMax; // Just have everything weigh 1 for now.

/// Trade records
    std::vector<TradeRecord*>tradeRecords;
    const unsigned tradeRecordsMaxElements = 9;

/// Bubbles
    const float bubblePadding = TILE_W/4;
    const float bubbleCornerRadius = 8;

    const float inventoryBubbleDrawX = SCREEN_W*1/40;
    const float inventoryBubbleDrawY = SCREEN_H*9/40;
    const float inventoryBubbleRowSpacing = BUILTIN_TEXT_HEIGHT;
    const float inventoryBubbleBaseCols = 6;
    const float inventoryBubbleBaseRows = 1;
    unsigned inventoryBubbleNumCols;
    unsigned inventoryBubbleNumRows;
    float inventoryBubbleWidth, inventoryBubbleHeight;

    const float tradeRecordsBubbleDrawX = SCREEN_W*1/40;
    const float tradeRecordsBubbleDrawY = SCREEN_H*15/40;
    const float tradeRecordsBubbleRowSpacing = BUILTIN_TEXT_HEIGHT;
    const unsigned tradeRecordsBubbleBaseRows = 1;
    const float tradeRecordsBubbleWidth = TILE_W*6;
    unsigned tradeRecordsBubbleNumRows;
    float tradeRecordsBubbleHeight;

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
    void ProgressTradeMission();

    int DetermineMostSuitableTradeDestination();
    void LoadGenericTradeMission();
    void UnloadTradeMission();

    void OverworldLogic();
    void SellCargo();
    void BuyCargo();
    void BuyTravelSupplies();

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
    void AddTradeRecord(int il, float ilq, int ig, float igq, int loc);

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
