#ifndef CARAVAN_H_INCLUDED
#define CARAVAN_H_INCLUDED

#include <iostream>
#include <vector>
#include <random>

#include "colorindex.h"
#include "lockon.h"

#include "being.h"
#include "inventory.h"
#include "placeindex.h"
#include "road.h"
#include "place.h"
#include "worldgraph.h"
#include "traderecord.h"

#include "flyingtext.h"

#include "bubbleview.h"


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
    bool crewBubbleNeedsUpdate;
    bool inventoryBubbleNeedsUpdate;
    bool tradeRecordsBubbleNeedsUpdate;
    bool pathfindingBubbleNeedsUpdate;

    /*
    float caravanCrewBubbleWidth;

    unsigned caravanInventoryBubbleNumCols;
    unsigned caravanInventoryBubbleNumRows;
    float caravanInventoryBubbleWidth, caravanInventoryBubbleHeight;
    */


/// Constructor
    Caravan();
    ~Caravan();
/// State functions
    bool IsActive();
/// Roster functions
    void AddMember(Being *b);
    //void SwapLeader(Being *b);
    void RemoveMember(Being *b);

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
    void AllBubblesNeedUpdate();

/// Drawing functions
    void DrawSpriteOnOverworld();
    void DrawActivity(float x, float y);
    void DrawCaravanCrewBubble();
    //void DrawCaravanTravelViewBubble();
    void DrawCaravanInventoryBubble();
    void DrawCaravanTradeRecordsBubble();
    void DrawCaravanPathfindingBubble();
};

#endif // CARAVAN_H_INCLUDED
