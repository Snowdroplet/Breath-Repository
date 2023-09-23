#include "traderecord.h"

TradeRecord::TradeRecord(int whichLocation)
{
    numRows = baseRows;

    location = whichLocation;
}

/*
TradeRecord::TradeRecord(int il, float ilq, int ig, float igq, int loc)
{
    itemLost = il;
    itemLostQuantity = ilq;

    itemGained = ig;
    itemGainedQuantity = igq;

    tradeLocation = loc;
}
*/

TradeRecord::~TradeRecord()
{
    tradeQuantities.clear();
}

void TradeRecord::ChangeEntry(int whichItem, int change)
{
    if(tradeQuantities.count(whichItem) > 0)
        tradeQuantities[whichItem] += change;

    else
        tradeQuantities[whichItem] = change;

    numRows = 1 + (tradeQuantities.size() / maxCols); // truncates decimal


}
