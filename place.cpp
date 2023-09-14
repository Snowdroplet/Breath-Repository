#include "place.h"

std::map<int, Place*> Place::places;

Place::Place(int id)
{
    placeIdentity = id;
    //std::cout << "Place created with ID " << id << std::endl;

    name = placeNames.at(placeIdentity);

    overworldXPosition = placeOverworldXYCells.at(placeIdentity)[0] *TILE_W;
    overworldYPosition = placeOverworldXYCells.at(placeIdentity)[1] *TILE_H;

    for(unsigned i = EXP_MARKER_FIRST; i <= EXP_MARKER_LAST; i++)
    {
        if(placeInitialPopulation.at(placeIdentity).at(i) > 0)
            population[i] = placeInitialPopulation.at(placeIdentity).at(i);
    }

    initialStandardOfLiving = LIVING_COMFORTABLE;

    maintainenceSecurityFactor = maintainenceConsumptionTierSecurityThreshold.at(initialStandardOfLiving); // Wants to have enough resources to live on for 3 days
    industrialSecurityFactor = 3; // Wants to have enough inputs for 3 days of industry

    //const int d/*ebug production quantity*/ = 6;
    for(std::vector<int>::const_iterator cit = placeInitialIndustries.at(placeIdentity).cbegin(); cit != placeInitialIndustries.at(placeIdentity).cend(); ++cit)
        AddIndustry(*cit);


    for(unsigned i = IT_MARKER_FIRST; i <= IT_MARKER_LAST; i++)
    {
        // The order of the following function calls is important


        maintainenceConsumptionTier.at(i) = initialStandardOfLiving;

        UpdateMaintainenceConsumptionTimerThreshold(i);

        maintainenceConsumptionTimer.at(i) = rand()% economyBaseMaintainenceConsumptionRate.at(i).at(initialStandardOfLiving);

        UpdateIndustrialConsumptionQuantityDaily(i); /// To do: Put at the end of AddIndustry in a loop that checks inputs of all industries

        UpdateSurplusAndDeficitRatios(i);

    }

    AddInitialStock();

    caravanseraiBubbleActive = false;
}

