#ifndef INDUSTRYINDEX_H_INCLUDED
#define INDUSTRYINDEX_H_INCLUDED

#include <map>

#include "inventoryindex.h"

enum enumIndustries
{
    IND_HUNT_CORPUS  = 0, IND_HUNT_PLASM  = 1, IND_HUNT_OCULUS    = 2, IND_HUNT_DORMANT_EGG = 3,
    IND_FARM_BERRIES = 4, IND_FARM_HERBS  = 5, IND_FARM_MUSHROOMS = 6, IND_FARM_SPICE       = 7,
    IND_MINE_CLAY    = 8, IND_MINE_COPPER = 9, IND_MINE_IRON     = 10, IND_MINE_LEYSTONE   = 11,

    IND_ALCHEMY_BRANDY = 12, IND_ALCHEMY_MEDICINE  = 13, IND_ALCHEMY_ETHER = 14, IND_ALCHEMY_COUNTERAGENT = 15,
    IND_SORCERY_EFFIGY  = 16, IND_SORCERY_CONTRACT  = 17, IND_SORCERY_VESSEL = 18, IND_SORCERY_GRIMOIRE     = 19,
    IND_MACHINE_FUEL    = 20, IND_MACHINE_CLOCKWORK = 21, IND_MACHINE_TOOLS  = 22, IND_MACHINE_AUTOMATON    = 23
};

const int IND_MARKER_FIRST = IND_HUNT_CORPUS;
const int IND_MARKER_LAST = IND_MACHINE_AUTOMATON;


enum enumExpertiseTypes {EXP_COMMON = 0, EXP_HUNT = 1, EXP_FARM = 2, EXP_MINE = 3, EXP_ALCHEMY = 4, EXP_SORCERY = 5, EXP_MECHANICS = 6};
const int EXP_MARKER_FIRST = EXP_COMMON;
const int EXP_MARKER_LAST = EXP_MECHANICS;

const std::map<int, float>baseProductionToComplete = // In hours
{
    {IND_HUNT_CORPUS,  4}, {IND_HUNT_PLASM,  4}, {IND_HUNT_OCULUS,    4}, {IND_HUNT_DORMANT_EGG, 16},
    {IND_FARM_BERRIES, 4}, {IND_FARM_HERBS,  4}, {IND_FARM_MUSHROOMS, 4}, {IND_FARM_SPICE,       16},
    {IND_MINE_CLAY,    4}, {IND_MINE_COPPER, 4}, {IND_MINE_IRON,      4}, {IND_MINE_LEYSTONE,    16},

    {IND_ALCHEMY_BRANDY, 8}, {IND_ALCHEMY_MEDICINE,  8}, {IND_ALCHEMY_ETHER, 8}, {IND_ALCHEMY_COUNTERAGENT, 32},
    {IND_SORCERY_EFFIGY,  8}, {IND_SORCERY_CONTRACT,  8}, {IND_SORCERY_VESSEL, 8}, {IND_SORCERY_GRIMOIRE,     32},
    {IND_MACHINE_FUEL,    8}, {IND_MACHINE_CLOCKWORK, 8}, {IND_MACHINE_TOOLS,  8}, {IND_MACHINE_AUTOMATON,    32}
};

