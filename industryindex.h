#ifndef INDUSTRYINDEX_H_INCLUDED
#define INDUSTRYINDEX_H_INCLUDED

#include <map>

#include "inventoryindex.h"

enum enumIndustries
{
    IND_HUNT_MEAT = 0,
    IND_HUNT_ECTOPLASM = 1, IND_SORCERY_CONTRACT = 2, IND_SORCERY_SPELLBOOK = 3,
    IND_FARM_RICE = 4, IND_ALCHEMY_ALCOHOL = 5,
    IND_FARM_MUSHROOMS = 6,
    IND_FARM_HERBS = 7, IND_ALCHEMY_MEDICINE = 8,
    IND_FARM_SPICE = 9,
    IND_MINE_CLAY = 10, IND_CRAFT_POTTERY = 11,
    IND_MINE_SILVER = 12, IND_CRAFT_JEWELRY = 13,
    IND_MINE_LEYSTONE = 14, IND_MACHINE_CLOCKWORK = 15, IND_MACHINE_AUTOMATON = 17
};

const int IND_MARKER_FIRST = IND_HUNT_MEAT;
const int IND_MARKER_LAST = IND_MACHINE_AUTOMATON;


enum enumExpertiseTypes {EXP_COMMON = 0, EXP_HUNT = 1, EXP_FARM = 2, EXP_MINE = 3, EXP_ALCHEMY = 4, EXP_SORCERY = 5, EXP_CRAFT = 6, EXP_MECHANICS = 7};
const int EXP_MARKER_FIRST = EXP_COMMON;
const int EXP_MARKER_LAST = EXP_MECHANICS;


const std::map<int, std::string>industryNames =
{
    {IND_HUNT_MEAT, "Hunting Beast Flesh"},
    {IND_HUNT_ECTOPLASM, "Hunting Ectoplasm"},
    {IND_SORCERY_CONTRACT, "Binding Ectoplasm -> Contracts"},
    {IND_SORCERY_SPELLBOOK, "Binding Contracts -> Spellbooks"},
    {IND_FARM_RICE, "Growing Rice"},
    {IND_ALCHEMY_ALCOHOL, "Brewing Rice -> Alcohol"},
    {IND_FARM_MUSHROOMS, "Growing Mushrooms"},
    {IND_FARM_HERBS, "Cultivating Herbs"},
    {IND_ALCHEMY_MEDICINE, "Brewing Herbs -> Medicines"},
    {IND_FARM_SPICE, "Cultivating Spices"},
    {IND_MINE_CLAY, "Mining Clay"},
    {IND_CRAFT_POTTERY, "Shaping Clay -> Pottery"},
    {IND_MINE_SILVER, "Mining Silver"},
    {IND_CRAFT_JEWELRY, "Crafting Silver -> Jewelry"},
    {IND_MINE_LEYSTONE, "Mining Leystone"},
    {IND_MACHINE_CLOCKWORK, "Shaping Leystone -> Clockwork"},
    {IND_MACHINE_AUTOMATON, "Assembling Clockwork -> Automata"}
};

const std::map<int, float>baseProductionToComplete =
{
    {IND_HUNT_MEAT, 72},
    {IND_HUNT_ECTOPLASM, 96},
    {IND_SORCERY_CONTRACT, 160},
    {IND_SORCERY_SPELLBOOK, 240},
    {IND_FARM_RICE, 240},
    {IND_ALCHEMY_ALCOHOL, 448},
    {IND_FARM_MUSHROOMS, 360},
    {IND_FARM_HERBS, 480},
    {IND_ALCHEMY_MEDICINE, 120},
    {IND_FARM_SPICE, 600},
    {IND_MINE_CLAY, 60},
    {IND_CRAFT_POTTERY, 120},
    {IND_MINE_SILVER, 120},
    {IND_CRAFT_JEWELRY, 240},
    {IND_MINE_LEYSTONE, 180},
    {IND_MACHINE_CLOCKWORK, 352},
    {IND_MACHINE_AUTOMATON, 704}
};

