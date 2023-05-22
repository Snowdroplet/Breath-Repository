#ifndef PLACEINDEX_H_INCLUDED
#define PLACEINDEX_H_INCLUDED

#include <map>
#include <vector>
#include <array>

#include "industryindex.h"

enum enumPlaces
{
    PL_NONE = -1,

    // Central Verus
    PL_ERICENNES = 0, PL_CHORAS = 1, PL_KETH_KETHER = 2,
    // "Western" Verus
    PL_KETH_ENTWEIR = 3, PL_VIELLEICHT = 4, PL_QUELLUDE = 5, PL_AMBLEFORTH = 6,
    // Southeast Verus
    PL_ROSKANEL = 7, PL_ROSELLA = 8,
    // Northwest Verus
    PL_OBSERVIA = 9, PL_COLDLAKE = 10, PL_UMBERDELL = 11,
    // Northeast Verus
    PL_RAMSHORN = 12, PL_HOLLYHEAD = 13, PL_JASPER = 14,
    // Sharumnir
    PL_RUMNIR = 15, PL_HEWNHEIM = 16, PL_ARTAS_ROCK = 17, PL_VERSE = 18,
    // Northern Xenia
    PL_YHANE = 19, PL_VEINS = 20, PL_XENIA = 21,
    // Southern Xenia
    PL_TOBANDJAN = 22, PL_QUMANTHA = 23,
    // Isolated Fields (Unnatural ley connections)
    PL_MAKHIA = 24, PL_HAPHADEE = 25, PL_ASTEROS = 26,
    // Thousand Isles
    PL_REACH = 27, PL_KARUNE = 28, PL_HATHSERA = 29, PL_DOZAAL = 30, PL_YULMER = 31,
    // Legendary Etruri
    PL_ETRURI = 32
};
const unsigned PL_MARKER_FIRST = PL_ERICENNES;
const unsigned PL_MARKER_LAST = PL_JASPER;

const std::map<int, std::string>placeNames =
{
    {PL_ERICENNES,"Ericennes"}, {PL_CHORAS,"Choras"}, {PL_KETH_KETHER,"Keth Kether"},
    {PL_KETH_ENTWEIR,"Keth Entweir"}, {PL_VIELLEICHT,"Vielleicht"}, {PL_QUELLUDE,"Quellude"}, {PL_AMBLEFORTH,"Ambleforth"},
    {PL_ROSKANEL,"Roskanel"}, {PL_ROSELLA,"Rosella"},
    {PL_OBSERVIA,"Observia"}, {PL_COLDLAKE,"Coldlake"}, {PL_UMBERDELL,"Umberdell"},
    {PL_RAMSHORN,"Ramshorn"}, {PL_HOLLYHEAD,"Hollyhead"}, {PL_JASPER,"Jasper"},
    {PL_RUMNIR, "Rumnir"}, {PL_HEWNHEIM,"Hewnheim"}, {PL_ARTAS_ROCK,"Arta's Rock"}, {PL_VERSE,"Verse"},
    {PL_YHANE,"Yhane"}, {PL_VEINS,"Veins"}, {PL_XENIA,"Xenia"},
    {PL_TOBANDJAN,"Tobandjan"}, {PL_QUMANTHA,"Qumantha"},
    {PL_MAKHIA,"Makhia"}, {PL_HAPHADEE,"Haphadee"}, {PL_ASTEROS,"Asteros"},
    {PL_REACH,"Reach"}, {PL_KARUNE,"Karune"}, {PL_HATHSERA,"Hathsera"}, {PL_DOZAAL,"Dozaal"},
    {PL_ETRURI,"Etruri"}
};

