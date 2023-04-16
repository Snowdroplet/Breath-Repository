#include "road.h"

Road::Road(int id)
{
    identity = id;
    switch(identity)
    {
    case ROAD_ERICENNES_CHORAS:
        endpointA = PL_ERICENNES;
        endpointB = PL_CHORAS;
        SetWaypoint(0, TILE_W*22, TILE_H*20);
        SetWaypoint(1, TILE_W*24, TILE_H*18);
        SetWaypoint(2, TILE_W*24, TILE_H*14);
        break;

    case ROAD_ERICENNES_KETH_KETHER:
        endpointA = PL_ERICENNES;
        endpointB = PL_KETH_KETHER;
        SetWaypoint(0, TILE_W*20, TILE_H*22);
        SetWaypoint(1, TILE_W*18, TILE_H*24);
        SetWaypoint(2, TILE_W*14, TILE_H*24);
        break;

    case ROAD_ERICENNES_KETH_ENTWEIR:
        endpointA = PL_ERICENNES;
        endpointB = PL_KETH_KETHER;
        SetWaypoint(0, TILE_W*18, TILE_H*20);
        SetWaypoint(1, TILE_W*16, TILE_H*18);
        SetWaypoint(2, TILE_W*13, TILE_H*18);
        break;

    case ROAD_KETH_KETHER_KETH_ENTWEIR:
        endpointA = PL_KETH_KETHER;
        endpointB = PL_KETH_ENTWEIR;
        SetWaypoint(0, TILE_W*12, TILE_H*22);
        SetWaypoint(1, TILE_W*11, TILE_H*21);
        SetWaypoint(2, TILE_W*11, TILE_H*20);
        break;

    case ROAD_KETH_KETHER_VIELLEICHT:
        endpointA = PL_KETH_KETHER;
        endpointB = PL_VIELLEICHT;
        SetWaypoint(0, TILE_W*10, TILE_H*24);
        SetWaypoint(1, TILE_W*8, TILE_H*26);
        SetWaypoint(2, TILE_W*1, TILE_H*26);
        break;

    case ROAD_KETH_KETHER_QUELLUDE:
        endpointA = PL_KETH_KETHER;
        endpointB = PL_QUELLUDE;
        SetWaypoint(0, TILE_W*12, TILE_H*26);
        SetWaypoint(1, TILE_W*12, TILE_H*28);
        SetWaypoint(2, TILE_W*8, TILE_H*32);
        break;

    case ROAD_KETH_ENTWEIR_AMBLEFORTH:
        endpointA = PL_KETH_ENTWEIR;
        endpointB = PL_AMBLEFORTH;
        SetWaypoint(0, TILE_W*9, TILE_H*18);
        SetWaypoint(1, TILE_W*6, TILE_H*18);
        SetWaypoint(2, TILE_W*4, TILE_H*16);
        break;

    case ROAD_VIELLEICHT_QUELLUDE:
        endpointA = PL_VIELLEICHT;
        endpointB = PL_QUELLUDE;
        SetWaypoint(0, TILE_W*3, TILE_H*28);
        SetWaypoint(1, TILE_W*3, TILE_H*31);
        SetWaypoint(2, TILE_W*4, TILE_H*32);
        break;

    }
}

Road::~Road()
{
    xWaypoints.clear();
    yWaypoints.clear();
}

void Road::DrawOnOverworld()
{
    al_draw_filled_circle(xWaypoints[0] - overworldCameraXPosition,
                          yWaypoints[0] - overworldCameraYPosition,
                          6, COL_BLUE);

    al_draw_filled_circle(xWaypoints[xWaypoints.rbegin()->first] - overworldCameraXPosition,
                          yWaypoints[yWaypoints.rbegin()->first] - overworldCameraYPosition,
                          6, COL_BLUE);

    for(unsigned i = 0; i < xWaypoints.size()-1; i++)
    {
        al_draw_line(xWaypoints[i] - overworldCameraXPosition,
                     yWaypoints[i] - overworldCameraYPosition,
                     xWaypoints[i+1] - overworldCameraXPosition,
                     yWaypoints[i+1] - overworldCameraYPosition,
                     COL_BLUE, 6);
        al_draw_line(xWaypoints[i] - overworldCameraXPosition,
                     yWaypoints[i] - overworldCameraYPosition,
                     xWaypoints[i+1] - overworldCameraXPosition,
                     yWaypoints[i+1] - overworldCameraYPosition,
                     COL_INDIGO, 2);
    }

    al_draw_filled_circle(xWaypoints[0] - overworldCameraXPosition,
                          yWaypoints[0] - overworldCameraYPosition,
                          3, COL_INDIGO);

    al_draw_filled_circle(xWaypoints[xWaypoints.rbegin()->first] - overworldCameraXPosition,
                          yWaypoints[yWaypoints.rbegin()->first] - overworldCameraYPosition,
                          3, COL_INDIGO);
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
