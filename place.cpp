#include "place.h"

std::map<int, Place*> Place::places;

Place::Place(int id)
{
    identity = id;
    //std::cout << "Place created with ID " << id << std::endl;

    name = placeNames.at(identity);

    overworldXPosition = placeOverworldXYCells.at(id)[0] *TILE_W;
    overworldYPosition = placeOverworldXYCells.at(id)[1] *TILE_H;

    population = placeInitialPopulation.at(id);

    standardOfLiving = LIVING_COMFORTABLE;

    //const int d/*ebug production quantity*/ = 6;
    for(std::vector<int>::const_iterator it = placeInitialIndustries.at(id).cbegin(); it != placeInitialIndustries.at(id).cend(); ++it)
        AddIndustry(*it, 1 + population[jobExpertiseType.at(*it)]);

    for(unsigned i = IT_MARKER_FIRST; i < IT_MARKER_LAST; i++)
        maintainenceConsumptionTier[i] = standardOfLiving;

    for(std::map<int,int>::iterator it = consumptionTimer.begin(); it != consumptionTimer.end(); ++it)
        (*it).second = rand()%economyBaseMaintainenceConsumptionRate.at((*it).first).at(standardOfLiving);

    for(std::map<int,float>::iterator it = consumptionDecimalOwing.begin(); it != consumptionDecimalOwing.end(); ++it)
        (*it).second = 0;

    AddInitialStock();

    visitorBubbleActive = false;
}

Place::~Place()
{
    //std::cout << "Place deleted." << std::endl;

    availableCrew.clear();
    citizens.clear();
    visitors.clear();

    for(std::vector<Industry*>::iterator it = industries.begin(); it != industries.end();)
    {
        delete *it;
        industries.erase(it);
    }

    connections.clear();

    for(std::vector<FlyingText*>::iterator it = upFlyingTexts.begin(); it != upFlyingTexts.end(); ++it)
        delete *it;
    upFlyingTexts.clear();

    for(std::vector<FlyingText*>::iterator it = downFlyingTexts.begin(); it != downFlyingTexts.end(); ++it)
        delete *it;
    downFlyingTexts.clear();

}

void Place::AddAvailableCrew(Being *b)
{
    availableCrew.push_back(b);
}

void Place::RemoveAvailableCrew(Being *b)
{

}

void Place::AddCitizen(Being *b)
{
    citizens.push_back(b);
}

void Place::RemoveCitizen(Being *b)
{

}

void Place::AddVisitorCaravan(Caravan *c)
{
    visitors.push_back(c);
    if(overworldCameraCaravan == c)
        UpdateAllBubbles();
    else
        UpdateVisitorBubble();
}

void Place::RemoveVisitorCaravan(Caravan *c)
{
    for(std::vector<Caravan*>::iterator it = visitors.begin(); it != visitors.end();)
    {
        if(*it == c)
            it = visitors.erase(it);
        else
        {
            (*it)->thresholdTimeAtPlace += removeVisitorCaravanDelay;
            ++it;
        }
    }



    UpdateVisitorBubble();
}

void Place::UpdateEconomyData()
{
    UpdateConsumptionData();
    UpdateProductionData();
}


void Place::UpdateConsumptionData()
{
    dailyConsumption.clear();
/// Industrial demand
    for(std::vector<Industry*>::iterator it = industries.begin(); it != industries.end(); ++it)
    {
        for(std::map<int,float>::iterator jt = (*it)->inputs.begin(); jt != (*it)->inputs.end(); ++jt)
        {
            if(dailyConsumption.count((*jt).first) < 1) // Not sure if this is necessary.
                dailyConsumption[(*jt).first] = 0;

            dailyConsumption[(*jt).first] += (*it)->CalculateAverageInput((*jt).first, 24);

            //std::cout << this->name << ": Daily consumption of " << itemNames.at((*jt).first) << " += " << dailyConsumption[(*jt).first] << std::endl;
        }
    }

/// Maintainence demand (city health/happiness demand)

    /*
        for(std::map<int, std::array<float,5>>::const_iterator it = economyBaseMaintainenceConsumptionRate.cbegin(); it != economyBaseMaintainenceConsumptionRate.cend(); ++it)
        {
            if(dailyConsumption.count((*jt).first) < 1) // Not sure if this is necessary.
                    dailyConsumption[(*jt).first] = 0;

            dailyConsumption[(*jt).first] +=
        }
    */
}