const std::map<int, std::map<int,float>>baseJobInputs =
{
    {IND_HUNT_CORPUS,      { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },
    {IND_HUNT_PLASM,       { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },
    {IND_HUNT_OCULUS,      { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },
    {IND_HUNT_DORMANT_EGG, { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },

    {IND_FARM_BERRIES,     { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },
    {IND_FARM_HERBS,       { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },
    {IND_FARM_MUSHROOMS,   { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },
    {IND_FARM_SPICE,       { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },

    {IND_MINE_CLAY,        { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },
    {IND_MINE_COPPER,      { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },
    {IND_MINE_IRON,        { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },
    {IND_MINE_LEYSTONE,    { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },

    {IND_ALCHEMY_BRANDY,      { { IT_BERRIES,   2.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_ALCHEMY_MEDICINE,     { { IT_HERBS,     2.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_ALCHEMY_ETHER,       { { IT_OCULUS,    2.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_ALCHEMY_COUNTERAGENT, { { IT_ETHER,    4.0 } /*,{ IT_X, 0.0 }*/ } },

    {IND_SORCERY_EFFIGY,       { { IT_CORPUS,    2.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_SORCERY_CONTRACT,     { { IT_PLASM,     2.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_SORCERY_VESSEL,       { { IT_CLAY,      2.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_SORCERY_GRIMOIRE,     { { IT_CONTRACT,  4.0 } /*,{ IT_X, 0.0 }*/ } },

    {IND_MACHINE_FUEL,         { { IT_MUSHROOMS, 2.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_MACHINE_CLOCKWORK,    { { IT_COPPER,    2.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_MACHINE_TOOLS,        { { IT_IRON,      2.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_MACHINE_AUTOMATON,    { { IT_CLOCKWORK, 4.0 } /*,{ IT_X, 0.0 }*/ } }
};


const std::map<int, std::map<int,float>>baseJobOutputs =
{
    {IND_HUNT_CORPUS,      { { IT_CORPUS,      1.0} /*,{ IT_X, 0.0 }*/ } },
    {IND_HUNT_PLASM,       { { IT_PLASM,       1.0} /*,{ IT_X, 0.0 }*/ } },
    {IND_HUNT_OCULUS,      { { IT_OCULUS,      1.0} /*,{ IT_X, 0.0 }*/ } },
    {IND_HUNT_DORMANT_EGG, { { IT_DORMANT_EGG, 1.0} /*,{ IT_X, 0.0 }*/ } },

    {IND_FARM_BERRIES,     { { IT_BERRIES,     1.0} /*,{ IT_X, 0.0 }*/ } },
    {IND_FARM_HERBS,       { { IT_HERBS,       1.0} /*,{ IT_X, 0.0 }*/ } },
    {IND_FARM_MUSHROOMS,   { { IT_MUSHROOMS,   1.0} /*,{ IT_X, 0.0 }*/ } },
    {IND_FARM_SPICE,       { { IT_SPICE,       1.0} /*,{ IT_X, 0.0 }*/ } },

    {IND_MINE_CLAY,        { { IT_CLAY,        1.0} /*,{ IT_X, 0.0 }*/ } },
    {IND_MINE_COPPER,      { { IT_COPPER,      1.0} /*,{ IT_X, 0.0 }*/ } },
    {IND_MINE_IRON,        { { IT_IRON,        1.0} /*,{ IT_X, 0.0 }*/ } },
    {IND_MINE_LEYSTONE,    { { IT_LEYSTONE,    1.0} /*,{ IT_X, 0.0 }*/ } },

    {IND_ALCHEMY_BRANDY,       { { IT_BRANDY,      1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_ALCHEMY_MEDICINE,     { { IT_MEDICINE,     1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_ALCHEMY_ETHER,       { { IT_ETHER,       1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_ALCHEMY_COUNTERAGENT, { { IT_COUNTERAGENT, 1.0 } /*,{ IT_X, 0.0 }*/ } },

    {IND_SORCERY_EFFIGY,       { { IT_EFFIGY,       1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_SORCERY_CONTRACT,     { { IT_CONTRACT,     1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_SORCERY_VESSEL,       { { IT_VESSEL,       1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_SORCERY_GRIMOIRE,     { { IT_GRIMOIRE,    1.0 } /*,{ IT_X, 0.0 }*/ } },

    {IND_MACHINE_FUEL,         { { IT_FUEL,         1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_MACHINE_CLOCKWORK,    { { IT_CLOCKWORK,    1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_MACHINE_TOOLS,        { { IT_TOOLS,        1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_MACHINE_AUTOMATON,    { { IT_AUTOMATON,    1.0 } /*,{ IT_X, 0.0 }*/ } }

};

#endif // INDUSTRYINDEX_H_INCLUDED
