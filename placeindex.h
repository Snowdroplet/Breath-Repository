#ifndef PLACEINDEX_H_INCLUDED
#define PLACEINDEX_H_INCLUDED

#include <map>
#include <vector>
#include <array>

#include "industryindex.h"
#include "sovereigntyindex.h"

enum enumPlaces
{
    PL_NONE = -1,

    // Verus
    PL_ERICENNES = 0, PL_CHORAS = 1, PL_KETH_KETHER = 2,
    PL_KETH_ENTWEIR = 3, PL_VIELLEICHT = 4, PL_QUELLUDE = 5, PL_AMBLEFORTH = 6,
    PL_ROSKANEL = 7, PL_ROSELLA = 8,
    PL_OBSERVIA = 9, PL_COLDLAKE = 10, PL_UMBERDELL = 11,
    PL_RAMSHORN = 12, PL_HOLLYHEAD = 13, PL_JASPER = 14,
    // Sharumnir
    PL_RUMNIR = 15, PL_HEWNHEIM = 16, PL_ARTAS_ROCK = 17, PL_VERSE = 18,
    // Xenia
    PL_YHANE = 19, PL_VEINS = 20, PL_QALAIZ = 21,
    PL_TOBANDJAN = 22, PL_QUMANTH = 23, PL_XENIA = 24,
    // Thousand Isles
    PL_REACH = 25, PL_KARUNE = 26, PL_HATHSERA = 27, PL_VORDOZAAL = 28, PL_YULMER = 29,
    // Transient Ley Fields
    PL_MAKHIA = 30, PL_HAPHADEE = 31, PL_ASTEROS = 32,
    PL_ETRURI = 33
};

struct PlaceIndex
{
    static const unsigned PL_MARKER_FIRST = PL_ERICENNES;
    static const unsigned PL_MARKER_LAST = PL_YULMER;

    static std::map<int,std::string>placeNames;

    static void LoadConfigurations()
    {
        for(unsigned i = PL_MARKER_FIRST; i <= PL_MARKER_LAST; i++)
        {
            std::string section = "place " + std::to_string(i);
            //std::cout << section << ": " << std::endl;
            placeNames[i] = Configuration::ReturnString(Configuration::placeCfg, section.c_str(), "name");
            //std::cout << placeNames[i] << std::endl;
        }
    }

};

