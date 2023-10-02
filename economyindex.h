#ifndef ECONOMYINDEX_H_INCLUDED
#define ECONOMYINDEX_H_INCLUDED

#include <array>
#include <map>

#include "inventoryindex.h"
#include "industryindex.h"

const std::map<int, int>economyBaseMaintainenceConsumptionRate = // Also known as "household consumption", as opposed to industrial consumption
{
    {IT_CORPUS,   48}, {IT_PLASM,   48}, {IT_OCULUS,     48}, {IT_STRANGE_EGG,  24},
    {IT_BERRIES,  48}, {IT_HERBS,   48}, {IT_MUSHROOMS,  48}, {IT_SPICE,        24},
    {IT_CLAY,     48}, {IT_COPPER,  48}, {IT_IRON,       48}, {IT_LEYSTONE,     24},

    {IT_ALCOHOL,  72}, {IT_MEDICINE,   72}, {IT_POISON,  72}, {IT_COUNTERAGENT, 168},
    {IT_EFFIGY,   72}, {IT_CONTRACT,   72}, {IT_VESSEL,  72}, {IT_GRIMOIRE,    168},
    {IT_FUEL,     72}, {IT_CLOCKWORK,  72}, {IT_TOOLS,   72}, {IT_AUTOMATON,    168}
};

#endif // ECONOMYINDEX_H_INCLUDED
