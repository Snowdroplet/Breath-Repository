#ifndef ROAD_H_INCLUDED
#define ROAD_H_INCLUDED

#include <iostream>
#include <map>


#include "gamestate.h"
#include "overworld.h"
#include "roadconsts.h"
#include "placeconsts.h"

class Road
{
public:
    int identity;
    float length;

    int endpointA; // Use the identity of a place.
    int endpointB;

    std::map<int,int>xWaypoints;
    std::map<int,int>yWaypoints;
    int lastWaypoint; // When not reversed.

    Road(int id);
    ~Road();

    void SetWaypoint(unsigned index, int x, int y);

    float ReturnSegmentLength(int a, int b);

    void DrawSegmentsOnOverworld();
};

#endif // ROAD_H_INCLUDED
