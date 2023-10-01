#include "road.h"

std::map<int, Road*> Road::roads;

Road::Road(int id)
{
    identity = id;
    selfPointer = this;

    name = roadNames.at(identity);

    SetGeography(roadGeographies.at(identity));
    SetSovereignty(roadSovereignties.at(identity));

    switch(identity)
    {
    case ROAD_ERICENNES_CHORAS:
        endpointA = PL_ERICENNES;
        endpointB = PL_CHORAS;
        SetWaypoint(0, TILE_W*21 + TILE_W/2, TILE_H*19 + TILE_H/2);
        SetWaypoint(1, TILE_W*24, TILE_H*18);
        SetWaypoint(2, TILE_W*24, TILE_H*13 + TILE_H/2);
        break;

    case ROAD_ERICENNES_KETH_KETHER:
        endpointA = PL_ERICENNES;
        endpointB = PL_KETH_KETHER;
        SetWaypoint(0, TILE_W*18 + TILE_W/2, TILE_H*20 + TILE_H/2);
        SetWaypoint(1, TILE_W*13 + TILE_W/2, TILE_H*20 + TILE_H/2);
        SetWaypoint(2, TILE_W*13 + TILE_W/2, TILE_H*24);
        break;

    case ROAD_ERICENNES_KETH_ENTWEIR:
        endpointA = PL_ERICENNES;
        endpointB = PL_KETH_ENTWEIR;
        SetWaypoint(0, TILE_W*18 + TILE_W/2, TILE_H*19 + TILE_H/2);
        SetWaypoint(1, TILE_W*16, TILE_H*17);
        SetWaypoint(2, TILE_W*10 + TILE_W/2, TILE_H*17);
        break;

    case ROAD_ERICENNES_ROSKANEL:
        endpointA = PL_ERICENNES;
        endpointB = PL_ROSKANEL;
        SetWaypoint(0, TILE_W*21 + TILE_W/2, TILE_H*20 + TILE_H/2);
        SetWaypoint(1, TILE_W*23 + TILE_W/2, TILE_H*22 + TILE_H/2);
        SetWaypoint(2, TILE_W*26, TILE_H*22 + TILE_H/2);
        break;

    case ROAD_WATERWAY_ERICENNES_COLDLAKE:
        endpointA = PL_ERICENNES;
        endpointB = PL_COLDLAKE;
        SetWaypoint(0, TILE_W*20, TILE_H*18 + TILE_H/2);
        SetWaypoint(1, TILE_W*20, TILE_H*17           );
        SetWaypoint(2, TILE_W*16, TILE_H*13           );
        SetWaypoint(3, TILE_W*16, TILE_H*11 + TILE_H/2);
        break;

    case ROAD_WATERWAY_ERICENNES_VEINS:
        endpointA = PL_ERICENNES;
        endpointB = PL_VEINS;
        SetWaypoint(0, TILE_W*20, TILE_H*21 + TILE_H/2);
        SetWaypoint(1, TILE_W*20, TILE_H*23           );
        SetWaypoint(2, TILE_W*16, TILE_H*27           );
        SetWaypoint(3, TILE_W*16, TILE_H*31 + TILE_H/2);
        break;

    case ROAD_CHORAS_COLDLAKE:
        endpointA = PL_CHORAS;
        endpointB = PL_COLDLAKE;
        SetWaypoint(0, TILE_W*22 + TILE_W/2, TILE_H*11 + TILE_H/2);
        SetWaypoint(1, TILE_W*20 + TILE_W/2, TILE_H*10);
        SetWaypoint(2, TILE_W*17 + TILE_W/2, TILE_H*10);
        break;

    case ROAD_CHORAS_RAMSHORN:
        endpointA = PL_CHORAS;
        endpointB = PL_RAMSHORN;
        SetWaypoint(0, TILE_W*25 + TILE_W/2, TILE_H*12);
        SetWaypoint(1, TILE_W*29 + TILE_W/2, TILE_H*12);
        SetWaypoint(2, TILE_W*31, TILE_H*10 + TILE_H/2);
        break;

    case ROAD_CHORAS_HOLLYHEAD:
        endpointA = PL_CHORAS;
        endpointB = PL_HOLLYHEAD;
        SetWaypoint(0, TILE_W*24, TILE_H*10 + TILE_H/2);
        SetWaypoint(1, TILE_W*24, TILE_H*9);
        SetWaypoint(2, TILE_W*25, TILE_H*8);
        SetWaypoint(3, TILE_W*25, TILE_H*6 + TILE_H/2);
        break;

    case ROAD_KETH_KETHER_KETH_ENTWEIR:
        endpointA = PL_KETH_KETHER;
        endpointB = PL_KETH_ENTWEIR;
        SetWaypoint(0, TILE_W*12, TILE_H*22 + TILE_H/2);
        SetWaypoint(1, TILE_W*9, TILE_H*22 + TILE_H/2);
        SetWaypoint(2, TILE_W*9, TILE_H*18 + TILE_H/2);
        break;

    case ROAD_KETH_KETHER_VIELLEICHT:
        endpointA = PL_KETH_KETHER;
        endpointB = PL_VIELLEICHT;
        SetWaypoint(0, TILE_W*10 + TILE_W/2, TILE_H*24);
        SetWaypoint(1, TILE_W*6, TILE_H*24);
        SetWaypoint(2, TILE_W*2 + TILE_W/2, TILE_H*27 + TILE_H/2);
        break;

    case ROAD_KETH_KETHER_QUELLUDE:
        endpointA = PL_KETH_KETHER;
        endpointB = PL_QUELLUDE;
        SetWaypoint(0, TILE_W*12, TILE_H*25 + TILE_W/2);
        SetWaypoint(1, TILE_W*12, TILE_H*28);
        SetWaypoint(2, TILE_W*7 + TILE_W/2, TILE_H*32);
        break;

    case ROAD_KETH_ENTWEIR_AMBLEFORTH:
        endpointA = PL_KETH_ENTWEIR;
        endpointB = PL_AMBLEFORTH;
        SetWaypoint(0, TILE_W*7 + TILE_W/2, TILE_H*17);
        SetWaypoint(1, TILE_W*5, TILE_H*17);
        SetWaypoint(2, TILE_W*4, TILE_H*15 + TILE_H/2);
        break;

    case ROAD_VIELLEICHT_QUELLUDE:
        endpointA = PL_VIELLEICHT;
        endpointB = PL_QUELLUDE;
        SetWaypoint(0, TILE_W*2 + TILE_W/2, TILE_H*28 + TILE_H/2);
        SetWaypoint(1, TILE_W*2 + TILE_W/2, TILE_H*32);
        SetWaypoint(2, TILE_W*4 + TILE_W/2, TILE_H*32);
        break;

    case ROAD_AMBLEFORTH_OBSERVIA:
        endpointA = PL_AMBLEFORTH;
        endpointB = PL_OBSERVIA;
        SetWaypoint(0, TILE_W*4,            TILE_H*12 + TILE_H/2);
        SetWaypoint(1, TILE_W*9 + TILE_W/2, TILE_H*12 + TILE_H/2);
        SetWaypoint(2, TILE_W*9 + TILE_W/2, TILE_H*6  + TILE_H/2);
        break;

    case ROAD_ROSKANEL_ROSELLA:
        endpointA = PL_ROSKANEL;
        endpointB = PL_ROSELLA;
        SetWaypoint(0, TILE_W*26, TILE_H*25 + TILE_H/2);
        SetWaypoint(1, TILE_W*26, TILE_H*28 + TILE_H/2);
        SetWaypoint(2, TILE_W*27 + TILE_W/2, TILE_H*28 + TILE_H/2);
        break;

    case ROAD_ROSKANEL_YHANE:
        endpointA = PL_ROSKANEL;
        endpointB = PL_YHANE;
        SetWaypoint(0, TILE_W*24 + TILE_W/2, TILE_H*24);
        SetWaypoint(1, TILE_W*24 + TILE_W/2, TILE_H*27 + TILE_H/2);
        SetWaypoint(2, TILE_W*22 + TILE_W/2, TILE_H*29 + TILE_H/2);
        SetWaypoint(3, TILE_W*21 + TILE_W/2, TILE_H*29 + TILE_H/2);
        break;

    case ROAD_OBSERVIA_COLDLAKE:
        endpointA = PL_OBSERVIA;
        endpointB = PL_COLDLAKE;
        SetWaypoint(0, TILE_W*11, TILE_H*6 + TILE_H/2);
        SetWaypoint(1, TILE_W*11, TILE_H*10);
        SetWaypoint(2, TILE_W*14 + TILE_W/2, TILE_H*10);
        break;

    case ROAD_OBSERVIA_UMBERDELL:
        endpointA = PL_OBSERVIA;
        endpointB = PL_UMBERDELL;
        SetWaypoint(0, TILE_W*9 + TILE_W/2, TILE_H*5);
        SetWaypoint(1, TILE_W*7, TILE_H*5);
        SetWaypoint(2, TILE_W*7, TILE_H*3);
        SetWaypoint(3, TILE_W*15 + TILE_W/2, TILE_H*3);
        break;

    case ROAD_RAMSHORN_JASPER:
        endpointA = PL_RAMSHORN;
        endpointB = PL_JASPER;
        SetWaypoint(0, TILE_W*31, TILE_H*7 + TILE_H/2);
        SetWaypoint(1, TILE_W*31, TILE_H*4);
        SetWaypoint(2, TILE_W*33, TILE_H*2);
        SetWaypoint(3, TILE_W*34 + TILE_W/2, TILE_H*2);
        break;

    case ROAD_HOLLYHEAD_RUMNIR:
        endpointA = PL_HOLLYHEAD;
        endpointB = PL_RUMNIR;
        SetWaypoint(0, TILE_W*25, TILE_H*3 + TILE_H/2);
        SetWaypoint(1, TILE_W*25, TILE_H*1);
        SetWaypoint(2, TILE_W*25, TILE_H*1);
        SetWaypoint(3, TILE_W*29, TILE_H*(-1) - TILE_H/2);
        SetWaypoint(4, TILE_W*29, TILE_H*(-4) - TILE_H/2);
        break;

    case ROAD_RUMNIR_HEWNHEIM:
        endpointA = PL_RUMNIR;
        endpointB = PL_HEWNHEIM;
        SetWaypoint(0, TILE_W*27 + TILE_W/2, TILE_H*(-7) + TILE_H/2);
        SetWaypoint(1, TILE_W*25 + TILE_W/2, TILE_H*(-9) + TILE_H/2);
        SetWaypoint(2, TILE_W*18 + TILE_W/2, TILE_H*(-9) + TILE_H/2);
        break;

    case ROAD_RUMNIR_ARTAS_ROCK:
        endpointA = PL_RUMNIR;
        endpointB = PL_ARTAS_ROCK;
        SetWaypoint(0, TILE_W*28 + TILE_W/2, TILE_H*(-8) + TILE_H/2);
        SetWaypoint(1, TILE_W*27, TILE_H*(-9));
        SetWaypoint(2, TILE_W*27, TILE_H*(-15) + TILE_H/2);
        break;

    case ROAD_HEWNHEIM_VERSE:
        endpointA = PL_HEWNHEIM;
        endpointB = PL_VERSE;
        SetWaypoint(0, TILE_W*16 + TILE_W/2, TILE_H*(-11) + TILE_H/2);
        SetWaypoint(1, TILE_W*16 + TILE_H/2, TILE_H*(-13)           );
        SetWaypoint(2, TILE_W*20 + TILE_W/2, TILE_H*(-18) + TILE_H/2);
        SetWaypoint(3, TILE_W*20 + TILE_W/2, TILE_H*(-21) + TILE_H/2);
        break;

    case ROAD_ARTAS_ROCK_VERSE:
        endpointA = PL_ARTAS_ROCK;
        endpointB = PL_VERSE;
        SetWaypoint(0, TILE_W*27,            TILE_H*(-18) + TILE_H/2);
        SetWaypoint(1, TILE_W*21 + TILE_W/2, TILE_H*(-18) + TILE_H/2);
        SetWaypoint(2, TILE_W*21 + TILE_W/2, TILE_H*(-21) + TILE_H/2);
        break;

    case ROAD_YHANE_VEINS:
        endpointA = PL_YHANE;
        endpointB = PL_VEINS;
        SetWaypoint(0, TILE_W*19 + TILE_W/2, TILE_H*31 + TILE_H/2);
        SetWaypoint(1, TILE_W*19 + TILE_W/2, TILE_H*33 + TILE_H/2);
        SetWaypoint(2, TILE_W*17 + TILE_W/2, TILE_H*33 + TILE_H/2);
        break;

    case ROAD_YHANE_QALAIZ:
        endpointA = PL_YHANE;
        endpointB = PL_QALAIZ;
        SetWaypoint(0, TILE_W*20 + TILE_W/2, TILE_H*31 + TILE_H/2);
        SetWaypoint(1, TILE_W*20 + TILE_W/2, TILE_H*36 + TILE_H/2);
        SetWaypoint(2, TILE_W*22 + TILE_W/2, TILE_H*39 + TILE_H/2);
        break;

    case ROAD_WATERWAY_VEINS_QUMANTH:
        endpointA = PL_VEINS;
        endpointB = PL_QUMANTH;
        SetWaypoint(0, TILE_W*16           , TILE_H*34 + TILE_H/2);
        SetWaypoint(1, TILE_W*16           , TILE_H*37           );
        SetWaypoint(2, TILE_W*15           , TILE_H*38           );
        SetWaypoint(3, TILE_W*15           , TILE_H*43 + TILE_H/2);
        break;

    case ROAD_QALAIZ_TOBANDJAN:
        endpointA = PL_QALAIZ;
        endpointB = PL_TOBANDJAN;
        SetWaypoint(0, TILE_W*25 + TILE_W/2, TILE_H*40 + TILE_H/2);
        SetWaypoint(1, TILE_W*25 + TILE_W/2, TILE_H*45 + TILE_H/2);
        SetWaypoint(2, TILE_W*23 + TILE_W/2, TILE_H*47 + TILE_H/2);
        break;

    case ROAD_QALAIZ_QUMANTH:
        endpointA = PL_QALAIZ;
        endpointB = PL_QUMANTH;
        SetWaypoint(0, TILE_W*24 + TILE_W/2, TILE_H*42 + TILE_H/2);
        SetWaypoint(1, TILE_W*24 + TILE_W/2, TILE_H*44 + TILE_H/2);
        SetWaypoint(2, TILE_W*23 + TILE_W/2, TILE_H*45 + TILE_H/2);
        SetWaypoint(3, TILE_W*16 + TILE_W/2, TILE_H*45 + TILE_H/2);
        break;

    case ROAD_QALAIZ_XENIA:
        endpointA = PL_QALAIZ;
        endpointB = PL_XENIA;
        SetWaypoint(0, TILE_W*24 + TILE_W/2, TILE_H*39 + TILE_H/2);
        SetWaypoint(1, TILE_W*28 + TILE_W/2, TILE_H*39 + TILE_H/2);
        SetWaypoint(2, TILE_W*30 + TILE_W/2, TILE_H*41 + TILE_H/2);
        SetWaypoint(3, TILE_W*30 + TILE_W/2, TILE_H*45 + TILE_H/2);
        break;
    }

    length = 0;
    for(int i = 0; i < lastWaypoint; ++i)
    {
        float dx = xWaypoints[i+1] - xWaypoints[i];
        float dy = yWaypoints[i+1] - yWaypoints[i];
        length += std::sqrt(dx*dx + dy*dy);
    }
    //std::cout << "Road " << id << " generated with length of " << length << std::endl;
}