Place::~Place()
{
    //std::cout << "Place deleted." << std::endl;

    //availableCrew.clear();
    citizenCaravans.clear();
    caravanserai.clear();

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

void Place::NewCitizenCaravan()
{
    // Construct the leader of the Caravan
    Being*newCaravanLeader = new Being();
    Being::people.push_back(newCaravanLeader);

    newCaravanLeader->SetHometown(placeIdentity);
    newCaravanLeader->SetRace(std::rand()%(RACE_MARKER_LAST-RACE_MARKER_FIRST+1));
    newCaravanLeader->SetName(raceNames.at(newCaravanLeader->race) + " " + std::to_string(std::rand()%999));


// Construct Caravan
    Caravan*newCaravan = new Caravan();
    citizenCaravans.push_back(newCaravan);
    Caravan::caravans.push_back(newCaravan);

    newCaravan->SetHometown(placeIdentity);
    newCaravan->AddMember(newCaravanLeader);
    newCaravan->MoveToPlace(this);


    UpdateCitizensBubble();
}

void Place::DeleteCitizenCaravan(Caravan *c)
{
    // code here

    UpdateCitizensBubble();
}

void Place::GenerateCitizenCaravans()
{
    unsigned numberToGenerate = 1;

    if(population.count(EXP_COMMON) > 0)
        numberToGenerate += population.at(EXP_COMMON)/2;

    for(unsigned i = 0; i < numberToGenerate; i++)
        NewCitizenCaravan();
}

int Place::DetermineMostSuitableTradeDestination()
{

    /// placeholder
    int result = rand()%(PL_MARKER_LAST-PL_MARKER_FIRST +1) + PL_MARKER_FIRST;

    /// list destinations within range
    /// score each destination by their sum deficits in sellingItems + sum surpluses in buyingItems

    //std::cout << "Most suitable trade destination set to " << placeNames.at(result) << std::endl;

    return result;
}


void Place::ProgressTradeMissions()
{
    for(std::vector<Caravan*>::iterator it = citizenCaravans.begin(); it != citizenCaravans.end(); ++it)
    {
        if((*it)->atHome)
        {
            //
            if((*it)->tradeMission.missionComplete)
            {
                (*it)->tradeMission.missionActive = false;
                (*it)->tradeMission.missionComplete = false;

                UnloadTradeMission(*it);
            }

            if(! (*it)->tradeMission.missionActive /**&& c->missionCooldown <= 0*/)
            {
                //std::cout << "debug: Caravan activated" << std::endl;
                (*it)->tradeMission.missionActive = true;
                LoadGenericTradeMission(*it);
                (*it)->tradeMission.SetTradeDestination(DetermineMostSuitableTradeDestination());
            }

        }
    }
}

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


void Place::AddToCaravanserai(Caravan *c)
{
    caravanserai.push_back(c);
    if(overworldCameraCaravan == c)
        UpdateAllBubbles();
    else
        UpdateCaravanseraiBubble();
}

void Place::RemoveFromCaravanserai(Caravan *c)
{
    //std::cout << "Debug: Attempting removal from caravanserai" << std::endl;
    for(std::vector<Caravan*>::iterator it = caravanserai.begin(); it != caravanserai.end();)
    {
        if(*it == c)
            it = caravanserai.erase(it);
        else
        {
            (*it)->thresholdTimeAtPlace += removeFromCaravanseraiDelay;
            ++it;
        }
    }

    UpdateCaravanseraiBubble();
    //std::cout << "Removed" << std::endl;

}

void Place::AddIndustry(int whichIndustry)
{
    float baseProdPerTick = 1;
    if(population.count(jobExpertiseType.at(whichIndustry)) > 0)
        baseProdPerTick += population[jobExpertiseType.at(whichIndustry)];

    if(population.count(jobExpertiseType.at(EXP_COMMON)) > 0)
        baseProdPerTick += population[EXP_COMMON]*0.25;

    industries.push_back(new Industry(whichIndustry, baseProdPerTick));
}

bool Place::CheckJobInputs(Industry *whichIndustry)
{
    for(std::map<unsigned,float>::iterator jt = whichIndustry->inputs.begin(); jt != whichIndustry->inputs.end(); ++jt)
    {
        if((inventory[PLACE_INVENTORY_MARKET].cargo.count((*jt).first) < 1)) // Is the job's input requirement present in map at all?
            return false;

        else if((inventory[PLACE_INVENTORY_MARKET].cargo[(*jt).first] < (*jt).second)) // Is the quantity in inventory less than the job's input requirement?
            return false;
    }
    return true;
}

void Place::DeductJobInputs(Industry* whichIndustry)
{
    for(std::map<unsigned,float>::iterator it = whichIndustry->inputs.begin(); it != whichIndustry->inputs.end(); ++it)
    {
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
            for(std::map<unsigned,float>::iterator jt = (*it)->outputs.begin(); jt != (*it)->outputs.end(); ++jt)
            {
                AddInventoryStock(PLACE_INVENTORY_MARKET, (*jt).first, (*jt).second);
                QueueUpFlyingText((*jt).first, "+" + std::to_string((int)(*jt).second), overworldXPosition, overworldYPosition);
            }

            (*it)->SetJobStateDeductionsNecessary();
        }
    }
}

void Place::UpdateMaintainenceConsumptionTimerThreshold(unsigned whichItem)
{
    maintainenceConsumptionTimerThreshold.at(whichItem) = economyBaseMaintainenceConsumptionRate.at(whichItem).at(maintainenceConsumptionTier.at(whichItem));
    UpdateMaintainenceConsumptionQuantityOnTick(whichItem); /// To do: Put in the upcoming threshold checking function for updating consumption tier
    UpdateMaintainenceConsumptionQuantityDaily(whichItem);
}