void Place::UpdateProductionData()
{
    for(std::vector<Industry*>::iterator it = industries.begin(); it != industries.end(); ++it)
    {
        for(std::map<int,float>::iterator jt = (*it)->inputs.begin(); jt != (*it)->inputs.end(); ++jt)
        {
            if(dailyConsumption.count((*jt).first) < 1) // Not sure if this is necessary.
                dailyConsumption[(*jt).first] = 0;

            dailyConsumption[(*jt).first] += (*it)->CalculateAverageInput((*jt).first, 24);

            //std::cout << this->name << ": Daily consumption of " << itemNames.at((*jt).first) << " += " << dailyConsumption[(*jt).first] << std::endl;
        }
    }
}


void Place::AddIndustry(int whichIndustry, float baseProdPerTick)
{
    industries.push_back(new Industry(whichIndustry, baseProdPerTick));
}

bool Place::CheckJobInputs(Industry *whichIndustry)
{
    for(std::map<int,float>::iterator jt = whichIndustry->inputs.begin(); jt != whichIndustry->inputs.end(); ++jt)
    {
        //if((inventory[PLACE_INVENTORY_INDUSTRIAL].cargo.count((*jt).first) < 1)) // Is the job's input requirement present in map at all?
          if((inventory[PLACE_INVENTORY_MARKET].cargo.count((*jt).first) < 1))
            return false;
        //else if((inventory[PLACE_INVENTORY_INDUSTRIAL].cargo[(*jt).first] < (*jt).second)) // Is the quantity in inventory less than the job's input requirement?
          else if((inventory[PLACE_INVENTORY_MARKET].cargo[(*jt).first] < (*jt).second))
            return false;
    }
    return true;
}

void Place::DeductJobInputs(Industry* whichIndustry)
{
    for(std::map<int,float>::iterator it = whichIndustry->inputs.begin(); it != whichIndustry->inputs.end(); ++it)
    {
        //RemoveInventoryStock(PLACE_INVENTORY_INDUSTRIAL, (*it).first, (*it).second);
        RemoveInventoryStock(PLACE_INVENTORY_MARKET, (*it).first, (*it).second);
        QueueDownFlyingText((*it).first, "-" + std::to_string((int)(*it).second), overworldXPosition, overworldYPosition);
    }
}

void Place::ProgressProduction()
{
    for(std::vector<Industry*>::iterator it = industries.begin(); it != industries.end(); ++it)
    {
        if((*it)->jobState == JOB_STATE_INSUFFICIENT_INPUTS)
            (*it)->ProgressJobPause();

        if((*it)->jobState == JOB_STATE_DEDUCTIONS_NECESSARY)
        {
            if(CheckJobInputs(*it))
            {
                DeductJobInputs(*it);
                (*it)->SetJobStateNormal();
            }
            else
                (*it)->SetJobStateInsufficientInputs(4);
        }

        if((*it)->jobState == JOB_STATE_NORMAL)
            (*it)->ProgressJobNormalState();

        if((*it)->jobState == JOB_STATE_HARVEST_READY)
        {
            for(std::map<int,float>::iterator jt = (*it)->outputs.begin(); jt != (*it)->outputs.end(); ++jt)
            {
                //AddInventoryStock(PLACE_INVENTORY_RESERVE, (*jt).first, (*jt).second);
                AddInventoryStock(PLACE_INVENTORY_MARKET, (*jt).first, (*jt).second);
                QueueUpFlyingText((*jt).first, "+" + std::to_string((int)(*jt).second), overworldXPosition, overworldYPosition);
            }

            (*it)->SetJobStateDeductionsNecessary();
        }
    }
}

