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


int Caravan::DetermineMostSuitableTradeDestination()
{

    /// placeholder
    int result = rand()%(PL_MARKER_LAST-PL_MARKER_FIRST +1) + PL_MARKER_FIRST;

    /// list destinations within range
    /// score each destination by their sum deficits in sellingItems + sum surpluses in buyingItems

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

                //UnloadTradeMission();
            }

            if(!tradeMission.missionActive) //&& c->missionCooldown <= 0)
            {
                //std::cout << "debug: Caravan activated" << std::endl;
                tradeMission.missionActive = true;
                //LoadGenericTradeMission(*it);
                tradeMission.SetTradeDestination(DetermineMostSuitableTradeDestination());
            }

        }
}


/*
void Place::LoadGenericTradeMission(Caravan *c)
{
    /// Generic trade mission loads caravan with the city's full breadth of surplus goods.
    /// The quantity of each good is directly proportional to surplusRatio.

    //std::cout << "Debug: Loading generic trade mission to " << c->caravanLeader->name << std::endl;

    c->tradeMission.SetMissionType(TRADE_MISSION_TYPE_GENERIC);

    c->tradeMission.sellingItems.clear();
    c->tradeMission.buyingItems.clear();

    if(surplusesTopTen.size() > 0)
    {
        float surplusSum = 0; // To tally up the total quantity of surplus goods across all items.

        for(std::vector<int>::iterator it = surplusesTopTen.begin(); it != surplusesTopTen.end(); ++it)
        {
            c->tradeMission.sellingItems[*it] = 0;
            surplusSum += surplusRatio.at(*it);
        }

        float cargoLimit = c->cargoWeightMax; // Assumes current weight of 0 after UnloadTradeMission

        /// revise loop to take into account the amount of surplus city is willing to sell (less than amount that would put it at low consumption tier... but how low?)
        for(std::map<int,float>::iterator it = c->tradeMission.sellingItems.begin(); it != c->tradeMission.sellingItems.end(); ++it)
        {
            float transferQuantity = (surplusRatio.at((*it).first) / surplusSum ) * cargoLimit; // Proportion of caravan's cargo hold to be filled up with each item

            if(transferQuantity >= 1) // Don't bother transferring less than 1. It'll get drawn as a zero in cargo and be confusing.
            {
                float transferLimit = 0; //Cannot transfer more stock than is present in city inventory
                if(inventory[PLACE_INVENTORY_MARKET].cargo.count((*it).first) > 0) /// Check if key exists in inventory map... which it should, since there is a surplus - however, program crashes without this line, so investigate
                    transferLimit = inventory[PLACE_INVENTORY_MARKET].cargo.at((*it).first);

                if(transferQuantity > transferLimit)
                    transferQuantity = transferLimit;

                // Must record transaction before transfering items out of city inventory or it'll record quantity as zero.
                c->AddTradeRecord(TRADE_RECORD_LOST_NOTHING,0,
                                  (*it).first, transferQuantity,
                                  placeIdentity);

                TransferInventoryStockToCaravan(PLACE_INVENTORY_MARKET, c, (*it).first, transferQuantity);

            }
        }
    }


}
*/

/*
void Place::UnloadTradeMission(Caravan *c)
{
    //std::cout<< "debug: Unloading trade mission of " << c->caravanLeader->name << std::endl;

    // Transfer entire contents of caravan to inventory

    if(c->inventory.cargo.size() > 0)
    {
        for(std::map<int,float>::iterator it = c->inventory.cargo.begin(); it != c->inventory.cargo.end(); ++it)
        {
            // Must record transaction before transfering to city inventory or it'll record quantity as zero.
            c->AddTradeRecord((*it).first, (*it).second,
                              TRADE_RECORD_GAINED_NOTHING, 0,
                              placeIdentity);

            TransferInventoryStockFromCaravan(PLACE_INVENTORY_MARKET, c, (*it).first, (*it).second);
        }


    }
    else
        std::cout << "Tried to unload, but cargo of inventory is size 0" << std::endl;

}
*/

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