void Place::ProgressMaintainenceConsumption()
{
    for(unsigned i = IT_MARKER_FIRST; i <= IT_MARKER_LAST; i++)
    {
        if(maintainenceConsumptionTimerThreshold.at(i) != (-1)) // Don't update timer if there is no consumption rate.
        {
            maintainenceConsumptionTimer.at(i)++;
            if(maintainenceConsumptionTimer.at(i) >= maintainenceConsumptionTimerThreshold.at(i))
            {
                if(inventory[PLACE_INVENTORY_MARKET].cargo.count(i) > 0 /*&& maintainenceConsumptionQuantityOnTickInteger > 0*/) // Check if key exists in map
                {
                    if(maintainenceConsumptionQuantityOnTick.at(i) <= inventory[PLACE_INVENTORY_MARKET].cargo.at(i))
                    {
                        RemoveInventoryStock(PLACE_INVENTORY_MARKET, i, maintainenceConsumptionQuantityOnTick.at(i));
                        QueueDownFlyingText(i, "-" + std::to_string((int)maintainenceConsumptionQuantityOnTick.at(i)), overworldXPosition, overworldYPosition);

#ifdef debug_output_place_progress_maintainence_consumption
                        std::cout << placeNames.at(placeIdentity) << " consumed " << (int)maintainenceConsumptionQuantity(i);
                        //if(maintainenceConsumptionDecimalOwing.at(i) > 0)
                        //std::cout << "(" << maintainenceConsumptionDecimalOwing.at(i) << " owing) ";
                        std::cout << itemNames.at(i) << " ---- ";
                        if(inventory[PLACE_INVENTORY_MARKET].cargo.count(i) > 0)
                            std::cout << inventory[PLACE_INVENTORY_MARKET].cargo.at(i);
                        else
                            std:: cout << "None";
                        std::cout << " remains." <<  std::endl;
#endif
                        /// increase contentment here

                    }
                    else // maintainenceComsumptionQuantityOnTick > inventory[PLACE_INVENTORY_MARKET].at((*it).first))
                    {
                        /// consume remainder here and set decimal to zero
#ifdef debug_output_place_progress_maintainence_consumption
                        std::cout << placeNames.at(placeIdentity) <<  " has insufficient " << itemNames.at(i) << " to meet consumption! ---- Need ";
                        std::cout << << maintainenceConsumptionQuantityInteger << "; ";
                        std::cout << inventory[PLACE_INVENTORY_MARKET].cargo.at(i) << " in stock! (Debug: con int > stock)" << std::endl;
#endif
                        /// decrease contentment here
                        /// cout contement increased by so and so.

                    }
                }
                else // inventory[PLACE_INVENTORY_MARKET].cargo.count((*it).first) <= 0
                {
                    /// consume remainder here and set decimal to zero
#ifdef debug_output_place_progress_maintainence_consumption
                    std::cout << placeNames.at(placeIdentity) <<  " has insufficient " << itemNames.at(i) << " to meet consumption! ---- Need ";
                    std::cout << maintainenceConsumptionQuantityInteger << "; none in stock! (Debug: Map index not present)" << std::endl;
#endif
                    /// decrease contentment here
                    /// cout contement increased by so and so.
                }

                maintainenceConsumptionTimer.at(i) = 0;
                UpdateMaintainenceConsumptionTier(i);

            }
        }
    }
}

float Place::CalculateIndustrialConsumptionQuantityDaily(unsigned whichItem)
{
    float result = 0;

    for(std::vector<Industry*>::iterator it = industries.begin(); it != industries.end(); ++it)
    {
        for(std::map<unsigned,float>::iterator jt = (*it)->inputs.begin(); jt != (*it)->inputs.end(); ++jt)
        {
            if((*jt).first == whichItem)
                result += ((*it)->productionPerTick*(float)HOURS_PER_DAY) / (*it)->productionToComplete * (*jt).second;
        }
    }

#ifdef debug_output_place_calculate_and_draw_consumption
    //if(result > 0)
    //std::cout << "Daily industrial consumption of " << itemNames.at(whichItem) << " at " << placeNames.at(placeIdentity) << ": " << result << " per day." << std::endl;
#endif

    return result;
}

