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
        SetWaypoint(0, Tile::WIDTH*21 + Tile::WIDTH/2, Tile::HEIGHT*19 + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*24, Tile::HEIGHT*18);
        SetWaypoint(2, Tile::WIDTH*24, Tile::HEIGHT*13 + Tile::HEIGHT/2);
        break;

    case ROAD_ERICENNES_KETH_KETHER:
        endpointA = PL_ERICENNES;
        endpointB = PL_KETH_KETHER;
        SetWaypoint(0, Tile::WIDTH*18 + Tile::WIDTH/2, Tile::HEIGHT*20 + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*13 + Tile::WIDTH/2, Tile::HEIGHT*20 + Tile::HEIGHT/2);
        SetWaypoint(2, Tile::WIDTH*13 + Tile::WIDTH/2, Tile::HEIGHT*24);
        break;

    case ROAD_ERICENNES_KETH_ENTWEIR:
        endpointA = PL_ERICENNES;
        endpointB = PL_KETH_ENTWEIR;
        SetWaypoint(0, Tile::WIDTH*18 + Tile::WIDTH/2, Tile::HEIGHT*19 + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*16, Tile::HEIGHT*17);
        SetWaypoint(2, Tile::WIDTH*10 + Tile::WIDTH/2, Tile::HEIGHT*17);
        break;

    case ROAD_ERICENNES_ROSKANEL:
        endpointA = PL_ERICENNES;
        endpointB = PL_ROSKANEL;
        SetWaypoint(0, Tile::WIDTH*21 + Tile::WIDTH/2, Tile::HEIGHT*20 + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*23 + Tile::WIDTH/2, Tile::HEIGHT*22 + Tile::HEIGHT/2);
        SetWaypoint(2, Tile::WIDTH*26, Tile::HEIGHT*22 + Tile::HEIGHT/2);
        break;

    case ROAD_WATERWAY_ERICENNES_COLDLAKE:
        endpointA = PL_ERICENNES;
        endpointB = PL_COLDLAKE;
        SetWaypoint(0, Tile::WIDTH*20, Tile::HEIGHT*18 + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*20, Tile::HEIGHT*17           );
        SetWaypoint(2, Tile::WIDTH*16, Tile::HEIGHT*13           );
        SetWaypoint(3, Tile::WIDTH*16, Tile::HEIGHT*11 + Tile::HEIGHT/2);
        break;

    case ROAD_WATERWAY_ERICENNES_VEINS:
        endpointA = PL_ERICENNES;
        endpointB = PL_VEINS;
        SetWaypoint(0, Tile::WIDTH*20, Tile::HEIGHT*21 + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*20, Tile::HEIGHT*23           );
        SetWaypoint(2, Tile::WIDTH*16, Tile::HEIGHT*27           );
        SetWaypoint(3, Tile::WIDTH*16, Tile::HEIGHT*31 + Tile::HEIGHT/2);
        break;

    case ROAD_CHORAS_COLDLAKE:
        endpointA = PL_CHORAS;
        endpointB = PL_COLDLAKE;
        SetWaypoint(0, Tile::WIDTH*22 + Tile::WIDTH/2, Tile::HEIGHT*11 + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*20 + Tile::WIDTH/2, Tile::HEIGHT*10);
        SetWaypoint(2, Tile::WIDTH*17 + Tile::WIDTH/2, Tile::HEIGHT*10);
        break;

    case ROAD_CHORAS_RAMSHORN:
        endpointA = PL_CHORAS;
        endpointB = PL_RAMSHORN;
        SetWaypoint(0, Tile::WIDTH*25 + Tile::WIDTH/2, Tile::HEIGHT*12);
        SetWaypoint(1, Tile::WIDTH*29 + Tile::WIDTH/2, Tile::HEIGHT*12);
        SetWaypoint(2, Tile::WIDTH*31, Tile::HEIGHT*10 + Tile::HEIGHT/2);
        break;

    case ROAD_CHORAS_HOLLYHEAD:
        endpointA = PL_CHORAS;
        endpointB = PL_HOLLYHEAD;
        SetWaypoint(0, Tile::WIDTH*24, Tile::HEIGHT*10 + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*24, Tile::HEIGHT*9);
        SetWaypoint(2, Tile::WIDTH*25, Tile::HEIGHT*8);
        SetWaypoint(3, Tile::WIDTH*25, Tile::HEIGHT*6 + Tile::HEIGHT/2);
        break;

    case ROAD_KETH_KETHER_KETH_ENTWEIR:
        endpointA = PL_KETH_KETHER;
        endpointB = PL_KETH_ENTWEIR;
        SetWaypoint(0, Tile::WIDTH*12, Tile::HEIGHT*22 + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*9, Tile::HEIGHT*22 + Tile::HEIGHT/2);
        SetWaypoint(2, Tile::WIDTH*9, Tile::HEIGHT*18 + Tile::HEIGHT/2);
        break;

    case ROAD_KETH_KETHER_VIELLEICHT:
        endpointA = PL_KETH_KETHER;
        endpointB = PL_VIELLEICHT;
        SetWaypoint(0, Tile::WIDTH*10 + Tile::WIDTH/2, Tile::HEIGHT*24);
        SetWaypoint(1, Tile::WIDTH*6, Tile::HEIGHT*24);
        SetWaypoint(2, Tile::WIDTH*2 + Tile::WIDTH/2, Tile::HEIGHT*27 + Tile::HEIGHT/2);
        break;

    case ROAD_KETH_KETHER_QUELLUDE:
        endpointA = PL_KETH_KETHER;
        endpointB = PL_QUELLUDE;
        SetWaypoint(0, Tile::WIDTH*12, Tile::HEIGHT*25 + Tile::WIDTH/2);
        SetWaypoint(1, Tile::WIDTH*12, Tile::HEIGHT*28);
        SetWaypoint(2, Tile::WIDTH*7 + Tile::WIDTH/2, Tile::HEIGHT*32);
        break;

    case ROAD_KETH_ENTWEIR_AMBLEFORTH:
        endpointA = PL_KETH_ENTWEIR;
        endpointB = PL_AMBLEFORTH;
        SetWaypoint(0, Tile::WIDTH*7 + Tile::WIDTH/2, Tile::HEIGHT*17);
        SetWaypoint(1, Tile::WIDTH*5, Tile::HEIGHT*17);
        SetWaypoint(2, Tile::WIDTH*4, Tile::HEIGHT*15 + Tile::HEIGHT/2);
        break;

    case ROAD_VIELLEICHT_QUELLUDE:
        endpointA = PL_VIELLEICHT;
        endpointB = PL_QUELLUDE;
        SetWaypoint(0, Tile::WIDTH*2 + Tile::WIDTH/2, Tile::HEIGHT*28 + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*2 + Tile::WIDTH/2, Tile::HEIGHT*32);
        SetWaypoint(2, Tile::WIDTH*4 + Tile::WIDTH/2, Tile::HEIGHT*32);
        break;

    case ROAD_WATERWAY_VIELLEICHT_REACH:
        endpointA = PL_VIELLEICHT;
        endpointB = PL_REACH;
        SetWaypoint(0, Tile::WIDTH*(-1)  + Tile::WIDTH/2, Tile::HEIGHT*28 + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*(-11) + Tile::WIDTH/2, Tile::HEIGHT*29 + Tile::HEIGHT/2);
        break;

    case ROAD_AMBLEFORTH_OBSERVIA:
        endpointA = PL_AMBLEFORTH;
        endpointB = PL_OBSERVIA;
        SetWaypoint(0, Tile::WIDTH*4,            Tile::HEIGHT*12 + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*9 + Tile::WIDTH/2, Tile::HEIGHT*12 + Tile::HEIGHT/2);
        SetWaypoint(2, Tile::WIDTH*9 + Tile::WIDTH/2, Tile::HEIGHT*6  + Tile::HEIGHT/2);
        break;

    case ROAD_ROSKANEL_ROSELLA:
        endpointA = PL_ROSKANEL;
        endpointB = PL_ROSELLA;
        SetWaypoint(0, Tile::WIDTH*26, Tile::HEIGHT*25 + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*26, Tile::HEIGHT*28 + Tile::HEIGHT/2);
        SetWaypoint(2, Tile::WIDTH*27 + Tile::WIDTH/2, Tile::HEIGHT*28 + Tile::HEIGHT/2);
        break;

    case ROAD_ROSKANEL_YHANE:
        endpointA = PL_ROSKANEL;
        endpointB = PL_YHANE;
        SetWaypoint(0, Tile::WIDTH*24 + Tile::WIDTH/2, Tile::HEIGHT*24);
        SetWaypoint(1, Tile::WIDTH*24 + Tile::WIDTH/2, Tile::HEIGHT*27 + Tile::HEIGHT/2);
        SetWaypoint(2, Tile::WIDTH*22 + Tile::WIDTH/2, Tile::HEIGHT*29 + Tile::HEIGHT/2);
        SetWaypoint(3, Tile::WIDTH*21 + Tile::WIDTH/2, Tile::HEIGHT*29 + Tile::HEIGHT/2);
        break;

    case ROAD_OBSERVIA_COLDLAKE:
        endpointA = PL_OBSERVIA;
        endpointB = PL_COLDLAKE;
        SetWaypoint(0, Tile::WIDTH*11, Tile::HEIGHT*6 + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*11, Tile::HEIGHT*10);
        SetWaypoint(2, Tile::WIDTH*14 + Tile::WIDTH/2, Tile::HEIGHT*10);
        break;

    case ROAD_OBSERVIA_UMBERDELL:
        endpointA = PL_OBSERVIA;
        endpointB = PL_UMBERDELL;
        SetWaypoint(0, Tile::WIDTH*9 + Tile::WIDTH/2, Tile::HEIGHT*5);
        SetWaypoint(1, Tile::WIDTH*7, Tile::HEIGHT*5);
        SetWaypoint(2, Tile::WIDTH*7, Tile::HEIGHT*3);
        SetWaypoint(3, Tile::WIDTH*15 + Tile::WIDTH/2, Tile::HEIGHT*3);
        break;

    case ROAD_RAMSHORN_JASPER:
        endpointA = PL_RAMSHORN;
        endpointB = PL_JASPER;
        SetWaypoint(0, Tile::WIDTH*31, Tile::HEIGHT*7 + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*31, Tile::HEIGHT*4);
        SetWaypoint(2, Tile::WIDTH*33, Tile::HEIGHT*2);
        SetWaypoint(3, Tile::WIDTH*34 + Tile::WIDTH/2, Tile::HEIGHT*2);
        break;

    case ROAD_HOLLYHEAD_RUMNIR:
        endpointA = PL_HOLLYHEAD;
        endpointB = PL_RUMNIR;
        SetWaypoint(0, Tile::WIDTH*25, Tile::HEIGHT*3 + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*25, Tile::HEIGHT*1);
        SetWaypoint(2, Tile::WIDTH*21, Tile::HEIGHT*(-1) - Tile::HEIGHT/2);
        SetWaypoint(3, Tile::WIDTH*21, Tile::HEIGHT*(-4) - Tile::HEIGHT/2);
        break;

    case ROAD_RUMNIR_HEWNHEIM:
        endpointA = PL_RUMNIR;
        endpointB = PL_HEWNHEIM;
        SetWaypoint(0, Tile::WIDTH*19 + Tile::WIDTH/2, Tile::HEIGHT*(-7) + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*17 + Tile::WIDTH/2, Tile::HEIGHT*(-9) + Tile::HEIGHT/2);
        SetWaypoint(2, Tile::WIDTH*10 + Tile::WIDTH/2, Tile::HEIGHT*(-9) + Tile::HEIGHT/2);
        break;

    case ROAD_RUMNIR_ARTAS_ROCK:
        endpointA = PL_RUMNIR;
        endpointB = PL_ARTAS_ROCK;
        SetWaypoint(0, Tile::WIDTH*20 + Tile::WIDTH/2, Tile::HEIGHT*(-8) + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*19, Tile::HEIGHT*(-9));
        SetWaypoint(2, Tile::WIDTH*19, Tile::HEIGHT*(-15) + Tile::HEIGHT/2);
        break;

    case ROAD_HEWNHEIM_VERSE:
        endpointA = PL_HEWNHEIM;
        endpointB = PL_VERSE;
        SetWaypoint(0, Tile::WIDTH*8  + Tile::WIDTH/2, Tile::HEIGHT*(-11) + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*8  + Tile::HEIGHT/2, Tile::HEIGHT*(-13)           );
        SetWaypoint(2, Tile::WIDTH*12 + Tile::WIDTH/2, Tile::HEIGHT*(-18) + Tile::HEIGHT/2);
        SetWaypoint(3, Tile::WIDTH*12 + Tile::WIDTH/2, Tile::HEIGHT*(-21) + Tile::HEIGHT/2);
        break;

    case ROAD_WATERWAY_HEWNHEIM_YULMER:
        endpointA = PL_HEWNHEIM;
        endpointB = PL_YULMER;
        SetWaypoint(0, Tile::WIDTH*( 7) + Tile::WIDTH/2, Tile::HEIGHT*(-9) + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*(-3) + Tile::WIDTH/2, Tile::HEIGHT*(-7)+ Tile::HEIGHT/2);
        break;

    case ROAD_ARTAS_ROCK_VERSE:
        endpointA = PL_ARTAS_ROCK;
        endpointB = PL_VERSE;
        SetWaypoint(0, Tile::WIDTH*19,            Tile::HEIGHT*(-18) + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*13 + Tile::WIDTH/2, Tile::HEIGHT*(-18) + Tile::HEIGHT/2);
        SetWaypoint(2, Tile::WIDTH*13 + Tile::WIDTH/2, Tile::HEIGHT*(-21) + Tile::HEIGHT/2);
        break;

    case ROAD_YHANE_VEINS:
        endpointA = PL_YHANE;
        endpointB = PL_VEINS;
        SetWaypoint(0, Tile::WIDTH*19 + Tile::WIDTH/2, Tile::HEIGHT*31 + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*19 + Tile::WIDTH/2, Tile::HEIGHT*33 + Tile::HEIGHT/2);
        SetWaypoint(2, Tile::WIDTH*17 + Tile::WIDTH/2, Tile::HEIGHT*33 + Tile::HEIGHT/2);
        break;

    case ROAD_YHANE_QALAIZ:
        endpointA = PL_YHANE;
        endpointB = PL_QALAIZ;
        SetWaypoint(0, Tile::WIDTH*20 + Tile::WIDTH/2, Tile::HEIGHT*31 + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*20 + Tile::WIDTH/2, Tile::HEIGHT*36 + Tile::HEIGHT/2);
        SetWaypoint(2, Tile::WIDTH*22 + Tile::WIDTH/2, Tile::HEIGHT*39 + Tile::HEIGHT/2);
        break;

    case ROAD_WATERWAY_VEINS_QUMANTH:
        endpointA = PL_VEINS;
        endpointB = PL_QUMANTH;
        SetWaypoint(0, Tile::WIDTH*16           , Tile::HEIGHT*34 + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*16           , Tile::HEIGHT*37           );
        SetWaypoint(2, Tile::WIDTH*15           , Tile::HEIGHT*38           );
        SetWaypoint(3, Tile::WIDTH*15           , Tile::HEIGHT*43 + Tile::HEIGHT/2);
        break;

    case ROAD_QALAIZ_TOBANDJAN:
        endpointA = PL_QALAIZ;
        endpointB = PL_TOBANDJAN;
        SetWaypoint(0, Tile::WIDTH*25 + Tile::WIDTH/2, Tile::HEIGHT*40 + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*25 + Tile::WIDTH/2, Tile::HEIGHT*45 + Tile::HEIGHT/2);
        SetWaypoint(2, Tile::WIDTH*23 + Tile::WIDTH/2, Tile::HEIGHT*47 + Tile::HEIGHT/2);
        break;

    case ROAD_QALAIZ_QUMANTH:
        endpointA = PL_QALAIZ;
        endpointB = PL_QUMANTH;
        SetWaypoint(0, Tile::WIDTH*24 + Tile::WIDTH/2, Tile::HEIGHT*42 + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*24 + Tile::WIDTH/2, Tile::HEIGHT*44 + Tile::HEIGHT/2);
        SetWaypoint(2, Tile::WIDTH*23 + Tile::WIDTH/2, Tile::HEIGHT*45 + Tile::HEIGHT/2);
        SetWaypoint(3, Tile::WIDTH*16 + Tile::WIDTH/2, Tile::HEIGHT*45 + Tile::HEIGHT/2);
        break;

    case ROAD_QALAIZ_XENIA:
        endpointA = PL_QALAIZ;
        endpointB = PL_XENIA;
        SetWaypoint(0, Tile::WIDTH*24 + Tile::WIDTH/2, Tile::HEIGHT*39 + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*28 + Tile::WIDTH/2, Tile::HEIGHT*39 + Tile::HEIGHT/2);
        SetWaypoint(2, Tile::WIDTH*30 + Tile::WIDTH/2, Tile::HEIGHT*41 + Tile::HEIGHT/2);
        SetWaypoint(3, Tile::WIDTH*30 + Tile::WIDTH/2, Tile::HEIGHT*45 + Tile::HEIGHT/2);
        break;

    case ROAD_WATERWAY_QUMANTH_HATHSERA:
        endpointA = PL_QUMANTH;
        endpointB = PL_HATHSERA;
        SetWaypoint(0, Tile::WIDTH*(13) + Tile::WIDTH/2, Tile::HEIGHT*45 + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*(-4) + Tile::WIDTH/2, Tile::HEIGHT*42 + Tile::HEIGHT/2);
        break;

    case ROAD_WATERWAY_REACH_KARUNE:
        endpointA = PL_REACH;
        endpointB = PL_KARUNE;
        SetWaypoint(0, Tile::WIDTH*(-13) + Tile::WIDTH/2, Tile::HEIGHT*28 + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*(-11) + Tile::WIDTH/2, Tile::HEIGHT*12 + Tile::HEIGHT/2);
        break;

    case ROAD_WATERWAY_REACH_HATHSERA:
        endpointA = PL_REACH;
        endpointB = PL_HATHSERA;
        SetWaypoint(0, Tile::WIDTH*(-13) + Tile::WIDTH/2, Tile::HEIGHT*31 + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*( -7) + Tile::WIDTH/2, Tile::HEIGHT*41  + Tile::HEIGHT/2);
        break;

    case ROAD_WATERWAY_KARUNE_YULMER:
        endpointA = PL_KARUNE;
        endpointB = PL_YULMER;
        SetWaypoint(0, Tile::WIDTH*(-10) + Tile::WIDTH/2, Tile::HEIGHT*  9  + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*( -5) + Tile::WIDTH/2, Tile::HEIGHT*(-5) + Tile::HEIGHT/2);
        break;

    case ROAD_WATERWAY_HATHSERA_VORDOZAAL:
        endpointA = PL_HATHSERA;
        endpointB = PL_VORDOZAAL;
        SetWaypoint(0, Tile::WIDTH*(-6) + Tile::WIDTH/2, Tile::HEIGHT*43 + Tile::HEIGHT/2);
        SetWaypoint(1, Tile::WIDTH*(-8) + Tile::WIDTH/2, Tile::HEIGHT*46 + Tile::HEIGHT/2);
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
        drawUnderColour = AllegroCustom::COL_JADE_1;
        break;
    case GEO_HILLS:
        drawUnderColour = AllegroCustom::COL_EARTHEN_2;
        break;
    case GEO_MOUNTAINS:
        drawUnderColour = AllegroCustom::COL_EARTHEN_1;
        break;
    case GEO_ICE_MOUNTAINS:
        drawUnderColour = AllegroCustom::COL_STEEL_4;
        break;
    case GEO_FOREST:
        drawUnderColour = AllegroCustom::COL_JADE_0;
        break;
    case GEO_RIVER:
        drawUnderColour = AllegroCustom::COL_AZURE_1;
        break;
    case GEO_OCEAN:
        drawUnderColour = AllegroCustom::COL_OCEAN_2;
        break;
    case GEO_TUNDRA:
        drawUnderColour = AllegroCustom::COL_STEEL_3;
        break;
    case GEO_DESERT:
        drawUnderColour = AllegroCustom::COL_ELECTRIC_4; //COL_CARAMEL_2;
        break;
    case GEO_RED_MESA:
        drawUnderColour = AllegroCustom::COL_RUST_2;
        break;
    case GEO_ASH_WASTE:
        drawUnderColour = AllegroCustom::COL_EARTHEN_1;
        break;
    case GEO_CLOUDS:
        drawUnderColour = AllegroCustom::COL_WIND_1;
        break;
    case GEO_TRANSIENT_LEY:
        drawUnderColour = AllegroCustom::COL_VIOLET_1;
        break;
    }

}

