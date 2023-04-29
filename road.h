#ifndef ROAD_H_INCLUDED
#define ROAD_H_INCLUDED

#include <iostream>
#include <map>

#include "gamestate.h"
#include "overworld.h"
#include "roadindex.h"
#include "placeindex.h"

class Road
{
public:
    static std::map<int,Road*>roads;
/// Identity
    int identity;
    Road *selfPointer;

    std::string name;

/// Connections
    int endpointA; // Use the identity of a place.
    int endpointB;

/// Geometry
    float length;
    std::map<int,int>xWaypoints;
    std::map<int,int>yWaypoints;
    int lastWaypoint; // When not reversed.

/// Constructor
    Road(int id);
    ~Road();


    void SetWaypoint(unsigned index, int x, int y);

    float ReturnSegmentLength(int a, int b);

    void DrawSegmentsOnOverworld();
};

#endif // ROAD_H_INCLUDED