void Place::UpdateMaintainenceConsumptionTier(unsigned whichItem)
{
    int currentTier = maintainenceConsumptionTier.at(whichItem);
    int previousTier = currentTier;

    // Check if city does not meet the requirements for current consumption tier (and isn't already at rock bottom).
    if(surplusRatio.at(whichItem) < maintainenceConsumptionTierSecurityThreshold.at(currentTier) && currentTier != LIVING_MARKER_FIRST)
        currentTier --;

    // Check if city meets the requirements for next consumption tier (and isn't already at the height of consumption).
    else if(currentTier != LIVING_MARKER_LAST)
    {
        if(surplusRatio.at(whichItem) >= maintainenceConsumptionTierSecurityThreshold.at(currentTier+1))
            currentTier ++;
    }

    if(currentTier != previousTier)
    {
        std::cout << "Consumption tier of " << itemNames.at(whichItem) << " at " << placeNames.at(placeIdentity) << " changed from " << previousTier << " to " << currentTier << std::endl;
        maintainenceConsumptionTier.at(whichItem) = currentTier;
        UpdateMaintainenceConsumptionTimerThreshold(whichItem);
    }
}

void Place::UpdateIndustrialConsumptionQuantityDaily(unsigned whichItem)
{
    industrialConsumptionQuantityDaily.at(whichItem) = CalculateIndustrialConsumptionQuantityDaily(whichItem);
}

float Place::CalculateMaintainenceConsumptionQuantityOnTick(unsigned whichItem)
{
    float result = 0;

    for(std::map<int,unsigned>::iterator jt = population.begin(); jt != population.end(); ++jt)
        result += ((*jt).second) * economyRoleMaintainenceConsumptionQuantity.at(whichItem).at((*jt).first); // Not consumptionRate, mind. Quantity.

#ifdef debug_output_place_calculate_and_draw_consumption
    //std::cout << "Maintainence consumption of " << itemNames.at(whichItem) << " at " << placeNames.at(placeIdentity) << ": " << result << " per tick." << std::endl;
#endif

    return result;
}

void Place::UpdateMaintainenceConsumptionQuantityOnTick(unsigned whichItem)
{
    maintainenceConsumptionQuantityOnTick.at(whichItem) = CalculateMaintainenceConsumptionQuantityOnTick(whichItem);
}

float Place::CalculateMaintainenceConsumptionQuantityDaily(unsigned whichItem)
{
    float result = 1;

    result += ((float)HOURS_PER_DAY / maintainenceConsumptionTimerThreshold.at(whichItem)) * maintainenceConsumptionQuantityOnTick.at(whichItem);

    return result;
}

void Place::UpdateMaintainenceConsumptionQuantityDaily(unsigned whichItem)
{
    maintainenceConsumptionQuantityDaily.at(whichItem) = CalculateMaintainenceConsumptionQuantityDaily(whichItem);
}

void Place::UpdateSurplusAndDeficitRatios(unsigned whichItem)
{
    float result = 0.0;
    float dailyMC = maintainenceConsumptionQuantityDaily.at(whichItem);
    float dailyIC = industrialConsumptionQuantityDaily.at(whichItem);
    if(inventory[PLACE_INVENTORY_MARKET].cargo.count(whichItem) > 0)
    {
        if(dailyMC > 0) // prevents division by zero
        {
            result += inventory[PLACE_INVENTORY_MARKET].cargo.at(whichItem) / dailyMC;
            result -= maintainenceSecurityFactor; // For maintainence component of surplus to be positive, the ratio above must be more than maintainence security factor
        }

        /// I think this one is probably correct (but only because IC has to be 0 if whichItem is not an input in any industry. But what if whichItem becomes an input of multiple industries? Then industrialSecurityFactor would have to be multiplied by the number of involved inudstries...
        if(dailyIC > 0) // prevents division by zero
        {
            result += inventory[PLACE_INVENTORY_MARKET].cargo.at(whichItem) / dailyIC;
            result -= industrialSecurityFactor; // For industrial component of surplus to be positive, the ratio above must be more than industrial security factor
        }


    }
    else // ! (inventory[PLACE_INVENTORY_MARKET].cargo.count(whichItem) > 0)
    {
        if(dailyMC > 0) // Prevents a situation where result is reduced by maintainence security on an item that nobody even cares to consume.
        {
            result += 1 / dailyMC;
            result -= maintainenceSecurityFactor;
        }

        if(dailyIC > 0)
        {
            result += 1 / dailyIC;
            result -= industrialSecurityFactor;
        }
    }

    surplusRatio.at(whichItem) = result;
    deficitRatio.at(whichItem) = (result - 1) * (-1); // Result - 1 because result is at least 1 in calculateMaintainenceQuantityDaily()
}

