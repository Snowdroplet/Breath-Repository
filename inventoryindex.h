#ifndef INVENTORYINDEX_H_INCLUDED
#define INVENTORYINDEX_H_INCLUDED

#include <map>
#include <string>

const int IT_NONE = -1;

enum enumItems
{
    IT_MEAT = 0,
    IT_COLD_BREATH = 1, IT_CONTRACT = 2, IT_SPELLBOOK = 3,
    IT_RICE = 4, IT_ALCOHOL = 5,
    IT_MUSHROOMS = 6,
    IT_HERBS = 7, IT_MEDICINE = 8,
    IT_SPICE = 9,
    IT_CLAY = 10, IT_POTTERY = 11,
    IT_SILVER = 12, IT_JEWELRY = 13,
    IT_LEYSTONE = 14, IT_CLOCKWORK = 15, IT_AUTOMATON = 16
};
const unsigned IT_MARKER_FIRST = IT_MEAT;
const unsigned IT_MARKER_LAST = IT_AUTOMATON;

const std::map<int,std::string>itemNames =
{
    {IT_MEAT, "Meat"},
    {IT_COLD_BREATH, "Cold Breath"}, {IT_CONTRACT, "Contract"}, {IT_SPELLBOOK, "Spellbook"},
    {IT_RICE, "Rice"}, {IT_ALCOHOL, "Alcohol"},
    {IT_MUSHROOMS, "Mushrooms"},
    {IT_HERBS, "Herbs"}, {IT_MEDICINE, "Medicine"},
    {IT_SPICE, "Spice"},
    {IT_CLAY, "Clay"}, {IT_POTTERY, "Pottery"},
    {IT_SILVER, "Silver"}, {IT_JEWELRY, "Jewelry"},
    {IT_LEYSTONE, "Leystone"}, {IT_CLOCKWORK, "Clockwork"}, {IT_AUTOMATON, "Automaton"}
};

/*
enum enumItems
{
    // Plant Materials
    IT_RICE, IT_ROOTS, IT_MUSHROOMS, IT_BERRIES, IT_NUTS, IT_HONEY,
    IT_PAPYRUS, IT_JUTE, IT_RESIN, IT_ANCIENT_WOOD, IT_SPICE, IT_ETHER,

    // Mineral Materials
    IT_CLAY, IT_LEYSTONE, IT_SALT, IT_QUARTZ, IT_SULPHUR, IT_OBSIDIAN,
    IT_IRON, IT_COPPER, IT_SILVER, IT_GOLD,
    IT_OPAL, IT_METEORITE,

    // Beast Materials
    IT_BEAST_BLOOD, IT_BEAST_FLESH, IT_BEAST_EGG,
    IT_FEATHERS, IT_ECTOPLASM, IT_COLD_OIL,
    IT_PEARL, IT_IVORY, IT_SILK,
    IT_FUR, IT_SCALES, IT_CHITIN,

    // Artificial Materials
    IT_ALCOHOL, IT_POISON, IT_COUNTERAGENT,
    IT_JAR, IT_GRAVEWAX, IT_SCRIMSHAW, IT_BLOOD_CRYSTAL, IT_INCENSE,
    IT_SCROLL, IT_VELLUM, IT_DARK_PIGMENTS, IT_BRIGHT_PIGMENTS,
    IT_CONTRACT, IT_SCRIPTURE, IT_SCHEMA,
    IT_CLOCKWORK,

    // General Goods
    IT_SALVE,
    IT_MARZIPAN, IT_BAKLAVA, IT_HOT_SAUCE, IT_CURRY,
    IT_MEAD, IT_KAFE, IT_LAUDANUM, IT_PERFUME,
    IT_KITE, IT_FINE_HEADDRESS, IT_JEWELRY,
    IT_ATLAS,

    // Sorcerous Goods
    IT_ATHAME, IT_ASTRAGALI, IT_CAULDRON, IT_FAMILIAR, IT_SPELLBOOK,

    // Martial Goods
    IT_IRONBREW, IT_CALIGRAPHY, IT_MARTIAL_BRACERS, IT_MIRROR, IT_SEALING_JAR,

    // Religious Goods
    IT_KLEI_MASK, IT_AMULET, IT_CANDLES, IT_PRAYERBOOK, IT_PHYLACTERY,

    // Mechanical Goods
    IT_ASTROLABE, IT_PHONOGRAPH, IT_CODEBOOK, IT_LEXICON, IT_AUTOMATON,

    // Traveller's Tools
    IT_WAYBREAD, IT_JERKY,
    IT_LEYPOST, IT_WEATHER_PROBE,
    IT_RED_TORCH, IT_CLEMENT_MUFFLER, IT_MURKY_TEA, IT_WARDING_POWDER, IT_SHELTER_STONE,
    IT_BLUE_TORCH, IT_FIRECRACKERS,
    IT_CURE_BLIGHT, IT_CURE_CORRUPTION
};
*/

#endif // INVENTORYINDEX_H_INCLUDED
