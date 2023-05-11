#ifndef JOBINDEX_H_INCLUDED
#define JOBINDEX_H_INCLUDED

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

const std::map<int, std::string>jobNames =
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


#endif // JOBINDEX_H_INCLUDED
