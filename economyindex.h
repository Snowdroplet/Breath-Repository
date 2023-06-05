#ifndef ECONOMYINDEX_H_INCLUDED
#define ECONOMYINDEX_H_INCLUDED

#include <array>
#include <map>

#include "inventoryindex.h"
#include "industryindex.h"

enum enumStandardsOfLiving
{
    LIVING_DESTITUTE = 0,   // City has < 0.5x its maitainence
    LIVING_POOR = 1,        // City has < 1x of its maintainence
    LIVING_COMFORTABLE = 2, // City has 1x of its maintainence
    LIVING_WEALTHY = 3,     // City has 3x of its maintainence
    LIVING_PROFLIGATE = 4   // City has 10x of its maintaienece
};
const int LIVING_MARKER_FIRST = LIVING_DESTITUTE;
const int LIVING_MARKER_LAST = LIVING_PROFLIGATE;

const std::map<int, std::array<int,LIVING_MARKER_LAST+1>>economyBaseMaintainenceConsumptionRate = // Also known as "household consumption", as opposed to industrial consumption
{
    // For an average person (common role, generic ancestry)
    // This accounts for "excess consumption" beyond basic needs like food, essentially "wasting" a unit to maintain standard of living.
    // Values are in hours between consumption of 1 unit.
                    //D     P     C     W     P
    {IT_MEAT,        {9999, 9999, 168,  36,   24  }},
    {IT_COLD_BREATH, {9999, 9999, 9999, 72,   24  }},
    {IT_CONTRACT,    {9999, 9999, 720,  168,  48  }},
    {IT_SPELLBOOK,   {9999, 9999, 9999, 720,  168 }},
    {IT_RICE,        {9999, 720,  168,  48,   24  }},
    {IT_ALCOHOL,     {336,  72,   96,   48,   24  }},
    {IT_MUSHROOMS,   {9999, 9999, 96,   72,   24  }},
    {IT_HERBS,       {9999, 9999, 168,  48,   24  }},
    {IT_MEDICINE,    {9999, 9999, 9999, 720,  168 }},
    {IT_SPICE,       {9999, 9999, 720,  168,  48  }},
    {IT_CLAY,        {9999, 9999, 2880, 336,  144 }},
    {IT_POTTERY,     {9999, 4320, 720,  336,  72  }},
    {IT_SILVER,      {9999, 9999, 9999, 2160, 336 }},
    {IT_JEWELRY,     {9999, 9999, 9999, 1440, 336 }},
    {IT_LEYSTONE,    {9999, 2160, 336,  72,   24  }},
    {IT_CLOCKWORK,   {9999, 9999, 9999, 2880, 720 }},
    {IT_AUTOMATON,   {9999, 9999, 9999, 8760, 2160}}
};


const std::map<int, std::array<float, EXP_MARKER_LAST+1>>economyRoleMaintainenceConsumptionQuantity =
{
//EXP_COMMON = 0, EXP_HUNT = 1, EXP_FARM = 2, EXP_MINE = 3, EXP_ALCHEMY = 4, EXP_SORCERY = 5, EXP_CRAFT = 6, EXP_MECHANICS = 7
//                      Com  Hunt  Farm  Mine  Alch   Sorc  Cra   Mech
    {IT_MEAT,        {   1,  1.5,  1.5,  1.5,    1,    1,    1,    1}},
    {IT_COLD_BREATH, {0.01,    1, 0.01, 0.01, 0.01,    1, 0.01, 0.01}},
    {IT_CONTRACT,    {0.01,  0.5, 0.01, 0.01,    1,    2,  0.5,  0.5}},
    {IT_SPELLBOOK,   {0.01, 0.01, 0.01, 0.01,    1,    1, 0.25, 0.25}},
    {IT_RICE,        {   1,  1.5,  1.5,  1.5,    1,    1,    1,    1}},
    {IT_ALCOHOL,     {   1,  1.5,  1.5,  1.5,    1,    1,    1,    1}},
    {IT_MUSHROOMS,   {   1,    1,    1,    1,  1.5,  1.5,    1,    1}},
    {IT_HERBS,       { 0.5,    1,    2,    1,    2,    1,    1,    1}},
    {IT_MEDICINE,    {   1,    3,    1,    2,    1,    1,    1,    1}},
    {IT_SPICE,       { 0.5,    1,    1,    1,    1,    1,    1,    1}},
    {IT_CLAY,        {0.01, 0.01,  0.5,    1, 0.01,    2,    2, 0.01}},
    {IT_POTTERY,     { 0.5,    1,    1,  1.5,    1,    1,    2,    1}},
    {IT_SILVER,      { 0.5,    1,    1,    1,    1,  1.5,  1.5,  1.5}},
    {IT_JEWELRY,     { 0.5,    1,    1,    1,    1,    2,  1.5,  1.5}},
    {IT_LEYSTONE,    {0.01,  1.5, 0.01,  1.5, 0.01,    1, 0.01,    1}},
    {IT_CLOCKWORK,   {0.01, 0.01,  0.5,  0.5,  0.5,  0.5, 0.01,    2}},
    {IT_AUTOMATON,   {0.01, 0.01,  0.5,  0.5, 0.25, 0.25, 0.01,    1}}
};

/// Better just keep a blank copy of the array around just in case
/*
     IT_MEAT,        { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_COLD_BREATH, { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_CONTRACT,    { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_SPELLBOOK,   { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_RICE,        { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_ALCOHOL,     { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_MUSHROOMS,   { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_HERBS,       { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_MEDICINE,    { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_SPICE,       { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_CLAY,        { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_POTTERY,     { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_SILVER,      { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_JEWELRY,     { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_LEYSTONE,    { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_CLOCKWORK,   { 0.0, 0.0, 0.0, 0.0, 0.0}},
    {IT_AUTOMATON,   { 0.0, 0.0, 0.0, 0.0, 0.0}}
*/

#endif // ECONOMYINDEX_H_INCLUDED