const std::map<int, std::array<float,2>>placeOverworldXYCells =
{
    {PL_ERICENNES,    {20 , 20 } },
    {PL_CHORAS,       {24 , 12 } },
    {PL_KETH_KETHER,  {12 , 24 } },

    {PL_KETH_ENTWEIR, {9  , 17 } },
    {PL_VIELLEICHT,   {1  , 28 } },
    {PL_QUELLUDE,     {6  , 32 } },
    {PL_AMBLEFORTH,   {4  , 14 } },

    {PL_ROSKANEL,     {26 , 24 } },
    {PL_ROSELLA,      {28 , 30 } },

    {PL_OBSERVIA,     {11 ,  5 } },
    {PL_COLDLAKE,     {16 , 10 } },
    {PL_UMBERDELL,    {17 ,  3 } },

    {PL_RAMSHORN,     {31 ,  9} },
    {PL_HOLLYHEAD,    {25 ,  5} },
    {PL_JASPER,       {36 ,  2} },

    {PL_RUMNIR,       {0 ,0 } },
    {PL_HEWNHEIM,     {0 ,0 } },
    {PL_ARTAS_ROCK,   {0 ,0 } },
    {PL_VERSE,        {0 ,0 } },

    {PL_YHANE,        {0 ,0 } },
    {PL_VEINS,        {0 ,0 } },
    {PL_XENIA,        {0 ,0 } },

    {PL_TOBANDJAN,    {0 ,0 } },
    {PL_QUMANTHA,     {0 ,0 } },

    {PL_MAKHIA,       {0 ,0 } },
    {PL_HAPHADEE,     {0 ,0 } },
    {PL_ASTEROS,      {0 ,0 } },

    {PL_REACH,        {0 ,0 } },
    {PL_KARUNE,       {0 ,0 } },
    {PL_HATHSERA,     {0 ,0 } },
    {PL_DOZAAL,       {0 ,0 } },
    {PL_YULMER,       {0 ,0 } },

    {PL_ETRURI,       {0 ,0 } }
};



const std::map<int, std::array<int,EXPERTISE_MARKER_LAST+1>>placeInitialPopulationExpertises =
{
//enum enumExpertiseTypes {EXP_COMMON = 0, EXP_HUNT = 1, EXP_FARM = 2, EXP_MINE = 3, EXP_ALCHEMY = 4, EXP_SORCERY = 5, EXP_CRAFT = 6, EXP_MECHANICS = 7};
// 1  = Homestead
// 5  = Town
// 10 = City
// 15 = Crowded city/Capital
// 20 = Max settlement (Qumanth in Xenia)

// Note that each citizen represents 1 expertise level in their industry.

                     // C  H  F  M  A  S  C  M      Target
    {PL_ERICENNES,    { 5, 1, 2, 0, 2, 2, 2, 1} }, // = 15
    {PL_CHORAS,       { 2, 1, 2, 2, 1, 1, 4, 0} }, // = 13
    {PL_KETH_KETHER,  { 3, 0, 1, 2, 0, 0, 1, 3} }, // = 10

    {PL_KETH_ENTWEIR, { 0, 2, 3, 0, 0, 0, 0, 0} }, // =  5
    {PL_VIELLEICHT,   { 0, 0, 0, 0, 0, 0, 0, 0} }, // = 10
    {PL_QUELLUDE,     { 0, 0, 0, 0, 0, 0, 0, 0} }, // =  3
    {PL_AMBLEFORTH,   { 0, 0, 0, 0, 0, 0, 0, 0} }, // =  2

    {PL_ROSKANEL,     { 0, 0, 0, 0, 0, 0, 0, 0} }, // =  8
    {PL_ROSELLA,      { 0, 0, 0, 0, 0, 0, 0, 0} }, // =  6

    {PL_OBSERVIA,     { 0, 0, 0, 0, 0, 0, 0, 0} }, // =  5
    {PL_COLDLAKE,     { 0, 0, 0, 0, 0, 0, 0, 0} }, // =  7
    {PL_UMBERDELL,    { 0, 0, 0, 0, 0, 0, 0, 0} }, // =  4

    {PL_RAMSHORN,     { 0, 0, 0, 0, 0, 0, 0, 0} }, // =  9
    {PL_HOLLYHEAD,    { 0, 0, 0, 0, 0, 0, 0, 0} }, // =  8
    {PL_JASPER,       { 0, 0, 0, 0, 0, 0, 0, 0} }, // =  5

    {PL_RUMNIR,       { 0, 0, 0, 0, 0, 0, 0, 0} }, // =  3
    {PL_HEWNHEIM,     { 0, 0, 0, 0, 0, 0, 0, 0} }, // = 13
    {PL_ARTAS_ROCK,   { 0, 0, 0, 0, 0, 0, 0, 0} }, // = 12
    {PL_VERSE,        { 0, 0, 0, 0, 0, 0, 0, 0} }, // =  8

    {PL_YHANE,        { 0, 0, 0, 0, 0, 0, 0, 0} }, // = 16
    {PL_VEINS,        { 0, 0, 0, 0, 0, 0, 0, 0} }, // =  6
    {PL_XENIA,        { 0, 0, 0, 0, 0, 0, 0, 0} }, // = 17

    {PL_TOBANDJAN,    { 0, 0, 0, 0, 0, 0, 0, 0} }, // = 14
    {PL_QUMANTHA,     { 0, 0, 0, 0, 0, 0, 0, 0} }, // = 20

    {PL_MAKHIA,       { 0, 0, 0, 0, 0, 0, 0, 0} }, // = 12
    {PL_HAPHADEE,     { 0, 0, 0, 0, 0, 0, 0, 0} }, // = 12
    {PL_ASTEROS,      { 0, 0, 0, 0, 0, 0, 0, 0} }, // =  1

    {PL_REACH,        { 0, 0, 0, 0, 0, 0, 0, 0} }, // = 17
    {PL_KARUNE,       { 0, 0, 0, 0, 0, 0, 0, 0} }, // = 15
    {PL_HATHSERA,     { 0, 0, 0, 0, 0, 0, 0, 0} }, // = 13
    {PL_DOZAAL,       { 0, 0, 0, 0, 0, 0, 0, 0} }, // = 16
    {PL_YULMER,       { 0, 0, 0, 0, 0, 0, 0, 0} }, // = 10

    {PL_ETRURI,       { 0, 0, 0, 0, 0, 0, 0, 0} }  // =  5
};

