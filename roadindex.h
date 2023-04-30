#ifndef ROADINDEX_H_INCLUDED
#define ROADINDEX_H_INCLUDED

#include <map>

enum enumRoads
{
    ROAD_NONE = -1,

    // List in order of place ID
    ROAD_ERICENNES_CHORAS = 0,
    ROAD_ERICENNES_KETH_KETHER = 1,
    ROAD_ERICENNES_KETH_ENTWEIR = 2,
    ROAD_ERICENNES_ROSKANEL = 3,

    ROAD_KETH_KETHER_KETH_ENTWEIR = 4,
    ROAD_KETH_KETHER_VIELLEICHT = 5,
    ROAD_KETH_KETHER_QUELLUDE = 6,

    ROAD_KETH_ENTWEIR_AMBLEFORTH = 7,

    ROAD_VIELLEICHT_QUELLUDE = 8,

    ROAD_ROSKANEL_ROSELLA = 9

};
const unsigned ROAD_MARKER_FIRST = ROAD_ERICENNES_CHORAS;
const unsigned ROAD_MARKER_LAST = ROAD_ROSKANEL_ROSELLA;

const std::map<int,std::string>roadNames =
{
    {ROAD_ERICENNES_CHORAS, "Ericennes-Choras Road"},
    {ROAD_ERICENNES_KETH_KETHER , "Ericennes-Keth Kether Road"},
    {ROAD_ERICENNES_KETH_ENTWEIR , "Ericennes-Keth Entweir Road"},
    {ROAD_ERICENNES_ROSKANEL , "Ericennes-Roskanel Road"},

    {ROAD_KETH_KETHER_KETH_ENTWEIR , "Keth Kether-Keth Entweir Road"},
    {ROAD_KETH_KETHER_VIELLEICHT , "Keth Kether-Vielleicht Road"},
    {ROAD_KETH_KETHER_QUELLUDE , "Keth Kether-Quellude Road"},

    {ROAD_KETH_ENTWEIR_AMBLEFORTH , "Keth Entweir-Ambleforth Road"},

    {ROAD_VIELLEICHT_QUELLUDE , "Vielleicht-Quellude Road"},

    {ROAD_ROSKANEL_ROSELLA , "Roskanel-Rosella Road"}
};

#endif // ROADINDEX_H_INCLUDED
