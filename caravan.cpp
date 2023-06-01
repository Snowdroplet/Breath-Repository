#include "caravan.h"

std::vector<Caravan*> Caravan::caravans;

Caravan::Caravan()
{
    SetActive(true);

    worldGraph.SetToBaseGraph();

    onReturnTrip = false;

    atPlace = false;
    onRoad = false;
    whichPlace = nullptr;
    whichRoad = nullptr;

    UpdateInventoryBubble();
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
    float previousOverworldXPosition = overworldXPosition;

    if(distanceFromNextWaypoint <= 0)
    {
        currentWaypoint = nextWaypoint;

        if(currentWaypoint == finalWaypoint)
        {
            atRoadsEnd = true;
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

        if(overworldXPosition != previousOverworldXPosition) // Prevents defaulting to left-facing when moving up or down vertical roads.
        {
            if(overworldXPosition > previousOverworldXPosition)
                caravanLeader->facingLeft = false;
            else
                caravanLeader->facingLeft = true;
        }
    }
}

void Caravan::OverworldLogic()
{
    if(onRoad)
    {
        if(atRoadsEnd)
            MoveToPlace(Place::places[roadDestination]);
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
            if(worldGraph.path.size() <= 1) // The last remaining node will be the destination - I can't call clear() worldGraph.path prematurely, but whatever.
            {
#ifdef debug_output_worldgraph_dijkstra
                std::cout << "Worldgraph path empty. " << std::endl;
#endif
                if(onReturnTrip)
                    pathfindingDestination = caravanLeader->hometown;
                else // not onReturnTrip
                    pathfindingDestination = rand()%(PL_MARKER_LAST-PL_MARKER_FIRST +1) + PL_MARKER_FIRST;
#ifdef debug_output_worldgraph_dijkstra
                std::cout << "Random destination set to " << placeNames.at(pathfindingDestination) << std::endl;
#endif
                if(pathfindingDestination != whichPlace->placeIdentity)
                {
                    worldGraph.Dijkstra(whichPlace->placeIdentity,pathfindingDestination);
#ifdef debug_output_worldgraph_dijkstra
                    std::cout << std::endl;
#endif
                }
                else
                {
#ifdef debug_output_worldgraph_dijkstra
                    std::cout << "No need to pathfind." << std::endl;
#endif
                }
            }
            else // !worldGraph.path.empty()
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
            }

            UpdatePathfindingBubble();
        }
    }
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

void Caravan::MoveToPlace(Place *p)
{
    atPlace = true;
    whichPlace = p;
    p->AddToCaravanserai(this);

    if(whichPlace->placeIdentity == caravanLeader->hometown)
        onReturnTrip = false;
    else if(whichPlace->placeIdentity == pathfindingDestination)
        onReturnTrip = true;

    onRoad = false;
    atRoadsEnd = false;

    currentTimeAtPlace = 0;
    thresholdTimeAtPlace = rand()%(MAX_TIME_AT_PLACE-MIN_TIME_AT_PLACE) + MIN_TIME_AT_PLACE;

    overworldXPosition = p->overworldXPosition;
    overworldYPosition = p->overworldYPosition;

    caravanLeader->facingLeft = false;

}

void Caravan::MoveToRoad(Road *r, bool isReverseRoad)
{

    if(atPlace)
        whichPlace->RemoveFromCaravanserai(this);

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

    UpdatePathfindingBubble();

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
    //std::cout << travelSpeed << std::endl;
}

void Caravan::AddInventoryStock(int a, float b)
{
    inventory.AddStock(a,b);
    UpdateInventoryBubble();
}
void Caravan::RemoveInventoryStock(int a, float b)
{
    inventory.RemoveStock(a,b);
    UpdateInventoryBubble();
}
void Caravan::SetInventoryStock(int a, float b)
{
    inventory.SetStock(a,b);
    UpdateInventoryBubble();
}

void Caravan::UpdateInventoryBubble()
{
    inventoryBubbleNumCols = inventoryBubbleBaseCols;
    inventoryBubbleNumRows = inventoryBubbleBaseRows;

    while(inventory.cargo.size() > inventoryBubbleNumCols*inventoryBubbleNumRows)
    {
        if(inventoryBubbleNumCols <= inventoryBubbleNumRows)
            inventoryBubbleNumCols++;
        else
            inventoryBubbleNumRows++;
    }

    inventoryBubbleWidth = inventoryBubbleNumCols*TILE_W;
    inventoryBubbleHeight = inventoryBubbleNumRows*(TILE_H+inventoryBubbleRowSpacing);
}

