#include "traderecord.h"

TradeRecord::TradeRecord(int whichLocation)
{
    numRows = baseRows;

    location = whichLocation;
}

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

    numRows = 1 + ((tradeQuantities.size()-1) / maxCols); // truncates decimal

    if(numRows < 1)
        numRows = 1;
}
