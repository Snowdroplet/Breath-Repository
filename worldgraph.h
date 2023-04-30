#ifndef WORLDGRAPH_H_INCLUDED
#define WORLDGRAPH_H_INCLUDED

//#define debug_output_worldgraph_dijkstra

#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

#include "placeindex.h"

/// Dependencies
class Place;

class WorldGraph
{
public:
/// Base graph
    static std::map<int, std::map<int,float>> s_baseGraph;
    static void AddPlaceToBaseGraph(int vertex); // Places are vertices
    static void AddRoadToBaseGraph(int endA, int endB, float weight); // Roads are edges


/// Current graph
    std::map<int, std::map<int,float>> graph; // A caravan's personal pathfinding graph. <place, <connected places, edge weight>
    std::vector<int>path; /// Later modify to support multiple paths; at least one for each objective.

/// Constructor
    WorldGraph();
    ~WorldGraph();

/// Pathfind
    void Dijkstra(int source, int destination);

/// Manipulate current graph
    void SetToBaseGraph();
};

#endif // WORLDGRAPH_H_INCLUDED
