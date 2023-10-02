#ifndef ROADINDEX_H_INCLUDED
#define ROADINDEX_H_INCLUDED

#include <map>

enum enumRoads
{
    ROAD_NONE = -1,

    // List in order of place ID
    ROAD_ERICENNES_CHORAS = 0, ROAD_ERICENNES_KETH_KETHER = 1, ROAD_ERICENNES_KETH_ENTWEIR = 2, ROAD_ERICENNES_ROSKANEL = 3,
    ROAD_WATERWAY_ERICENNES_COLDLAKE = 4, ROAD_WATERWAY_ERICENNES_VEINS = 5,
    ROAD_CHORAS_COLDLAKE = 6, ROAD_CHORAS_RAMSHORN = 7, ROAD_CHORAS_HOLLYHEAD = 8,
    ROAD_KETH_KETHER_KETH_ENTWEIR = 9, ROAD_KETH_KETHER_VIELLEICHT = 10, ROAD_KETH_KETHER_QUELLUDE = 11,
    ROAD_KETH_ENTWEIR_AMBLEFORTH = 12,
    ROAD_VIELLEICHT_QUELLUDE = 13,
    ROAD_WATERWAY_VIELLEICHT_REACH = 14,
    ROAD_AMBLEFORTH_OBSERVIA = 15,
    ROAD_ROSKANEL_ROSELLA = 16, ROAD_ROSKANEL_YHANE = 17,
    ROAD_OBSERVIA_COLDLAKE = 18, ROAD_OBSERVIA_UMBERDELL = 19,
    ROAD_RAMSHORN_JASPER = 20,
    ROAD_HOLLYHEAD_RUMNIR = 21,
    ROAD_RUMNIR_HEWNHEIM = 22, ROAD_RUMNIR_ARTAS_ROCK = 23,
    ROAD_HEWNHEIM_VERSE = 24,
    ROAD_WATERWAY_HEWNHEIM_YULMER = 25,
    ROAD_ARTAS_ROCK_VERSE = 26,
    ROAD_YHANE_VEINS = 27, ROAD_YHANE_QALAIZ = 28,
    ROAD_WATERWAY_VEINS_QUMANTH = 29,
    ROAD_QALAIZ_TOBANDJAN = 30, ROAD_QALAIZ_QUMANTH = 31, ROAD_QALAIZ_XENIA = 32,
    ROAD_WATERWAY_QUMANTH_HATHSERA = 33,
    ROAD_WATERWAY_REACH_KARUNE = 34, ROAD_WATERWAY_REACH_HATHSERA = 35,
    ROAD_WATERWAY_KARUNE_YULMER = 36,
    ROAD_WATERWAY_HATHSERA_VORDOZAAL = 37
};
const unsigned ROAD_MARKER_FIRST = ROAD_ERICENNES_CHORAS;
const unsigned ROAD_MARKER_LAST = ROAD_WATERWAY_HATHSERA_VORDOZAAL;

enum enumRoadGeographies
{
    GEO_PLAINS,

    GEO_HILLS,
    GEO_MOUNTAINS,
    GEO_ICE_MOUNTAINS,

    GEO_FOREST,

    GEO_RIVER,
    GEO_OCEAN,

    GEO_TUNDRA,
    GEO_DESERT,
    GEO_RED_MESA,

    GEO_ASH_WASTE,

    GEO_CLOUDS,

    GEO_TRANSIENT_LEY
};


