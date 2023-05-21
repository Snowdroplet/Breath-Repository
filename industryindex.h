#ifndef INDUSTRYINDEX_H_INCLUDED
#define INDUSTRYINDEX_H_INCLUDED

#include <map>

enum enumExpertiseTypes
{
    EXP_HUNT,
    EXP_FARM,
    EXP_MINE,
    EXP_ALCHEMY,
    EXP_CRAFT
};

enum enumIndustries
{
    IND_HUNT_MEAT,
    IND_HUNT_COLD_BREATH, IND_ALCHEMY_CONTRACT, IND_ALCHEMY_SPELLBOOK,
    IND_FARM_RICE, IND_ALCHEMY_ALCOHOL,
    IND_FARM_MUSHROOMS,
    IND_FARM_HERBS, IND_ALCHEMY_MEDICINE,
    IND_FARM_SPICE,
    IND_MINE_CLAY, IND_CRAFT_POTTERY,
    IND_MINE_SILVER, IND_CRAFT_JEWELRY,
    IND_MINE_LEYSTONE, IND_CRAFT_CLOCKWORK, IND_CRAFT_AUTOMATON
};

const std::map<int, std::string>industryNames =
{
    {IND_HUNT_MEAT, "Hunting Beasts for Meat"},
    {IND_HUNT_COLD_BREATH, "Hunting Ghosts for Cold Breath"},
    {IND_ALCHEMY_CONTRACT, "Binding Cold Breath -> Contracts"},
    {IND_ALCHEMY_SPELLBOOK, "Binding Contracts -> Spellbooks"},
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
    {IND_CRAFT_CLOCKWORK, "Shaping Leystone -> Clockwork"},
    {IND_CRAFT_AUTOMATON, "Assembling Clockwork -> Automata"}
};

const std::map<int, float>baseProductionToComplete =
{
    {IND_HUNT_MEAT, 24},
    {IND_HUNT_COLD_BREATH, 36},
    {IND_ALCHEMY_CONTRACT, 16},
    {IND_ALCHEMY_SPELLBOOK, 24},
    {IND_FARM_RICE, 120},
    {IND_ALCHEMY_ALCOHOL, 448},
    {IND_FARM_MUSHROOMS, 120},
    {IND_FARM_HERBS, 240},
    {IND_ALCHEMY_MEDICINE, 12},
    {IND_FARM_SPICE, 240},
    {IND_MINE_CLAY, 24},
    {IND_CRAFT_POTTERY, 24},
    {IND_MINE_SILVER, 56},
    {IND_CRAFT_JEWELRY, 56},
    {IND_MINE_LEYSTONE, 88},
    {IND_CRAFT_CLOCKWORK, 88},
    {IND_CRAFT_AUTOMATON, 352}
};




#endif // INDUSTRYINDEX_H_INCLUDED
