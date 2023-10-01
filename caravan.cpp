#include "caravan.h"

std::vector<Caravan*> Caravan::caravans;

Caravan::Caravan()
{
    SetActive(true);
    caravanLeader = nullptr;
    hometownPointer = nullptr;

    worldGraph.SetToBaseGraph();

    atPlace = false;
    atHome = false;
    onRoad = false;

    whichPlace = nullptr;
    whichRoad = nullptr;

    UpdateInventoryBubble();
    UpdateTradeRecordsBubble();

}

Caravan::~Caravan()
{
    //std::cout << "Caravan deleted." << std::endl;

    for(std::vector<Being*>::iterator it = members.begin(); it != members.end();) // Not meant to delete the Beings.
    {
        members.erase(it);
    }

    for(std::vector<TradeRecord*>::iterator it = tradeRecords.begin(); it != tradeRecords.end();)
    {
        delete *it;
        tradeRecords.erase(it);
    }

}

void Caravan::SetActive(bool a)
{
    active = a;
}

void Caravan::SetHometown(int id)
{
    hometownID = id;
    hometownPointer = Place::places.at(id);
}


int Caravan::SelectRandomTradeDestination()
{
    int result = rand()%(PL_MARKER_LAST-PL_MARKER_FIRST +1) + PL_MARKER_FIRST;

    //std::cout << "Most suitable trade destination set to " << placeNames.at(result) << std::endl;

    return result;
}