void Place::ProgressConsumption()
{
    for(std::map<int,int>::iterator it = consumptionTimer.begin(); it != consumptionTimer.end(); ++it)
    {
        int consumptionTimerThreshold = (*it).second = economyBaseMaintainenceConsumptionRate.at((*it).first).at(standardOfLiving);

        if(consumptionTimerThreshold != -1)
        {
            (*it).second++;
            if((*it).second >= consumptionTimerThreshold)
            {
                float consumptionQuantity = 0;
                consumptionQuantity += consumptionDecimalOwing.at((*it).first);
                consumptionDecimalOwing.at((*it).first) = 0;

                for(unsigned i = EXP_MARKER_FIRST; i < EXP_MARKER_LAST; i++)
                    consumptionQuantity += population[i] * economyRoleMaintainenceConsumptionQuantity.at((*it).first).at(i); // Not consumptionRate, mind. Quantity.

                float consumptionQuantityInteger;
                consumptionDecimalOwing.at((*it).first) += std::modf(consumptionQuantity,&consumptionQuantityInteger);


                // map::count taken care of in inventory.cpp
                RemoveInventoryStock(PLACE_INVENTORY_MARKET,(*it).first, consumptionQuantityInteger);


                (*it).second = 0;
            }
        }

    }
}

void Place::AddInventoryStock(unsigned whichInventory, int a, int b)
{
    unsigned prev = inventory[whichInventory].cargo.size();
    inventory[whichInventory].AddStock(a,b);

    if(inventory[whichInventory].cargo.size() != prev)
        UpdateInventoryBubble(whichInventory);
}
void Place::RemoveInventoryStock(unsigned whichInventory, int a, int b)
{
    unsigned prev = inventory[whichInventory].cargo.size();
    inventory[whichInventory].RemoveStock(a,b);

    if(inventory[whichInventory].cargo.size() != prev)
        UpdateInventoryBubble(whichInventory);
}
void Place::SetInventoryStock(unsigned whichInventory, int a, int b)
{
    unsigned prev = inventory[whichInventory].cargo.size();
    inventory[whichInventory].SetStock(a,b);

    if(inventory[whichInventory].cargo.size() != prev)
        UpdateInventoryBubble(whichInventory);
}

void Place::TransferInventoryStock(unsigned sourceInv, unsigned destInv, int a, int b)
{
    RemoveInventoryStock(sourceInv,a,b);
    AddInventoryStock(destInv,a,b);
}

/*
void Place::SetResourceAllocation(float reserveProportion, float marketProportion, float industrialProportion, float maintainenceProportion)
{
    float total = reserveProportion + marketProportion + industrialProportion + maintainenceProportion;

    resourceAllocation[PLACE_INVENTORY_RESERVE] = reserveProportion/total;
    resourceAllocation[PLACE_INVENTORY_MARKET] = marketProportion/total;
    resourceAllocation[PLACE_INVENTORY_INDUSTRIAL] = industrialProportion/total;
    resourceAllocation[PLACE_INVENTORY_MAINTAINENCE] = maintainenceProportion/total;
}
*/

/*
void Place::AllocateReserve(unsigned whichItem)
{
    float transferQuantity = inventory[PLACE_INVENTORY_RESERVE].cargo.at(whichItem);


/// Should allocate resourceAllocationOwing[] from previous cycles first, before anything else.

    for(unsigned i = PLACE_INVENTORY_MARKER_FIRST; i < PLACE_INVENTORY_MARKER_LAST+1; i++)
    {
        float toTransfer = transferQuantity/resourceAllocation[whichItem];
        float toTransferInteger; // TransferInventoryStock can only accept whole numbers. (float type for modf)

        resourceAllocationOwing[i] = std::modf(toTransfer,&toTransferInteger); // Splits toTransfer into its fractional part(transfer integer) and decimal part(owing).

        std::cout << toTransfer << " --> fractional: " << toTransferInteger << "   decimal: " << resourceAllocation[i] << std::endl;

        TransferInventoryStock(PLACE_INVENTORY_RESERVE,i,whichItem,toTransferInteger);

    }
}
*/



