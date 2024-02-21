#ifndef ECONOMYINDEX_H_INCLUDED
#define ECONOMYINDEX_H_INCLUDED

#include <array>
#include <map>

#include "inventoryindex.h"
#include "industryindex.h"

const std::map<int, int>economyBaseMaintainenceConsumptionRate = // Also known as "household consumption", as opposed to industrial consumption
{
    {InventoryIndex::IT_CORPUS,   48}, {InventoryIndex::IT_PLASM,   48}, {InventoryIndex::IT_OCULUS,     48}, {InventoryIndex::IT_DORMANT_EGG,  24},
    {InventoryIndex::IT_BERRIES,  48}, {InventoryIndex::IT_HERBS,   48}, {InventoryIndex::IT_MUSHROOMS,  48}, {InventoryIndex::IT_SPICE,        24},
    {InventoryIndex::IT_CLAY,     48}, {InventoryIndex::IT_COPPER,  48}, {InventoryIndex::IT_IRON,       48}, {InventoryIndex::IT_LEYSTONE,     24},

    {InventoryIndex::IT_BRANDY,   72}, {InventoryIndex::IT_MEDICINE,   72}, {InventoryIndex::IT_ETHER,   72}, {InventoryIndex::IT_COUNTERAGENT, 168},
    {InventoryIndex::IT_EFFIGY,   72}, {InventoryIndex::IT_CONTRACT,   72}, {InventoryIndex::IT_VESSEL,  72}, {InventoryIndex::IT_GRIMOIRE,     168},
    {InventoryIndex::IT_FUEL,     72}, {InventoryIndex::IT_CLOCKWORK,  72}, {InventoryIndex::IT_TOOLS,   72}, {InventoryIndex::IT_AUTOMATON,    168}
};

#endif // ECONOMYINDEX_H_INCLUDED