void Caravan::ProgressTradeMission()
{
    if(atHome)
    {
        if(tradeMission.missionComplete)
        {
            tradeMission.missionActive = false;
            tradeMission.missionComplete = false;
        }

        if(!tradeMission.missionActive) //&& c->missionCooldown <= 0)
        {
            tradeMission.missionActive = true;
            tradeMission.SetTradeDestination(SelectRandomTradeDestination());
        }
    }
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
    ProgressTradeMission();

    if(onRoad)
    {
        if(atRoadsEnd)
        {
            MoveToPlace(Place::places[roadDestination]);

            whichPlace->TradeWithCaravan(this);
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
            if(worldGraph.path.size() <= 1) // The last remaining node will be the destination - I can't call clear() worldGraph.path prematurely, but whatever.
            {
                //std::cout << "Worldgraph path empty. " << std::endl;

                if(tradeMission.onReturnTrip)
                    pathfindingDestination = hometownID;
                else // not onReturnTrip -- i.e. leaving hometown on a mission
                {
                    pathfindingDestination = tradeMission.tradeDestination;
                    //std::cout << "Random destination set to " << placeNames.at(pathfindingDestination) << std::endl;
                }

                if(pathfindingDestination != whichPlace->placeIdentity)
                {
                    worldGraph.Dijkstra(whichPlace->placeIdentity,pathfindingDestination); // This also overwrites the path with that last remaining element at index 0.
                    //std::cout << std::endl;
                }

            }
            else // !worldGraph.path.empty()
            {
                worldGraph.path.erase(worldGraph.path.begin());

                int nextPlaceOnPath = worldGraph.path[0];
                //std::cout << "NextPlaceOnPath is " << placeNames.at(worldGraph.path[0]) << std::endl;

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

    if(whichPlace == hometownPointer)
    {
        if(tradeMission.onReturnTrip) // prevents Caravan from being instantly unloaded after first mission after generation is issued
            tradeMission.missionComplete = true;

        tradeMission.onReturnTrip = false;
        atHome = true;
    }
    else if(whichPlace->placeIdentity == pathfindingDestination)
        tradeMission.onReturnTrip = true;

    onRoad = false;
    whichRoad = nullptr;
    atRoadsEnd = false;

    currentTimeAtPlace = 0;
    thresholdTimeAtPlace = rand()%(MAX_TIME_AT_PLACE-MIN_TIME_AT_PLACE) + MIN_TIME_AT_PLACE;

    overworldXPosition = p->overworldXPosition;
    overworldYPosition = p->overworldYPosition;

    if(caravanLeader != nullptr)
        caravanLeader->facingLeft = false;

}

void Caravan::MoveToRoad(Road *r, bool isReverseRoad)
{

    if(atPlace)
        whichPlace->RemoveFromCaravanserai(this);

    atPlace = false;
    // Do *not* whichPlace = nullptr; as it will cause a crash when iterating through whichPlace->connections in OverworldLogic()

    atHome = false;

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

    UpdateCargoWeightMax();
    UpdateCargoWeight();
}

void Caravan::UpdateCargoWeight()
{
    float result = 0;

    for(std::map<int,float>::iterator it = inventory.cargo.begin(); it != inventory.cargo.end(); ++it)
        result += (*it).second;

    cargoWeight = result;

}

void Caravan::UpdateCargoWeightMax()
{
    cargoWeightMax = 40;
}

void Caravan::AddInventoryStock(int a, float b)
{
    inventory.AddStock(a,b);
    UpdateCargoWeight();
    UpdateInventoryBubble();
}
void Caravan::RemoveInventoryStock(int a, float b)
{
    inventory.RemoveStock(a,b);
    UpdateCargoWeight();
    UpdateInventoryBubble();
}
void Caravan::SetInventoryStock(int a, float b)
{
    inventory.SetStock(a,b);
    UpdateCargoWeight();
    UpdateInventoryBubble();
}

void Caravan::AddTradeRecord(int location)
{
    tradeRecords.push_back(new TradeRecord(location));
}

void Caravan::UpdateTradeRecordQuantities(int whichItem, int change)
{
    tradeRecords.back()->ChangeEntry(whichItem, change);
}

void Caravan::CheckTradeRecordsRowLimit()
{
    unsigned rowCount = 0;

    for(std::vector<TradeRecord*>::iterator it = tradeRecords.begin(); it != tradeRecords.end(); ++it)
        rowCount += (*it)->numRows;

    while(rowCount > tradeRecordsMaxRows && tradeRecords.size() > 1) // Trim trade records down to their maximum total rows.
    {
        rowCount -= tradeRecords.front()->numRows;

        delete tradeRecords.front();
        tradeRecords.erase(tradeRecords.begin());
    }
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

void Caravan::UpdateTradeRecordsBubble()
{
    tradeRecordsBubbleNumRows = tradeRecordsBubbleBaseRows;

    unsigned rowCount = 0;
    for(std::vector<TradeRecord*>::iterator it = tradeRecords.begin(); it != tradeRecords.end(); ++it)
        rowCount += (*it)->numRows;

    if(rowCount > tradeRecordsBubbleBaseRows)
        tradeRecordsBubbleNumRows = rowCount;

    tradeRecordsBubbleHeight = tradeRecordsBubbleNumRows*(TILE_H+tradeRecordsBubbleRowSpacing);
}

void Caravan::UpdatePathfindingBubble()
{
    pathfindingBubbleNumCols = pathfindingBubbleBaseCols;
    pathfindingBubbleNumRows = pathfindingBubbleBaseRows;

    if(worldGraph.path.size() > pathfindingBubbleNumCols)
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
                                     COLKEY_UI_BUBBLE_BODY);


    al_draw_rounded_rectangle(inventoryBubbleDrawX - bubblePadding,
                              inventoryBubbleDrawY - bubblePadding,
                              inventoryBubbleDrawX + inventoryBubbleWidth + bubblePadding,
                              inventoryBubbleDrawY + inventoryBubbleHeight + bubblePadding,
                              bubbleCornerRadius,
                              bubbleCornerRadius,
                              COLKEY_UI_BUBBLE_FRAME,
                              4);

    al_draw_text(builtin,COLKEY_TEXT,inventoryBubbleDrawX, inventoryBubbleDrawY-bubblePadding-BUILTIN_TEXT_HEIGHT, ALLEGRO_ALIGN_LEFT, "Cargo:");

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

            string_al_draw_text(builtin, COLKEY_TEXT, drawX+TILE_W, drawY+TILE_H, ALLEGRO_ALIGN_RIGHT, std::to_string((int)(*it).second));
            i++;
        }
    }
    else
        al_draw_text(builtin,COLKEY_TEXT,inventoryBubbleDrawX,inventoryBubbleDrawY,ALLEGRO_ALIGN_LEFT,"(No cargo carried).");

    string_al_draw_text(builtin,COLKEY_TEXT,inventoryBubbleDrawX,
                        inventoryBubbleDrawY+inventoryBubbleHeight + BUILTIN_TEXT_HEIGHT,
                        ALLEGRO_ALIGN_LEFT,
                        "Weight: " + std::to_string((int)cargoWeight) + " / " + std::to_string((int)cargoWeightMax) );

}

void Caravan::DrawTradeRecordsBubble()
{
    al_draw_filled_rounded_rectangle(tradeRecordsBubbleDrawX - bubblePadding,
                                     tradeRecordsBubbleDrawY - bubblePadding,
                                     tradeRecordsBubbleDrawX + tradeRecordsBubbleWidth + bubblePadding,
                                     tradeRecordsBubbleDrawY + tradeRecordsBubbleHeight + bubblePadding,
                                     bubbleCornerRadius,
                                     bubbleCornerRadius,
                                     COLKEY_UI_BUBBLE_BODY);

    al_draw_rounded_rectangle(tradeRecordsBubbleDrawX - bubblePadding,
                              tradeRecordsBubbleDrawY - bubblePadding,
                              tradeRecordsBubbleDrawX + tradeRecordsBubbleWidth + bubblePadding,
                              tradeRecordsBubbleDrawY + tradeRecordsBubbleHeight + bubblePadding,
                              bubbleCornerRadius,
                              bubbleCornerRadius,
                              COLKEY_UI_BUBBLE_FRAME,
                              4);


    al_draw_text(builtin, COLKEY_TEXT, tradeRecordsBubbleDrawX, tradeRecordsBubbleDrawY-bubblePadding-BUILTIN_TEXT_HEIGHT, ALLEGRO_ALIGN_LEFT, "Trade Records:");

    if(tradeRecords.size() > 0)
    {
        unsigned col = 0;
        unsigned row = 0;

        for(std::vector<TradeRecord*>::reverse_iterator rit = tradeRecords.rbegin(); rit != tradeRecords.rend(); ++rit)
        {

            string_al_draw_text(builtin, COLKEY_TEXT,
                                tradeRecordsBubbleDrawX + tradeRecordsBubblePlaceNameWidth,
                                tradeRecordsBubbleDrawY + row*(TILE_H + tradeRecordsBubbleRowSpacing),
                                ALLEGRO_ALIGN_RIGHT,
                                placeNames.at((*rit)->location)); //+ " (" + std::to_string((*rit)->numRows) + ")");


            if((*rit)->tradeQuantities.size() > 0)
            {
                for(std::map<int, int>::iterator jt = (*rit)->tradeQuantities.begin(); jt != (*rit)->tradeQuantities.end(); ++jt)
                {
                    if(col >= tradeRecordsBubbleNumIconCols)
                    {
                        col = 0;
                        row++;
                    }

                    float iconDrawX = tradeRecordsBubbleDrawX + tradeRecordsBubblePlaceNameWidth + col*(TILE_W);
                    float iconDrawY = tradeRecordsBubbleDrawY + row*(TILE_H + tradeRecordsBubbleRowSpacing);

                    if((*jt).second < 0)
                        al_draw_filled_rectangle(iconDrawX, iconDrawY,
                                             iconDrawX+TILE_W, iconDrawY+TILE_H+tradeRecordsBubbleRowSpacing,
                                             COLKEY_UI_TRADERECORD_NEGATIVE);
                    else
                        al_draw_filled_rectangle(iconDrawX, iconDrawY,
                                             iconDrawX+TILE_W, iconDrawY+TILE_H+tradeRecordsBubbleRowSpacing,
                                             COLKEY_UI_TRADERECORD_POSITIVE);


                    al_draw_bitmap_region(cargoPng,
                                          ((*jt).first)*TILE_W, 0,
                                          TILE_W, TILE_H,
                                          iconDrawX, iconDrawY,
                                          0);

                    string_al_draw_text(builtin, COLKEY_TEXT, iconDrawX+TILE_W, iconDrawY+TILE_H, ALLEGRO_ALIGN_RIGHT, std::to_string((*jt).second));

                    col++;
                }

            }
            else if((*rit)->tradeQuantities.size() == 0) // tradeQuantities vector empty
            {
                string_al_draw_text(builtin, COLKEY_TEXT,
                                    tradeRecordsBubbleDrawX + tradeRecordsBubblePlaceNameWidth + col*(TILE_W),
                                    tradeRecordsBubbleDrawY + row*(TILE_H + tradeRecordsBubbleRowSpacing) + TILE_H/2 - BUILTIN_TEXT_HEIGHT/2,
                                    ALLEGRO_ALIGN_LEFT,
                                    "(No transaction).");
            }

            col = 0;
            row++;
        }
    }
    else
        al_draw_text(builtin,COLKEY_TEXT,tradeRecordsBubbleDrawX, tradeRecordsBubbleDrawY, ALLEGRO_ALIGN_LEFT, "(No recent trades).");
}

void Caravan::DrawPathfindingBubble()
{
    al_draw_filled_rounded_rectangle(pathfindingBubbleDrawX - bubblePadding,
                                     pathfindingBubbleDrawY - bubblePadding,
                                     pathfindingBubbleDrawX + pathfindingBubbleWidth + bubblePadding,
                                     pathfindingBubbleDrawY + pathfindingBubbleHeight + bubblePadding,
                                     bubbleCornerRadius,
                                     bubbleCornerRadius,
                                     COLKEY_UI_BUBBLE_BODY);

    al_draw_rounded_rectangle(pathfindingBubbleDrawX - bubblePadding,
                      pathfindingBubbleDrawY - bubblePadding,
                      pathfindingBubbleDrawX + pathfindingBubbleWidth + bubblePadding,
                      pathfindingBubbleDrawY + pathfindingBubbleHeight + bubblePadding,
                      bubbleCornerRadius,
                      bubbleCornerRadius,
                      COLKEY_UI_BUBBLE_FRAME,
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

            string_al_draw_text(builtin, COLKEY_TEXT,
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
        al_draw_text(builtin, COLKEY_TEXT,
                     pathfindingBubbleDrawX+pathfindingBubbleWidth/2,
                     pathfindingBubbleDrawY+pathfindingBubbleWidth/2 - BUILTIN_TEXT_HEIGHT,
                     ALLEGRO_ALIGN_CENTER, "(No Path)");
    }
    al_draw_text(builtin,COLKEY_TEXT,
                 pathfindingBubbleDrawX,
                 pathfindingBubbleDrawY-bubblePadding-BUILTIN_TEXT_HEIGHT,
                 ALLEGRO_ALIGN_LEFT, "Pathfinding:");
}
