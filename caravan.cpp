#include "caravan.h"

Caravan::Caravan()
{
    SetActive(true);
    atPlace = false;
    onRoad = false;
    whichPlace = nullptr;
    whichRoad = nullptr;
}

Caravan::~Caravan()
{
    std::cout << "Caravan deleted." << std::endl;

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
            atRoadsEnd = true;

        MoveToRoadSegment(currentWaypoint, reverseRoad);
    }
    else
    {
        float segmentTravelled = (roadSegmentLength-distanceFromNextWaypoint)/roadSegmentLength;

        overworldXPosition = overworldXPosition + (overworldXDestination - overworldXPosition) * segmentTravelled;
        overworldYPosition = overworldYPosition + (overworldYDestination - overworldYPosition) * segmentTravelled;

        //std::cout << "D from waypoint: " << distanceFromNextWaypoint << ", X: " << overworldXPosition << " , Y: " << overworldXPosition << std::endl;
    }
}

void Caravan::Travel()
{
    if(onRoad)
    {
        // switch() travel activity here

        distanceFromNextWaypoint -= travelSpeed;
        UpdateOverworldPosition();
    }
}

void Caravan::MoveToPlace(Place *p)
{
    atPlace = true;
    onRoad = false;
    whichPlace = p;
}

void Caravan::MoveToRoad(Road *r, bool isReverseRoad)
{
    atPlace = false;
    onRoad = true;
    whichRoad = r;
    reverseRoad = isReverseRoad;

    if(!reverseRoad)
        MoveToRoadSegment(0,false);
    else
        MoveToRoadSegment(whichRoad->lastWaypoint, true);

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

    overworldXPosition = whichRoad->xWaypoints[currentWaypoint];
    overworldYPosition = whichRoad->yWaypoints[currentWaypoint];
    overworldXDestination = whichRoad->xWaypoints[nextWaypoint];
    overworldYDestination = whichRoad->yWaypoints[nextWaypoint];
    roadSegmentLength = whichRoad->ReturnSegmentLength(currentWaypoint, nextWaypoint);
    distanceFromNextWaypoint = roadSegmentLength;

    atRoadsEnd = false;

    std::cout << "Current waypoint: " << currentWaypoint << ", Next waypoint: " << nextWaypoint << ", Final waypoint: " << finalWaypoint << std::endl;
}

void Caravan::DrawOnOverworld()
{
    if(onRoad)
        caravanLeader->DrawOverworldActivity(overworldXPosition,overworldYPosition);

    else if(atPlace)
    {

    }
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
}

void Caravan::UpdateTravelSpeed()
{
    if(members.size() > 0)
    {
        float lowestTravelSpeed = 99;
        for(unsigned i = 0; i < members.size()-1; i++)
        {
            if(members[i]->travelSpeed < lowestTravelSpeed)
                lowestTravelSpeed = members[i]->travelSpeed;
        }
        travelSpeed = lowestTravelSpeed;
    }

}