void Place::AddInitialStock()
{
    for(std::vector<Industry*>::iterator it = industries.begin(); it != industries.end(); ++it)
    {
        for(std::map<int,float>::iterator jt = (*it)->inputs.begin(); jt != (*it)->inputs.end(); ++jt)
            AddInventoryStock(PLACE_INVENTORY_MARKET, (*jt).first, (*jt).second*2);
            ///AddInventoryStock(PLACE_INVENTORY_INDUSTRIAL, (*jt).first, (*jt).second*2);

        for(std::map<int,float>::iterator kt = (*it)->outputs.begin(); kt != (*it)->outputs.end(); ++kt)
            AddInventoryStock(PLACE_INVENTORY_MARKET, (*kt).first, (*kt).second*1);
            ///AddInventoryStock(PLACE_INVENTORY_RESERVE, (*kt).first, (*kt).second*1);
    }

    for(unsigned i = IT_MARKER_FIRST; i < IT_MARKER_LAST; i++)
    {
        for(unsigned j = EXP_MARKER_FIRST; j < EXP_MARKER_LAST; j++)
        {
            float toAdd = (economyRoleMaintainenceConsumptionQuantity.at(i).at(standardOfLiving))*population[j]*3;
            if(toAdd >= 1)
                AddInventoryStock(PLACE_INVENTORY_MARKET, i, toAdd); // Truncates, of course.

            /// Instead of consumption * 3, should give enough consumption for 7 days' maintainence.
        }
    }
}

void Place::UpdateAllBubbles()
{
    UpdateVisitorBubble();
    UpdateInventoryBubbles();
    UpdateIndustriesBubble();
}

void Place::UpdateVisitorBubble()
{
    if(visitors.size() > 0)
    {
        visitorBubbleNumCols = 1;
        visitorBubbleNumRows = 1;

        while(visitors.size() > visitorBubbleNumCols*visitorBubbleNumRows)
        {
            if(visitorBubbleNumCols <= visitorBubbleNumRows)
                visitorBubbleNumCols++;
            else
                visitorBubbleNumRows++;
        }

        visitorBubbleActive = true;
        visitorBubbleWidth = visitorBubbleNumCols*TILE_W;
        visitorBubbleHeight = visitorBubbleNumRows*TILE_H;
    }
    else
        visitorBubbleActive = false;
}

void Place::UpdateInventoryBubbles()
{
    for(unsigned i = PLACE_INVENTORY_MARKER_FIRST; i < PLACE_INVENTORY_MARKER_LAST+1; i++)
        UpdateInventoryBubble(i);
}

void Place::UpdateInventoryBubble(unsigned which)
{
    inventoryBubbleNumCols[which] = inventoryBubbleBaseCols;
    inventoryBubbleNumRows[which] = inventoryBubbleBaseRows;

    while(inventory[which].cargo.size() > inventoryBubbleNumCols[which]*inventoryBubbleNumRows[which])
    {
        if(inventoryBubbleNumCols[which] <= inventoryBubbleNumRows[which])
            inventoryBubbleNumCols[which]++;
        else
            inventoryBubbleNumRows[which]++;
    }

    inventoryBubbleWidth[which] = inventoryBubbleNumCols[which]*TILE_W;
    inventoryBubbleHeight[which] = inventoryBubbleNumRows[which]*(TILE_H+inventoryBubbleRowSpacing);
}

void Place::UpdateIndustriesBubble()
{

    industriesBubbleHeight = industries.size()*(TILE_H+industriesBubbleRowSpacing + BUILTIN_TEXT_HEIGHT);
}

void Place::ProgressIndustriesBubbleProgressBars()
{
    for(std::vector<Industry*>::iterator it = industries.begin(); it != industries.end(); ++it)
        (*it)->UpdateProgressBar();
}