Road::~Road()
{
    xWaypoints.clear();
    yWaypoints.clear();
}

void Road::SetGeography(int whichGeography)
{
    geography = whichGeography;
    switch(whichGeography)
    {
    case GEO_PLAINS:
        drawUnderColour = COL_JADE_1;
        break;
    case GEO_HILLS:
        drawUnderColour = COL_EARTHEN_2;
        break;
    case GEO_MOUNTAINS:
        drawUnderColour = COL_EARTHEN_1;
        break;
    case GEO_ICE_MOUNTAINS:
        drawUnderColour = COL_STEEL_4;
        break;
    case GEO_FOREST:
        drawUnderColour = COL_JADE_0;
        break;
    case GEO_RIVER:
        drawUnderColour = COL_AZURE_1;
        break;
    case GEO_OCEAN:
        drawUnderColour = COL_OCEAN_2;
        break;
    case GEO_TUNDRA:
        drawUnderColour = COL_STEEL_3;
        break;
    case GEO_DESERT:
        drawUnderColour = COL_ELECTRIC_4; //COL_CARAMEL_2;
        break;
    case GEO_RED_MESA:
        drawUnderColour = COL_RUST_2;
        break;
    case GEO_ASH_WASTE:
        drawUnderColour = COL_EARTHEN_1;
        break;
    case GEO_CLOUDS:
        drawUnderColour = COL_WIND_1;
        break;
    case GEO_TRANSIENT_LEY:
        drawUnderColour = COL_VIOLET_1;
        break;
    }

}

