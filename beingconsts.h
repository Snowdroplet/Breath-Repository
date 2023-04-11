#ifndef BEINGCONSTS_H_INCLUDED
#define BEINGCONSTS_H_INCLUDED

const int NUM_RACES = 7;
enum enumRace
{
    RACE_VERIT = 0,   // Hares of Verus
    RACE_YETI = 1,    // Greathares of Rumnir
    RACE_MAKHI = 2,   // Dwarves of Makhia
    RACE_BEYU = 3,    // Catfish of the thousand isles
    RACE_HAPHAE = 4,  // Birds of Haphaedee
    RACE_MESERA = 5,  // Plants of Hathsera
    RACE_ORDON = 6,   // Salamanders of Ordozaal
};

const std::string raceNames[NUM_RACES] =
{
    "Verit",
    "Yeti",
    "Makhi",
    "Beyu",
    "Haphae",
    "Mesera",
    "Ordon"
};

const int NUM_SKILLS = 20;
enum enumSkillKeys
{
    SK_VERESE = 0,
    SK_XENIAN = 1,
    SK_RUMNIRI = 2,
    SK_MAKHIAN = 3,
    SK_REACH_COMMON = 4,
    SK_YULMERESE = 5,
    SK_KARUN = 6,
    SK_HAPHAE = 7,
    SK_MESEREN = 8,
    SK_ZAALTONGUE = 9,

    SK_HARVEST_LORE = 10,
    SK_MINERAL_LORE = 11,
    SK_BEAST_LORE = 12,
    SK_SORCERY_LORE = 13,
    SK_DIVINE_LORE = 14,
    SK_MARTIAL_LORE = 15,
    SK_MACHINE_LORE = 16,

    SK_TUNDRA_SURVIVAL = 17,
    SK_DESERT_SURVIVAL = 18,
    SK_SWAMP_SURVIVAL = 19,
    SK_OCEAN_SURVIVAL = 20

};

#endif // BEINGCONSTS_H_INCLUDED