void Place::DrawSpriteOnOverworld()
{
    float drawX = overworldXPosition - overworldCameraXPosition - OVERWORLD_SPRITE_W/2;
    float drawY = overworldYPosition - overworldCameraYPosition - OVERWORLD_SPRITE_H/2;

    if(drawX > OVERWORLD_MIN_DRAW_X && drawX < OVERWORLD_MAX_DRAW_X
            && drawY > OVERWORLD_MIN_DRAW_Y && drawY < OVERWORLD_MAX_DRAW_Y)
    {
        float nameDrawX = overworldXPosition - overworldCameraXPosition;
        float nameDrawY = overworldYPosition - overworldCameraYPosition + OVERWORLD_SPRITE_H/2;

        al_draw_bitmap_region(overworldPlacePng,
                              0 + identity*64, 0,
                              64,64,
                              drawX,
                              drawY,
                              0);

        string_al_draw_text(builtin, COL_BLACK, nameDrawX, nameDrawY, ALLEGRO_ALIGN_CENTER, name);
    }
}

void Place::DrawVisitorBubbleOnOverworld()
{
    if(visitorBubbleActive)
    {
        /// To do: Adjust for sprites that are not TILE_W in size.

        float drawX = overworldXPosition - overworldCameraXPosition;
        float drawY = overworldYPosition - overworldCameraYPosition - OVERWORLD_SPRITE_H;

        if(drawX > OVERWORLD_MIN_DRAW_X && drawX < OVERWORLD_MAX_DRAW_X
                && drawY > OVERWORLD_MIN_DRAW_Y && drawY < OVERWORLD_MAX_DRAW_Y)
        {


            al_draw_filled_rounded_rectangle(drawX - visitorBubbleWidth/2 - bubbleWidthPadding,
                                             drawY - visitorBubbleHeight/2 - bubbleHeightPadding,
                                             drawX + visitorBubbleWidth/2 + bubbleWidthPadding,
                                             drawY + visitorBubbleHeight/2 + bubbleHeightPadding,
                                             bubbleCornerRadius,
                                             bubbleCornerRadius,
                                             COL_DARK_WHITE);


            al_draw_rounded_rectangle(drawX - visitorBubbleWidth/2 - bubbleWidthPadding,
                                      drawY - visitorBubbleHeight/2 - bubbleHeightPadding,
                                      drawX + visitorBubbleWidth/2 + bubbleWidthPadding,
                                      drawY + visitorBubbleHeight/2 + bubbleHeightPadding,
                                      bubbleCornerRadius,
                                      bubbleCornerRadius,
                                      COL_INDIGO,
                                      4);

            for(unsigned i = 0; i < visitors.size(); i++)
            {
                visitors[i]->DrawActivity(drawX - visitorBubbleWidth/2 + (i%visitorBubbleNumCols*TILE_W) + TILE_W/2,
                                          drawY - visitorBubbleHeight/2 + (i/visitorBubbleNumCols*TILE_H) + TILE_H/2);
            }

        }
    }
}

void Place::QueueUpFlyingText(int ic, std::string t, float x, float y)
{
    upFlyingTexts.push_back(new FlyingText(ic, t, x, y, true));
}

void Place::QueueDownFlyingText(int ic, std::string t, float x, float y)
{
    downFlyingTexts.push_back(new FlyingText(ic, t, x, y, false));
}

void Place::ProgressFlyingTexts()
{
    for(std::vector<FlyingText*>::iterator it = upFlyingTexts.begin(); it != upFlyingTexts.end();)
    {
        if(!(*it)->active)
        {
            delete *it;
            upFlyingTexts.erase(it);
        }
        else
        {
            if((*it)->queued)
            {
                if(it == upFlyingTexts.begin())
                    (*it)->queued = false;

                if(it > upFlyingTexts.begin())
                {
                    (*it)->queued = false;
                    for(std::vector<FlyingText*>::iterator rjt = it; rjt != upFlyingTexts.begin(); --rjt)
                    {
                        (*(rjt-1))->overworldYPosition -= MINI_TILE_H;
                    }
                }
            }

            (*it)->Progress();
            ++it;
        }
    }

    for(std::vector<FlyingText*>::iterator it = downFlyingTexts.begin(); it != downFlyingTexts.end();)
    {
        if(!(*it)->active)
        {
            delete *it;
            downFlyingTexts.erase(it);
        }
        else
        {
            if((*it)->queued)
            {
                if(it == downFlyingTexts.begin())
                    (*it)->queued = false;

                if(it > downFlyingTexts.begin())
                {
                    (*it)->queued = false;
                    for(std::vector<FlyingText*>::iterator rjt = it; rjt != downFlyingTexts.begin(); --rjt)
                    {
                        (*(rjt-1))->overworldYPosition += MINI_TILE_H;
                    }
                }
            }

            (*it)->Progress();
            ++it;
        }
    }
}

