#include "trademission.h"

TradeMission::TradeMission()
{
    //std::cout << "Trade mission initialized" << std::endl;
    missionActive = false;
    missionComplete = false;

    onReturnTrip = false;
}

TradeMission::~TradeMission()
{

}

void TradeMission::ProgressMission()
{

}

void TradeMission::SetTradeDestination(int dest){tradeDestination = dest;}
