#ifndef INVENTORYINDEX_H_INCLUDED
#define INVENTORYINDEX_H_INCLUDED

#include <map>
#include <string>

const int IT_NONE = -1;

enum enumItems
{
    IT_CORPUS  = 0, IT_PLASM  = 1, IT_OCULUS    = 2, IT_STRANGE_EGG  = 3,
    IT_BERRIES = 4, IT_HERBS  = 5, IT_MUSHROOMS = 6, IT_SPICE        = 7,
    IT_CLAY    = 8, IT_COPPER = 9, IT_IRON     = 10, IT_LEYSTONE    = 11,

    IT_BRANDY = 12, IT_MEDICINE  = 13, IT_ETHER = 14, IT_COUNTERAGENT = 15,
    IT_EFFIGY  = 16, IT_CONTRACT  = 17, IT_VESSEL = 18, IT_GRIMOIRE     = 19,
    IT_FUEL    = 20, IT_CLOCKWORK = 21, IT_TOOLS  = 22, IT_AUTOMATON    = 23
};
const unsigned IT_MARKER_FIRST = IT_CORPUS;
const unsigned IT_MARKER_LAST = IT_AUTOMATON;

const std::map<int,std::string>itemNames =
{
    {IT_CORPUS, "Corpus"}, {IT_PLASM, "Plasm"}, {IT_OCULUS, "Oculus"}, {IT_STRANGE_EGG, "Strange Egg"},
    {IT_BERRIES, "Berries"}, {IT_HERBS, "Herbs"}, {IT_MUSHROOMS, "Mushrooms"}, {IT_SPICE, "Spice"},
    {IT_CLAY, "Clay"}, {IT_COPPER, "Copper"}, {IT_IRON, "Iron"}, {IT_LEYSTONE, "Leystone"},

    {IT_BRANDY, "Alcohol"}, {IT_MEDICINE, "Medicine"}, {IT_ETHER, "Poison"}, {IT_COUNTERAGENT, "Counteragent"},
    {IT_EFFIGY, "Effigy"}, {IT_CONTRACT, "Contract"}, {IT_VESSEL, "Vessel"}, {IT_GRIMOIRE, "Spellbook"},
    {IT_FUEL, "Fuel"}, {IT_CLOCKWORK, "Clockwork"}, {IT_TOOLS, "Tools"}, {IT_AUTOMATON, "Automaton"}
};

#endif // INVENTORYINDEX_H_INCLUDED
