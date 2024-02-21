#include "place.h"

std::map<int, Place*> Place::places;

Place::Place(int id)
{
    placeIdentity = id;

    name = placeNames.at(placeIdentity);

    sovereignty = placeSovereignties.at(placeIdentity);

    overworldXPosition = placeOverworldXYCells.at(placeIdentity)[0] *Tile::WIDTH;
    overworldYPosition = placeOverworldXYCells.at(placeIdentity)[1] *Tile::HEIGHT;

    for(unsigned i = EXP_MARKER_FIRST; i <= EXP_MARKER_LAST; i++)
    {
        if(placeInitialPopulation.at(placeIdentity).at(i) > 0)
            population[i] = placeInitialPopulation.at(placeIdentity).at(i);
    }


    for(std::vector<int>::const_iterator cit = placeInitialIndustries.at(placeIdentity).cbegin(); cit != placeInitialIndustries.at(placeIdentity).cend(); ++cit)
        AddIndustry(*cit);

    UpdateItemsProducedAndConsumedByIndustries();

    for(unsigned i = InventoryIndex::IT_MARKER_FIRST; i <= InventoryIndex::IT_MARKER_LAST; i++)
    {
        // The order of the following function calls is important

        UpdateMaintainenceConsumptionTimerThreshold(i);

        maintainenceConsumptionTimer.at(i) = rand() % economyBaseMaintainenceConsumptionRate.at(i);

        UpdateIndustrialConsumptionQuantityDaily(i); /// To do: Put at the end of AddIndustry in a loop that checks inputs of all industries

        UpdateSurplusAndDeficitRatios(i);
    }


    AddInitialMarketStock();

    AllBubblesNeedUpdate();
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
    newCaravanLeader->SetAncestry(std::rand()%(ANCESTRY_MARKER_LAST-ANCESTRY_MARKER_FIRST+1));
    newCaravanLeader->SetName(beingAncestryNames.at(newCaravanLeader->ancestry) + " " + std::to_string(std::rand()%999));


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
    if(LockOn::whichCaravan == c)
        //UpdateAllBubbles();
        AllBubblesNeedUpdate();
    else
        //UpdatePlaceCaravanseraiBubble();
        caravanseraiBubbleNeedsUpdate = true;
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
            (*it)->thresholdHoursAtPlace += removeFromCaravanseraiDelayHours;
            ++it;
        }
    }

    //UpdatePlaceCaravanseraiBubble();
    caravanseraiBubbleNeedsUpdate = true;
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
        {

            (*it)->ProgressJobPause();
        }

        if((*it)->jobState == JOB_STATE_DEDUCTIONS_NECESSARY)
        {
            if(CheckJobInputs(*it))
            {
                DeductJobInputs(*it);
                (*it)->SetJobStateNormal();
            }
            else
                (*it)->SetJobStateInsufficientInputs(/*4*/);
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
    for(unsigned i = InventoryIndex::IT_MARKER_FIRST; i <= InventoryIndex::IT_MARKER_LAST; i++)
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
                result += ((*it)->productionPerTick*(float)Calendar::HOURS_PER_DAY) / (*it)->productionToComplete * (*jt).second;
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

    result += 1;

    return result;
}

void Place::UpdateMaintainenceConsumptionQuantityOnTick(unsigned whichItem)
{
    maintainenceConsumptionQuantityOnTick.at(whichItem) = CalculateMaintainenceConsumptionQuantityOnTick(whichItem);
}

float Place::CalculateMaintainenceConsumptionQuantityDaily(unsigned whichItem)
{
    float result = 1;

    result += ((float)Calendar::HOURS_PER_DAY / maintainenceConsumptionTimerThreshold.at(whichItem)) * maintainenceConsumptionQuantityOnTick.at(whichItem);

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
    deficitRatio.at(whichItem) = (result - 1) * (-1); // (Result - 1) because result is at least 1 in calculateMaintainenceQuantityDaily()
}

void Place::UpdateSurplusesDescending()
{
    surplusesDescending.clear();

    std::vector<int> indices(surplusRatio.size());
    for (unsigned i = 0; i <= surplusRatio.size()-1; i++)
        indices[i] = i;

    // Sort indices based on the values in surplusRatio (in descending order)
    std::stable_sort(indices.begin(), indices.end(), [&](int a, int b)
    {
        return surplusRatio[a] > surplusRatio[b];
    } );

    // Store the indices of the ten highest values (or fewer if there are fewer than ten)
    for(unsigned i = 0; i < surplusRatio.size(); i++)
    {
        // Don't store surpluses less than 0. Those are deficits.
        if(surplusRatio[indices[i]] >= 0)
            surplusesDescending.push_back(indices[i]);
    }

    //UpdatePlaceSurplusBubble();
    surplusBubbleNeedsUpdate = true;
}