void Caravan::UpdatePathfindingBubble()
{
    pathfindingBubbleNumCols = pathfindingBubbleBaseCols;
    pathfindingBubbleNumRows = pathfindingBubbleBaseRows;

    if(worldGraph.path.size() > pathfindingBubbleBaseCols)
        pathfindingBubbleNumCols = worldGraph.path.size();

    pathfindingBubbleWidth = pathfindingBubbleNumCols*(2*TILE_W+pathfindingBubbleColSpacing) - pathfindingBubbleColSpacing;
    pathfindingBubbleHeight = pathfindingBubbleNumRows*(2*TILE_H+pathfindingBubbleRowSpacing);
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

void Caravan::DrawInventoryBubble()
{
    al_draw_filled_rounded_rectangle(inventoryBubbleDrawX - bubblePadding,
                                     inventoryBubbleDrawY - bubblePadding,
                                     inventoryBubbleDrawX + inventoryBubbleWidth + bubblePadding,
                                     inventoryBubbleDrawY + inventoryBubbleHeight + bubblePadding,
                                     bubbleCornerRadius,
                                     bubbleCornerRadius,
                                     COL_DARK_WHITE);


    al_draw_rounded_rectangle(inventoryBubbleDrawX - bubblePadding,
                              inventoryBubbleDrawY - bubblePadding,
                              inventoryBubbleDrawX + inventoryBubbleWidth + bubblePadding,
                              inventoryBubbleDrawY + inventoryBubbleHeight + bubblePadding,
                              bubbleCornerRadius,
                              bubbleCornerRadius,
                              COL_INDIGO,
                              4);

    al_draw_text(builtin,COL_BLACK,inventoryBubbleDrawX, inventoryBubbleDrawY-bubblePadding-BUILTIN_TEXT_HEIGHT, ALLEGRO_ALIGN_LEFT, "Cargo:");

    if(inventory.cargo.size() > 0)
    {
        unsigned i = 0;
        for(std::map<int,float>::iterator it = inventory.cargo.begin(); it != inventory.cargo.end(); ++it)
        {
            float drawX = inventoryBubbleDrawX + i%inventoryBubbleNumCols*TILE_W;
            float drawY = inventoryBubbleDrawY + i/inventoryBubbleNumCols*(TILE_H + inventoryBubbleRowSpacing);

            al_draw_bitmap_region(cargoPng,
                                  ((*it).first)*TILE_W, 0,
                                  TILE_W, TILE_H,
                                  drawX, drawY,
                                  0);

            string_al_draw_text(builtin, COL_BLACK, drawX+TILE_W, drawY+TILE_H, ALLEGRO_ALIGN_RIGHT, std::to_string((int)(*it).second));
            i++;
        }
    }
    else
        al_draw_text(builtin,COL_BLACK,inventoryBubbleDrawX,inventoryBubbleDrawY,ALLEGRO_ALIGN_LEFT,"(No cargo carried).");
}

void Caravan::DrawPathfindingBubble()
{
    al_draw_filled_rounded_rectangle(pathfindingBubbleDrawX - bubblePadding,
                                         pathfindingBubbleDrawY - bubblePadding,
                                         pathfindingBubbleDrawX + pathfindingBubbleWidth + bubblePadding,
                                         pathfindingBubbleDrawY + pathfindingBubbleHeight + bubblePadding,
                                         bubbleCornerRadius,
                                         bubbleCornerRadius,
                                         COL_DARK_WHITE);

        al_draw_rectangle(pathfindingBubbleDrawX - bubblePadding,
                          pathfindingBubbleDrawY - bubblePadding,
                          pathfindingBubbleDrawX + pathfindingBubbleWidth + bubblePadding,
                          pathfindingBubbleDrawY + pathfindingBubbleHeight + bubblePadding,
                          COL_INDIGO,
                          4);

    if(!worldGraph.path.empty())
    {

        for(unsigned i = 0; i < worldGraph.path.size(); i++)
        {
            float drawX = pathfindingBubbleDrawX + i*(2*TILE_H+pathfindingBubbleColSpacing);
            float drawY = pathfindingBubbleDrawY;
            al_draw_bitmap_region(overworldPlacePng,
                                  worldGraph.path[i]*2*TILE_W, 0,
                                  2*TILE_W, 2*TILE_H,
                                  drawX, drawY,
                                  0);

            string_al_draw_text(builtin, COL_BLACK,
                                drawX + TILE_W, drawY + 2*TILE_H,
                                ALLEGRO_ALIGN_CENTER,
                                placeNames.at(worldGraph.path[i]));

            if(i < worldGraph.path.size()-1)
            {
                al_draw_bitmap(redArrowPng,
                               drawX+2*TILE_W,
                               drawY+TILE_H/2,
                               0);
            }
        }
    }
    else
    {
        al_draw_text(builtin, COL_BLACK,
                     pathfindingBubbleDrawX+pathfindingBubbleWidth/2,
                     pathfindingBubbleDrawY+pathfindingBubbleWidth/2 - BUILTIN_TEXT_HEIGHT,
                     ALLEGRO_ALIGN_CENTER, "(No Path)");
    }
    al_draw_text(builtin,COL_BLACK,
                 pathfindingBubbleDrawX,
                 pathfindingBubbleDrawY-bubblePadding-BUILTIN_TEXT_HEIGHT,
                 ALLEGRO_ALIGN_LEFT, "Pathfinding:");
}
