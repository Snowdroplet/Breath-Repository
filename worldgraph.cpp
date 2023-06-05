#include "worldgraph.h"

std::map<int,std::map<int,float>>WorldGraph::s_baseGraph;

void WorldGraph::AddPlaceToBaseGraph(int vertex)
{
    if (s_baseGraph.find(vertex) == s_baseGraph.end()) // vertex not already listed
    {
        s_baseGraph[vertex] = {}; // Creates an empty map at index "vertex"
#ifdef debug_output_worldgraph_dijkstra
        std::cout << "Vertex " << vertex << " added to base graph." << std::endl;
#endif
    }

}


void WorldGraph::AddRoadToBaseGraph(int endA, int endB, float weight)
{

    AddPlaceToBaseGraph(endA);
    AddPlaceToBaseGraph(endB);

    s_baseGraph[endA][endB] = weight; // <endA , <endB , weight>>
    s_baseGraph[endB][endA] = weight;

#ifdef debug_output_worldgraph_dijkstra
    std::cout << "Road " << placeNames.at(endA) << " -- " << placeNames.at(endB) << " Weight:" << weight << " added to graph" << std::endl;
#endif
}

WorldGraph::WorldGraph()
{
    SetToBaseGraph();
    //std::cout << "Caravan graph set to base graph here" << std::endl;
}

WorldGraph::~WorldGraph()
{
    graph.clear();
}


void WorldGraph::Dijkstra(int source, int destination)
{
    path.clear();

  //std::priority_queue<std::pair<float, int>, std::vector<std::pair<float, int>>, std::greater<>> priorityQueue;
    std::priority_queue<std::pair<int,float>, std::vector<std::pair<int,float>>, std::greater<>> priorityQueue;
    std::map<int,float> distances;
    std::map<int,int> previous;
    std::set<int> visitedVertices;

    for (const auto& vertex : graph)
    {
        distances[vertex.first] = INT_MAX;
    }
    distances[source] = 0;

    priorityQueue.push({0, source});

    while (!priorityQueue.empty())
    {
        int currentVertex = priorityQueue.top().second;
        priorityQueue.pop();

        if (visitedVertices.find(currentVertex) != visitedVertices.end())
        {
            continue;
        }

        visitedVertices.insert(currentVertex);

        for (const auto& neighbor : graph.at(currentVertex))
        {
            int neighborVertex = neighbor.first;
            float neighborWeight = neighbor.second;
            float newDistance = distances[currentVertex] + neighborWeight;
            if (newDistance < distances[neighborVertex])
            {
                distances[neighborVertex] = newDistance;
#ifdef debug_output_worldgraph_dijkstra
                std::cout << "distance of vertex " << placeNames.at(neighborVertex) << " (from source " << placeNames.at(source) << ") becomes " << newDistance << std::endl; // Error check
#endif
                previous[neighborVertex] = currentVertex;
                priorityQueue.push({newDistance, neighborVertex});
            }
        }
    }

    if (distances[destination] == INT_MAX)
    {
        path.clear();
#ifdef debug_output_worldgraph_dijkstra
        std::cout << "Destination vertex is unreachable" << std::endl;
#endif
        return;
    }

    int currentVertex = destination;
    while (currentVertex != source)
    {
        path.push_back(currentVertex);
        visitedVertices.insert(currentVertex);
        currentVertex = previous[currentVertex];
    }

    path.push_back(source);

    std::reverse(path.begin(), path.end());

#ifdef debug_output_worldgraph_dijkstra
    std::cout << "Path prepared: ";
    for (const auto& vertex : path)
    {
        std::cout << placeNames.at(vertex) << "  ";
    }
    std::cout << std::endl;
#endif

}



void WorldGraph::SetToBaseGraph()
{
    graph = s_baseGraph;
}