void Place::UpdateDeficitsDescending()
{
    deficitsDescending.clear();

    std::vector<int> indices(deficitRatio.size());
    for(unsigned i = 0; i <= deficitRatio.size()-1; i++)
        indices[i] = i;

    // Sort the indices based on the values in deficitRatio (in descending order)
    std::stable_sort(indices.begin(), indices.end(), [&](int a, int b)
    {
        return deficitRatio[a] > deficitRatio[b];
    } );

    // Store the indices of the ten highest values (or fewer if there are fewer than ten)
    for(unsigned i = 0; i < deficitRatio.size(); i++)
    {
        // Don't store deficits of 0 or less. Those are surpluses.
        if(deficitRatio[indices[i]] >= 0)
            deficitsDescending.push_back(indices[i]);
    }

    //UpdatePlaceDeficitBubble();
    deficitBubbleNeedsUpdate = true;
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

    if(deficitsDescending.size() > 0)
    {
        std::vector<int>itemsToUnload = deficitsDescending; // Copies from surplusesDescending. Must not access deficitsDescending directly because its contents are updated every time cargo is transfered in or out of city inventories.
        for(std::vector<int>::iterator it = itemsToUnload.begin(); it != itemsToUnload.end(); ++it)
        {
            if(c->inventory.cargo.count(*it) > 0)
            {
                int transferQuantity = c->inventory.cargo.at(*it); // So... All of it.
                if(transferQuantity >= 1)
                {
                    c->UpdateTradeRecordQuantities(*it,transferQuantity*(-1));
                    TransferCaravanStockToMarketBufferStock(c, *it, transferQuantity);
                    ///QueueUpFlyingText(*it, "+" + std::to_string(transferQuantity), overworldXPosition, overworldYPosition);
                }
            }
        }
    }

    // Routine intended to prevent saturated caravans from wandering endlessly between cities that don't have a deficit for any of their goods.
    // Caravans that are at least 60% encumbered must trade away half their weight in order to make room for loading. Prefer supplying the city's lower surpluses (note the reverse iteration).
    // Stop if the caravan has at least half its carrying capacity freed up.
    if(c->cargoWeight >= c->cargoWeightMax*6/10)
    {
        //std::cout << placeNames.at(placeIdentity) << " didn't need anything from heavily loaded caravan " << c->caravanLeader->name << ", but cargo was unloaded anyway to make room." << std::endl;

        std::vector<int>itemsToUnload = surplusesDescending;
        for(std::vector<int>::reverse_iterator rit = surplusesDescending.rbegin(); rit != surplusesDescending.rend(); ++rit)
        {
            if(c->inventory.cargo.count(*rit) > 0)
            {
                int transferQuantity = c->inventory.cargo.at(*rit);
                if(transferQuantity >= 1)
                {
                    c->UpdateTradeRecordQuantities(*rit,transferQuantity*(-1));
                    TransferCaravanStockToMarketBufferStock(c, *rit, transferQuantity);
                    ///QueueUpFlyingText(*rit, "+" + std::to_string(transferQuantity), overworldXPosition, overworldYPosition);
                }
            }

            if(c->cargoWeight <= c->cargoWeightMax/2)
                break;
        }
    }

    c->CheckTradeRecordsRowLimit();
    //c->UpdateCaravanTradeRecordsBubble();
    c->tradeRecordsBubbleNeedsUpdate = true;
}