void Road::SetSovereignty(int whichSovereignty)
{
    sovereignty = whichSovereignty;

    switch(sovereignty)
    {
    case SOV_NULL:
        drawOverColour = COL_FLESH_2;
        break;
    case SOV_VERUS:
        drawOverColour = COL_JADE_2;
        break;
    case SOV_SHARUMNIR:
        drawOverColour = COL_STEEL_2;
        break;
    case SOV_XENIA:
        drawOverColour = COL_ELECTRIC_2;
        break;
    case SOV_THOUSAND_ISLES:
        drawOverColour = COL_AZURE_2;
        break;
    default:
        drawOverColour = COL_WIND_3;
        break;
    }
}

void Road::DrawSegmentsOnOverworld()
{
    al_draw_filled_circle(xWaypoints[0] - overworldCameraXPosition,
                          yWaypoints[0] - overworldCameraYPosition,
                          6, drawUnderColour);

    al_draw_filled_circle(xWaypoints[xWaypoints.rbegin()->first] - overworldCameraXPosition,
                          yWaypoints[yWaypoints.rbegin()->first] - overworldCameraYPosition,
                          6, drawUnderColour);

    for(unsigned i = 0; i < xWaypoints.size()-1; i++)
    {
        al_draw_line(xWaypoints[i] - overworldCameraXPosition,
                     yWaypoints[i] - overworldCameraYPosition,
                     xWaypoints[i+1] - overworldCameraXPosition,
                     yWaypoints[i+1] - overworldCameraYPosition,
                     drawUnderColour, 6);
        al_draw_line(xWaypoints[i] - overworldCameraXPosition,
                     yWaypoints[i] - overworldCameraYPosition,
                     xWaypoints[i+1] - overworldCameraXPosition,
                     yWaypoints[i+1] - overworldCameraYPosition,
                     drawOverColour, 2);
    }

    al_draw_filled_circle(xWaypoints[0] - overworldCameraXPosition,
                          yWaypoints[0] - overworldCameraYPosition,
                          3, drawOverColour);

    al_draw_filled_circle(xWaypoints[xWaypoints.rbegin()->first] - overworldCameraXPosition,
                          yWaypoints[yWaypoints.rbegin()->first] - overworldCameraYPosition,
                          3, drawOverColour);
}

void Road::SetWaypoint(unsigned index, int x, int y)
{
    xWaypoints[index] = x;
    yWaypoints[index] = y;

    lastWaypoint = xWaypoints.size()-1;
}

float Road::ReturnSegmentLength(int a, int b)
{
    float x1 = xWaypoints[a];
    float y1 = yWaypoints[a];
    float x2 = xWaypoints[b];
    float y2 = yWaypoints[b];

    return std::hypot(y2-y1,x2-x1);
}
