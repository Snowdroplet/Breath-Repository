#ifndef TRADERECORD_H_INCLUDED
#define TRADERECORD_H_INCLUDED

const int TRADE_RECORD_LOST_NOTHING = -1;
const int TRADE_RECORD_GAINED_NOTHING = -1;

class TradeRecord
{
public:
    int itemLost;
    float itemLostQuantity;

    int itemGained;
    float itemGainedQuantity;

    int tradeLocation;

public:
    TradeRecord(int il, float ilq, int ig, float igq, int loc);
    ~TradeRecord();
};

#endif // TRADERECORD_H_INCLUDED
