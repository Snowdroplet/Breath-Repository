#include "place.h"

std::map<int, Place*> Place::places;

Place::Place(int id)
{
    identity = id;
    selfPointer = this;
    //std::cout << "Place created with ID " << id << std::endl;

    name = placeNames.at(identity);

    /// Replace with read from external file later
    switch(identity)
    {
    case PL_ERICENNES:
        epithet = ", Capital of Verus";
        overworldXPosition = TILE_W*20;
        overworldYPosition = TILE_H*20;
        AddIndustry(IND_FARM_RICE,1);
        AddIndustry(IND_ALCHEMY_ALCOHOL, 1);
        AddIndustry(IND_ALCHEMY_CONTRACT, 1);
        break;

    case PL_CHORAS:
        overworldXPosition = TILE_W*24;
        overworldYPosition = TILE_H*12;
        AddIndustry(IND_FARM_MUSHROOMS, 1);
        AddIndustry(IND_FARM_HERBS, 1);
        AddIndustry(IND_MINE_CLAY, 1);
        AddIndustry(IND_CRAFT_POTTERY, 1);
        break;

    case PL_KETH_KETHER:
        overworldXPosition = TILE_W*12;
        overworldYPosition = TILE_H*24;
        AddIndustry(IND_MINE_LEYSTONE,1);
        AddIndustry(IND_CRAFT_CLOCKWORK,1);
        AddIndustry(IND_CRAFT_AUTOMATON,1);
        break;

    case PL_KETH_ENTWEIR:
        overworldXPosition = TILE_W*9;
        overworldYPosition = TILE_H*17;
        AddIndustry(IND_FARM_HERBS,1);
        AddIndustry(IND_FARM_MUSHROOMS,1);
        break;

    case PL_VIELLEICHT:
        overworldXPosition = TILE_W*1;
        overworldYPosition = TILE_H*28;
        AddIndustry(IND_HUNT_COLD_BREATH,1);
        AddIndustry(IND_FARM_SPICE,1);
        break;

    case PL_QUELLUDE:
        overworldXPosition = TILE_W*6;
        overworldYPosition = TILE_H*32;
        AddIndustry(IND_ALCHEMY_ALCOHOL,1);
        AddIndustry(IND_ALCHEMY_SPELLBOOK,1);
        break;

    case PL_AMBLEFORTH:
        overworldXPosition = TILE_W*4;
        overworldYPosition = TILE_H*14;
        AddIndustry(IND_HUNT_MEAT,1);
        AddIndustry(IND_FARM_RICE,1);
        break;

    case PL_ROSKANEL:
        overworldXPosition = TILE_W*26;
        overworldYPosition = TILE_H*24;
        AddIndustry(IND_HUNT_COLD_BREATH,1);
        break;

    case PL_ROSELLA:
        overworldXPosition = TILE_W*28;
        overworldYPosition = TILE_H*30;
        AddIndustry(IND_FARM_SPICE,1);
        break;

    case PL_OBSERVIA:
        overworldXPosition = TILE_W*11;
        overworldYPosition = TILE_H*5;
        AddIndustry(IND_ALCHEMY_CONTRACT,1);
        AddIndustry(IND_ALCHEMY_SPELLBOOK,1);
        break;

    case PL_COLDLAKE:
        overworldXPosition = TILE_W*16;
        overworldYPosition = TILE_H*10;
        AddIndustry(IND_MINE_SILVER,1);
        AddIndustry(IND_MINE_LEYSTONE,1);
        break;

    case PL_UMBERDELL:
        overworldXPosition = TILE_W*17;
        overworldYPosition = TILE_H*3;
        AddIndustry(IND_FARM_MUSHROOMS,1);
        AddIndustry(IND_FARM_HERBS,1);
        AddIndustry(IND_ALCHEMY_MEDICINE,1);
        break;

    case PL_RAMSHORN:
        overworldXPosition = TILE_W*31;
        overworldYPosition = TILE_H*9;
        AddIndustry(IND_HUNT_MEAT,1);
        AddIndustry(IND_HUNT_COLD_BREATH,1);
        break;

    case PL_HOLLYHEAD:
        overworldXPosition = TILE_W*25;
        overworldYPosition = TILE_H*5;
        AddIndustry(IND_CRAFT_JEWELRY,1);
        break;

    case PL_JASPER:
        overworldXPosition = TILE_W*36;
        overworldYPosition = TILE_H*2;
        AddIndustry(IND_MINE_SILVER,1);
        AddIndustry(IND_CRAFT_JEWELRY,1);
        AddIndustry(IND_ALCHEMY_ALCOHOL,1);
        break;
    }

    AddInitialStock();
    visitorBubbleActive = false;
}