void Road::SetSovereignty(int whichSovereignty)
{
    sovereignty = whichSovereignty;

    switch(sovereignty)
    {
    case SOV_NULL:
        drawOverColour = AllegroCustom::COL_FLESH_2;
        break;
    case SOV_VERUS:
        drawOverColour = AllegroCustom::COL_JADE_2;
        break;
    case SOV_SHARUMNIR:
        drawOverColour = AllegroCustom::COL_STEEL_2;
        break;
    case SOV_XENIA:
        drawOverColour = AllegroCustom::COL_ELECTRIC_2;
        break;
    case SOV_THOUSAND_ISLES:
        drawOverColour = AllegroCustom::COL_AZURE_2;
        break;
    default:
        drawOverColour = AllegroCustom::COL_WIND_3;
        break;
    }
}

void Road::DrawSegmentsOnOverworld()
{
    al_draw_filled_circle(xWaypoints[0] - Camera::xPosition,
                          yWaypoints[0] - Camera::yPosition,
                          6, drawUnderColour);

    al_draw_filled_circle(xWaypoints[xWaypoints.rbegin()->first] - Camera::xPosition,
                          yWaypoints[yWaypoints.rbegin()->first] - Camera::yPosition,
                          6, drawUnderColour);

    for(unsigned i = 0; i < xWaypoints.size()-1; i++)
    {
        al_draw_line(xWaypoints[i] - Camera::xPosition,
                     yWaypoints[i] - Camera::yPosition,
                     xWaypoints[i+1] - Camera::xPosition,
                     yWaypoints[i+1] - Camera::yPosition,
                     drawUnderColour, 6);
        al_draw_line(xWaypoints[i] - Camera::xPosition,
                     yWaypoints[i] - Camera::yPosition,
                     xWaypoints[i+1] - Camera::xPosition,
                     yWaypoints[i+1] - Camera::yPosition,
                     drawOverColour, 2);
    }

    al_draw_filled_circle(xWaypoints[0] - Camera::xPosition,
                          yWaypoints[0] - Camera::yPosition,
                          3, drawOverColour);

    al_draw_filled_circle(xWaypoints[xWaypoints.rbegin()->first] - Camera::xPosition,
                          yWaypoints[yWaypoints.rbegin()->first] - Camera::yPosition,
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
