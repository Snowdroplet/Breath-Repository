#include "traderecord.h"

TradeRecord::TradeRecord(int il, float ilq, int ig, float igq, int loc)
{
    itemLost = il;
    itemLostQuantity = ilq;

    itemGained = ig;
    itemGainedQuantity = igq;

    tradeLocation = loc;
}

TradeRecord::~TradeRecord()
{

}
