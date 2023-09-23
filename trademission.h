#ifndef TRADEMISSION_H_INCLUDED
#define TRADEMISSION_H_INCLUDED

#include <iostream>
#include <map>

/// Distance modifier: Take into account how long it'll take to reach the target city *and return home,*
/// and how many consumption cycles will have passed for relevant items over that period.

enum enumMissionType
{
    TRADE_MISSION_TYPE_GENERIC, // Dealing in the city's full breadth of surplus goods, proportional to surplus ratio. Buy and sell.
    TRADE_MISSION_TYPE_PICKUP_ORDER, // Buying goods at a specific location according to predetermined purchase order.
    TRADE_MISSION_TYPE_DROPOFF_ORDER // Selling goods at a specific location according to predetermined sales order.
};

class TradeMission
{
public:
    int missionType;

    bool missionActive; // Whether to run mission logic.

    int tradeDestination; // Set by SetTradeDestination in Place::DetermineMostSuitableTradeLocation

    bool missionComplete; // Return home if mission is complete. (Returned home, or bought/sold all required items)

    bool onReturnTrip;

    TradeMission();
    ~TradeMission();

    void ProgressMission();
    void SetMissionType(int whichMissionType);
    void SetTradeDestination(int dest);
    void TerminateMission(); // Complete mission prematurely (and return home).
};

#endif // TRADEMISSION_H_INCLUDED
