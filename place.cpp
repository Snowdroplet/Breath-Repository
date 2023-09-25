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


    //maintainenceSecurityFactor = 3; // Wants to have enough goods for 3 days of consumption
    //industrialSecurityFactor = 3; // Wants to have enough inputs for 3 days of industry

    //const int d/*ebug production quantity*/ = 6;
    for(std::vector<int>::const_iterator cit = placeInitialIndustries.at(placeIdentity).cbegin(); cit != placeInitialIndustries.at(placeIdentity).cend(); ++cit)
        AddIndustry(*cit);

    UpdateItemsProducedAndConsumedByIndustries();

    for(unsigned i = IT_MARKER_FIRST; i <= IT_MARKER_LAST; i++)
    {
        // The order of the following function calls is important

        UpdateMaintainenceConsumptionTimerThreshold(i);

        maintainenceConsumptionTimer.at(i) = rand() % economyBaseMaintainenceConsumptionRate.at(i);

        UpdateIndustrialConsumptionQuantityDaily(i); /// To do: Put at the end of AddIndustry in a loop that checks inputs of all industries

        UpdateSurplusAndDeficitRatios(i);
    }


    AddInitialMarketStock();
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

    LoadCaravan(newCaravan);
}

void Place::DeleteCitizenCaravan(Caravan *c)
{
    // code here
    // don't actually delete the object. The pointer still would still exist in Caravan::caravans

    //UpdateCitizensBubble();
}

void Place::GenerateCitizenCaravans()
{
    unsigned numberToGenerate = 1;

    if(population.count(EXP_COMMON) > 0)
        numberToGenerate += population.at(EXP_COMMON)/2;

    for(unsigned i = 0; i < numberToGenerate; i++)
        NewCitizenCaravan();
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
    //if(population.count(jobExpertiseType.at(whichIndustry)) > 0)
    //    baseProdPerTick += population[jobExpertiseType.at(whichIndustry)];

    //if(population.count(jobExpertiseType.at(EXP_COMMON)) > 0)
    //    baseProdPerTick += population[EXP_COMMON]*0.25;

    industries.push_back(new Industry(whichIndustry, baseProdPerTick));
}

bool Place::CheckJobInputs(Industry *whichIndustry)
{
    for(std::map<unsigned,float>::iterator jt = whichIndustry->inputs.begin(); jt != whichIndustry->inputs.end(); ++jt)
    {
        if((market.cargo.count((*jt).first) < 1)) // Is the job's input requirement present in map at all?
            return false;

        else if((market.cargo[(*jt).first] < (*jt).second)) // Is the quantity in inventory less than the job's input requirement?
            return false;
    }
    return true;
}

void Place::DeductJobInputs(Industry* whichIndustry)
{
    for(std::map<unsigned,float>::iterator it = whichIndustry->inputs.begin(); it != whichIndustry->inputs.end(); ++it)
    {
        RemoveMarketStock((*it).first, (*it).second);
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
                AddMarketStock((*jt).first, (*jt).second);
                QueueUpFlyingText((*jt).first, "+" + std::to_string((int)(*jt).second), overworldXPosition, overworldYPosition);
            }

            (*it)->SetJobStateDeductionsNecessary();
        }
    }
}


