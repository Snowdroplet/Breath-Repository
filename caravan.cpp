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

    UpdateCaravanInventoryBubble();
    UpdateCaravanTradeRecordsBubble();

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
    return result;
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
        if(hourChangeTick)
        {
            /// debug
            /*
            if(currentHoursAtPlace > 20)
            {
                std::cout << "Debug: " << caravanLeader->name << " spent " << currentHoursAtPlace << "/" << thresholdHoursAtPlace <<" hours at " << placeNames.at(whichPlace->placeIdentity) << std::endl;
                std::cout << "Number of destinations on path: " << worldGraph.path.size() << std::endl;
                std::cout << "Hometown: " << placeNames.at(hometownID) << std::endl;
            }
            */
            /// ---

            currentHoursAtPlace++;
            if(currentHoursAtPlace >= thresholdHoursAtPlace)
            {

                if(worldGraph.path.size() <= 1) // The path has been followed to its last node. This remaining node will be the destination - I can't call clear() worldGraph.path prematurely, but whatever.
                {

                    pathfindingDestination = SelectRandomTradeDestination(); // This line isn't redundant. Removing it will cause the entire world to congregate at Ericennes (place identity zero).
                    while(pathfindingDestination == whichPlace->placeIdentity) // Reroll until the destination is not the current location.
                    {
                        pathfindingDestination = SelectRandomTradeDestination();
                        //std:: cout << "Debug: " << caravanLeader->name << " rerolled pathfinding destination to " << placeNames.at(pathfindingDestination) << std::endl;
                    }

                    worldGraph.Dijkstra(whichPlace->placeIdentity,pathfindingDestination); // This also overwrites the path with that last remaining element at index 0.

                }
                else // worldGraph.path.size > 1
                {
                    worldGraph.path.erase(worldGraph.path.begin());

                    int nextPlaceOnPath = worldGraph.path[0];

                    for(std::vector<Road*>::iterator it = whichPlace->connections.begin(); it != whichPlace->connections.end(); ++it)
                    {
                        if((*it)->endpointA == nextPlaceOnPath)
                            MoveToRoad((*it),true); // Reverse path = true

                        else if((*it)->endpointB == nextPlaceOnPath)
                            MoveToRoad((*it),false); // Forward path = true
                    }
                }

                UpdateCaravanPathfindingBubble();
            }
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
        atHome = true;


    onRoad = false;
    whichRoad = nullptr;
    atRoadsEnd = false;

    currentHoursAtPlace = 0;
    thresholdHoursAtPlace = rand()%(MAX_HOURS_AT_PLACE-MIN_HOURS_AT_PLACE) + MIN_HOURS_AT_PLACE;

    overworldXPosition = p->overworldXPosition;
    overworldYPosition = p->overworldYPosition;

    if(caravanLeader != nullptr)
        caravanLeader->facingLeft = false;

/// Effects on UI bubbles
    if(overworldCameraCaravan == this)
        bubbleViewPlace = p;

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

    UpdateCaravanPathfindingBubble();

/// Effects on UI bubbles
    if(overworldCameraCaravan == this)
        bubbleViewPlace = nullptr;
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
    UpdateCaravanInventoryBubble();
}
void Caravan::RemoveInventoryStock(int a, float b)
{
    inventory.RemoveStock(a,b);
    UpdateCargoWeight();
    UpdateCaravanInventoryBubble();
}
void Caravan::SetInventoryStock(int a, float b)
{
    inventory.SetStock(a,b);
    UpdateCargoWeight();
    UpdateCaravanInventoryBubble();
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

void Caravan::UpdateCaravanInventoryBubble()
{
        caravanInventoryBubbleNumCols = caravanInventoryBubbleBaseCols;
        caravanInventoryBubbleNumRows = caravanInventoryBubbleBaseRows;

        while(inventory.cargo.size() > caravanInventoryBubbleNumCols*caravanInventoryBubbleNumRows)
        {
            if(caravanInventoryBubbleNumCols <= caravanInventoryBubbleNumRows)
                caravanInventoryBubbleNumCols++;
            else
                caravanInventoryBubbleNumRows++;
        }

        caravanInventoryBubbleWidth = caravanInventoryBubbleNumCols*TILE_W;
        caravanInventoryBubbleHeight = caravanInventoryBubbleNumRows*(TILE_H+caravanInventoryBubbleRowSpacing);
}

void Caravan::UpdateCaravanTradeRecordsBubble()
{
        caravanTradeRecordsBubbleNumRows = caravanTradeRecordsBubbleBaseRows;

        unsigned rowCount = 0;
        for(std::vector<TradeRecord*>::iterator it = tradeRecords.begin(); it != tradeRecords.end(); ++it)
            rowCount += (*it)->numRows;

        if(rowCount > caravanTradeRecordsBubbleBaseRows)
            caravanTradeRecordsBubbleNumRows = rowCount;

        caravanTradeRecordsBubbleHeight = caravanTradeRecordsBubbleNumRows*(TILE_H+caravanTradeRecordsBubbleRowSpacing);
}

void Caravan::UpdateCaravanPathfindingBubble()
{

        caravanPathfindingBubbleNumCols = caravanPathfindingBubbleBaseCols;
        caravanPathfindingBubbleNumRows = caravanPathfindingBubbleBaseRows;

        if(worldGraph.path.size() > caravanPathfindingBubbleNumCols)
            caravanPathfindingBubbleNumCols = worldGraph.path.size();

        caravanPathfindingBubbleWidth = caravanPathfindingBubbleNumCols*(2*TILE_W+caravanPathfindingBubbleColSpacing) - caravanPathfindingBubbleColSpacing;
        caravanPathfindingBubbleHeight = caravanPathfindingBubbleNumRows*(2*TILE_H+caravanPathfindingBubbleRowSpacing);
}

void Caravan::UpdateAllBubbles()
{
    UpdateCaravanInventoryBubble();
    UpdateCaravanTradeRecordsBubble();
    UpdateCaravanPathfindingBubble();
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

void Caravan::DrawCaravanInventoryBubble()
{
    al_draw_filled_rounded_rectangle(caravanInventoryBubbleDrawX - bubblePadding,
                                     caravanInventoryBubbleDrawY - bubblePadding,
                                     caravanInventoryBubbleDrawX + caravanInventoryBubbleWidth + bubblePadding,
                                     caravanInventoryBubbleDrawY + caravanInventoryBubbleHeight + bubblePadding,
                                     bubbleCornerRadius,
                                     bubbleCornerRadius,
                                     COLKEY_UI_BUBBLE_BODY);


    al_draw_rounded_rectangle(caravanInventoryBubbleDrawX - bubblePadding,
                              caravanInventoryBubbleDrawY - bubblePadding,
                              caravanInventoryBubbleDrawX + caravanInventoryBubbleWidth + bubblePadding,
                              caravanInventoryBubbleDrawY + caravanInventoryBubbleHeight + bubblePadding,
                              bubbleCornerRadius,
                              bubbleCornerRadius,
                              COLKEY_UI_BUBBLE_FRAME,
                              4);

    string_al_draw_text(builtin8,COLKEY_TEXT,caravanInventoryBubbleDrawX, caravanInventoryBubbleDrawY-bubblePadding-TEXT_HEIGHT_8, ALLEGRO_ALIGN_LEFT, caravanInventoryBubbleLabel);

    if(inventory.cargo.size() > 0)
    {
        unsigned i = 0;
        for(std::map<int,float>::iterator it = inventory.cargo.begin(); it != inventory.cargo.end(); ++it)
        {
            float drawX = caravanInventoryBubbleDrawX + i%caravanInventoryBubbleNumCols*TILE_W;
            float drawY = caravanInventoryBubbleDrawY + i/caravanInventoryBubbleNumCols*(TILE_H + caravanInventoryBubbleRowSpacing);

            al_draw_bitmap_region(cargoPng,
                                  ((*it).first)*TILE_W, 0,
                                  TILE_W, TILE_H,
                                  drawX, drawY,
                                  0);

            string_al_draw_text(builtin8, COLKEY_TEXT, drawX+TILE_W, drawY+TILE_H, ALLEGRO_ALIGN_RIGHT, std::to_string((int)(*it).second));
            i++;
        }
    }
    else
        string_al_draw_text(builtin8,COLKEY_TEXT,caravanInventoryBubbleDrawX,caravanInventoryBubbleDrawY,ALLEGRO_ALIGN_LEFT,caravanInventoryBubbleEmptyText);

    string_al_draw_text(builtin8,COLKEY_TEXT,caravanInventoryBubbleDrawX,
                        caravanInventoryBubbleDrawY+caravanInventoryBubbleHeight + TEXT_HEIGHT_8,
                        ALLEGRO_ALIGN_LEFT,
                        "Weight: " + std::to_string((int)cargoWeight) + " / " + std::to_string((int)cargoWeightMax) );

}

void Caravan::DrawCaravanTradeRecordsBubble()
{
    al_draw_filled_rounded_rectangle(caravanTradeRecordsBubbleDrawX - bubblePadding,
                                     caravanTradeRecordsBubbleDrawY - bubblePadding,
                                     caravanTradeRecordsBubbleDrawX + caravanTradeRecordsBubbleWidth + bubblePadding,
                                     caravanTradeRecordsBubbleDrawY + caravanTradeRecordsBubbleHeight + bubblePadding,
                                     bubbleCornerRadius,
                                     bubbleCornerRadius,
                                     COLKEY_UI_BUBBLE_BODY);

    al_draw_rounded_rectangle(caravanTradeRecordsBubbleDrawX - bubblePadding,
                              caravanTradeRecordsBubbleDrawY - bubblePadding,
                              caravanTradeRecordsBubbleDrawX + caravanTradeRecordsBubbleWidth + bubblePadding,
                              caravanTradeRecordsBubbleDrawY + caravanTradeRecordsBubbleHeight + bubblePadding,
                              bubbleCornerRadius,
                              bubbleCornerRadius,
                              COLKEY_UI_BUBBLE_FRAME,
                              4);


    string_al_draw_text(builtin8, COLKEY_TEXT, caravanTradeRecordsBubbleDrawX, caravanTradeRecordsBubbleDrawY-bubblePadding-TEXT_HEIGHT_8, ALLEGRO_ALIGN_LEFT, caravanTradeRecordsBubbleLabel);

    if(tradeRecords.size() > 0)
    {
        unsigned col = 0;
        unsigned row = 0;

        for(std::vector<TradeRecord*>::reverse_iterator rit = tradeRecords.rbegin(); rit != tradeRecords.rend(); ++rit)
        {
            string_al_draw_text(builtin8, COLKEY_TEXT,
                                caravanTradeRecordsBubbleDrawX + caravanTradeRecordsBubblePlaceNameWidth,
                                caravanTradeRecordsBubbleDrawY + row*(TILE_H + caravanTradeRecordsBubbleRowSpacing),
                                ALLEGRO_ALIGN_RIGHT,
                                placeNames.at((*rit)->location)); //+ " (" + std::to_string((*rit)->numRows) + ")");


            if((*rit)->tradeQuantities.size() > 0)
            {
                for(std::map<int, int>::iterator jt = (*rit)->tradeQuantities.begin(); jt != (*rit)->tradeQuantities.end(); ++jt)
                {
                    if(col >= caravanTradeRecordsBubbleNumIconCols)
                    {
                        col = 0;
                        row++;
                    }

                    float iconDrawX = caravanTradeRecordsBubbleDrawX + caravanTradeRecordsBubblePlaceNameWidth + col*(TILE_W);
                    float iconDrawY = caravanTradeRecordsBubbleDrawY + row*(TILE_H + caravanTradeRecordsBubbleRowSpacing);

                    if((*jt).second < 0)
                        al_draw_filled_rectangle(iconDrawX, iconDrawY,
                                                 iconDrawX+TILE_W, iconDrawY+TILE_H+caravanTradeRecordsBubbleRowSpacing,
                                                 COLKEY_UI_TRADERECORD_NEGATIVE);
                    else
                        al_draw_filled_rectangle(iconDrawX, iconDrawY,
                                                 iconDrawX+TILE_W, iconDrawY+TILE_H+caravanTradeRecordsBubbleRowSpacing,
                                                 COLKEY_UI_TRADERECORD_POSITIVE);


                    al_draw_bitmap_region(cargoPng,
                                          ((*jt).first)*TILE_W, 0,
                                          TILE_W, TILE_H,
                                          iconDrawX, iconDrawY,
                                          0);

                    string_al_draw_text(builtin8, COLKEY_TEXT, iconDrawX+TILE_W, iconDrawY+TILE_H, ALLEGRO_ALIGN_RIGHT, std::to_string((*jt).second));

                    col++;
                }

            }
            else if((*rit)->tradeQuantities.size() == 0) // tradeQuantities vector empty
            {
                string_al_draw_text(builtin8, COLKEY_TEXT,
                                    caravanTradeRecordsBubbleDrawX + caravanTradeRecordsBubblePlaceNameWidth + col*(TILE_W),
                                    caravanTradeRecordsBubbleDrawY + row*(TILE_H + caravanTradeRecordsBubbleRowSpacing) + TILE_H/2 - TEXT_HEIGHT_8/2,
                                    ALLEGRO_ALIGN_LEFT,
                                    caravanTradeRecordsBubbleNoTransactionText);
            }

            col = 0;
            row++;
        }
    }
    else
        string_al_draw_text(builtin8,COLKEY_TEXT,caravanTradeRecordsBubbleDrawX, caravanTradeRecordsBubbleDrawY, ALLEGRO_ALIGN_LEFT, caravanTradeRecordsBubbleEmptyText);
}

void Caravan::DrawCaravanPathfindingBubble()
{
    al_draw_filled_rounded_rectangle(caravanPathfindingBubbleDrawX - bubblePadding,
                                     caravanPathfindingBubbleDrawY - bubblePadding,
                                     caravanPathfindingBubbleDrawX + caravanPathfindingBubbleWidth + bubblePadding,
                                     caravanPathfindingBubbleDrawY + caravanPathfindingBubbleHeight + bubblePadding,
                                     bubbleCornerRadius,
                                     bubbleCornerRadius,
                                     COLKEY_UI_BUBBLE_BODY);

    al_draw_rounded_rectangle(caravanPathfindingBubbleDrawX - bubblePadding,
                              caravanPathfindingBubbleDrawY - bubblePadding,
                              caravanPathfindingBubbleDrawX + caravanPathfindingBubbleWidth + bubblePadding,
                              caravanPathfindingBubbleDrawY + caravanPathfindingBubbleHeight + bubblePadding,
                              bubbleCornerRadius,
                              bubbleCornerRadius,
                              COLKEY_UI_BUBBLE_FRAME,
                              4);

    if(!worldGraph.path.empty())
    {

        for(unsigned i = 0; i < worldGraph.path.size(); i++)
        {
            float drawX = caravanPathfindingBubbleDrawX + i*(2*TILE_H+caravanPathfindingBubbleColSpacing);
            float drawY = caravanPathfindingBubbleDrawY;
            al_draw_bitmap_region(overworldPlacePng,
                                  worldGraph.path[i]*2*TILE_W, 0,
                                  2*TILE_W, 2*TILE_H,
                                  drawX, drawY,
                                  0);

            string_al_draw_text(builtin8, COLKEY_TEXT,
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
        string_al_draw_text(builtin8, COLKEY_TEXT,
                            caravanPathfindingBubbleDrawX+caravanPathfindingBubbleWidth/2,
                            caravanPathfindingBubbleDrawY+caravanPathfindingBubbleWidth/2 - TEXT_HEIGHT_8,
                            ALLEGRO_ALIGN_CENTER, caravanPathfindingBubbleLabel);
    }
    string_al_draw_text(builtin8,COLKEY_TEXT,
                        caravanPathfindingBubbleDrawX,
                        caravanPathfindingBubbleDrawY-bubblePadding-TEXT_HEIGHT_8,
                        ALLEGRO_ALIGN_LEFT, caravanPathfindingBubbleLabel);
}
