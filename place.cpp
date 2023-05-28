#include "place.h"

std::map<int, Place*> Place::places;

Place::Place(int id)
{
    identity = id;
    //std::cout << "Place created with ID " << id << std::endl;

    name = placeNames.at(identity);

    overworldXPosition = placeOverworldXYCells.at(identity)[0] *TILE_W;
    overworldYPosition = placeOverworldXYCells.at(identity)[1] *TILE_H;

    //population = placeInitialPopulation.at(identity);

    for(unsigned i = EXP_MARKER_FIRST; i <= EXP_MARKER_LAST; i++)
    {
        if(placeInitialPopulation.at(identity).at(i) > 0)
            population[i] = placeInitialPopulation.at(identity).at(i);
    }

    standardOfLiving = LIVING_COMFORTABLE;

    //const int d/*ebug production quantity*/ = 6;
    for(std::vector<int>::const_iterator cit = placeInitialIndustries.at(identity).cbegin(); cit != placeInitialIndustries.at(identity).cend(); ++cit)
        AddIndustry(*cit, 1 + population[jobExpertiseType.at(*cit)]);

    for(unsigned i = IT_MARKER_FIRST; i < IT_MARKER_LAST; i++)
    {
        maintainenceConsumptionTier[i] = standardOfLiving;
        consumptionTimer[i] = rand()% economyBaseMaintainenceConsumptionRate.at(i).at(standardOfLiving);
        consumptionDecimalOwing[i] = 0;
    }

    AddInitialStock();

    visitorBubbleActive = false;
}

