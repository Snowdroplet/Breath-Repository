#ifndef INDUSTRYINDEX_H_INCLUDED
#define INDUSTRYINDEX_H_INCLUDED

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
    IND_HUNT_COLD_BLOOD, IND_ALCHEMY_CONTRACT, IND_ALCHEMY_SPELLBOOK,
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
    {IND_HUNT_MEAT, "Hunting meaty beasts"},
    {IND_HUNT_COLD_BLOOD, "Hunting cold-blooded monsters"},
    {IND_ALCHEMY_CONTRACT, "Binding blood contracts"},
    {IND_ALCHEMY_SPELLBOOK, "Binding spellbooks"},
    {IND_FARM_RICE, "Growing rice"},
    {IND_ALCHEMY_ALCOHOL, "Brewing alcohol"},
    {IND_FARM_MUSHROOMS, "Growing mushrooms"},
    {IND_FARM_HERBS, "Growing herbs"},
    {IND_ALCHEMY_MEDICINE, "Mixing medicines"},
    {IND_FARM_SPICE, "Growing spice"},
    {IND_MINE_CLAY, "Mining clay"},
    {IND_CRAFT_POTTERY, "Crafting pottery"},
    {IND_MINE_SILVER, "Mining silver"},
    {IND_CRAFT_JEWELRY, "Crafting jewelry"},
    {IND_MINE_LEYSTONE, "Mining leystone"},
    {IND_CRAFT_CLOCKWORK, "Constructing clockwork parts"},
    {IND_CRAFT_AUTOMATON, "Constructing automata"}
};

const std::map<int, float>baseProductionToComplete =
{
    {IND_HUNT_MEAT, 24},
    {IND_HUNT_COLD_BLOOD, 24},
    {IND_ALCHEMY_CONTRACT, 8},
    {IND_ALCHEMY_SPELLBOOK, 8},
    {IND_FARM_RICE, 120},
    {IND_ALCHEMY_ALCOHOL, 448},
    {IND_FARM_MUSHROOMS, 120},
    {IND_FARM_HERBS, 240},
    {IND_ALCHEMY_MEDICINE, 8},
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