const std::map<int, std::array<float,2>>placeOverworldXYCells =
{
    /*
    {PL_ERICENNES,    { 20,  20 } },
    {PL_CHORAS,       { 24,  12 } },
    {PL_KETH_KETHER,  { 12,  24 } },

    {PL_KETH_ENTWEIR, { 9,  17 } },
    {PL_VIELLEICHT,   { 1,  28 } },
    {PL_QUELLUDE,     { 6,  32 } },
    {PL_AMBLEFORTH,   { 4,  14 } },

    {PL_ROSKANEL,     { 26,  24 } },
    {PL_ROSELLA,      { 28,  30 } },

    {PL_OBSERVIA,     { 11,   5 } },
    {PL_COLDLAKE,     { 16,  10 } },
    {PL_UMBERDELL,    { 17,   3 } },

    {PL_RAMSHORN,     { 31,   9 } },
    {PL_HOLLYHEAD,    { 25,   5 } },
    {PL_JASPER,       { 36,   2 } },

    {PL_RUMNIR,       { 21,  -6 } },
    {PL_HEWNHEIM,     {  9,  -9 } },
    {PL_ARTAS_ROCK,   { 19, -16 } },
    {PL_VERSE,        { 13, -22 } },

    {PL_YHANE,        { 20,  30 } },
    {PL_VEINS,        { 16,  33 } },
    {PL_QALAIZ,       { 24,  41 } },

    {PL_TOBANDJAN,    { 22,  48 } },
    {PL_QUMANTH,      { 15,  45 } },
    {PL_XENIA,        { 30,  47 } },

    {PL_REACH,        {-12,  30 } },
    {PL_KARUNE,       {-10,  11 } },
    {PL_HATHSERA,     { -5,  42 } },
    {PL_VORDOZAAL,    { -8,  48 } },
    {PL_YULMER,       { -4,  -6 } },

    {PL_MAKHIA,       {0, 0 } },
    {PL_HAPHADEE,     {0, 0 } },
    {PL_ASTEROS,      {-5, 21 } },

    {PL_ETRURI,       {0,0 } }*/

    {PL_ERICENNES,    { 70,  70 } },
    {PL_CHORAS,       { 74,  62 } },
    {PL_KETH_KETHER,  { 62,  74 } },

    {PL_KETH_ENTWEIR, { 59,  67 } },
    {PL_VIELLEICHT,   { 51,  78 } },
    {PL_QUELLUDE,     { 56,  82 } },
    {PL_AMBLEFORTH,   { 54,  64 } },

    {PL_ROSKANEL,     { 76,  74 } },
    {PL_ROSELLA,      { 78,  80 } },

    {PL_OBSERVIA,     { 61,  55 } },
    {PL_COLDLAKE,     { 66,  60 } },
    {PL_UMBERDELL,    { 67,  53 } },

    {PL_RAMSHORN,     { 81,  59 } },
    {PL_HOLLYHEAD,    { 75,  55 } },
    {PL_JASPER,       { 86,  52 } },

    {PL_RUMNIR,       { 71,  44 } },
    {PL_HEWNHEIM,     { 59,  41 } },
    {PL_ARTAS_ROCK,   { 69,  34 } },
    {PL_VERSE,        { 63,  28 } },

    {PL_YHANE,        { 70,  80 } },
    {PL_VEINS,        { 66,  83 } },
    {PL_QALAIZ,       { 74,  91 } },

    {PL_TOBANDJAN,    { 72,  98 } },
    {PL_QUMANTH,      { 65,  95 } },
    {PL_XENIA,        { 80,  97 } },

    {PL_REACH,        { 38,  80 } },
    {PL_KARUNE,       { 40,  61 } },
    {PL_HATHSERA,     { 45,  92 } },
    {PL_VORDOZAAL,    { 42,  98 } },
    {PL_YULMER,       { 46,  44 } },

    {PL_MAKHIA,       {50, 50 } },
    {PL_HAPHADEE,     {50, 50 } },
    {PL_ASTEROS,      {45, 71 } },

    {PL_ETRURI,       {50,50 } }
};