const std::map<int, std::map<int,float>>baseJobInputs =
{

    {IND_HUNT_MEAT,         { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },
    {IND_HUNT_ECTOPLASM,    { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },
    {IND_SORCERY_CONTRACT,  { { IT_ECTOPLASM,    4.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_SORCERY_SPELLBOOK, { { IT_CONTRACT,     6.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_FARM_RICE,         { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },
    {IND_ALCHEMY_ALCOHOL,   { { IT_RICE,        30.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_FARM_MUSHROOMS,    { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },
    {IND_FARM_HERBS,        { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },
    {IND_ALCHEMY_MEDICINE,  { { IT_HERBS,        2.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_FARM_SPICE,        { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },
    {IND_MINE_CLAY,         { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },
    {IND_CRAFT_POTTERY,     { { IT_CLAY,         4.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_MINE_SILVER,       { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },
    {IND_CRAFT_JEWELRY,     { { IT_SILVER,       2.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_MINE_LEYSTONE,     { /*{ IT_X, 0.0 }*/        /*,{ IT_X, 0.0 }*/ } },
    {IND_MACHINE_CLOCKWORK, { { IT_LEYSTONE,     5.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_MACHINE_AUTOMATON, { { IT_CLOCKWORK,   50.0 } /*,{ IT_X, 0.0 }*/ } }
};

const std::map<int, std::map<int,float>>baseJobOutputs =
{
    {IND_HUNT_MEAT,         { { IT_MEAT,        10.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_HUNT_ECTOPLASM,    { { IT_ECTOPLASM,    6.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_SORCERY_CONTRACT,  { { IT_CONTRACT,     1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_SORCERY_SPELLBOOK, { { IT_SPELLBOOK,    1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_FARM_RICE,         { { IT_RICE,        50.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_ALCHEMY_ALCOHOL,   { { IT_ALCOHOL,     25.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_FARM_MUSHROOMS,    { { IT_MUSHROOMS,   30.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_FARM_HERBS,        { { IT_HERBS,       20.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_ALCHEMY_MEDICINE,  { { IT_MEDICINE,     2.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_FARM_SPICE,        { { IT_SPICE,       10.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_MINE_CLAY,         { { IT_CLAY,        10.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_CRAFT_POTTERY,     { { IT_POTTERY,      1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_MINE_SILVER,       { { IT_SILVER,       5.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_CRAFT_JEWELRY,     { { IT_JEWELRY,      1.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_MINE_LEYSTONE,     { { IT_LEYSTONE,     6.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_MACHINE_CLOCKWORK, { { IT_CLOCKWORK,   10.0 } /*,{ IT_X, 0.0 }*/ } },
    {IND_MACHINE_AUTOMATON, { { IT_AUTOMATON,    1.0 } /*,{ IT_X, 0.0 }*/ } }
};

const std::map<int, int>jobExpertiseType =
{
    {IND_HUNT_MEAT, EXP_HUNT},
    {IND_HUNT_ECTOPLASM, EXP_HUNT},
    {IND_SORCERY_CONTRACT, EXP_SORCERY},
    {IND_SORCERY_SPELLBOOK, EXP_SORCERY},
    {IND_FARM_RICE, EXP_FARM},
    {IND_ALCHEMY_ALCOHOL, EXP_ALCHEMY},
    {IND_FARM_MUSHROOMS, EXP_FARM},
    {IND_FARM_HERBS, EXP_FARM},
    {IND_ALCHEMY_MEDICINE, EXP_ALCHEMY},
    {IND_FARM_SPICE, EXP_FARM},
    {IND_MINE_CLAY, EXP_MINE},
    {IND_CRAFT_POTTERY, EXP_CRAFT},
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
    {IND_FARM_RICE, 1},
    {IND_ALCHEMY_ALCOHOL, 1},
    {IND_FARM_MUSHROOMS, 2},
    {IND_FARM_HERBS, 3},
    {IND_ALCHEMY_MEDICINE, 2},
    {IND_FARM_SPICE, 4},
    {IND_MINE_CLAY, 1},
    {IND_CRAFT_POTTERY, 1},
    {IND_MINE_SILVER, 2},
    {IND_CRAFT_JEWELRY, 2},
    {IND_MINE_LEYSTONE, 3},
    {IND_MACHINE_CLOCKWORK, 3},
    {IND_MACHINE_AUTOMATON, 4}
};

#endif // INDUSTRYINDEX_H_INCLUDED