void Place::UpdateMaintainenceConsumptionTimerThreshold(unsigned whichItem)
{
    maintainenceConsumptionTimerThreshold.at(whichItem) = economyBaseMaintainenceConsumptionRate.at(whichItem);
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
                if(market.cargo.count(i) > 0) /// && maintainenceConsumptionQuantityOnTickInteger > 0) // Check if key exists in map
                {
                    if(maintainenceConsumptionQuantityOnTick.at(i) <= market.cargo.at(i))
                    {
                        RemoveMarketStock(i, maintainenceConsumptionQuantityOnTick.at(i));
                        QueueDownFlyingText(i, "-" + std::to_string((int)maintainenceConsumptionQuantityOnTick.at(i)), overworldXPosition, overworldYPosition);

#ifdef debug_output_place_progress_maintainence_consumption
                        std::cout << placeNames.at(placeIdentity) << " consumed " << (int)maintainenceConsumptionQuantity(i);
                        //if(maintainenceConsumptionDecimalOwing.at(i) > 0)
                        //std::cout << "(" << maintainenceConsumptionDecimalOwing.at(i) << " owing) ";
                        std::cout << itemNames.at(i) << " ---- ";
                        if(inventory[market.cargo.count(i) > 0)
                            std::cout << market.cargo.at(i);
                        else
                            std:: cout << "None";
                        std::cout << " remains." <<  std::endl;
#endif
                        /// increase contentment here

                    }
                    else // maintainenceComsumptionQuantityOnTick > market.at((*it).first))
                    {
                        /// consume remainder here and set decimal to zero
#ifdef debug_output_place_progress_maintainence_consumption
                        std::cout << placeNames.at(placeIdentity) <<  " has insufficient " << itemNames.at(i) << " to meet consumption! ---- Need ";
                        std::cout << << maintainenceConsumptionQuantityInteger << "; ";
                        std::cout << market.cargo.at(i) << " in stock! (Debug: con int > stock)" << std::endl;
#endif
                        /// decrease contentment here
                        /// cout contement increased by so and so.

                    }
                }
                else // market.cargo.count((*it).first) <= 0
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


/**
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
*/

void Place::UpdateIndustrialConsumptionQuantityDaily(unsigned whichItem)
{
    industrialConsumptionQuantityDaily.at(whichItem) = CalculateIndustrialConsumptionQuantityDaily(whichItem);
}

float Place::CalculateMaintainenceConsumptionQuantityOnTick(unsigned whichItem)
{
    float result = 0;

    /*
    for(std::map<int,unsigned>::iterator jt = population.begin(); jt != population.end(); ++jt)
        result += ((*jt).second) * economyRoleMaintainenceConsumptionQuantity.at(whichItem).at((*jt).first); // Not consumptionRate, mind. Quantity.
    */

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
    if(market.cargo.count(whichItem) > 0)
    {
        if(dailyMC > 0) // prevents division by zero
        {
            result += market.cargo.at(whichItem) / dailyMC;
            result -= maintainenceSecurityFactor; // For maintainence component of surplus to be positive, the ratio above must be more than maintainence security factor
        }

        /// I think this one is probably correct (but only because IC has to be 0 if whichItem is not an input in any industry. But what if whichItem becomes an input of multiple industries? Then industrialSecurityFactor would have to be multiplied by the number of involved inudstries...
        if(dailyIC > 0) // prevents division by zero
        {
            result += market.cargo.at(whichItem) / dailyIC;
            result -= industrialSecurityFactor; // For industrial component of surplus to be positive, the ratio above must be more than industrial security factor
        }


    }
    else // ! (market.cargo.count(whichItem) > 0)
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

void Place::TradeWithCaravan(Caravan *c)
{
    UnloadCaravanToMarketBuffer(c);
    LoadCaravan(c);
    DumpMarketBufferStockToMarketStock();
}

void Place::UnloadCaravanToMarketBuffer(Caravan *c)
{
    c->AddTradeRecord(placeIdentity);

    if(deficitsTopTen.size() > 0)
    {
        std::vector<int>itemsToUnload = deficitsTopTen; // Copies from surplusesTopTen. Must not access deficitsTopTen directly because its contents are updated every time cargo is transfered in or out of city inventories.
        for(std::vector<int>::iterator it = itemsToUnload.begin(); it != itemsToUnload.end(); ++it)
        {
            if(c->inventory.cargo.count(*it) > 0)
            {
                int transferQuantity = c->inventory.cargo.at(*it); // So... All of it.
                if(transferQuantity >= 1)
                {
                    c->UpdateTradeRecordQuantities(*it,transferQuantity*(-1));
                    TransferCaravanStockToMarketBufferStock(c, *it, transferQuantity);
                    QueueUpFlyingText(*it, "+" + std::to_string(transferQuantity), overworldXPosition, overworldYPosition);
                }
            }
        }
        DumpMarketBufferStockToMarketStock();
    }

    c->CheckTradeRecordsRowLimit();
    c->UpdateTradeRecordsBubble();
}

void Place::LoadCaravan(Caravan *c)
{
    /// Loads caravan with the city's (top ten) breadth of surplus goods.
    /// The quantity of each good is directly proportional to surplusRatio.

    //std::cout << "Debug: Loading surplus cargo to caravan " << c->caravanLeader->name << std::endl;

    c->AddTradeRecord(placeIdentity);

    if(surplusesTopTen.size() > 0)
    {
        float surplusSum = 0; // To tally up the total quantity of surplus goods across all items.
        std::vector<int>itemsToLoad; // Copies from surplusesTopTen. Must not access surplusesTopTen directly because its contents are updated every time cargo is transfered in or out of city inventories.

        for(std::vector<int>::iterator it = surplusesTopTen.begin(); it != surplusesTopTen.end(); ++it)
        {
            surplusSum += surplusRatio.at(*it);
            itemsToLoad.push_back(*it);
        }

        int cargoLimit = c->cargoWeightMax - c->cargoWeight;

        /// revise loop to take into account the amount of surplus city is willing to sell (less than amount that would put it at low consumption tier... but how low?)
        for(std::vector<int>::iterator it = itemsToLoad.begin(); it != itemsToLoad.end(); ++it)
        {
            if(market.cargo.count(*it) > 0) /// Check if key exists in inventory map... which it should, since there is a surplus - however, program crashes without this line, so investigate /// Perhaps the surpluses vector isn't updated promptly?
            {
                int transferQuantity = (surplusRatio.at(*it) / surplusSum ) * cargoLimit; // Proportion of caravan's cargo hold to be filled up with each item
                if(transferQuantity >= 1) // Don't bother transferring less than 1. It'll get drawn as a zero in cargo and be confusing.
                {
                    int transferLimit = market.cargo.at(*it);; //Cannot transfer more stock than is present in city market inventory
                    if(transferQuantity > transferLimit)
                        transferQuantity = transferLimit;

                    // Must record transaction before transfering items out of city market inventory or it'll record quantity as zero.
                    c->UpdateTradeRecordQuantities(*it, transferQuantity);
                    TransferMarketStockToCaravanStock(c, *it, transferQuantity);
                    QueueDownFlyingText(*it, "-" + std::to_string(transferQuantity), overworldXPosition, overworldYPosition);
                }
            }
        }
    }

    c->CheckTradeRecordsRowLimit();
    c->UpdateTradeRecordsBubble();
}

void Place::UpdateItemsProducedAndConsumedByIndustries()
{
    for(size_t i = 0; i <= IT_MARKER_LAST; i++)
    {
        itemsConsumedByIndustries[i] = false;
        itemsProducedByIndustries[i] = false;
    }

    for(std::vector<Industry*>::iterator it = industries.begin(); it != industries.end(); ++it)
    {
        for(std::map<unsigned,float>::iterator jt1 = (*it)->inputs.begin(); jt1 != (*it)->inputs.end(); ++jt1)
        {
            itemsConsumedByIndustries[(*jt1).first] = true;
            //std::cout << placeNames.at(placeIdentity) << ": consumption of " << itemNames.at((*jt1).first) << " true -" << std::endl;
        }

        for(std::map<unsigned,float>::iterator jt2 = (*it)->outputs.begin(); jt2 != (*it)->outputs.end(); ++jt2)
        {
            itemsProducedByIndustries[(*jt2).first] = true;
            //std::cout << placeNames.at(placeIdentity) << ": production of " << itemNames.at((*jt2).first) << " true -" << std::endl;
        }
    }
}

void Place::AddMarketStock(int a, float b)
{
    unsigned prev = market.cargo.size();
    market.AddStock(a,b);

    if(market.cargo.size() != prev)
        UpdateMarketBubble();

    UpdateSurplusAndDeficitRatios(a);
    UpdateSurplusesTopTen();
    UpdateDeficitsTopTen();
}
void Place::RemoveMarketStock(int a, float b)
{
    unsigned prev = market.cargo.size();
    market.RemoveStock(a,b);

    if(market.cargo.size() != prev)
        UpdateMarketBubble();

    UpdateSurplusAndDeficitRatios(a);
    UpdateSurplusesTopTen();
    UpdateDeficitsTopTen();
}
void Place::SetMarketStock(int a, float b)
{
    unsigned prev = market.cargo.size();
    market.SetStock(a,b);

    if(market.cargo.size() != prev)
        UpdateMarketBubble();

    UpdateSurplusAndDeficitRatios(a);
    UpdateSurplusesTopTen();
    UpdateDeficitsTopTen();
}


void Place::AddMarketBufferStock(int a, float b)
{
    marketBuffer.AddStock(a,b);
}

void Place::RemoveMarketBufferStock(int a, float b)
{
    market.RemoveStock(a,b);
}

void Place::SetMarketBufferStock(int a, float b)
{
    marketBuffer.SetStock(a,b);
}


// Transfer market items (directly) to caravan
void Place::TransferMarketStockToCaravanStock(Caravan *c, int a, float b)
{
    RemoveMarketStock(a,b);
    c->AddInventoryStock(a,b);
}


// Transfer individual caravan items to buffer
void Place::TransferCaravanStockToMarketBufferStock(Caravan* c, int a, float b)
{
    c->RemoveInventoryStock(a,b);
    AddMarketBufferStock(a,b);
}
// Dump entire buffer to market
void Place::DumpMarketBufferStockToMarketStock()
{
    for(std::map<int, float>::iterator it = marketBuffer.cargo.begin(); it != marketBuffer.cargo.end(); ++it)
    {
        int item = it->first;
        float quantity = it->second;
        RemoveMarketBufferStock(item,quantity);
        market.AddStock(item,quantity);
    }
}

void Place::AddInitialMarketStock()
{
    /*
    for(unsigned i = IT_MARKER_FIRST; i <= IT_MARKER_LAST; i++)
    {
        for (std::map<int, unsigned>::iterator it = population.begin(); it != population.end(); ++it)
        {
            if(population.count((*it).second) > 0)
            {
                float toAdd = economyRoleMaintainenceConsumptionQuantity.at(i).at((*it).first) * population.at((*it).second) * 2; // Arbitrary multiplier of 2 here.
                AddInventoryStock(market, i, toAdd);
            }
        }
    }
    */

    for(std::vector<Industry*>::iterator it = industries.begin(); it != industries.end(); ++it)
    {
        for(std::map<unsigned,float>::iterator jt = (*it)->inputs.begin(); jt != (*it)->inputs.end(); ++jt)
            AddMarketStock((*jt).first, (*jt).second* 10);

        for(std::map<unsigned,float>::iterator kt = (*it)->outputs.begin(); kt != (*it)->outputs.end(); ++kt)
            AddMarketStock((*kt).first, (*kt).second* 10); // The multiplier of 5 here is just arbitrary.
    }
}

void Place::UpdateAllBubbles()
{
    UpdatePopulationBubble();
    UpdateCaravanseraiBubble();

    UpdateSurplusBubble();
    UpdateDeficitBubble();

    UpdateMarketBubble();
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


void Place::UpdateCaravanseraiBubble()
{

    caravanseraiBubbleNumCols = caravanseraiBubbleBaseCols;
    caravanseraiBubbleNumRows = caravanseraiBubbleBaseRows;

    while(caravanserai.size() > caravanseraiBubbleNumCols*caravanseraiBubbleNumRows)
    {
        if(caravanseraiBubbleNumCols <= caravanseraiBubbleNumRows)
            caravanseraiBubbleNumCols++;
        else
            caravanseraiBubbleNumRows++;
    }

    caravanseraiBubbleWidth = caravanseraiBubbleNumCols*TILE_W;
    caravanseraiBubbleHeight = caravanseraiBubbleNumRows*TILE_H;
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

void Place::UpdateMarketBubble()
{
    marketBubbleNumCols = marketBubbleBaseCols;
    marketBubbleNumRows = marketBubbleBaseRows;

    while(market.cargo.size() > marketBubbleNumCols*marketBubbleNumRows)
    {
        if(marketBubbleNumCols <= marketBubbleNumRows)
            marketBubbleNumCols++;
        else
            marketBubbleNumRows++;
    }

    marketBubbleWidth = marketBubbleNumCols*TILE_W;
    marketBubbleHeight = marketBubbleNumRows*(TILE_H+marketBubbleRowSpacing);
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


void Place::DrawCaravanseraiBubble()
{
    /// To do: Adjust for sprites that are not TILE_W in size.

    al_draw_filled_rounded_rectangle(caravanseraiBubbleDrawX - bubblePadding,
                                     caravanseraiBubbleDrawY - bubblePadding,
                                     caravanseraiBubbleDrawX + caravanseraiBubbleWidth + bubblePadding,
                                     caravanseraiBubbleDrawY + caravanseraiBubbleHeight + bubblePadding,
                                     bubbleCornerRadius, bubbleCornerRadius,
                                     COL_DARK_WHITE);


    al_draw_rounded_rectangle(caravanseraiBubbleDrawX - bubblePadding,
                              caravanseraiBubbleDrawY - bubblePadding,
                              caravanseraiBubbleDrawX + caravanseraiBubbleWidth + bubblePadding,
                              caravanseraiBubbleDrawY + caravanseraiBubbleHeight + bubblePadding,
                              bubbleCornerRadius, bubbleCornerRadius,
                              COL_INDIGO, 4);

    string_al_draw_text(builtin,COL_BLACK,caravanseraiBubbleDrawX, caravanseraiBubbleDrawY-bubblePadding-BUILTIN_TEXT_HEIGHT, ALLEGRO_ALIGN_LEFT, caravanseraiBubbleLabel);

    if(caravanserai.size() > 0)
    {
        unsigned s = 0;
        for(std::vector<Caravan*>::iterator it = caravanserai.begin(); it != caravanserai.end(); ++it)
        {
            float drawX = caravanseraiBubbleDrawX + s%caravanseraiBubbleNumCols*TILE_W;
            float drawY = caravanseraiBubbleDrawY + s/caravanseraiBubbleNumCols*TILE_H;

            (*it)->DrawActivity(drawX + TILE_W/2,
                                drawY + TILE_H/2);
            s++;
        }
    }
    else
        string_al_draw_text(builtin,COL_BLACK,caravanseraiBubbleDrawX,caravanseraiBubbleDrawY,ALLEGRO_ALIGN_LEFT,caravanseraiBubbleEmptyText);
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

void Place::DrawMarketBubble()
{
        al_draw_filled_rounded_rectangle(marketBubbleDrawX - bubblePadding,
                                         marketBubbleDrawY - bubblePadding,
                                         marketBubbleDrawX + marketBubbleWidth + bubblePadding,
                                         marketBubbleDrawY + marketBubbleHeight + bubblePadding,
                                         bubbleCornerRadius, bubbleCornerRadius,
                                         COL_DARK_WHITE);


        al_draw_rounded_rectangle(marketBubbleDrawX - bubblePadding,
                                  marketBubbleDrawY - bubblePadding,
                                  marketBubbleDrawX + marketBubbleWidth + bubblePadding,
                                  marketBubbleDrawY + marketBubbleHeight + bubblePadding,
                                  bubbleCornerRadius, bubbleCornerRadius,
                                  COL_INDIGO, 4);

        string_al_draw_text(builtin,COL_BLACK,marketBubbleDrawX, marketBubbleDrawY-bubblePadding-BUILTIN_TEXT_HEIGHT, ALLEGRO_ALIGN_LEFT, marketBubbleLabel);

        if(market.cargo.size() > 0)
        {
            unsigned s = 0;
            for(std::map<int,float>::iterator it = market.cargo.begin(); it != market.cargo.end(); ++it)
            {
                float drawX = marketBubbleDrawX + s%marketBubbleNumCols*TILE_W;
                float drawY = marketBubbleDrawY + s/marketBubbleNumCols*(TILE_H+marketBubbleRowSpacing);

                if((*it).second >= 1)
                {
                    al_draw_bitmap_region(cargoPng,
                                          0+((*it).first)*TILE_W, 0,
                                          TILE_W, TILE_H,
                                          drawX, drawY,
                                          0);

                    string_al_draw_text(builtin, COL_BLACK, drawX+TILE_W, drawY+TILE_H, ALLEGRO_ALIGN_RIGHT, std::to_string((int)(*it).second));
                    s++;
                }
            }
        }
        else
            string_al_draw_text(builtin,COL_BLACK,marketBubbleDrawX,marketBubbleDrawY,ALLEGRO_ALIGN_LEFT,marketBubbleEmptyText);
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

    for(std::vector<FlyingText*>::iterator it = downFlyingTexts.begin(); it != downFlyingTexts.end(); ++it)
        (*it)->overworldYPosition -= 2*MINI_TILE_H;
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