const std::map<int,std::string>roadNames =
{
    {ROAD_ERICENNES_CHORAS, "Ericennes-Choras Road"},
    {ROAD_ERICENNES_KETH_KETHER, "Ericennes-Keth Kether Road"},
    {ROAD_ERICENNES_KETH_ENTWEIR, "Ericennes-Keth Entweir Road"},
    {ROAD_ERICENNES_ROSKANEL, "Ericennes-Roskanel Road"},

    {ROAD_WATERWAY_ERICENNES_COLDLAKE, "Ericennes-Coldlake Waterway"},
    {ROAD_WATERWAY_ERICENNES_VEINS, "Ericennes-Veins Waterway"},

    {ROAD_CHORAS_COLDLAKE, "Choras-Coldlake Road"},
    {ROAD_CHORAS_RAMSHORN, "Choras-Ramshorn Road"},
    {ROAD_CHORAS_HOLLYHEAD, "Choras-Hollyhead Road"},

    {ROAD_KETH_KETHER_KETH_ENTWEIR, "Keth Kether-Keth Entweir Road"},
    {ROAD_KETH_KETHER_VIELLEICHT, "Keth Kether-Vielleicht Road"},
    {ROAD_KETH_KETHER_QUELLUDE, "Keth Kether-Quellude Road"},

    {ROAD_KETH_ENTWEIR_AMBLEFORTH, "Keth Entweir-Ambleforth Road"},

    {ROAD_VIELLEICHT_QUELLUDE, "Vielleicht-Quellude Road"},
    {ROAD_WATERWAY_VIELLEICHT_REACH, "Vielleicht-Reach Waterway"},

    {ROAD_AMBLEFORTH_OBSERVIA, "Ambleforth-Observia Road"},

    {ROAD_ROSKANEL_ROSELLA, "Roskanel-Rosella Road"},
    {ROAD_ROSKANEL_YHANE, "Roskanel-Yhane Road"},

    {ROAD_OBSERVIA_COLDLAKE, "Observia-Coldlake Road"},
    {ROAD_OBSERVIA_UMBERDELL, "Observia-Umberdell Road"},

    {ROAD_RAMSHORN_JASPER, "Ramshorn-Jasper Road"},

    {ROAD_HOLLYHEAD_RUMNIR, "Hollyhead-Rumnir Road"},

    {ROAD_RUMNIR_HEWNHEIM, "Rumnir-Hewnheim Road"},
    {ROAD_RUMNIR_ARTAS_ROCK, "Rumnir-Arta's Rock Road"},

    {ROAD_HEWNHEIM_VERSE, "Hewnheim-Verse Road"},

    {ROAD_WATERWAY_HEWNHEIM_YULMER, "Hewnheim-Yulmer Waterway"},

    {ROAD_ARTAS_ROCK_VERSE, "Arta's Rock-Verse Road"},

    {ROAD_YHANE_VEINS, "Yhane-Veins Road"},
    {ROAD_YHANE_QALAIZ, "Yhane-Qalaiz Road"},

    {ROAD_WATERWAY_VEINS_QUMANTH, "Veins-Qumanth Waterway"},

    {ROAD_QALAIZ_TOBANDJAN, "Qalaiz-Tobandjan Road"},
    {ROAD_QALAIZ_QUMANTH, "Qalaiz-Qumanth Road"},
    {ROAD_QALAIZ_XENIA, "Qalaiz-Xenia Road"},

    {ROAD_WATERWAY_QUMANTH_HATHSERA, "Qumanth-Hathsera Waterway"},

    {ROAD_WATERWAY_REACH_KARUNE, "Reach-Karune Waterway"},
    {ROAD_WATERWAY_REACH_HATHSERA, "Reach-Hathesera Waterway"},

    {ROAD_WATERWAY_KARUNE_YULMER, "Karune-Yulmer Waterway"},

    {ROAD_WATERWAY_HATHSERA_VORDOZAAL, "Hathsera-Vordozaal Waterway"}
};

const std::map<int,int>roadGeographies =
{
    {ROAD_ERICENNES_CHORAS, GEO_MOUNTAINS},
    {ROAD_ERICENNES_KETH_KETHER, GEO_HILLS},
    {ROAD_ERICENNES_KETH_ENTWEIR, GEO_FOREST},
    {ROAD_ERICENNES_ROSKANEL, GEO_PLAINS},

    {ROAD_WATERWAY_ERICENNES_COLDLAKE, GEO_RIVER},
    {ROAD_WATERWAY_ERICENNES_VEINS, GEO_RIVER},

    {ROAD_CHORAS_COLDLAKE, GEO_HILLS},
    {ROAD_CHORAS_RAMSHORN, GEO_PLAINS},
    {ROAD_CHORAS_HOLLYHEAD, GEO_TUNDRA},

    {ROAD_KETH_KETHER_KETH_ENTWEIR, GEO_FOREST},
    {ROAD_KETH_KETHER_VIELLEICHT, GEO_PLAINS},
    {ROAD_KETH_KETHER_QUELLUDE, GEO_FOREST},

    {ROAD_KETH_ENTWEIR_AMBLEFORTH, GEO_PLAINS},

    {ROAD_VIELLEICHT_QUELLUDE, GEO_FOREST},
    {ROAD_WATERWAY_VIELLEICHT_REACH, GEO_OCEAN},

    {ROAD_AMBLEFORTH_OBSERVIA, GEO_MOUNTAINS},

    {ROAD_ROSKANEL_ROSELLA, GEO_DESERT},
    {ROAD_ROSKANEL_YHANE, GEO_DESERT},

    {ROAD_OBSERVIA_COLDLAKE, GEO_HILLS},
    {ROAD_OBSERVIA_UMBERDELL, GEO_FOREST},

    {ROAD_RAMSHORN_JASPER, GEO_TUNDRA},

    {ROAD_HOLLYHEAD_RUMNIR, GEO_TUNDRA},

    {ROAD_RUMNIR_HEWNHEIM, GEO_ICE_MOUNTAINS},
    {ROAD_RUMNIR_ARTAS_ROCK, GEO_TUNDRA},

    {ROAD_HEWNHEIM_VERSE, GEO_TUNDRA},

    {ROAD_WATERWAY_HEWNHEIM_YULMER, GEO_OCEAN},

    {ROAD_ARTAS_ROCK_VERSE, GEO_ICE_MOUNTAINS},

    {ROAD_YHANE_VEINS, GEO_RED_MESA},
    {ROAD_YHANE_QALAIZ, GEO_RED_MESA},

    {ROAD_WATERWAY_VEINS_QUMANTH, GEO_RIVER},

    {ROAD_QALAIZ_TOBANDJAN, GEO_DESERT},
    {ROAD_QALAIZ_QUMANTH, GEO_RED_MESA},
    {ROAD_QALAIZ_XENIA, GEO_DESERT},

    {ROAD_WATERWAY_QUMANTH_HATHSERA, GEO_OCEAN},

    {ROAD_WATERWAY_REACH_KARUNE, GEO_OCEAN},
    {ROAD_WATERWAY_REACH_HATHSERA, GEO_OCEAN},

    {ROAD_WATERWAY_KARUNE_YULMER, GEO_OCEAN},

    {ROAD_WATERWAY_HATHSERA_VORDOZAAL, GEO_OCEAN}
};