const std::map<int, std::vector<int>>placeInitialIndustries =
{
/*
    IND_HUNT_MEAT = 0,
    IND_HUNT_COLD_BREATH = 1, IND_SORCERY_CONTRACT = 2, IND_SORCERY_SPELLBOOK = 3,
    IND_FARM_RICE = 4, IND_ALCHEMY_ALCOHOL = 5,
    IND_FARM_MUSHROOMS = 6,
    IND_FARM_HERBS = 7, IND_ALCHEMY_MEDICINE = 8,
    IND_FARM_SPICE = 9,
    IND_MINE_CLAY = 10, IND_CRAFT_POTTERY = 11,
    IND_MINE_SILVER = 12, IND_CRAFT_JEWELRY = 13,
    IND_MINE_LEYSTONE = 14, IND_MACHINE_CLOCKWORK = 15, IND_MACHINE_AUTOMATON = 17
*/

    {PL_ERICENNES,    { IND_FARM_RICE, IND_ALCHEMY_ALCOHOL, IND_SORCERY_CONTRACT} },
    {PL_CHORAS,       { IND_FARM_MUSHROOMS, IND_FARM_HERBS, IND_MINE_CLAY, IND_CRAFT_POTTERY} },
    {PL_KETH_KETHER,  { IND_MINE_LEYSTONE, IND_MACHINE_CLOCKWORK, IND_MACHINE_AUTOMATON} },

    {PL_KETH_ENTWEIR, { IND_FARM_MUSHROOMS, IND_FARM_HERBS} },
    {PL_VIELLEICHT,   { IND_HUNT_COLD_BREATH, IND_FARM_SPICE} },
    {PL_QUELLUDE,     { IND_ALCHEMY_ALCOHOL, IND_SORCERY_SPELLBOOK} },
    {PL_AMBLEFORTH,   { IND_HUNT_MEAT, IND_FARM_RICE} },

    {PL_ROSKANEL,     { IND_HUNT_COLD_BREATH} },
    {PL_ROSELLA,      { IND_FARM_SPICE} },

    {PL_OBSERVIA,     { IND_SORCERY_CONTRACT, IND_SORCERY_SPELLBOOK} },
    {PL_COLDLAKE,     { IND_MINE_SILVER, IND_MINE_LEYSTONE} },
    {PL_UMBERDELL,    { IND_FARM_MUSHROOMS, IND_FARM_HERBS, IND_ALCHEMY_MEDICINE} },

    {PL_RAMSHORN,     { IND_HUNT_MEAT, IND_HUNT_COLD_BREATH} },
    {PL_HOLLYHEAD,    { IND_FARM_RICE, IND_MINE_CLAY} },
    {PL_JASPER,       { IND_MINE_SILVER, IND_CRAFT_JEWELRY, IND_ALCHEMY_ALCOHOL} },

    {PL_RUMNIR,       { IND_FARM_MUSHROOMS, IND_FARM_HERBS, IND_MINE_CLAY, IND_CRAFT_POTTERY} },
    {PL_HEWNHEIM,     { IND_FARM_MUSHROOMS, IND_FARM_HERBS, IND_MINE_CLAY, IND_CRAFT_POTTERY} },
    {PL_ARTAS_ROCK,   { IND_FARM_MUSHROOMS, IND_FARM_HERBS, IND_MINE_CLAY, IND_CRAFT_POTTERY} },
    {PL_VERSE,        { IND_FARM_MUSHROOMS, IND_FARM_HERBS, IND_MINE_CLAY, IND_CRAFT_POTTERY} },

    {PL_YHANE,        { IND_FARM_MUSHROOMS, IND_FARM_HERBS, IND_MINE_CLAY, IND_CRAFT_POTTERY} },
    {PL_VEINS,        { IND_FARM_MUSHROOMS, IND_FARM_HERBS, IND_MINE_CLAY, IND_CRAFT_POTTERY} },
    {PL_XENIA,        { IND_FARM_MUSHROOMS, IND_FARM_HERBS, IND_MINE_CLAY, IND_CRAFT_POTTERY} },

    {PL_TOBANDJAN,    { IND_FARM_MUSHROOMS, IND_FARM_HERBS, IND_MINE_CLAY, IND_CRAFT_POTTERY} },
    {PL_QUMANTHA,     { IND_FARM_MUSHROOMS, IND_FARM_HERBS, IND_MINE_CLAY, IND_CRAFT_POTTERY} },

    {PL_MAKHIA,       { IND_FARM_MUSHROOMS, IND_FARM_HERBS, IND_MINE_CLAY, IND_CRAFT_POTTERY} },
    {PL_HAPHADEE,     { IND_FARM_MUSHROOMS, IND_FARM_HERBS, IND_MINE_CLAY, IND_CRAFT_POTTERY} },
    {PL_ASTEROS,      { IND_FARM_MUSHROOMS, IND_FARM_HERBS, IND_MINE_CLAY, IND_CRAFT_POTTERY} },

    {PL_REACH,        { IND_FARM_MUSHROOMS, IND_FARM_HERBS, IND_MINE_CLAY, IND_CRAFT_POTTERY} },
    {PL_KARUNE,       { IND_FARM_MUSHROOMS, IND_FARM_HERBS, IND_MINE_CLAY, IND_CRAFT_POTTERY} },
    {PL_HATHSERA,     { IND_FARM_MUSHROOMS, IND_FARM_HERBS, IND_MINE_CLAY, IND_CRAFT_POTTERY} },
    {PL_DOZAAL,       { IND_FARM_MUSHROOMS, IND_FARM_HERBS, IND_MINE_CLAY, IND_CRAFT_POTTERY} },
    {PL_YULMER,       { IND_FARM_MUSHROOMS, IND_FARM_HERBS, IND_MINE_CLAY, IND_CRAFT_POTTERY} },

    {PL_ETRURI,       { IND_FARM_MUSHROOMS, IND_FARM_HERBS, IND_MINE_CLAY, IND_CRAFT_POTTERY} },

};

#endif // PLACEINDEX_H_INCLUDED
