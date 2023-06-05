#ifndef TRADEMISSION_H_INCLUDED
#define TRADEMISSION_H_INCLUDED

#include <iostream>
#include <map>

/// Distance modifier: Take into account how long it'll take to reach the target city *and return home,*
/// and how many consumption cycles will have passed for relevant items over that period.

class TradeMission
{
public:
    bool missionActive; // Whether to run mission logic.

    int tradeDestination; // Set by SetTradeDestination in Place::DetermineMostSuitableTradeLocation

    bool sellMission; // Complete all sales to complete mission.
    bool buyMission; // Complete all purchases to complete mission.
    bool missionComplete; // Return home if mission is complete. (Returned home, or bought/sold all required items)

    bool onReturnTrip;

    std::map<int, float>sellingItems; // <index of item, number to complete objective>.
    float sellingMinimumProfitPercentage; // <index, minimum sell value>. Items to be sold for at least minimum sell value; not less.

    std::map<int, float>buyingItems; // <index of item, number to complete objective>.
    float buyingMinimumProfitPercentage; // Items to purchase. <index, maximum buy value>. Items to be bought for at least maximum sell value; not more.

    TradeMission();
    ~TradeMission();

    void ProgressMission();
    void SetTradeDestination(int dest);
    void TerminateMission(); // Complete mission prematurely (and return home).
};

#endif // TRADEMISSION_H_INCLUDED