const std::map<int,int>roadSovereignties =
{
    {ROAD_ERICENNES_CHORAS, SOV_VERUS},
    {ROAD_ERICENNES_KETH_KETHER, SOV_VERUS},
    {ROAD_ERICENNES_KETH_ENTWEIR, SOV_VERUS},
    {ROAD_ERICENNES_ROSKANEL, SOV_VERUS},

    {ROAD_WATERWAY_ERICENNES_COLDLAKE, SOV_VERUS},
    {ROAD_WATERWAY_ERICENNES_VEINS, SOV_VERUS_XENIA_BORDER},

    {ROAD_CHORAS_COLDLAKE, SOV_VERUS},
    {ROAD_CHORAS_RAMSHORN, SOV_VERUS},
    {ROAD_CHORAS_HOLLYHEAD, SOV_VERUS},

    {ROAD_KETH_KETHER_KETH_ENTWEIR, SOV_VERUS},
    {ROAD_KETH_KETHER_VIELLEICHT, SOV_VERUS},
    {ROAD_KETH_KETHER_QUELLUDE,SOV_VERUS},

    {ROAD_KETH_ENTWEIR_AMBLEFORTH, SOV_VERUS},

    {ROAD_VIELLEICHT_QUELLUDE, SOV_VERUS},

    {ROAD_WATERWAY_VIELLEICHT_REACH,SOV_VERUS_THOUSAND_ISLES_BORDER},

    {ROAD_AMBLEFORTH_OBSERVIA, SOV_VERUS},

    {ROAD_ROSKANEL_ROSELLA, SOV_VERUS},
    {ROAD_ROSKANEL_YHANE, SOV_VERUS_XENIA_BORDER},

    {ROAD_OBSERVIA_COLDLAKE, SOV_VERUS},
    {ROAD_OBSERVIA_UMBERDELL, SOV_VERUS},

    {ROAD_RAMSHORN_JASPER, SOV_VERUS},

    {ROAD_HOLLYHEAD_RUMNIR, SOV_VERUS_SHARUMNIR_BORDER},

    {ROAD_RUMNIR_HEWNHEIM, SOV_SHARUMNIR},
    {ROAD_RUMNIR_ARTAS_ROCK, SOV_SHARUMNIR},

    {ROAD_HEWNHEIM_VERSE, SOV_SHARUMNIR},

    {ROAD_WATERWAY_HEWNHEIM_YULMER, SOV_SHARUMNIR_THOUSAND_ISLES_BORDER},

    {ROAD_ARTAS_ROCK_VERSE, SOV_SHARUMNIR},

    {ROAD_YHANE_VEINS, SOV_XENIA},
    {ROAD_YHANE_QALAIZ, SOV_XENIA},

    {ROAD_WATERWAY_VEINS_QUMANTH, SOV_XENIA},

    {ROAD_WATERWAY_QUMANTH_HATHSERA, SOV_XENIA_THOUSAND_ISLES_BORDER},

    {ROAD_QALAIZ_TOBANDJAN, SOV_XENIA},
    {ROAD_QALAIZ_QUMANTH, SOV_XENIA},
    {ROAD_QALAIZ_XENIA, SOV_XENIA},

    {ROAD_WATERWAY_REACH_KARUNE, SOV_THOUSAND_ISLES},
    {ROAD_WATERWAY_REACH_HATHSERA, SOV_THOUSAND_ISLES},

    {ROAD_WATERWAY_KARUNE_YULMER, SOV_THOUSAND_ISLES},

    {ROAD_WATERWAY_HATHSERA_VORDOZAAL, SOV_THOUSAND_ISLES}
};

#endif // ROADINDEX_H_INCLUDED