const std::map<int, const std::array<int,EXP_MARKER_LAST+1>>placeInitialPopulation =
{
//EXP_COMMON = 0, EXP_HUNT = 1, EXP_FARM = 2, EXP_MINE = 3, EXP_ALCHEMY = 4, EXP_SORCERY = 5, EXP_CRAFT = 6, EXP_MECHANICS = 7};
// 1  = Homestead
// 5  = Town
// 10 = City
// 15 = Crowded city/Capital
// 20 = Max settlement (Qumanth in Xenia)

// Note that each citizen represents 1 expertise level in their industry.

//                      C     H  F  M     A  S  M      Target
    {PL_ERICENNES,    { 5,    1, 2, 0,    2, 2, 3} }, // = 15
    {PL_CHORAS,       { 2,    1, 2, 2,    1, 1, 4} }, // = 13
    {PL_KETH_KETHER,  { 3,    0, 1, 2,    0, 0, 4} }, // = 10

    {PL_KETH_ENTWEIR, { 1,    1, 3, 0,    0, 0, 0} }, // =  5
    {PL_VIELLEICHT,   { 4,    2, 2, 0,    0, 0, 2} }, // = 10
    {PL_QUELLUDE,     { 0,    0, 0, 0,    1, 2, 0} }, // =  3
    {PL_AMBLEFORTH,   { 1,    0, 1, 0,    0, 0, 0} }, // =  2

    {PL_ROSKANEL,     { 4,    3, 0, 0,    1, 0, 0} }, // =  8
    {PL_ROSELLA,      { 2,    0, 2, 1,    0, 0, 1} }, // =  6

    {PL_OBSERVIA,     { 0,    0, 0, 0,    0, 4, 1} }, // =  5
    {PL_COLDLAKE,     { 2,    0, 1, 4,    0, 0, 0} }, // =  7
    {PL_UMBERDELL,    { 0,    0, 2, 0,    2, 0, 0} }, // =  4

    {PL_RAMSHORN,     { 2,    5, 0, 0,    2, 0, 0} }, // =  9
    {PL_HOLLYHEAD,    { 3,    0, 3, 1,    0, 1, 0} }, // =  8
    {PL_JASPER,       { 0,    0, 0, 1,    0, 0, 4} }, // =  5

    {PL_RUMNIR,       { 0,    1, 0, 0,    0, 0, 2} }, // =  3
    {PL_HEWNHEIM,     { 3,    1, 1, 5,    0, 0, 3} }, // = 13
    {PL_ARTAS_ROCK,   { 4,    1, 1, 0,    2, 1, 3} }, // = 12
    {PL_VERSE,        { 1,    0, 1, 0,    3, 3, 0} }, // =  8

    {PL_YHANE,        { 4,    2, 2, 2,    2, 2, 2} }, // = 16
    {PL_VEINS,        { 1,    0, 0, 3,    1, 0, 1} }, // =  6
    {PL_QALAIZ,       { 1,    3, 0, 0,    1, 0, 0} }, // =  5

    {PL_TOBANDJAN,    { 5,    0, 6, 0,    1, 1, 1} }, // = 14
    {PL_QUMANTH,      { 6,    4, 2, 1,    2, 6, 0} }, // = 20
    {PL_XENIA,        { 7,    1, 2, 0,    4, 2, 1} }, // = 17

    {PL_REACH,        { 3,    3, 2, 3,    2, 2, 2} }, // = 17
    {PL_KARUNE,       { 4,    2, 3, 2,    3, 1, 0} }, // = 15
    {PL_HATHSERA,     { 1,    5, 6, 0,    1, 0, 0} }, // = 13
    {PL_VORDOZAAL,    { 0,    3, 0, 2,    0, 0, 3} }, // =  8
    {PL_YULMER,       { 3,    1, 1, 0,    0, 1, 0} }, // =  6

    {PL_MAKHIA,       { 0,    0, 0, 0,    0, 0, 0} }, // = 12
    {PL_HAPHADEE,     { 0,    0, 0, 0,    0, 0, 0} }, // = 12
    {PL_ASTEROS,      { 0,    0, 0, 0,    0, 0, 0} }, // =  1

    {PL_ETRURI,       { 0,    0, 0, 0,    0, 0, 0} }  // =  5
};

