#ifndef INDUSTRYINDEX_H_INCLUDED
#define INDUSTRYINDEX_H_INCLUDED

#include <map>

#include "inventoryindex.h"

enum enumIndustries
{
    IND_HUNT_CORPUS  = 0, IND_HUNT_PLASM  = 1, IND_HUNT_OCULUS    = 2, IND_HUNT_STRANGE_EGG = 3,
    IND_FARM_BERRIES = 4, IND_FARM_HERBS  = 5, IND_FARM_MUSHROOMS = 6, IND_FARM_SPICE       = 7,
    IND_MINE_CLAY    = 8, IND_MINE_COPPER = 9, IND_MINE_IRON     = 10, IND_MINE_LEYSTONE   = 11,

    IND_ALCHEMY_ALCOHOL = 12, IND_ALCHEMY_MEDICINE  = 13, IND_ALCHEMY_POISON = 14, IND_ALCHEMY_COUNTERAGENT = 15,
    IND_SORCERY_EFFIGY  = 16, IND_SORCERY_CONTRACT  = 17, IND_SORCERY_VESSEL = 18, IND_SORCERY_SPELLBOOK    = 19,
    IND_MACHINE_FUEL    = 20, IND_MACHINE_CLOCKWORK = 21, IND_MACHINE_TOOLS  = 22, IND_MACHINE_AUTOMATON    = 23
};

const int IND_MARKER_FIRST = IND_HUNT_CORPUS;
const int IND_MARKER_LAST = IND_MACHINE_AUTOMATON;


enum enumExpertiseTypes {EXP_COMMON = 0, EXP_HUNT = 1, EXP_FARM = 2, EXP_MINE = 3, EXP_ALCHEMY = 4, EXP_SORCERY = 5, EXP_MECHANICS = 6};
const int EXP_MARKER_FIRST = EXP_COMMON;
const int EXP_MARKER_LAST = EXP_MECHANICS;


/*
const std::map<int, std::string>industryNames =
{
    {IND_HUNT_MEAT, "Hunting Beast Flesh"},
    {IND_HUNT_ECTOPLASM, "Hunting Ectoplasm"},
    {IND_SORCERY_CONTRACT, "Binding Ectoplasm -> Contracts"},
    {IND_SORCERY_SPELLBOOK, "Binding Contracts -> Spellbooks"},
    {IND_FARM_BERRIES, "Growing Berries"},
    {IND_ALCHEMY_ALCOHOL, "Brewing Rice -> Alcohol"},
    {IND_FARM_MUSHROOMS, "Growing Mushrooms"},
    {IND_FARM_HERBS, "Cultivating Herbs"},
    {IND_ALCHEMY_MEDICINE, "Brewing Herbs -> Medicines"},
    {IND_FARM_SPICE, "Cultivating Spices"},
    {IND_MINE_CLAY, "Mining Clay"},
    {IND_SORCERY_VESSEL, "Shaping Clay -> Pottery"},
    {IND_MINE_SILVER, "Mining Silver"},
    {IND_CRAFT_JEWELRY, "Crafting Silver -> Jewelry"},
    {IND_MINE_LEYSTONE, "Mining Leystone"},
    {IND_MACHINE_CLOCKWORK, "Shaping Leystone -> Clockwork"},
    {IND_MACHINE_AUTOMATON, "Assembling Clockwork -> Automata"}
};
*/

