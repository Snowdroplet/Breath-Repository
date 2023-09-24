#ifndef TRADERECORD_H_INCLUDED
#define TRADERECORD_H_INCLUDED

#include <map>

class TradeRecord
{
public:
    std::map<int, int>tradeQuantities;
    const unsigned baseRows = 1;
    unsigned numRows;

    const unsigned maxCols = 4;

    int location;

public:

    TradeRecord(int whichLocation);
    ~TradeRecord();

    void ChangeEntry(int whichItem, int change);

};

#endif // TRADERECORD_H_INCLUDED
