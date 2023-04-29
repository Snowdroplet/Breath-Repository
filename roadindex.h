#ifndef ROADINDEX_H_INCLUDED
#define ROADINDEX_H_INCLUDED

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

#endif // ROADINDEX_H_INCLUDED
