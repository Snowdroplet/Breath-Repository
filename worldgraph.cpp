#include "worldgraph.h"

std::map<int,std::map<int,float>>WorldGraph::s_baseGraph;

void WorldGraph::AddPlaceToBaseGraph(int vertex)
{
    if (s_baseGraph.find(vertex) == s_baseGraph.end()) // vertex not already listed
    {
        s_baseGraph[vertex] = {}; // Creates an empty map at index "vertex"
        //std::cout << "Vertex " << vertex << " added to graph." << std::endl;
    }

}


void WorldGraph::AddRoadToBaseGraph(int endA, int endB, float weight)
{

    AddPlaceToBaseGraph(endA);
    AddPlaceToBaseGraph(endB);

    s_baseGraph[endA][endB] = weight; // <endA , <endB , weight>>

}

WorldGraph::WorldGraph()
{
    SetToBaseGraph();
}

WorldGraph::~WorldGraph()
{
    graph.clear();
}


void WorldGraph::Dijkstra(int source, int destination)
{
    // Create a priority queue to store the vertices in increasing order of their distances.
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<>> priorityQueue;

    // Create a map to store the distances from the source vertex to each vertex.
    std::map<int,int> distances;
    for (const auto& vertex : graph)
    {
        distances[vertex.first] = INT_MAX;
    }
    distances[source] = 0;

    // Create a map to store the previous vertex in the shortest path.
    std::map<int,int> previous;

    // Add the source vertex to the priority queue.
    priorityQueue.push({0, source});
    while (!priorityQueue.empty())
    {
        // Pop the vertex with the smallest distance from the priority queue.
        int currentVertex = priorityQueue.top().second;
        priorityQueue.pop();
        // Stop the algorithm once the destination vertex has been visited.
        if (currentVertex == destination)
        {
            break;
        }
        // Update the distances of the neighbors if necessary.
        for (const auto& neighbor : graph.at(currentVertex))
        {
            int neighborVertex = neighbor.first;
            int neighborWeight = neighbor.second;
            int newDistance = distances[currentVertex] + neighborWeight;
            if (newDistance < distances[neighborVertex])
            {
                distances[neighborVertex] = newDistance;
                previous[neighborVertex] = currentVertex;
                priorityQueue.push({newDistance, neighborVertex});
            }
        }
    }


    // Reconstruct the shortest path from the source to the destination.
    path.clear();
    int currentVertex = destination;
    while (currentVertex != source)
    {
        path.push_back(currentVertex);
        currentVertex = previous[currentVertex];
    }
    path.push_back(source);
    std::reverse(path.begin(), path.end());
}


void WorldGraph::SetToBaseGraph()
{
    graph = s_baseGraph;
}