const std::map<int, float>baseProductionToComplete = // In hours
{
    {IND_HUNT_CORPUS,  4}, {IND_HUNT_PLASM,  4}, {IND_HUNT_OCULUS,    4}, {IND_HUNT_STRANGE_EGG, 16},
    {IND_FARM_BERRIES, 4}, {IND_FARM_HERBS,  4}, {IND_FARM_MUSHROOMS, 4}, {IND_FARM_SPICE,       16},
    {IND_MINE_CLAY,    4}, {IND_MINE_COPPER, 4}, {IND_MINE_IRON,      4}, {IND_MINE_LEYSTONE,    16},

    {IND_ALCHEMY_ALCOHOL, 8}, {IND_ALCHEMY_MEDICINE,  8}, {IND_ALCHEMY_POISON, 8}, {IND_ALCHEMY_COUNTERAGENT, 32},
    {IND_SORCERY_EFFIGY,  8}, {IND_SORCERY_CONTRACT,  8}, {IND_SORCERY_VESSEL, 8}, {IND_SORCERY_SPELLBOOK,    32},
    {IND_MACHINE_FUEL,    8}, {IND_MACHINE_CLOCKWORK, 8}, {IND_MACHINE_TOOLS,  8}, {IND_MACHINE_AUTOMATON,    32}
};

