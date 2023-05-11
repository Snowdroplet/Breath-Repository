#include "caravan.h"

std::vector<Caravan*> Caravan::caravans;

Caravan::Caravan()
{
    SetActive(true);

    worldGraph.SetToBaseGraph();

    atPlace = false;
    onRoad = false;
    whichPlace = nullptr;
    whichRoad = nullptr;
}

Caravan::~Caravan()
{
    //std::cout << "Caravan deleted." << std::endl;

    for(std::vector<Being*>::iterator it = members.begin(); it != members.end();) // Not meant to delete the Beings.
    {
        members.erase(it);
    }

}

void Caravan::SetActive(bool a)
{
    active = a;
}

void Caravan::UpdateOverworldPosition()
{
    if(distanceFromNextWaypoint <= 0)
    {
        currentWaypoint = nextWaypoint;

        if(currentWaypoint == finalWaypoint)
        {
            atRoadsEnd = true;
            atPlace = true;
            //std::cout << "at roads end true" << std::endl;
        }

        MoveToRoadSegment(currentWaypoint, reverseRoad);
    }
    else
    {
        timeToNextWaypoint = distanceFromNextWaypoint / travelSpeed;

        overworldXPosition += (overworldXDestination - overworldXPosition) / timeToNextWaypoint;
        overworldYPosition += (overworldYDestination - overworldYPosition) / timeToNextWaypoint;

        //std::cout << "T from waypoint: " << timeToNextWaypoint << std::endl;
        //std::cout << "D from waypoint: " << distanceFromNextWaypoint << ", X: " << overworldXPosition << " , Y: " << overworldXPosition << std::endl;
    }
}

void Caravan::OverworldLogic()
{
    if(onRoad)
    {
        if(atRoadsEnd)
        {
            MoveToPlace(Place::places[roadDestination]);
        }
        else
        {
            distanceFromNextWaypoint -= travelSpeed;
            UpdateOverworldPosition();
        }
    }
    else if(atPlace)
    {
        currentTimeAtPlace++;
        if(currentTimeAtPlace >= thresholdTimeAtPlace)
        {
            if(worldGraph.path.empty())
            {
#ifdef debug_output_worldgraph_dijkstra
                std::cout << "Worldgraph path empty. " << std::endl;
#endif
                pathfindingDestination = rand()%(PL_MARKER_LAST-PL_MARKER_FIRST +1) + PL_MARKER_FIRST;
#ifdef debug_output_worldgraph_dijkstra
                std::cout << "Random destination set to " << placeNames.at(pathfindingDestination) << std::endl;
#endif
                if(pathfindingDestination != whichPlace->identity)
                {
                    worldGraph.Dijkstra(whichPlace->identity,pathfindingDestination);
                    std::cout << std::endl;
                }
                else
                {
#ifdef debug_output_worldgraph_dijkstra
                    std::cout << "No need to pathfind." << std::endl;
#endif
                }
            }
            else
            {
                worldGraph.path.erase(worldGraph.path.begin());

                int nextPlaceOnPath = worldGraph.path[0];
#ifdef debug_output_worldgraph_dijkstra
                std::cout << "NextPlaceOnPath is " << placeNames.at(worldGraph.path[0]) << std::endl;
#endif

                for(std::vector<Road*>::iterator it = whichPlace->connections.begin(); it != whichPlace->connections.end(); ++it)
                {
                    if((*it)->endpointA == nextPlaceOnPath)
                        MoveToRoad((*it),true);

                    else if((*it)->endpointB == nextPlaceOnPath)
                        MoveToRoad((*it),false);

                }

                if(worldGraph.path.size() == 1)
                    worldGraph.path.clear();
            }
        }
    }
}

void Caravan::MoveToPlace(Place *p)
{
    atPlace = true;
    whichPlace = p;
    p->AddVisitorCaravan(this);

    onRoad = false;
    atRoadsEnd = false;

    currentTimeAtPlace = 0;

    thresholdTimeAtPlace = rand()%(MAX_TIME_AT_PLACE-MIN_TIME_AT_PLACE) + MIN_TIME_AT_PLACE;


}

void Caravan::MoveToRoad(Road *r, bool isReverseRoad)
{
    if(atPlace)
    {
        whichPlace->RemoveVisitorCaravan(this);
    }

    atPlace = false;

    onRoad = true;
    whichRoad = r;
    atRoadsEnd = false;

    reverseRoad = isReverseRoad;

    if(!reverseRoad)
    {
        roadDestination = r->endpointB;
        MoveToRoadSegment(0,false);
    }
    else
    {
        roadDestination = r->endpointA;
        MoveToRoadSegment(whichRoad->lastWaypoint, true);
    }

}

void Caravan::MoveToRoadSegment(int a, bool isReverseRoad)
{
    reverseRoad = isReverseRoad;
    currentWaypoint = a;

    if(!reverseRoad)
    {
        nextWaypoint = currentWaypoint+1;
        finalWaypoint = whichRoad->lastWaypoint;

    }
    else
    {
        nextWaypoint = currentWaypoint-1;
        finalWaypoint = 0;
    }

    if(!atRoadsEnd)
    {
        overworldXDestination = whichRoad->xWaypoints[nextWaypoint];
        overworldYDestination = whichRoad->yWaypoints[nextWaypoint];
        overworldXPosition = whichRoad->xWaypoints[currentWaypoint];
        overworldYPosition = whichRoad->yWaypoints[currentWaypoint];
        roadSegmentLength = whichRoad->ReturnSegmentLength(currentWaypoint, nextWaypoint);
        distanceFromNextWaypoint = roadSegmentLength;
    }

    //std::cout << "Current waypoint: " << currentWaypoint << ", Next waypoint: " << nextWaypoint << ", Final waypoint: " << finalWaypoint << std::endl;
    //std::cout << "Number of segments: " << whichRoad->xWaypoints.size() << std::endl;
}

void Caravan::DrawSpriteOnOverworld()
{
    if(onRoad)
    {
        DrawActivity(overworldXPosition - overworldCameraXPosition,overworldYPosition - overworldCameraYPosition);

    }

    else if(atPlace /* and the open place interface is equal to whichPlace */)
    {

    }
}

void Caravan::DrawActivity(float x, float y)
{
    caravanLeader->DrawActivity(x, y);
}

bool Caravan::IsActive()
{
    return active;
}

void Caravan::AddMember(Being *b)
{
    members.push_back(b);
    if(members.size() == 1)
        caravanLeader = members[0];

    UpdateTravelSpeed();
    std::cout << travelSpeed << std::endl;
}

void Caravan::UpdateTravelSpeed()
{
    if(members.size() > 0)
    {
        float lowestTravelSpeed = 99;
        for(std::vector<Being*>::iterator it = members.begin(); it != members.end(); ++it)
        {
            if((*it)->travelSpeed < lowestTravelSpeed)
                lowestTravelSpeed = (*it)->travelSpeed;
        }
        travelSpeed = lowestTravelSpeed;
    }

}