Place::~Place()
{
    //std::cout << "Place deleted." << std::endl;

    for(std::vector<Being*>::iterator it = availableCrew.begin(); it != availableCrew.end();)
    {
        availableCrew.erase(it);
    }

    for(std::vector<Industry*>::iterator it = industries.begin(); it != industries.end();)
    {
        delete *it;
        industries.erase(it);
    }
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

void Place::AddIndustry(int whichIndustry, float baseProdPerTick)
{
    industries.push_back(new Industry(whichIndustry, baseProdPerTick));
}

bool Place::ActivateJob(Industry *whichIndustry)
{
    bool materialsSufficient = true;
    std::map<int, float>materialsRequested;
    for(std::map<int,float>::iterator jt = whichIndustry->inputs.begin(); jt != whichIndustry->inputs.end(); ++jt)
    {
        materialsRequested[(*jt).first] = (*jt).second;

        if(inventory.cargo.count((*jt).first) > 0)
        {
            if(inventory.cargo[(*jt).first] < materialsRequested[(*jt).first])
            {
                materialsSufficient = false;
                //insufficiencies[(*jt).first] += (materialsRequested[(*jt).first] - inventory.cargo[(*jt).first]);
            }
        }
        else
        {
            materialsSufficient = false;
            //insufficiencies[(*jt).first] += materialsRequested[(*jt).first];
        }
    }

    if(materialsSufficient)
    {
        for(std::map<int,float>::iterator jt = materialsRequested.begin(); jt != materialsRequested.end(); ++jt)
            RemoveInventoryStock((*jt).first,(*jt).second);

        whichIndustry->jobActive = true;
        whichIndustry->jobComplete = false;
        return true;
    }
    else
        return false;
}

void Place::ProgressEconomy()
{
    for(std::vector<Industry*>::iterator it = industries.begin(); it != industries.end(); ++it)
    {
        // Activate job if materials are sufficient.
        if(!(*it)->jobActive)
        {
            if((*it)->jobActivationPaused)
            {
                (*it)->ProgressPausedJobActivation(1);
            }
            else
            {
                if(!ActivateJob(*it)) // Materials were insufficient
                {
                    (*it)->PauseJobActivation(8); //hours, hopefully
                    // Adjust industrial demand for insufficient materials here.
                }
            }
        }

        if((*it)->jobActive)
            (*it)->ProgressJob();

        if((*it)->jobComplete)
        {
            for(std::map<int,float>::iterator jt = (*it)->outputs.begin(); jt != (*it)->outputs.end(); ++jt)
            {
                AddInventoryStock((*jt).first, (*jt).second);
            }
            (*it)->jobComplete = false;
        }
    }
}

void Place::AddInventoryStock(int a, float b)
{
    unsigned prev = inventory.cargo.size();
    inventory.AddStock(a,b);

    if(inventory.cargo.size() != prev)
        UpdateInventoryBubble();
}
void Place::RemoveInventoryStock(int a, float b)
{
    unsigned prev = inventory.cargo.size();
    inventory.RemoveStock(a,b);

    if(inventory.cargo.size() != prev)
        UpdateInventoryBubble();
}
void Place::SetInventoryStock(int a, float b)
{
    unsigned prev = inventory.cargo.size();
    inventory.SetStock(a,b);

    if(inventory.cargo.size() != prev)
        UpdateInventoryBubble();
}

void Place::AddInitialStock()
{
    for(std::vector<Industry*>::iterator it = industries.begin(); it != industries.end(); ++it)
    {
        for(std::map<int,float>::iterator jt = (*it)->inputs.begin(); jt != (*it)->inputs.end(); ++jt)
        {
            inventory.cargo[(*jt).first] += (*jt).second*5;
        }
        for(std::map<int,float>::iterator jt = (*it)->outputs.begin(); jt != (*it)->outputs.end(); ++jt)
        {
            inventory.cargo[(*jt).first] += (*jt).second*5;
        }

    }
}

void Place::UpdateAllBubbles()
{
    UpdateVisitorBubble();
    UpdateInventoryBubble();
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

void Place::UpdateInventoryBubble()
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

void Place::UpdateIndustriesBubble()
{
    industriesBubbleHeight = industries.size()*(TILE_H+industriesBubbleRowSpacing);
}

void Place::DrawSpriteOnOverworld()
{
    int drawX = overworldXPosition - overworldCameraXPosition - OVERWORLD_SPRITE_W/2;
    int drawY = overworldYPosition - overworldCameraYPosition - OVERWORLD_SPRITE_H/2;

    if(drawX > OVERWORLD_MIN_DRAW_X && drawX < OVERWORLD_MAX_DRAW_X
            && drawY > OVERWORLD_MIN_DRAW_Y && drawY < OVERWORLD_MAX_DRAW_Y)
    {
        int nameDrawX = overworldXPosition - overworldCameraXPosition;
        int nameDrawY = overworldYPosition - overworldCameraYPosition + OVERWORLD_SPRITE_H/2;

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

void Place::DrawInventoryBubble()
{
    al_draw_filled_rounded_rectangle(inventoryBubbleDrawX - bubbleWidthPadding,
                                     inventoryBubbleDrawY - bubbleHeightPadding,
                                     inventoryBubbleDrawX + inventoryBubbleWidth + bubbleWidthPadding,
                                     inventoryBubbleDrawY + inventoryBubbleHeight + bubbleHeightPadding,
                                     bubbleCornerRadius,
                                     bubbleCornerRadius,
                                     COL_DARK_WHITE);


    al_draw_rounded_rectangle(inventoryBubbleDrawX - bubbleWidthPadding,
                              inventoryBubbleDrawY - bubbleHeightPadding,
                              inventoryBubbleDrawX + inventoryBubbleWidth + bubbleWidthPadding,
                              inventoryBubbleDrawY + inventoryBubbleHeight + bubbleHeightPadding,
                              bubbleCornerRadius,
                              bubbleCornerRadius,
                              COL_INDIGO,
                              4);

    al_draw_text(builtin,COL_BLACK,inventoryBubbleDrawX, inventoryBubbleDrawY-bubbleHeightPadding-8, ALLEGRO_ALIGN_LEFT, "Local Market:");

    if(inventory.cargo.size() > 0)
    {
        unsigned i = 0;
        for(std::map<int,float>::iterator it = inventory.cargo.begin(); it != inventory.cargo.end(); ++it)
        {
            float drawX = inventoryBubbleDrawX + i%inventoryBubbleNumCols*TILE_W;
            float drawY = inventoryBubbleDrawY + i/inventoryBubbleNumCols*(TILE_H+inventoryBubbleRowSpacing);

            al_draw_bitmap_region(cargoPng,
                                  0+((*it).first)*TILE_W, 0,
                                  TILE_W, TILE_H,
                                  drawX, drawY,
                                  0);

            string_al_draw_text(builtin, COL_BLACK, drawX+TILE_W, drawY+TILE_H, ALLEGRO_ALIGN_RIGHT, std::to_string((int)(*it).second));
            i++;
        }
    }
    else
        al_draw_text(builtin,COL_BLACK,inventoryBubbleDrawX,inventoryBubbleDrawY,ALLEGRO_ALIGN_LEFT,"(No cargo to trade).");

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
            if(industries[i]->jobActive)
            {
                float percentage = industries[i]->productionContributed/industries[i]->productionToComplete;
                al_draw_filled_rectangle(industriesBubbleDrawX + 2.5*TILE_W,
                                         industriesBubbleDrawY + i*(TILE_H + industriesBubbleRowSpacing),
                                         industriesBubbleDrawX + 2.5*TILE_W + (industriesBubbleWidth-2.5*TILE_W)*percentage,
                                         industriesBubbleDrawY + i * (TILE_H + industriesBubbleRowSpacing) + TILE_H,
                                         COL_WHITE);
                al_draw_rectangle(industriesBubbleDrawX + 2.5*TILE_W,
                                  industriesBubbleDrawY + i*(TILE_H + industriesBubbleRowSpacing),
                                  industriesBubbleDrawX + industriesBubbleWidth,
                                  industriesBubbleDrawY + i*(TILE_H + industriesBubbleRowSpacing) + TILE_H,
                                  COL_VIOLET,
                                  1);
            }
            else // if !jobActive
            {
                float percentage = industries[i]->jobActivationPauseTicks/industries[i]->jobActivationPauseThreshold;
                al_draw_filled_rectangle(industriesBubbleDrawX + 2.5*TILE_W,
                                         industriesBubbleDrawY + i*(TILE_H + industriesBubbleRowSpacing),
                                         industriesBubbleDrawX + 2.5*TILE_W + (industriesBubbleWidth-2.5*TILE_W)*percentage,
                                         industriesBubbleDrawY + i*(TILE_H + industriesBubbleRowSpacing) + TILE_H,
                                         COL_RED);

                al_draw_rectangle(industriesBubbleDrawX + 2.5*TILE_W,
                                  industriesBubbleDrawY + i*(TILE_H + industriesBubbleRowSpacing),
                                  industriesBubbleDrawX + industriesBubbleWidth,
                                  industriesBubbleDrawY + i*(TILE_H + industriesBubbleRowSpacing) + TILE_H,
                                  COL_ORANGE,
                                  1);

            }

            al_draw_bitmap_region(cargoPng,
                                  (industries[i]->outputs.begin()->first)*TILE_W,0,
                                  TILE_W,TILE_H,
                                  industriesBubbleDrawX+TILE_W*1.5, industriesBubbleDrawY + i*(TILE_H + industriesBubbleRowSpacing),
                                  0);

            if(industries[i]->inputs.size() > 0)
            {
                al_draw_bitmap_region(cargoPng,
                                      (industries[i]->inputs.begin()->first)*TILE_W,0,
                                       TILE_W,TILE_H,
                                       industriesBubbleDrawX, industriesBubbleDrawY + i*(TILE_H + industriesBubbleRowSpacing),
                                       0);

                al_draw_bitmap(industryRedArrowPng,
                               industriesBubbleDrawX+TILE_W*0.75,
                               industriesBubbleDrawY + i*(TILE_H + industriesBubbleRowSpacing),
                               0);
            }



            string_al_draw_text(builtin, COL_BLACK, industriesBubbleDrawX + 3*TILE_W,industriesBubbleDrawY + i*(TILE_H+industriesBubbleRowSpacing) + 12, ALLEGRO_ALIGN_LEFT, industries[i]->industryName);
        }
    }
    else
        al_draw_text(builtin, COL_BLACK, industriesBubbleDrawX,industriesBubbleDrawY,ALLEGRO_ALIGN_LEFT,"(No industries here).");

}
