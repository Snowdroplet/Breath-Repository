#ifndef INVENTORYINDEX_H_INCLUDED
#define INVENTORYINDEX_H_INCLUDED

const int IT_NONE = -1;

enum enumItems
{
    IT_MEAT,
    IT_MUSHROOMS,
    IT_SPICE,
    IT_RICE, IT_ALCOHOL,
    IT_HERBS, IT_MEDICINE,
    IT_CLAY, IT_POTTERY,
    IT_SILVER, IT_JEWELRY,
    IT_LEYSTONE, IT_CLOCKWORK, IT_AUTOMATON,
    IT_COLD_BLOOD, IT_CONTRACT, IT_SPELLBOOK
};

const std::map<int,float>baseValue =
{
    {IT_MEAT, 4},
    {IT_MUSHROOMS, 1},
    {IT_SPICE, 5},
    {IT_RICE, 1}, {IT_ALCOHOL, 4},
    {IT_HERBS, 2}, {IT_MEDICINE, 7},
    {IT_CLAY, 1}, {IT_POTTERY, 1},
    {IT_SILVER, 10}, {IT_JEWELRY, 20},
    {IT_LEYSTONE, 2}, {IT_CLOCKWORK, 8}, {IT_AUTOMATON, 80},
    {IT_COLD_BLOOD, 6}, {IT_CONTRACT, 20}, {IT_SPELLBOOK, 100}
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
