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

const std::map<int, float>economyBaseItemValue =
{
    // The intention is that base value depends on
    // on hours required for a production cycle divided by units produced per cycle
    // plus the values of all items that go into its production.

    // I initially thought to create an baseValuesInit() type function that
    // pre-calculates base values at the start of the game, but it
    // may be better to adjust those values manually for the time being
    // as economic interactions are not in their final state yet.

    /*{ITEM,     (input cost + prod hrs)/output quantity}  */

    {IT_MEAT,      (0        + 72)/10},  // 7.2

    {IT_ECTOPLASM, (0        + 96)/6},   // 16
    {IT_CONTRACT,  (16*4     + 160)/1},  // 224
    {IT_SPELLBOOK, (224*6    + 240)/1},  // 1584

    {IT_RICE,      (0        + 240)/50}, // 4.8
    {IT_ALCOHOL,   (30*4.8   + 448)/25}, // 23.68

    {IT_MUSHROOMS, (0        + 360)/30}, // 12

    {IT_HERBS,     (0        + 480)/20}, // 24
    {IT_MEDICINE,  (24*2     + 120)/2},  // 84

    {IT_SPICE,     (0        + 600)/10}, // 60

    {IT_CLAY,      (0        + 60)/10},  // 6
    {IT_POTTERY,   (6*4      + 120)/1},  // 144

    {IT_SILVER,    (0        + 120)/5},  // 24
    {IT_JEWELRY,   (24*2     + 240)/1},  // 264

    {IT_LEYSTONE,  (0        + 180)/6},  // 30
    {IT_CLOCKWORK, (30*5     + 352)/5},  // 100.4
    {IT_AUTOMATON, (100.4*50 + 704)/1}   // 5724
};

const std::map<int, float>economyItemBaseQuantity =
{
    // Volume at which item is traded at 100% of base value, before any other modifiers.
    // This number should be related to the volume of goods that an industry can produce per production cycle.

    //{ITEM, production output quantity * 20 }

    {IT_MEAT,      200},

    {IT_ECTOPLASM, 120},
    {IT_CONTRACT,  20},
    {IT_SPELLBOOK, 20},

    {IT_RICE,      1000},
    {IT_ALCOHOL,   500},

    {IT_MUSHROOMS, 600},

    {IT_HERBS,     400},
    {IT_MEDICINE,  40},

    {IT_SPICE,     200},

    {IT_CLAY,      200},
    {IT_POTTERY,   20},

    {IT_SILVER,    100},
    {IT_JEWELRY,   20},

    {IT_LEYSTONE,  120},
    {IT_CLOCKWORK, 100},
    {IT_AUTOMATON, 20}

};

const std::map<int, std::array<int,LIVING_MARKER_LAST+1>>economyBaseMaintainenceConsumptionRate = // Also known as "household consumption", as opposed to industrial consumption
{
    // For an average person (common role, generic ancestry)
    // This accounts for "excess consumption" beyond basic needs like food, essentially "wasting" a unit to maintain standard of living.
    // Values are in hours between consumption of 1 unit.
                    //D     P     C     W     P
    {IT_MEAT,        {9999, 9999, 168,  36,   24  }},
    {IT_ECTOPLASM,   {9999, 9999, 9999, 72,   24  }},
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
    {IT_ECTOPLASM,   {0.01,    1, 0.01, 0.01, 0.01,    1, 0.01, 0.01}},
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
    {IT_ECTOPLASM,   { 0.0, 0.0, 0.0, 0.0, 0.0}},
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
