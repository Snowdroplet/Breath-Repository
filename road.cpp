#include "road.h"

std::map<int, Road*> Road::roads;

Road::Road(int id)
{
    identity = id;
    selfPointer = this;

    switch(identity)
    {
    case ROAD_ERICENNES_CHORAS:
        name = "Ericennes-Choras Road";
        endpointA = PL_ERICENNES;
        endpointB = PL_CHORAS;
        SetWaypoint(0, TILE_W*21 + TILE_W/2, TILE_H*19 + TILE_H/2);
        SetWaypoint(1, TILE_W*24, TILE_H*18);
        SetWaypoint(2, TILE_W*24, TILE_H*13 + TILE_H/2);
        break;

    case ROAD_ERICENNES_KETH_KETHER:
        name = "Ericennes-Keth Kether Road";
        endpointA = PL_ERICENNES;
        endpointB = PL_KETH_KETHER;
        SetWaypoint(0, TILE_W*18 + TILE_W/2, TILE_H*20 + TILE_H/2);
        SetWaypoint(1, TILE_W*17, TILE_H*23);
        SetWaypoint(2, TILE_W*13 + TILE_W/2, TILE_H*24);
        break;

    case ROAD_ERICENNES_KETH_ENTWEIR:
        name = "Ericennes-Keth Entweir Road";
        endpointA = PL_ERICENNES;
        endpointB = PL_KETH_ENTWEIR;
        SetWaypoint(0, TILE_W*18 + TILE_W/2, TILE_H*19 + TILE_H/2);
        SetWaypoint(1, TILE_W*16, TILE_H*18);
        SetWaypoint(2, TILE_W*10 + TILE_W/2, TILE_H*17);
        break;

    case ROAD_ERICENNES_ROSKANEL:
        name = "Ericennes-Roskanel Road";
        endpointA = PL_ERICENNES;
        endpointB = PL_ROSKANEL;
        SetWaypoint(0, TILE_W*21 + TILE_W/2, TILE_H*20 + TILE_H/2);
        SetWaypoint(1, TILE_W*22 + TILE_W/2, TILE_H*22 + TILE_H/2);
        SetWaypoint(2, TILE_W*24 + TILE_W/2, TILE_H*24);
        break;

    case ROAD_KETH_KETHER_KETH_ENTWEIR:
        name = "Keth Kether-Keth Entweir Road";
        endpointA = PL_KETH_KETHER;
        endpointB = PL_KETH_ENTWEIR;
        SetWaypoint(0, TILE_W*12, TILE_H*22 + TILE_H/2);
        SetWaypoint(1, TILE_W*10, TILE_H*21);
        SetWaypoint(2, TILE_W*9, TILE_H*18 + TILE_H/2);
        break;

    case ROAD_KETH_KETHER_VIELLEICHT:
        name = "Keth Kether-Vielleicht Road";
        endpointA = PL_KETH_KETHER;
        endpointB = PL_VIELLEICHT;
        SetWaypoint(0, TILE_W*10 + TILE_W/2, TILE_H*24);
        SetWaypoint(1, TILE_W*6 + TILE_W/2, TILE_H*27 + TILE_H/2);
        SetWaypoint(2, TILE_W*2 + TILE_W/2, TILE_H*27 + TILE_H/2);
        break;

    case ROAD_KETH_KETHER_QUELLUDE:
        name = "Keth Kether-Quellude Road";
        endpointA = PL_KETH_KETHER;
        endpointB = PL_QUELLUDE;
        SetWaypoint(0, TILE_W*12, TILE_H*25 + TILE_W/2);
        SetWaypoint(1, TILE_W*12, TILE_H*28);
        SetWaypoint(2, TILE_W*7 + TILE_W/2, TILE_H*32);
        break;

    case ROAD_KETH_ENTWEIR_AMBLEFORTH:
        name = "Keth Entweir-Ambleforth Road";
        endpointA = PL_KETH_ENTWEIR;
        endpointB = PL_AMBLEFORTH;
        SetWaypoint(0, TILE_W*7 + TILE_W/2, TILE_H*17);
        SetWaypoint(1, TILE_W*5, TILE_H*17);
        SetWaypoint(2, TILE_W*4, TILE_H*15 + TILE_H/2);
        break;

    case ROAD_VIELLEICHT_QUELLUDE:
        name = "Vielleicht-Quellude Road";
        endpointA = PL_VIELLEICHT;
        endpointB = PL_QUELLUDE;
        SetWaypoint(0, TILE_W*2 + TILE_W/2, TILE_H*28 + TILE_H/2);
        SetWaypoint(1, TILE_W*3, TILE_H*31);
        SetWaypoint(2, TILE_W*4 + TILE_W/2, TILE_H*32);
        break;

    case ROAD_ROSKANEL_ROSELLA:
        name = "Roskanel-Rosella Road";
        endpointA = PL_ROSKANEL;
        endpointB = PL_ROSELLA;
        SetWaypoint(0, TILE_W*26, TILE_H*25 + TILE_H/2);
        SetWaypoint(1, TILE_W*26, TILE_H*28 + TILE_H/2);
        SetWaypoint(2, TILE_W*27 + TILE_W/2, TILE_H*28 + TILE_H/2);
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

void Road::DrawSegmentsOnOverworld()
{
    al_draw_filled_circle(xWaypoints[0] - overworldCameraXPosition,
                          yWaypoints[0] - overworldCameraYPosition,
                          6, COL_DARK_BROWN);

    al_draw_filled_circle(xWaypoints[xWaypoints.rbegin()->first] - overworldCameraXPosition,
                          yWaypoints[yWaypoints.rbegin()->first] - overworldCameraYPosition,
                          6, COL_DARK_BROWN);

    for(unsigned i = 0; i < xWaypoints.size()-1; i++)
    {
        al_draw_line(xWaypoints[i] - overworldCameraXPosition,
                     yWaypoints[i] - overworldCameraYPosition,
                     xWaypoints[i+1] - overworldCameraXPosition,
                     yWaypoints[i+1] - overworldCameraYPosition,
                     COL_DARK_BROWN, 6);
        al_draw_line(xWaypoints[i] - overworldCameraXPosition,
                     yWaypoints[i] - overworldCameraYPosition,
                     xWaypoints[i+1] - overworldCameraXPosition,
                     yWaypoints[i+1] - overworldCameraYPosition,
                     COL_BROWN, 2);
    }

    al_draw_filled_circle(xWaypoints[0] - overworldCameraXPosition,
                          yWaypoints[0] - overworldCameraYPosition,
                          3, COL_BROWN);

    al_draw_filled_circle(xWaypoints[xWaypoints.rbegin()->first] - overworldCameraXPosition,
                          yWaypoints[yWaypoints.rbegin()->first] - overworldCameraYPosition,
                          3, COL_BROWN);
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