void Place::UpdateSurplusesTopTen()
{
    surplusesTopTen.clear();

    std::vector<int> indices(surplusRatio.size());
    for (unsigned i = 0; i <= surplusRatio.size()-1; i++)
        indices[i] = i;

    // Sort indices based on the values in surplusRatio (in descending order)
    std::stable_sort(indices.begin(), indices.end(), [&](int a, int b)
    {
        return surplusRatio[a] > surplusRatio[b];
    } );

    // Store the indices of the ten highest values (or fewer if there are fewer than ten)
    for (int i = 0; i < std::min(static_cast<int>(surplusRatio.size()-1), 10); i++)
    {
        // Don't store surpluses less than 0. Those are deficits.
        if(surplusRatio[indices[i]] >= 0)
            surplusesTopTen.push_back(indices[i]);
    }

    UpdateSurplusBubble();
}

void Place::UpdateDeficitsTopTen()
{
    deficitsTopTen.clear();

    std::vector<int> indices(deficitRatio.size());
    for(unsigned i = 0; i <= deficitRatio.size()-1; i++)
        indices[i] = i;

    // Sort the indices based on the values in deficitRatio (in descending order)
    std::stable_sort(indices.begin(), indices.end(), [&](int a, int b)
    {
        return deficitRatio[a] > deficitRatio[b];
    } );

    // Store the indices of the ten highest values (or fewer if there are fewer than ten)
    for (int i = 0; i < std::min(static_cast<int>(deficitRatio.size()-1), 10); i++)
    {
        // Don't store deficits less than 0. Those are surpluses.
        if(deficitRatio[indices[i]] > 0)
            deficitsTopTen.push_back(indices[i]);
    }

    UpdateDeficitBubble();
}

void Place::AddInventoryStock(unsigned whichInventory, int a, float b)
{
    unsigned prev = inventory[whichInventory].cargo.size();
    inventory[whichInventory].AddStock(a,b);

    if(inventory[whichInventory].cargo.size() != prev)
        UpdateInventoryBubble(whichInventory);

    UpdateSurplusAndDeficitRatios(a);
    UpdateSurplusesTopTen();
    UpdateDeficitsTopTen();
    //UpdateMaintainenceConsumptionTier(a);
}
void Place::RemoveInventoryStock(unsigned whichInventory, int a, float b)
{
    unsigned prev = inventory[whichInventory].cargo.size();
    inventory[whichInventory].RemoveStock(a,b);

    if(inventory[whichInventory].cargo.size() != prev)
        UpdateInventoryBubble(whichInventory);

    UpdateSurplusAndDeficitRatios(a);
    UpdateSurplusesTopTen();
    UpdateDeficitsTopTen();
    //UpdateMaintainenceConsumptionTier(a);

}
void Place::SetInventoryStock(unsigned whichInventory, int a, float b)
{
    unsigned prev = inventory[whichInventory].cargo.size();
    inventory[whichInventory].SetStock(a,b);

    if(inventory[whichInventory].cargo.size() != prev)
        UpdateInventoryBubble(whichInventory);

    UpdateSurplusAndDeficitRatios(a);
    UpdateSurplusesTopTen();
    UpdateDeficitsTopTen();
    //UpdateMaintainenceConsumptionTier(a);
}

void Place::TransferInventoryStock(unsigned sourceInv, unsigned destInv, int a, float b)
{
    RemoveInventoryStock(sourceInv,a,b);
    AddInventoryStock(destInv,a,b);
}

void Place::TransferInventoryStockToCaravan(unsigned sourceInv, Caravan* c, int a, float b)
{
    RemoveInventoryStock(sourceInv,a,b);
    c->AddInventoryStock(a,b);
}

void Place::TransferInventoryStockFromCaravan(unsigned destInv, Caravan *c, int a, float b)
{
    AddInventoryStock(destInv,a,b);
    c->RemoveInventoryStock(a,b);
}