const std::map<int, std::vector<int>>placeInitialIndustries =
{
    {PL_ERICENNES,    { IND_FARM_BERRIES, IND_ALCHEMY_BRANDY, IND_ALCHEMY_COUNTERAGENT, IND_SORCERY_EFFIGY, IND_SORCERY_CONTRACT} },
    {PL_CHORAS,       { IND_FARM_MUSHROOMS, IND_FARM_HERBS, IND_MINE_CLAY, IND_ALCHEMY_ETHER, IND_SORCERY_VESSEL} },
    {PL_KETH_KETHER,  { IND_MINE_COPPER, IND_MINE_LEYSTONE, IND_MACHINE_FUEL, IND_MACHINE_CLOCKWORK, IND_MACHINE_AUTOMATON} },

    {PL_KETH_ENTWEIR, { IND_HUNT_CORPUS, IND_HUNT_OCULUS, IND_FARM_MUSHROOMS, IND_FARM_HERBS} },
    {PL_VIELLEICHT,   { IND_HUNT_PLASM, IND_HUNT_OCULUS, IND_FARM_SPICE, IND_SORCERY_EFFIGY, IND_MACHINE_FUEL} },
    {PL_QUELLUDE,     { IND_HUNT_DORMANT_EGG, IND_ALCHEMY_BRANDY, IND_SORCERY_CONTRACT} },
    {PL_AMBLEFORTH,   { IND_HUNT_CORPUS, IND_FARM_BERRIES} },

    {PL_ROSKANEL,     { IND_HUNT_PLASM, IND_ALCHEMY_MEDICINE, IND_MACHINE_TOOLS} },
    {PL_ROSELLA,      { IND_HUNT_DORMANT_EGG, IND_FARM_SPICE, IND_MINE_CLAY} },

    {PL_OBSERVIA,     { IND_HUNT_PLASM, IND_HUNT_OCULUS, IND_SORCERY_EFFIGY, IND_SORCERY_CONTRACT, IND_SORCERY_GRIMOIRE} },
    {PL_COLDLAKE,     { IND_MINE_CLAY, IND_MINE_COPPER, IND_MINE_IRON, IND_MINE_LEYSTONE} },
    {PL_UMBERDELL,    { IND_HUNT_DORMANT_EGG, IND_FARM_MUSHROOMS, IND_FARM_HERBS, IND_ALCHEMY_MEDICINE} },

    {PL_RAMSHORN,     { IND_HUNT_CORPUS, IND_HUNT_PLASM, IND_ALCHEMY_BRANDY} },
    {PL_HOLLYHEAD,    { IND_FARM_BERRIES, IND_MINE_CLAY, IND_SORCERY_CONTRACT, IND_MACHINE_FUEL} },
    {PL_JASPER,       { IND_MINE_IRON, IND_MACHINE_TOOLS, IND_MACHINE_FUEL, IND_MACHINE_CLOCKWORK} },

    {PL_RUMNIR,       { IND_HUNT_CORPUS, IND_HUNT_OCULUS, IND_SORCERY_EFFIGY} },
    {PL_HEWNHEIM,     { IND_HUNT_PLASM, IND_FARM_MUSHROOMS, IND_MINE_COPPER, IND_MINE_LEYSTONE, IND_ALCHEMY_ETHER, IND_MACHINE_CLOCKWORK} },
    {PL_ARTAS_ROCK,   { IND_FARM_HERBS, IND_MINE_CLAY, IND_SORCERY_VESSEL, IND_MACHINE_AUTOMATON} },
    {PL_VERSE,        { IND_HUNT_DORMANT_EGG, IND_ALCHEMY_MEDICINE, IND_ALCHEMY_ETHER, IND_SORCERY_CONTRACT, IND_SORCERY_GRIMOIRE} },

    {PL_YHANE,        { IND_HUNT_OCULUS, IND_FARM_MUSHROOMS, IND_MINE_COPPER, IND_ALCHEMY_ETHER, IND_SORCERY_CONTRACT, IND_MACHINE_FUEL} },
    {PL_VEINS,        { IND_FARM_BERRIES, IND_FARM_HERBS, IND_MINE_LEYSTONE, IND_ALCHEMY_BRANDY, IND_ALCHEMY_MEDICINE} },
    {PL_QALAIZ,       { IND_HUNT_CORPUS, IND_MINE_IRON, IND_ALCHEMY_ETHER, IND_MACHINE_FUEL} },

    {PL_TOBANDJAN,    { IND_FARM_HERBS, IND_FARM_SPICE, IND_MINE_CLAY, IND_SORCERY_EFFIGY} },
    {PL_QUMANTH,      { IND_HUNT_PLASM, IND_FARM_BERRIES, IND_ALCHEMY_COUNTERAGENT, IND_SORCERY_CONTRACT, IND_SORCERY_VESSEL, IND_SORCERY_GRIMOIRE} },
    {PL_XENIA,        { IND_HUNT_DORMANT_EGG, IND_MINE_COPPER, IND_ALCHEMY_BRANDY, IND_MACHINE_TOOLS, IND_MACHINE_CLOCKWORK, IND_MACHINE_AUTOMATON } },

    {PL_REACH,        { IND_HUNT_CORPUS, IND_MINE_CLAY, IND_MINE_LEYSTONE, IND_ALCHEMY_BRANDY, IND_SORCERY_EFFIGY, IND_MACHINE_TOOLS} },
    {PL_KARUNE,       { IND_HUNT_DORMANT_EGG, IND_FARM_HERBS, IND_MINE_COPPER, IND_ALCHEMY_ETHER, IND_ALCHEMY_COUNTERAGENT, IND_SORCERY_CONTRACT} },
    {PL_HATHSERA,     { IND_FARM_BERRIES, IND_FARM_MUSHROOMS, IND_FARM_HERBS, IND_FARM_SPICE, IND_ALCHEMY_MEDICINE, IND_SORCERY_VESSEL} },
    {PL_VORDOZAAL,    { IND_HUNT_OCULUS, IND_HUNT_DORMANT_EGG, IND_MINE_IRON, IND_MINE_LEYSTONE, IND_MACHINE_TOOLS} },
    {PL_YULMER,       { IND_HUNT_PLASM, IND_HUNT_OCULUS, IND_FARM_MUSHROOMS, IND_SORCERY_GRIMOIRE} },

    {PL_MAKHIA,       { IND_FARM_MUSHROOMS, IND_FARM_HERBS, IND_MINE_CLAY, IND_SORCERY_VESSEL} },
    {PL_HAPHADEE,     { IND_FARM_MUSHROOMS, IND_FARM_HERBS, IND_MINE_CLAY, IND_SORCERY_VESSEL} },
    {PL_ASTEROS,      { IND_FARM_MUSHROOMS, IND_FARM_HERBS, IND_MINE_CLAY, IND_SORCERY_VESSEL} },

    {PL_ETRURI,       { IND_FARM_MUSHROOMS, IND_FARM_HERBS, IND_MINE_CLAY, IND_SORCERY_VESSEL} },

};