const std::map<int, std::map<int,float>>baseJobInputs =
{
    {IND_HUNT_CORPUS,      { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },
    {IND_HUNT_PLASM,       { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },
    {IND_HUNT_OCULUS,      { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },
    {IND_HUNT_STRANGE_EGG, { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },

    {IND_FARM_BERRIES,     { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },
    {IND_FARM_HERBS,       { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },
    {IND_FARM_MUSHROOMS,   { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },
    {IND_FARM_SPICE,       { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },

    {IND_MINE_CLAY,        { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },
    {IND_MINE_COPPER,      { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },
    {IND_MINE_IRON,        { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },
    {IND_MINE_LEYSTONE,    { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },

    {IND_ALCHEMY_ALCOHOL,      { { IT_BERRIES,   1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_ALCHEMY_MEDICINE,     { { IT_HERBS,     1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_ALCHEMY_POISON,       { { IT_OCULUS,    1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_ALCHEMY_COUNTERAGENT, { { IT_POISON,    2.0 } /*,{ IT_X, 0.0 }*/ } },

    {IND_SORCERY_EFFIGY,       { { IT_CORPUS,    1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_SORCERY_CONTRACT,     { { IT_PLASM,     1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_SORCERY_VESSEL,       { { IT_CLAY,      1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_SORCERY_SPELLBOOK,    { { IT_CONTRACT,  2.0 } /*,{ IT_X, 0.0 }*/ } },

    {IND_MACHINE_FUEL,         { { IT_MUSHROOMS, 1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_MACHINE_CLOCKWORK,    { { IT_COPPER,    1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_MACHINE_TOOLS,        { { IT_IRON,      1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_MACHINE_AUTOMATON,    { { IT_CLOCKWORK, 2.0 } /*,{ IT_X, 0.0 }*/ } }
};


const std::map<int, std::map<int,float>>baseJobOutputs =
{
    {IND_HUNT_CORPUS,      { { IT_CORPUS,      1.0} /*,{ IT_X, 0.0 }*/ } },
    {IND_HUNT_PLASM,       { { IT_PLASM,       1.0} /*,{ IT_X, 0.0 }*/ } },
    {IND_HUNT_OCULUS,      { { IT_OCULUS,      1.0} /*,{ IT_X, 0.0 }*/ } },
    {IND_HUNT_STRANGE_EGG, { { IT_STRANGE_EGG, 1.0} /*,{ IT_X, 0.0 }*/ } },

    {IND_FARM_BERRIES,     { { IT_BERRIES,     1.0} /*,{ IT_X, 0.0 }*/ } },
    {IND_FARM_HERBS,       { { IT_HERBS,       1.0} /*,{ IT_X, 0.0 }*/ } },
    {IND_FARM_MUSHROOMS,   { { IT_MUSHROOMS,   1.0} /*,{ IT_X, 0.0 }*/ } },
    {IND_FARM_SPICE,       { { IT_SPICE,       1.0} /*,{ IT_X, 0.0 }*/ } },

    {IND_MINE_CLAY,        { { IT_CLAY,        1.0} /*,{ IT_X, 0.0 }*/ } },
    {IND_MINE_COPPER,      { { IT_COPPER,      1.0} /*,{ IT_X, 0.0 }*/ } },
    {IND_MINE_IRON,        { { IT_IRON,        1.0} /*,{ IT_X, 0.0 }*/ } },
    {IND_MINE_LEYSTONE,    { { IT_LEYSTONE,    1.0} /*,{ IT_X, 0.0 }*/ } },

    {IND_ALCHEMY_ALCOHOL,      { { IT_ALCOHOL,      1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_ALCHEMY_MEDICINE,     { { IT_MEDICINE,     1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_ALCHEMY_POISON,       { { IT_POISON,       1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_ALCHEMY_COUNTERAGENT, { { IT_COUNTERAGENT, 1.0 } /*,{ IT_X, 0.0 }*/ } },

    {IND_SORCERY_EFFIGY,       { { IT_EFFIGY,       1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_SORCERY_CONTRACT,     { { IT_CONTRACT,     1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_SORCERY_VESSEL,       { { IT_VESSEL,       1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_SORCERY_SPELLBOOK,    { { IT_SPELLBOOK,    1.0 } /*,{ IT_X, 0.0 }*/ } },

    {IND_MACHINE_FUEL,         { { IT_FUEL,         1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_MACHINE_CLOCKWORK,    { { IT_CLOCKWORK,    1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_MACHINE_TOOLS,        { { IT_TOOLS,        1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_MACHINE_AUTOMATON,    { { IT_AUTOMATON,    1.0 } /*,{ IT_X, 0.0 }*/ } }

};

/**
const std::map<int, int>jobExpertiseType =
{
    {IND_HUNT_MEAT, EXP_HUNT},
    {IND_HUNT_ECTOPLASM, EXP_HUNT},
    {IND_SORCERY_CONTRACT, EXP_SORCERY},
    {IND_SORCERY_SPELLBOOK, EXP_SORCERY},
    {IND_FARM_BERRIES, EXP_FARM},
    {IND_ALCHEMY_ALCOHOL, EXP_ALCHEMY},
    {IND_FARM_MUSHROOMS, EXP_FARM},
    {IND_FARM_HERBS, EXP_FARM},
    {IND_ALCHEMY_MEDICINE, EXP_ALCHEMY},
    {IND_FARM_SPICE, EXP_FARM},
    {IND_MINE_CLAY, EXP_MINE},
    {IND_SORCERY_VESSEL, EXP_CRAFT},
    {IND_MINE_SILVER, EXP_MINE},
    {IND_CRAFT_JEWELRY, EXP_CRAFT},
    {IND_MINE_LEYSTONE, EXP_MINE},
    {IND_MACHINE_CLOCKWORK, EXP_MECHANICS},
    {IND_MACHINE_AUTOMATON, EXP_MECHANICS}
};

const std::map<int, int>jobExpertiseLevel =
{
    {IND_HUNT_MEAT, 1},
    {IND_HUNT_ECTOPLASM, 2},
    {IND_SORCERY_CONTRACT, 3},
    {IND_SORCERY_SPELLBOOK, 4},
    {IND_FARM_BERRIES, 1},
    {IND_ALCHEMY_ALCOHOL, 1},
    {IND_FARM_MUSHROOMS, 2},
    {IND_FARM_HERBS, 3},
    {IND_ALCHEMY_MEDICINE, 2},
    {IND_FARM_SPICE, 4},
    {IND_MINE_CLAY, 1},
    {IND_SORCERY_VESSEL, 1},
    {IND_MINE_SILVER, 2},
    {IND_CRAFT_JEWELRY, 2},
    {IND_MINE_LEYSTONE, 3},
    {IND_MACHINE_CLOCKWORK, 3},
    {IND_MACHINE_AUTOMATON, 4}
};
*/

#endif // INDUSTRYINDEX_H_INCLUDED