void Caravan::SellCargo()
{
    if(tradeMission.missionType == TRADE_MISSION_TYPE_GENERIC)
    {
        //exponential time complexity
        //produce a two-dimensional array that compares every item in caravan's cargo with every item in city market.
        //List the best deal for each cargo item (the one that eliminates the most deficit in the home city while promoting the most surplus)
        //Trade if the deal passes both parties' willingness to pay. Move on to the second, third, fourth... best deal until no possible deals remain. Break loop early if less than 1 full unit of cargo remains to sell.

        std::vector<float>tradeBenefit; // flattened 2d array ---  row index * numColumns  + column index;

        //int rows = inventory.cargo.size();
        //int cols = whichPlace->inventory[PLACE_INVENTORY_MARKET].cargo.size();

        /*
        /// populate grid
        for(int y = 0; y < rows; y++)
        {
            for(int x = 0; x < cols; x++)
            {
                tradeBenefit.push_back(
                                        // home city's deficit
                                        // city's buy price

                                                 );


            }
        }

        /// list best deals
        for(int y = 0; y < rows; y++)
        {
            for(int x = 0; x < cols; x++)
            {
                int bestDealIndex = -1;
                if(bestDealIndex > -1 && )
                {

                }
            }
        }
        */

    }
    else if(tradeMission.missionType == TRADE_MISSION_TYPE_PICKUP_ORDER)
    {

    }
    else if(tradeMission.missionType == TRADE_MISSION_TYPE_DROPOFF_ORDER)
    {

    }
}

void Caravan::BuyCargo()
{

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
    cargoWeightMax = 100;
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

void Caravan::AddTradeRecord(int il, float ilq, int ig, float igq, int loc)
{
    if(tradeRecords.size() >= tradeRecordsMaxElements)
    {
        delete tradeRecords.front();
        tradeRecords.erase(tradeRecords.begin()); // Infamously inefficient to remove elements from a vector this way, but who cares?
    }

    TradeRecord *newTradeRecord = new TradeRecord(il, ilq, ig, igq, loc);
    tradeRecords.push_back(newTradeRecord);

    UpdateTradeRecordsBubble();
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

    if(tradeRecords.size() > tradeRecordsBubbleNumRows)
        tradeRecordsBubbleNumRows = tradeRecords.size();

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

    string_al_draw_text(builtin,COL_BLACK,inventoryBubbleDrawX,
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
                                     COL_DARK_WHITE);

    al_draw_rounded_rectangle(tradeRecordsBubbleDrawX - bubblePadding,
                              tradeRecordsBubbleDrawY - bubblePadding,
                              tradeRecordsBubbleDrawX + tradeRecordsBubbleWidth + bubblePadding,
                              tradeRecordsBubbleDrawY + tradeRecordsBubbleHeight + bubblePadding,
                              bubbleCornerRadius,
                              bubbleCornerRadius,
                              COL_INDIGO,
                              4);

    al_draw_text(builtin, COL_BLACK, tradeRecordsBubbleDrawX, tradeRecordsBubbleDrawY-bubblePadding-BUILTIN_TEXT_HEIGHT, ALLEGRO_ALIGN_LEFT, "Trade Records:");

    if(tradeRecords.size() > 0)
    {
        unsigned i = 0;
        for(std::vector<TradeRecord*>::iterator it = tradeRecords.begin(); it != tradeRecords.end(); ++it)
        {
            float drawX = tradeRecordsBubbleDrawX;
            float drawY = tradeRecordsBubbleDrawY + i*(TILE_H + tradeRecordsBubbleRowSpacing);

            if((*it)->itemLost != TRADE_RECORD_LOST_NOTHING)
            {
                al_draw_bitmap_region(cargoPng,
                                  ((*it)->itemLost)*TILE_W, 0,
                                  TILE_W, TILE_H,
                                  drawX, drawY,
                                  0);

                string_al_draw_text(builtin, COL_BLACK, drawX+TILE_W, drawY+TILE_H, ALLEGRO_ALIGN_RIGHT, std::to_string((int)(*it)->itemLostQuantity));
            }

            al_draw_bitmap(redArrowPng, drawX + TILE_W, drawY, 0);

            if((*it)->itemGained != TRADE_RECORD_GAINED_NOTHING)
            {
                al_draw_bitmap_region(cargoPng,
                                 ((*it)->itemGained)*TILE_W, 0,
                                  TILE_W, TILE_H,
                                  drawX + 2*TILE_W, drawY,
                                  0);

                string_al_draw_text(builtin, COL_BLACK,
                                    drawX + 3*TILE_W,
                                    drawY+TILE_H,
                                    ALLEGRO_ALIGN_RIGHT, std::to_string((int)(*it)->itemGainedQuantity));
            }

            string_al_draw_text(builtin, COL_BLACK,
                                drawX + 3.5*TILE_W,
                                drawY + TILE_H/2 - tradeRecordsBubbleRowSpacing/2,
                                ALLEGRO_ALIGN_LEFT, placeNames.at((*it)->tradeLocation));
            i++;
        }
    }
    else
        al_draw_text(builtin,COL_BLACK,tradeRecordsBubbleDrawX, tradeRecordsBubbleDrawY, ALLEGRO_ALIGN_LEFT, "(No recent trades).");
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