void Place::AddInitialStock()
{
    for (unsigned i = IT_MARKER_FIRST; i <= IT_MARKER_LAST; i++)
    {
        for (std::map<int, unsigned>::iterator it = population.begin(); it != population.end(); ++it)
        {
            if(population.count((*it).second) > 0)
            {
                float toAdd = economyRoleMaintainenceConsumptionQuantity.at(i).at((*it).first) * population.at((*it).second) * 2; // Arbitrary 1 here.
                AddInventoryStock(PLACE_INVENTORY_MARKET, i, toAdd);
            }
        }
    }

    for(std::vector<Industry*>::iterator it = industries.begin(); it != industries.end(); ++it)
    {
        for(std::map<unsigned,float>::iterator jt = (*it)->inputs.begin(); jt != (*it)->inputs.end(); ++jt)
            AddInventoryStock(PLACE_INVENTORY_MARKET, (*jt).first, (*jt).second* 2);

        for(std::map<unsigned,float>::iterator kt = (*it)->outputs.begin(); kt != (*it)->outputs.end(); ++kt)
            AddInventoryStock(PLACE_INVENTORY_MARKET, (*kt).first, (*kt).second* 2); // The multiplier here is just arbitrary. It could be, say, 2.
    }
}

void Place::UpdateAllBubbles()
{
    UpdatePopulationBubble();
    UpdateCitizensBubble();
    UpdateCaravanseraiBubble();
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

void Place::UpdateCaravanseraiBubble()
{
    if(caravanserai.size() > 0)
    {
        caravanseraiBubbleNumCols = 1;
        caravanseraiBubbleNumRows = 1;

        while(caravanserai.size() > caravanseraiBubbleNumCols*caravanseraiBubbleNumRows)
        {
            if(caravanseraiBubbleNumCols <= caravanseraiBubbleNumRows)
                caravanseraiBubbleNumCols++;
            else
                caravanseraiBubbleNumRows++;
        }

        caravanseraiBubbleActive = true;
        caravanseraiBubbleWidth = caravanseraiBubbleNumCols*TILE_W;
        caravanseraiBubbleHeight = caravanseraiBubbleNumRows*TILE_H;
    }
    else
        caravanseraiBubbleActive = false;
}

void Place::UpdateSurplusBubble()
{
    surplusBubbleNumCols = surplusBubbleBaseCols;

    if(surplusesTopTen.size() > 0)
        surplusBubbleNumRows = surplusesTopTen.size();
    else
        surplusBubbleNumRows = 1;

    surplusBubbleWidth = surplusBubbleNumCols*TILE_W + TILE_W*1.5; // inelegantly extended by TILE_W*1.5
    surplusBubbleHeight = surplusBubbleNumRows*TILE_H;
}

void Place::UpdateDeficitBubble()
{
    deficitBubbleNumCols = deficitBubbleBaseCols;

    if(deficitsTopTen.size() > 0)
        deficitBubbleNumRows = deficitsTopTen.size();
    else
        deficitBubbleNumRows = 1;

    deficitBubbleWidth = deficitBubbleNumCols*TILE_W + TILE_W*1.5; // inelegantly extended by TILE_W*1.5
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
                              0 + placeIdentity*64, 0,
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
    for(std::map<int, unsigned>::iterator it = population.begin(); it != population.end(); ++it)
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

    string_al_draw_text(builtin,COL_BLACK,citizensBubbleDrawX, citizensBubbleDrawY-bubblePadding-8, ALLEGRO_ALIGN_LEFT, citizensBubbleLabel);

    if(citizenCaravans.size() > 0)
    {
        for(unsigned i = 0; i < citizenCaravans.size(); i++)
        {
            // DrawActivity is centered on draw coordinate -- must offset
            citizenCaravans[i]->DrawActivity(citizensBubbleDrawX + TILE_W/2,
                                             citizensBubbleDrawY + TILE_W*i  + TILE_H/2);

            string_al_draw_text(builtin, COL_BLACK,
                                citizensBubbleDrawX + TILE_W + TILE_W/4,
                                citizensBubbleDrawY + TILE_H*i,
                                ALLEGRO_ALIGN_LEFT, citizenCaravans[i]->caravanLeader->name);

            if(citizenCaravans[i]->atPlace)
                string_al_draw_text(builtin, COL_BLACK,
                                    citizensBubbleDrawX + TILE_W + TILE_W/4,
                                    citizensBubbleDrawY + TILE_H*i + BUILTIN_TEXT_HEIGHT,
                                    ALLEGRO_ALIGN_LEFT, citizenCaravans[i]->whichPlace->name);
            else if(citizenCaravans[i]->onRoad)
                string_al_draw_multiline_text(builtin, COL_BLACK,
                                              citizensBubbleDrawX + TILE_W + TILE_W/4,
                                              citizensBubbleDrawY + TILE_H*i + BUILTIN_TEXT_HEIGHT,
                                              citizensBubbleWidth - TILE_W - TILE_W/4,                   // max width of multiline text
                                              BUILTIN_TEXT_HEIGHT,
                                              ALLEGRO_ALIGN_LEFT, citizenCaravans[i]->whichRoad->name);
        }
    }
    else
        al_draw_text(builtin, COL_BLACK, citizensBubbleDrawX, citizensBubbleDrawY,ALLEGRO_ALIGN_LEFT,"(None).");
}

void Place::DrawCaravanseraiBubbleOnOverworld()
{
    if(caravanseraiBubbleActive)
    {
        /// To do: Adjust for sprites that are not TILE_W in size.

        float drawX = overworldXPosition - overworldCameraXPosition;
        float drawY = overworldYPosition - overworldCameraYPosition - OVERWORLD_SPRITE_H;

        if(drawX > OVERWORLD_MIN_DRAW_X && drawX < OVERWORLD_MAX_DRAW_X
                && drawY > OVERWORLD_MIN_DRAW_Y && drawY < OVERWORLD_MAX_DRAW_Y)
        {


            al_draw_filled_rounded_rectangle(drawX - caravanseraiBubbleWidth/2 - bubblePadding,
                                             drawY - caravanseraiBubbleHeight/2 - bubblePadding,
                                             drawX + caravanseraiBubbleWidth/2 + bubblePadding,
                                             drawY + caravanseraiBubbleHeight/2 + bubblePadding,
                                             bubbleCornerRadius,
                                             bubbleCornerRadius,
                                             COL_DARK_WHITE);


            al_draw_rounded_rectangle(drawX - caravanseraiBubbleWidth/2 - bubblePadding,
                                      drawY - caravanseraiBubbleHeight/2 - bubblePadding,
                                      drawX + caravanseraiBubbleWidth/2 + bubblePadding,
                                      drawY + caravanseraiBubbleHeight/2 + bubblePadding,
                                      bubbleCornerRadius,
                                      bubbleCornerRadius,
                                      COL_INDIGO,
                                      4);

            for(unsigned i = 0; i < caravanserai.size(); i++)
            {
                caravanserai[i]->DrawActivity(drawX - caravanseraiBubbleWidth/2 + (i%caravanseraiBubbleNumCols*TILE_W) + TILE_W/2,
                                              drawY - caravanseraiBubbleHeight/2 + (i/caravanseraiBubbleNumCols*TILE_H) + TILE_H/2);
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

    unsigned drawRow = 0;
    for(std::vector<int>::iterator it = surplusesTopTen.begin(); it != surplusesTopTen.end(); ++it)
    {

        al_draw_bitmap_region(cargoPng,
                              (*it)*TILE_W, 0,
                              TILE_W,TILE_H,
                              surplusBubbleDrawX,surplusBubbleDrawY + TILE_H*drawRow, 0);

        al_draw_bitmap_region(consumptionTierIcon,
                              maintainenceConsumptionTier.at(*it)*(MINI_TILE_W), 0,
                              MINI_TILE_W, MINI_TILE_H,
                              surplusBubbleDrawX - TILE_W/2,
                              surplusBubbleDrawY + TILE_H*drawRow, 0);

        std::stringstream roundedSurplusRatio;
        roundedSurplusRatio << std::fixed << std::setprecision(2) << surplusRatio.at(*it); // Rounded to 2 decimal places


#ifdef debug_output_place_calculate_and_draw_consumption
        string_al_draw_text(builtin,COL_GREEN,
                            surplusBubbleDrawX + TILE_W*1.125,
                            surplusBubbleDrawY + TILE_H*drawRow,
                            ALLEGRO_ALIGN_LEFT,roundedSurplusRatio.str());

        std::stringstream roundedDailyMC;
        roundedDailyMC << std::fixed << std::setprecision(2) << maintainenceConsumptionQuantityDaily.at(*it);
        string_al_draw_text(builtin,COL_GREEN,
                            surplusBubbleDrawX + TILE_W*1.125,
                            surplusBubbleDrawY + TILE_H*drawRow + BUILTIN_TEXT_HEIGHT,
                            ALLEGRO_ALIGN_LEFT, "MC " + roundedDailyMC.str());

        std::stringstream roundedDailyIC;
        roundedDailyIC << std::fixed << std::setprecision(2) << industrialConsumptionQuantityDaily.at(*it);
        string_al_draw_text(builtin,COL_GREEN,
                            surplusBubbleDrawX + TILE_W*1.125,
                            surplusBubbleDrawY + TILE_H*drawRow + BUILTIN_TEXT_HEIGHT*2,
                            ALLEGRO_ALIGN_LEFT, "IC " + roundedDailyIC.str());
#else
        string_al_draw_text(builtin,COL_GREEN,
                            surplusBubbleDrawX + TILE_W*1.125,
                            surplusBubbleDrawY + TILE_H*drawRow + TILE_H/2 - BUILTIN_TEXT_HEIGHT/2,
                            ALLEGRO_ALIGN_LEFT,roundedSurplusRatio.str());

#endif

        drawRow++;
    }

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

    unsigned drawRow = 0;
    for(std::vector<int>::iterator it = deficitsTopTen.begin(); it != deficitsTopTen.end(); ++it)
    {

        al_draw_bitmap_region(cargoPng,
                              (*it)*TILE_W, 0,
                              TILE_W,TILE_H,
                              deficitBubbleDrawX, deficitBubbleDrawY + TILE_H*drawRow, 0);

        al_draw_bitmap_region(consumptionTierIcon,
                              maintainenceConsumptionTier.at(*it)*(MINI_TILE_W), 0,
                              MINI_TILE_W, MINI_TILE_H,
                              deficitBubbleDrawX - TILE_W/2,
                              deficitBubbleDrawY + TILE_H*drawRow, 0);

        std::stringstream roundedDeficitRatio;
        roundedDeficitRatio << std::fixed << std::setprecision(2) << deficitRatio.at(*it); // Rounded to 2 decimal places


#ifdef debug_output_place_calculate_and_draw_consumption
        string_al_draw_text(builtin,COL_RED,
                            deficitBubbleDrawX + TILE_W*1.125,
                            deficitBubbleDrawY + TILE_H*drawRow,
                            ALLEGRO_ALIGN_LEFT, roundedDeficitRatio.str());

        std::stringstream roundedDailyMC;
        roundedDailyMC << std::fixed << std::setprecision(2) << maintainenceConsumptionQuantityDaily.at(*it);
        string_al_draw_text(builtin,COL_RED,
                            deficitBubbleDrawX + TILE_W*1.125,
                            deficitBubbleDrawY + TILE_H*drawRow + BUILTIN_TEXT_HEIGHT,
                            ALLEGRO_ALIGN_LEFT, "MC " + roundedDailyMC.str());

        std::stringstream roundedDailyIC;
        roundedDailyIC << std::fixed << std::setprecision(2) << industrialConsumptionQuantityDaily.at(*it);
        string_al_draw_text(builtin,COL_RED,
                            deficitBubbleDrawX + TILE_W*1.125,
                            deficitBubbleDrawY + TILE_H*drawRow + BUILTIN_TEXT_HEIGHT*2,
                            ALLEGRO_ALIGN_LEFT, "IC " + roundedDailyIC.str());
#else
        string_al_draw_text(builtin,COL_RED,
                            deficitBubbleDrawX + TILE_W*1.125,
                            deficitBubbleDrawY + TILE_H*drawRow + TILE_W/2 - BUILTIN_TEXT_HEIGHT/2,
                            ALLEGRO_ALIGN_LEFT, roundedDeficitRatio.str());

#endif



        drawRow++;

    }

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
            for(std::map<int,float>::iterator it = inventory[i].cargo.begin(); it != inventory[i].cargo.end(); ++it)
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

