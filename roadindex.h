#ifndef ROADINDEX_H_INCLUDED
#define ROADINDEX_H_INCLUDED

#include <map>

enum enumRoads
{
    ROAD_NONE = -1,

    // List in order of place ID
    ROAD_ERICENNES_CHORAS = 0, ROAD_ERICENNES_KETH_KETHER = 1, ROAD_ERICENNES_KETH_ENTWEIR = 2, ROAD_ERICENNES_ROSKANEL = 3,
    ROAD_CHORAS_COLDLAKE = 4, ROAD_CHORAS_RAMSHORN = 5, ROAD_CHORAS_HOLLYHEAD = 6,
    ROAD_KETH_KETHER_KETH_ENTWEIR = 7, ROAD_KETH_KETHER_VIELLEICHT = 8, ROAD_KETH_KETHER_QUELLUDE = 9,
    ROAD_KETH_ENTWEIR_AMBLEFORTH = 10, ROAD_VIELLEICHT_QUELLUDE = 11, ROAD_AMBLEFORTH_OBSERVIA = 12, ROAD_ROSKANEL_ROSELLA = 13,
    ROAD_OBSERVIA_COLDLAKE = 14, ROAD_OBSERVIA_UMBERDELL = 15,
    ROAD_RAMSHORN_JASPER = 16, ROAD_JASPER_RUMNIR = 17,
    ROAD_RUMNIR_HEWNHEIM = 18, ROAD_RUMNIR_ARTAS_ROCK = 19,
    ROAD_HEWNHEIM_VERSE = 20, ROAD_ARTAS_ROCK_VERSE = 21
};
const unsigned ROAD_MARKER_FIRST = ROAD_ERICENNES_CHORAS;
const unsigned ROAD_MARKER_LAST = ROAD_ARTAS_ROCK_VERSE;

const std::map<int,std::string>roadNames =
{
    {ROAD_ERICENNES_CHORAS, "Ericennes-Choras Road"},
    {ROAD_ERICENNES_KETH_KETHER, "Ericennes-Keth Kether Road"},
    {ROAD_ERICENNES_KETH_ENTWEIR, "Ericennes-Keth Entweir Road"},
    {ROAD_ERICENNES_ROSKANEL, "Ericennes-Roskanel Road"},

    {ROAD_CHORAS_COLDLAKE, "Choras-Coldlake Road"},
    {ROAD_CHORAS_RAMSHORN, "Choras-Ramshorn Road"},
    {ROAD_CHORAS_HOLLYHEAD, "Choras-Hollyhead Road"},

    {ROAD_KETH_KETHER_KETH_ENTWEIR, "Keth Kether-Keth Entweir Road"},
    {ROAD_KETH_KETHER_VIELLEICHT, "Keth Kether-Vielleicht Road"},
    {ROAD_KETH_KETHER_QUELLUDE, "Keth Kether-Quellude Road"},

    {ROAD_KETH_ENTWEIR_AMBLEFORTH, "Keth Entweir-Ambleforth Road"},

    {ROAD_VIELLEICHT_QUELLUDE, "Vielleicht-Quellude Road"},

    {ROAD_AMBLEFORTH_OBSERVIA, "Ambleforth-Observia Road"},

    {ROAD_ROSKANEL_ROSELLA, "Roskanel-Rosella Road"},

    {ROAD_OBSERVIA_COLDLAKE, "Observia-Coldlake Road"},
    {ROAD_OBSERVIA_UMBERDELL, "Observia-Umberdell Road"},

    {ROAD_RAMSHORN_JASPER, "Ramshorn-Jasper Road"},

    {ROAD_JASPER_RUMNIR, "Jasper-Rumnir Road"},

    {ROAD_RUMNIR_HEWNHEIM, "Rumnir-Hewnheim Road"},
    {ROAD_RUMNIR_ARTAS_ROCK, "Rumnir-Arta's Rock Road"},

    {ROAD_HEWNHEIM_VERSE, "Hewnheim-Verse Road"},
    {ROAD_ARTAS_ROCK_VERSE, "Arta's Rock-Verse Road"}
};

#endif // ROADINDEX_H_INCLUDED