void Place::LoadCaravan(Caravan *c)
{
    /// Loads caravan with the city's breadth of surplus goods.
    /// The quantity of each good is directly proportional to surplusRatio.

    //std::cout << "Debug: Loading surplus cargo to caravan " << c->caravanLeader->name << std::endl;

    c->AddTradeRecord(placeIdentity);

    if(surplusesDescending.size() > 0)
    {
        float surplusSum = 0; // To tally up the total quantity of surplus goods across all items.
        std::vector<int>itemsToLoad; // Copies from surplusesDescending. Must not access surplusesDescending directly because its contents are updated every time cargo is transfered in or out of city inventories.

        for(std::vector<int>::iterator it = surplusesDescending.begin(); it != surplusesDescending.end(); ++it)
        {
            surplusSum += surplusRatio.at(*it);
            itemsToLoad.push_back(*it);
        }

        int cargoLimit = c->cargoWeightMax - c->cargoWeight;

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
                    ///QueueDownFlyingText(*it, "-" + std::to_string(transferQuantity), overworldXPosition, overworldYPosition);
                }
            }
        }
    }

    c->CheckTradeRecordsRowLimit();
    //c->UpdateCaravanTradeRecordsBubble();
    c->tradeRecordsBubbleNeedsUpdate = true;
}

void Place::UpdateItemsProducedAndConsumedByIndustries()
{
    for(size_t i = 0; i <= InventoryIndex::IT_MARKER_LAST; i++)
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
        marketBubbleNeedsUpdate = true;
        //UpdatePlaceMarketBubble();

    UpdateSurplusAndDeficitRatios(a);
    UpdateSurplusesDescending();
    UpdateDeficitsDescending();
}
void Place::RemoveMarketStock(int a, float b)
{
    unsigned prev = market.cargo.size();
    market.RemoveStock(a,b);

    if(market.cargo.size() != prev)
        marketBubbleNeedsUpdate = true;
        //UpdatePlaceMarketBubble();

    UpdateSurplusAndDeficitRatios(a);
    UpdateSurplusesDescending();
    UpdateDeficitsDescending();
}
void Place::SetMarketStock(int a, float b)
{
    unsigned prev = market.cargo.size();
    market.SetStock(a,b);

    if(market.cargo.size() != prev)
        marketBubbleNeedsUpdate = true;
        //UpdatePlaceMarketBubble();

    UpdateSurplusAndDeficitRatios(a);
    UpdateSurplusesDescending();
    UpdateDeficitsDescending();
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
        AddMarketStock(item,quantity);
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

void Place::AllBubblesNeedUpdate()
{
    populationBubbleNeedsUpdate = true;
    caravanseraiBubbleNeedsUpdate = true;
    surplusBubbleNeedsUpdate = true;
    deficitBubbleNeedsUpdate = true;
    marketBubbleNeedsUpdate = true;
    industriesBubbleNeedsUpdate = true;
}

void Place::ProgressPlaceIndustriesBubbleProgressBars()
{
    for(std::vector<Industry*>::iterator it = industries.begin(); it != industries.end(); ++it)
        (*it)->UpdateProgressBar();
}

void Place::DrawSpriteOnOverworld()
{
    float drawX = overworldXPosition - Camera::xPosition - OVERWORLD_SPRITE_W/2;
    float drawY = overworldYPosition - Camera::yPosition - OVERWORLD_SPRITE_H/2;

    if(drawX > Camera::OVERWORLD_MIN_DRAW_X && drawX < Camera::OVERWORLD_MAX_DRAW_X
            && drawY > Camera::OVERWORLD_MIN_DRAW_Y && drawY < Camera::OVERWORLD_MAX_DRAW_Y)
    {
        float nameDrawX = overworldXPosition - Camera::xPosition;
        float nameDrawY = overworldYPosition - Camera::yPosition + OVERWORLD_SPRITE_H/2;

        al_draw_bitmap_region(Resource::overworldPlacePng,
                              0 + placeIdentity*64, 0,
                              64,64,
                              drawX,
                              drawY,
                              0);

        AllegroCustom::string_al_draw_text(Resource::builtin8, COLKEY_TEXT, nameDrawX, nameDrawY, ALLEGRO_ALIGN_CENTER, name);
    }
}

void Place::QueueUpFlyingText(int ic, std::string t, float x, float y)
{
    upFlyingTexts.push_back(new FlyingText(ic, t, x, y, true));
}

void Place::QueueDownFlyingText(int ic, std::string t, float x, float y)
{
    downFlyingTexts.push_back(new FlyingText(ic, t, x, y, false));

    //for(std::vector<FlyingText*>::iterator it = downFlyingTexts.begin(); it != downFlyingTexts.end(); ++it)
    //  (*it)->overworldYPosition += Tile::MINI_HEIGHT;
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
                        (*(rjt-1))->overworldYPosition -= Tile::MINI_HEIGHT;
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
                        (*(rjt-1))->overworldYPosition += Tile::MINI_HEIGHT;
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