void Place::DrawInventoryBubbles()
{

    for(unsigned i = PLACE_INVENTORY_MARKER_FIRST; i < PLACE_INVENTORY_MARKER_LAST+1; i++)
    {
        al_draw_filled_rounded_rectangle(inventoryBubbleDrawX[i] - bubbleWidthPadding,
                                         inventoryBubbleDrawY[i] - bubbleHeightPadding,
                                         inventoryBubbleDrawX[i] + inventoryBubbleWidth[i] + bubbleWidthPadding,
                                         inventoryBubbleDrawY[i] + inventoryBubbleHeight[i] + bubbleHeightPadding,
                                         bubbleCornerRadius,
                                         bubbleCornerRadius,
                                         COL_DARK_WHITE);


        al_draw_rounded_rectangle(inventoryBubbleDrawX[i] - bubbleWidthPadding,
                                  inventoryBubbleDrawY[i] - bubbleHeightPadding,
                                  inventoryBubbleDrawX[i] + inventoryBubbleWidth[i] + bubbleWidthPadding,
                                  inventoryBubbleDrawY[i] + inventoryBubbleHeight[i] + bubbleHeightPadding,
                                  bubbleCornerRadius,
                                  bubbleCornerRadius,
                                  COL_INDIGO,
                                  4);

        string_al_draw_text(builtin,COL_BLACK,inventoryBubbleDrawX[i], inventoryBubbleDrawY[i]-bubbleHeightPadding-8, ALLEGRO_ALIGN_LEFT, inventoryBubbleLabel[i]);

        if(inventory[i].cargo.size() > 0)
        {
            unsigned s = 0;
            for(std::map<int,int>::iterator it = inventory[i].cargo.begin(); it != inventory[i].cargo.end(); ++it)
            {
                float drawX = inventoryBubbleDrawX[i] + s%inventoryBubbleNumCols[i]*TILE_W;
                float drawY = inventoryBubbleDrawY[i] + s/inventoryBubbleNumCols[i]*(TILE_H+inventoryBubbleRowSpacing);

                al_draw_bitmap_region(cargoPng,
                                      0+((*it).first)*TILE_W, 0,
                                      TILE_W, TILE_H,
                                      drawX, drawY,
                                      0);

                string_al_draw_text(builtin, COL_BLACK, drawX+TILE_W, drawY+TILE_H, ALLEGRO_ALIGN_RIGHT, std::to_string((int)(*it).second));
                s++;
            }
        }
        else
            al_draw_text(builtin,COL_BLACK,inventoryBubbleDrawX[i],inventoryBubbleDrawY[i],ALLEGRO_ALIGN_LEFT,"(No cargo).");
    }

}