Place::~Place()
{
    //std::cout << "Place deleted." << std::endl;

    availableCrew.clear();
    citizenCaravans.clear();
    visitorCaravans.clear();

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

void Place::AddCitizenCaravan(Being *b)
{
    citizenCaravans.push_back(b);
}

void Place::RemoveCitizenCaravan(Being *b)
{

}

void Place::AddVisitorCaravan(Caravan *c)
{
    visitorCaravans.push_back(c);
    if(overworldCameraCaravan == c)
        UpdateAllBubbles();
    else
        UpdateVisitorBubble();
}

void Place::RemoveVisitorCaravan(Caravan *c)
{
    for(std::vector<Caravan*>::iterator it = visitorCaravans.begin(); it != visitorCaravans.end();)
    {
        if(*it == c)
            it = visitorCaravans.erase(it);
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
        int consumptionTimerThreshold = economyBaseMaintainenceConsumptionRate.at((*it).first).at(standardOfLiving);

        if(consumptionTimerThreshold != (-1))
        {
            (*it).second++;
            if((*it).second >= consumptionTimerThreshold)
            {
                float consumptionQuantity = 0;

                if(consumptionDecimalOwing.at((*it).first) >= 1)
                {
                    consumptionQuantity += consumptionDecimalOwing[(*it).first];
                    consumptionDecimalOwing.at((*it).first) = 0;
                }

                for(std::map<int,int>::iterator jt = population.begin(); jt != population.end(); ++jt)
                    consumptionQuantity += ((*jt).second) * economyRoleMaintainenceConsumptionQuantity.at((*it).first).at((*jt).first); // Not consumptionRate, mind. Quantity.

                float consumptionQuantityInteger;
                consumptionDecimalOwing[(*it).first] += std::modf(consumptionQuantity,&consumptionQuantityInteger);

                if(inventory[PLACE_INVENTORY_MARKET].cargo.count((*it).first) > 0 && consumptionQuantityInteger > 0)
                {
                    if(consumptionQuantityInteger <= inventory[PLACE_INVENTORY_MARKET].cargo.at((*it).first))
                    {
                        RemoveInventoryStock(PLACE_INVENTORY_MARKET, (*it).first, consumptionQuantityInteger);
                        QueueDownFlyingText((*it).first, "-" + std::to_string((int)consumptionQuantityInteger), overworldXPosition, overworldYPosition);
                        std::cout << placeNames.at(identity) << " consumed " << (int)consumptionQuantityInteger << " " << itemNames.at((*it).first) << " ---- ";
                        if(inventory[PLACE_INVENTORY_MARKET].cargo.count((*it).first) > 0)
                            std::cout << inventory[PLACE_INVENTORY_MARKET].cargo.at((*it).first);
                        else
                            std:: cout << "None";
                        std::cout << " remains." <<  std::endl;

                        /// increase contentment here

                    }
                    else // consumptionQuantityInteger > inventory[PLACE_INVENTORY_MARKET].at((*it).first))
                    {
                        /// consume remainder here and set decimal to zero
                        std::cout << placeNames.at(identity) <<  " has insufficient " << itemNames.at((*it).first) << " to meet consumption! ---- Need " << consumptionQuantityInteger << "; "<< inventory[PLACE_INVENTORY_MARKET].cargo.at((*it).first) << " in stock! (Debug: con int > stock)" << std::endl;
                        /// decrease contentment here
                        /// cout contement increased by so and so.

                    }
                }
                else // inventory[PLACE_INVENTORY_MARKET].cargo.count((*it).first) <= 0
                {
                    /// consume remainder here and set decimal to zero
                    std::cout << placeNames.at(identity) <<  " has insufficient " << itemNames.at((*it).first) << " to meet consumption! ---- Need " << consumptionQuantityInteger << "; none in stock! (Debug: Map index not present)" << std::endl;
                    /// decrease contentment here
                    /// cout contement increased by so and so.
                }

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

    for (unsigned i = IT_MARKER_FIRST; i <= IT_MARKER_LAST; i++)
    {
        for (std::map<int, int>::iterator it = population.begin(); it != population.end(); ++it)
        {
            if(population.count((*it).second) > 0)
            {
                float toAdd = economyRoleMaintainenceConsumptionQuantity.at(i).at((*it).first) * population.at((*it).second) * 1;
                if (toAdd >= 1)
                    AddInventoryStock(PLACE_INVENTORY_MARKET, i, toAdd); // Truncates, of course.

                /// Instead of consumption * 1, should give enough consumption for 30 days' maintainence or something.
            }
        }
    }
}

void Place::UpdateAllBubbles()
{
    UpdatePopulationBubble();
    UpdateCitizensBubble();
    UpdateVisitorBubble();
    UpdateSurplusBubble();
    UpdateDeficitBubble();
    UpdateInventoryBubbles();
    UpdateIndustriesBubble();
}

void Place::UpdatePopulationBubble()
{
    populationBubbleNumCols = populationBubbleBaseCols;

    if(population.size() > 0)
    {
        while(population.size() > populationBubbleNumCols)
            populationBubbleNumCols++;
    }

    populationBubbleWidth = TILE_W*populationBubbleNumCols;
}

void Place::UpdateCitizensBubble()
{
    citizensBubbleNumRows = citizensBubbleBaseRows;

    if(citizenCaravans.size() > citizensBubbleNumRows)
        citizensBubbleNumRows = citizenCaravans.size();

    citizensBubbleHeight = citizensBubbleNumRows*TILE_W;
}

void Place::UpdateVisitorBubble()
{
    if(visitorCaravans.size() > 0)
    {
        visitorBubbleNumCols = 1;
        visitorBubbleNumRows = 1;

        while(visitorCaravans.size() > visitorBubbleNumCols*visitorBubbleNumRows)
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

void Place::UpdateSurplusBubble()
{
    surplusBubbleNumCols = surplusBubbleBaseCols;
    surplusBubbleNumRows = surplusBubbleBaseRows;

    surplusBubbleWidth = surplusBubbleNumCols*TILE_W;
    surplusBubbleHeight = surplusBubbleNumRows*TILE_H;
}

void Place::UpdateDeficitBubble()
{
    deficitBubbleNumCols = deficitBubbleBaseCols;
    deficitBubbleNumRows = deficitBubbleBaseRows;

    deficitBubbleWidth = deficitBubbleNumCols*TILE_W;
    deficitBubbleHeight = deficitBubbleNumRows*TILE_H;
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

void Place::DrawPopulationBubble()
{

    al_draw_filled_rounded_rectangle(populationBubbleDrawX - bubblePadding,
                                     populationBubbleDrawY - bubblePadding,
                                     populationBubbleDrawX + populationBubbleWidth + bubblePadding,
                                     populationBubbleDrawY + populationBubbleHeight + bubblePadding,
                                     bubbleCornerRadius, bubbleCornerRadius,
                                     COL_DARK_WHITE);

    al_draw_rounded_rectangle(populationBubbleDrawX - bubblePadding,
                              populationBubbleDrawY - bubblePadding,
                              populationBubbleDrawX + populationBubbleWidth + bubblePadding,
                              populationBubbleDrawY + populationBubbleHeight + bubblePadding,
                              bubbleCornerRadius, bubbleCornerRadius,
                              COL_INDIGO,
                              4);

    unsigned i = 0;
    for(std::map<int,int>::iterator it = population.begin(); it != population.end(); ++it)
    {
        al_draw_bitmap_region(expertiseIconPng,
                              ((*it).first)*TILE_W, 0,
                              TILE_W,TILE_H,
                              populationBubbleDrawX + i*TILE_W,
                              populationBubbleDrawY,
                              0);

        string_al_draw_text(builtin,COL_BLACK, populationBubbleDrawX + i*TILE_W + TILE_W, populationBubbleDrawY+TILE_H,ALLEGRO_ALIGN_RIGHT,std::to_string((*it).second));
        i++;
    }

    string_al_draw_text(builtin,COL_BLACK, populationBubbleDrawX, populationBubbleDrawY-bubblePadding-8, ALLEGRO_ALIGN_LEFT, populationBubbleLabel);
}

void Place::DrawCitizensBubble()
{
    al_draw_filled_rounded_rectangle(citizensBubbleDrawX - bubblePadding,
                                     citizensBubbleDrawY - bubblePadding,
                                     citizensBubbleDrawX + citizensBubbleWidth + bubblePadding,
                                     citizensBubbleDrawY + citizensBubbleHeight + bubblePadding,
                                     bubbleCornerRadius, bubbleCornerRadius,
                                     COL_DARK_WHITE);

    al_draw_rounded_rectangle(citizensBubbleDrawX - bubblePadding,
                              citizensBubbleDrawY - bubblePadding,
                              citizensBubbleDrawX + citizensBubbleWidth + bubblePadding,
                              citizensBubbleDrawY + citizensBubbleHeight + bubblePadding,
                              bubbleCornerRadius, bubbleCornerRadius,
                              COL_INDIGO,
                              4);

    al_draw_text(builtin,COL_BLACK,citizensBubbleDrawX, citizensBubbleDrawY-bubblePadding-8, ALLEGRO_ALIGN_LEFT, "Citizen Caravans:");

    if(citizenCaravans.size() > 0)
    {

    }
    else
        al_draw_text(builtin, COL_BLACK, citizensBubbleDrawX, citizensBubbleDrawY,ALLEGRO_ALIGN_LEFT,"(None).");
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


            al_draw_filled_rounded_rectangle(drawX - visitorBubbleWidth/2 - bubblePadding,
                                             drawY - visitorBubbleHeight/2 - bubblePadding,
                                             drawX + visitorBubbleWidth/2 + bubblePadding,
                                             drawY + visitorBubbleHeight/2 + bubblePadding,
                                             bubbleCornerRadius,
                                             bubbleCornerRadius,
                                             COL_DARK_WHITE);


            al_draw_rounded_rectangle(drawX - visitorBubbleWidth/2 - bubblePadding,
                                      drawY - visitorBubbleHeight/2 - bubblePadding,
                                      drawX + visitorBubbleWidth/2 + bubblePadding,
                                      drawY + visitorBubbleHeight/2 + bubblePadding,
                                      bubbleCornerRadius,
                                      bubbleCornerRadius,
                                      COL_INDIGO,
                                      4);

            for(unsigned i = 0; i < visitorCaravans.size(); i++)
            {
                visitorCaravans[i]->DrawActivity(drawX - visitorBubbleWidth/2 + (i%visitorBubbleNumCols*TILE_W) + TILE_W/2,
                                                 drawY - visitorBubbleHeight/2 + (i/visitorBubbleNumCols*TILE_H) + TILE_H/2);
            }

        }
    }
}

void Place::DrawSurplusBubble()
{
    al_draw_filled_rounded_rectangle(surplusBubbleDrawX - bubblePadding,
                                     surplusBubbleDrawY - bubblePadding,
                                     surplusBubbleDrawX + surplusBubbleWidth + bubblePadding,
                                     surplusBubbleDrawY + surplusBubbleHeight + bubblePadding,
                                     bubbleCornerRadius, bubbleCornerRadius,
                                     COL_DARK_WHITE);


    al_draw_rounded_rectangle(surplusBubbleDrawX - bubblePadding,
                              surplusBubbleDrawY - bubblePadding,
                              surplusBubbleDrawX + surplusBubbleWidth + bubblePadding,
                              surplusBubbleDrawY + surplusBubbleHeight + bubblePadding,
                              bubbleCornerRadius, bubbleCornerRadius,
                              COL_INDIGO, 4);

    string_al_draw_text(builtin, COL_BLACK, surplusBubbleDrawX, surplusBubbleDrawY-bubblePadding-BUILTIN_TEXT_HEIGHT, ALLEGRO_ALIGN_LEFT, surplusBubbleLabel);

}

void Place::DrawDeficitBubble()
{
    al_draw_filled_rounded_rectangle(deficitBubbleDrawX - bubblePadding,
                                     deficitBubbleDrawY - bubblePadding,
                                     deficitBubbleDrawX + deficitBubbleWidth + bubblePadding,
                                     deficitBubbleDrawY + deficitBubbleHeight + bubblePadding,
                                     bubbleCornerRadius, bubbleCornerRadius,
                                     COL_DARK_WHITE);


    al_draw_rounded_rectangle(deficitBubbleDrawX - bubblePadding,
                              deficitBubbleDrawY - bubblePadding,
                              deficitBubbleDrawX + deficitBubbleWidth + bubblePadding,
                              deficitBubbleDrawY + deficitBubbleHeight + bubblePadding,
                              bubbleCornerRadius, bubbleCornerRadius,
                              COL_INDIGO, 4);

    string_al_draw_text(builtin, COL_BLACK, deficitBubbleDrawX, deficitBubbleDrawY-bubblePadding-BUILTIN_TEXT_HEIGHT, ALLEGRO_ALIGN_LEFT, deficitBubbleLabel);

}

void Place::DrawInventoryBubbles()
{

    for(unsigned i = PLACE_INVENTORY_MARKER_FIRST; i < PLACE_INVENTORY_MARKER_LAST+1; i++)
    {
        al_draw_filled_rounded_rectangle(inventoryBubbleDrawX[i] - bubblePadding,
                                         inventoryBubbleDrawY[i] - bubblePadding,
                                         inventoryBubbleDrawX[i] + inventoryBubbleWidth[i] + bubblePadding,
                                         inventoryBubbleDrawY[i] + inventoryBubbleHeight[i] + bubblePadding,
                                         bubbleCornerRadius,
                                         bubbleCornerRadius,
                                         COL_DARK_WHITE);


        al_draw_rounded_rectangle(inventoryBubbleDrawX[i] - bubblePadding,
                                  inventoryBubbleDrawY[i] - bubblePadding,
                                  inventoryBubbleDrawX[i] + inventoryBubbleWidth[i] + bubblePadding,
                                  inventoryBubbleDrawY[i] + inventoryBubbleHeight[i] + bubblePadding,
                                  bubbleCornerRadius,
                                  bubbleCornerRadius,
                                  COL_INDIGO,
                                  4);

        string_al_draw_text(builtin,COL_BLACK,inventoryBubbleDrawX[i], inventoryBubbleDrawY[i]-bubblePadding-BUILTIN_TEXT_HEIGHT, ALLEGRO_ALIGN_LEFT, inventoryBubbleLabel[i]);

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
    al_draw_filled_rounded_rectangle(industriesBubbleDrawX - bubblePadding,
                                     industriesBubbleDrawY - bubblePadding,
                                     industriesBubbleDrawX + industriesBubbleWidth + bubblePadding,
                                     industriesBubbleDrawY + industriesBubbleHeight + bubblePadding,
                                     bubbleCornerRadius,
                                     bubbleCornerRadius,
                                     COL_DARK_WHITE);

    al_draw_rounded_rectangle(industriesBubbleDrawX - bubblePadding,
                              industriesBubbleDrawY - bubblePadding,
                              industriesBubbleDrawX + industriesBubbleWidth + bubblePadding,
                              industriesBubbleDrawY + industriesBubbleHeight + bubblePadding,
                              bubbleCornerRadius,
                              bubbleCornerRadius,
                              COL_INDIGO,
                              4);

    string_al_draw_text(builtin,COL_BLACK,industriesBubbleDrawX, industriesBubbleDrawY-bubblePadding-8, ALLEGRO_ALIGN_LEFT, industriesBubbleLabel);

    if(industries.size() > 0)
    {
        for(unsigned i = 0; i < industries.size(); i++)
        {
            float drawX = industriesBubbleDrawX + industriesBubbleProgressBarOffset;
            float drawY = industriesBubbleDrawY + i*(TILE_H + industriesBubbleRowSpacing + BUILTIN_TEXT_HEIGHT);

/// To do: Animation to fade through input/ouputs in sequence or rotate through them like cards in a stacked deck
// Draw icon and quantity text for job output
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

// Draw icon and quantity text for job inputs (if job has inputs)
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

                // Draw red X over inputs, if inputs are insufficient
                if(industries[i]->jobState == JOB_STATE_INSUFFICIENT_INPUTS)
                    al_draw_bitmap(redTransparentXPng,
                                   industriesBubbleDrawX, drawY,
                                   0);
            }

// Draw progress bar
            if(industries[i]->jobState == JOB_STATE_INSUFFICIENT_INPUTS)
                al_draw_filled_rectangle(drawX, drawY + TILE_H*0.75,
                                         drawX + industries[i]->pauseProgressBarFill*industriesBubbleProgressBarWidth,
                                         drawY + TILE_H,
                                         al_map_rgba(127,0,0,200));
            else
                al_draw_filled_rectangle(drawX, drawY,
                                         drawX + industries[i]->productionProgressBarFill*industriesBubbleProgressBarWidth,
                                         drawY + TILE_H,
                                         COL_WHITE);
// Draw progress bar outline
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

            string_al_draw_text(builtin, COL_BLACK,
                                industriesBubbleDrawX + 3*TILE_W,
                                drawY + TILE_H/2-BUILTIN_TEXT_HEIGHT,
                                ALLEGRO_ALIGN_LEFT, industries[i]->remainingTimeText);
        }
    }
    else
        string_al_draw_text(builtin, COL_BLACK, industriesBubbleDrawX,industriesBubbleDrawY,ALLEGRO_ALIGN_LEFT, industriesBubbleEmptyText);

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

