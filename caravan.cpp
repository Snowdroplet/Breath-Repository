#include "caravan.h"

Caravan::Caravan()
{
    SetActive(true);
    atPlace = false;
    onRoad = false;
    whichPlace = PL_NONE;
    whichRoad = ROAD_NONE;


}

Caravan::~Caravan()
{
    std::cout << "Caravan deleted." << std::endl;

    for(std::vector<Being*>::iterator it = members.begin(); it != members.end();)
    {
        members.erase(it);
    }

}

void Caravan::SetActive(bool a){active = a;}

void Caravan::MoveToPlace(Place *p)
{
    atPlace = true;
    onRoad = false;
    whichPlace = p->identity;
}

void Caravan::MoveToRoad(Road *r, bool isEndpointA)
{
    atPlace = false;
    onRoad = true;
    whichRoad = r->identity;

    if(isEndpointA)
    {
        reverseRoad = false;
        overworldXPosition = r->xWaypoints[0];
        overworldYPosition = r->yWaypoints[0];
        currentWaypoint = 0;
        nextWaypoint = currentWaypoint + 1;
    }
    else
    {
        reverseRoad = true;
        overworldXPosition = r->xWaypoints.end()->second;
        overworldYPosition = r->yWaypoints.end()->second;

        currentWaypoint = r->xWaypoints.end()->first;
        nextWaypoint = currentWaypoint - 1;
    }
}

void Caravan::DrawToOverworld()
{
    //caravanLeader->
}

bool Caravan::IsActive(){return active;}

void Caravan::AddMember(Being *b)
{
    members.push_back(b);
    if(members.size() == 1)
        caravanLeader = members[0];
}
