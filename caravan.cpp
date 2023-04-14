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

    for(std::vector<Being*>::iterator it = members.begin(); it != members.end();)
    {
        members.erase(it);
    }

}

void Caravan::UpdateOverworldPosition()
{
    float x1 = whichRoad->xWaypoints[currentWaypoint];
    float y1 = whichRoad->yWaypoints[currentWaypoint];

    float x2 = whichRoad->xWaypoints[nextWaypoint];
    float y2 = whichRoad->yWaypoints[nextWaypoint];

    overworldXPosition = x2-x1;
    overworldYPosition = y2-y1;
    distanceFromNextWaypoint = std::hypot(x2-x1, y2-y1);

    if(distanceFromNextWaypoint <= 0)
    {
        currentWaypoint = nextWaypoint;
        if(currentWaypoint == finalWaypoint)
        {
            atRoadsEnd = true;
        }
        else if(!reverseRoad && currentWaypoint < whichRoad->xWaypoints.end()->first)
            nextWaypoint++;

        else if(reverseRoad && currentWaypoint > 0)
                nextWaypoint --;

    }

}

void Caravan::SetActive(bool a){active = a;}

void Caravan::MoveToPlace(Place *p)
{
    atPlace = true;
    onRoad = false;
    whichPlace = p;
}

void Caravan::MoveToRoad(Road *r, bool isEndpointA)
{
    atPlace = false;
    onRoad = true;
    whichRoad = r;

    if(isEndpointA)
    {
        reverseRoad = false;
        overworldXPosition = whichRoad->xWaypoints[0];
        overworldYPosition = whichRoad->yWaypoints[0];
        currentWaypoint = 0;
        nextWaypoint = currentWaypoint + 1;
        finalWaypoint = whichRoad->xWaypoints.end()->first;
    }
    else
    {
        reverseRoad = true;
        overworldXPosition = whichRoad->xWaypoints.end()->second;
        overworldYPosition = whichRoad->yWaypoints.end()->second;
        currentWaypoint = whichRoad->xWaypoints.end()->first;
        nextWaypoint = currentWaypoint - 1;
        finalWaypoint = 0;
    }

    distanceFromNextWaypoint = 9999; // Failsafe for now - perhaps remove later.
    atRoadsEnd = false;
}

void Caravan::DrawOnOverworld()
{
    if(onRoad)
        caravanLeader->DrawOverworldActivity(overworldXPosition,overworldYPosition);

    else if(atPlace)
    {

    }
}

bool Caravan::IsActive(){return active;}

void Caravan::AddMember(Being *b)
{
    members.push_back(b);
    if(members.size() == 1)
        caravanLeader = members[0];
}

void Caravan::UpdateTravelSpeed()
{
    if(members.size() > 0)
    {
        float lowestTravelSpeed = 999;
        for(unsigned i = 0; i < members.size()-1; i++)
        {
            if(members[i]->travelSpeed < lowestTravelSpeed)
                lowestTravelSpeed = members[i]->travelSpeed;
        }
    }
}