void Place::DrawIndustriesBubble()
{
    al_draw_filled_rounded_rectangle(industriesBubbleDrawX - bubbleWidthPadding,
                                     industriesBubbleDrawY - bubbleHeightPadding,
                                     industriesBubbleDrawX + industriesBubbleWidth + bubbleWidthPadding,
                                     industriesBubbleDrawY + industriesBubbleHeight + bubbleHeightPadding,
                                     bubbleCornerRadius,
                                     bubbleCornerRadius,
                                     COL_DARK_WHITE);

    al_draw_rounded_rectangle(industriesBubbleDrawX - bubbleWidthPadding,
                              industriesBubbleDrawY - bubbleHeightPadding,
                              industriesBubbleDrawX + industriesBubbleWidth + bubbleWidthPadding,
                              industriesBubbleDrawY + industriesBubbleHeight + bubbleHeightPadding,
                              bubbleCornerRadius,
                              bubbleCornerRadius,
                              COL_INDIGO,
                              4);

    al_draw_text(builtin,COL_BLACK,industriesBubbleDrawX, industriesBubbleDrawY-bubbleHeightPadding-8, ALLEGRO_ALIGN_LEFT, "Local Industries:");

    if(industries.size() > 0)
    {
        for(unsigned i = 0; i < industries.size(); i++)
        {
            float drawX = industriesBubbleDrawX + industriesBubbleProgressBarOffset;
            float drawY = industriesBubbleDrawY + i*(TILE_H + industriesBubbleRowSpacing + BUILTIN_TEXT_HEIGHT);

            al_draw_filled_rectangle(drawX, drawY,
                                     drawX + industries[i]->productionProgressBarFill*industriesBubbleProgressBarWidth,
                                     drawY + TILE_H,
                                     COL_WHITE);

            if(industries[i]->jobState == JOB_STATE_INSUFFICIENT_INPUTS)
            {
                al_draw_filled_rectangle(drawX, drawY + TILE_H*0.75,
                                         drawX + industries[i]->pauseProgressBarFill*industriesBubbleProgressBarWidth,
                                         drawY + TILE_H,
                                         al_map_rgba(127,0,0,200));
            }

            if(industries[i]->jobState == JOB_STATE_INSUFFICIENT_INPUTS)
                al_draw_rectangle(drawX, drawY,
                                  drawX+industriesBubbleProgressBarWidth,
                                  drawY + TILE_H,
                                  COL_ORANGE,
                                  1);

            else
                al_draw_rectangle(drawX, drawY,
                                  drawX+industriesBubbleProgressBarWidth,
                                  drawY + TILE_H,
                                  COL_VIOLET,
                                  1);

/// To do: Animation to fade through input/ouputs in sequence or rotate through them like cards in a stacked deck
            al_draw_bitmap_region(cargoPng,
                                  (industries[i]->outputs.begin()->first)*TILE_W,0,
                                  TILE_W,TILE_H,
                                  industriesBubbleDrawX+TILE_W*1.5, drawY,
                                  0);

            string_al_draw_text(builtin, COL_BLACK,
                                industriesBubbleDrawX + TILE_W*1.5 +TILE_W,
                                drawY + TILE_H,
                                ALLEGRO_ALIGN_RIGHT,
                                std::to_string((int)industries[i]->outputs.begin()->second));


            if(industries[i]->inputs.size() > 0)
            {

                al_draw_bitmap_region(cargoPng,
                                      (industries[i]->inputs.begin()->first)*TILE_W,0,
                                      TILE_W,TILE_H,
                                      industriesBubbleDrawX, drawY,
                                      0);

                string_al_draw_text(builtin, COL_BLACK,
                                    industriesBubbleDrawX + TILE_W,
                                    drawY + TILE_H,
                                    ALLEGRO_ALIGN_RIGHT,
                                    std::to_string((int)industries[i]->inputs.begin()->second));

                al_draw_bitmap(redArrowPng,
                               industriesBubbleDrawX+TILE_W*0.75,
                               drawY,
                               0);
            }

            string_al_draw_text(builtin, COL_BLACK,
                                industriesBubbleDrawX + 3*TILE_W,
                                drawY + TILE_H/2-BUILTIN_TEXT_HEIGHT,
                                ALLEGRO_ALIGN_LEFT, industries[i]->industryName);
        }
    }
    else
        al_draw_text(builtin, COL_BLACK, industriesBubbleDrawX,industriesBubbleDrawY,ALLEGRO_ALIGN_LEFT,"(No industries here).");

}

void Place::DrawFlyingTexts()
{
    for(std::vector<FlyingText*>::iterator it = upFlyingTexts.begin(); it != upFlyingTexts.end(); ++it)
    {
        (*it)->DrawOnOverworld();
    }

    for(std::vector<FlyingText*>::iterator it = downFlyingTexts.begin(); it != downFlyingTexts.end(); ++it)
    {
        (*it)->DrawOnOverworld();
    }
}
