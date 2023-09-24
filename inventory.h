#ifndef INVENTORY_H_INCLUDED
#define INVENTORY_H_INCLUDED

#include <map>
#include <iterator>

#include "inventoryindex.h"

#include "UI.h"
#include "resource.h"

/*

const int IT_RANGE_FIRST = 0;
const int IT_RANGE_LAST = 1;

const int inventoryRange[UI_BARTER_NUM_TABS][2] =
{
    {IT_BERRIES, IT_ETHER},  // Plant
    {IT_CLAY, IT_METEORITE},  // Mineral
    {IT_BEAST_BLOOD, IT_CHITIN},  // Beast
    {IT_ALCOHOL, IT_CLOCKWORK},  // Artificial
    {IT_SALVE, IT_AUTOMATON}, // Trade
    {IT_WAYBREAD, IT_CURE_CORRUPTION}  // Tools
};

*/

struct Inventory
{
    std::map<int,float>cargo;
    //std::map<int,float>cargoInTab;

    Inventory();
    ~Inventory();

    void SetStock(int a, float b);
    void AddStock(int a, float b);
    void RemoveStock(int a, float b);

    //void DrawVertical(int rows, float x, float y);
    //void DrawHorizontal(int cols, float x, float y);

    //void RefreshCargoInTab();
    //int GetItemTypeAtInput(unsigned input);


};

#endif // INVENTORY_H_INCLUDED