const std::map<int,int>placeSovereignties =
{
    {PL_ERICENNES, SOV_VERUS}, {PL_CHORAS,SOV_VERUS}, {PL_KETH_KETHER, SOV_VERUS},
    {PL_KETH_ENTWEIR, SOV_VERUS}, {PL_VIELLEICHT, SOV_VERUS}, {PL_QUELLUDE, SOV_VERUS}, {PL_AMBLEFORTH,SOV_VERUS},
    {PL_ROSKANEL,SOV_VERUS}, {PL_ROSELLA,SOV_VERUS},
    {PL_OBSERVIA,SOV_VERUS}, {PL_COLDLAKE,SOV_VERUS}, {PL_UMBERDELL,SOV_VERUS},
    {PL_RAMSHORN,SOV_VERUS}, {PL_HOLLYHEAD,SOV_VERUS}, {PL_JASPER,SOV_VERUS},

    {PL_RUMNIR, SOV_SHARUMNIR}, {PL_HEWNHEIM,SOV_SHARUMNIR}, {PL_ARTAS_ROCK, SOV_SHARUMNIR}, {PL_VERSE, SOV_SHARUMNIR},

    {PL_YHANE, SOV_XENIA}, {PL_VEINS, SOV_XENIA}, {PL_QALAIZ, SOV_XENIA},
    {PL_TOBANDJAN, SOV_XENIA}, {PL_QUMANTH, SOV_XENIA}, {PL_XENIA, SOV_XENIA},

    {PL_REACH, SOV_THOUSAND_ISLES}, {PL_KARUNE, SOV_THOUSAND_ISLES}, {PL_HATHSERA, SOV_THOUSAND_ISLES}, {PL_VORDOZAAL, SOV_THOUSAND_ISLES}, {PL_YULMER, SOV_THOUSAND_ISLES},

    {PL_MAKHIA, SOV_NULL}, {PL_HAPHADEE, SOV_NULL}, {PL_ASTEROS, SOV_NULL},
    {PL_ETRURI, SOV_NULL}
};

#endif // PLACEINDEX_H_INCLUDED
