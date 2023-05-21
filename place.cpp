#include "place.h"

std::map<int, Place*> Place::places;

Place::Place(int id)
{
    identity = id;
    //std::cout << "Place created with ID " << id << std::endl;

    name = placeNames.at(identity);

    const int d/*ebug production quantity*/ = 6;

    /// Replace with read from external file later
    switch(identity)
    {
    case PL_ERICENNES:
        epithet = ", Capital of Verus";
        overworldXPosition = TILE_W*20;
        overworldYPosition = TILE_H*20;
        AddIndustry(IND_FARM_RICE, d);
        AddIndustry(IND_ALCHEMY_ALCOHOL, d);
        AddIndustry(IND_ALCHEMY_CONTRACT, d);
        break;


    case PL_CHORAS:
        overworldXPosition = TILE_W*24;
        overworldYPosition = TILE_H*12;
        AddIndustry(IND_FARM_MUSHROOMS, d);
        AddIndustry(IND_FARM_HERBS, d);
        AddIndustry(IND_MINE_CLAY, d);
        AddIndustry(IND_CRAFT_POTTERY, d);
        break;

    case PL_KETH_KETHER:
        overworldXPosition = TILE_W*12;
        overworldYPosition = TILE_H*24;
        AddIndustry(IND_MINE_LEYSTONE, d);
        AddIndustry(IND_CRAFT_CLOCKWORK, d);
        AddIndustry(IND_CRAFT_AUTOMATON, d);
        break;

    case PL_KETH_ENTWEIR:
        overworldXPosition = TILE_W*9;
        overworldYPosition = TILE_H*17;
        AddIndustry(IND_FARM_HERBS,d );
        AddIndustry(IND_FARM_MUSHROOMS, d);
        break;

    case PL_VIELLEICHT:
        overworldXPosition = TILE_W*1;
        overworldYPosition = TILE_H*28;
        AddIndustry(IND_HUNT_COLD_BREATH, d);
        AddIndustry(IND_FARM_SPICE, d);
        break;

    case PL_QUELLUDE:
        overworldXPosition = TILE_W*6;
        overworldYPosition = TILE_H*32;
        AddIndustry(IND_ALCHEMY_ALCOHOL, d);
        AddIndustry(IND_ALCHEMY_SPELLBOOK, d);
        break;

    case PL_AMBLEFORTH:
        overworldXPosition = TILE_W*4;
        overworldYPosition = TILE_H*14;
        AddIndustry(IND_HUNT_MEAT, d);
        AddIndustry(IND_FARM_RICE, d);
        break;

    case PL_ROSKANEL:
        overworldXPosition = TILE_W*26;
        overworldYPosition = TILE_H*24;
        AddIndustry(IND_HUNT_COLD_BREATH, d);
        break;

    case PL_ROSELLA:
        overworldXPosition = TILE_W*28;
        overworldYPosition = TILE_H*30;
        AddIndustry(IND_FARM_SPICE, d);
        break;

    case PL_OBSERVIA:
        overworldXPosition = TILE_W*11;
        overworldYPosition = TILE_H*5;
        AddIndustry(IND_ALCHEMY_CONTRACT, d);
        AddIndustry(IND_ALCHEMY_SPELLBOOK, d);
        break;

    case PL_COLDLAKE:
        overworldXPosition = TILE_W*16;
        overworldYPosition = TILE_H*10;
        AddIndustry(IND_MINE_SILVER, d);
        AddIndustry(IND_MINE_LEYSTONE, d);
        break;

    case PL_UMBERDELL:
        overworldXPosition = TILE_W*17;
        overworldYPosition = TILE_H*3;
        AddIndustry(IND_FARM_MUSHROOMS, d);
        AddIndustry(IND_FARM_HERBS, d);
        AddIndustry(IND_ALCHEMY_MEDICINE, d);
        break;

    case PL_RAMSHORN:
        overworldXPosition = TILE_W*31;
        overworldYPosition = TILE_H*9;
        AddIndustry(IND_HUNT_MEAT, d);
        AddIndustry(IND_HUNT_COLD_BREATH, d);
        break;

    case PL_HOLLYHEAD:
        overworldXPosition = TILE_W*25;
        overworldYPosition = TILE_H*5;
        AddIndustry(IND_CRAFT_JEWELRY, d);
        break;

    case PL_JASPER:
        overworldXPosition = TILE_W*36;
        overworldYPosition = TILE_H*2;
        AddIndustry(IND_MINE_SILVER, d);
        AddIndustry(IND_CRAFT_JEWELRY, d);
        AddIndustry(IND_ALCHEMY_ALCOHOL, d);
        break;
    }

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

void Place::AddIndustry(int whichIndustry, float baseProdPerTick)
{
    industries.push_back(new Industry(whichIndustry, baseProdPerTick));
}

bool Place::CheckJobInputs(Industry *whichIndustry)
{
    for(std::map<int,float>::iterator jt = whichIndustry->inputs.begin(); jt != whichIndustry->inputs.end(); ++jt)
    {
        if(!(inventory.cargo.count((*jt).first) > 0)) // Is the job's input requirement not present in inventory at all?
            return false;
        else
            if(!(inventory.cargo[(*jt).first] >= (*jt).first)) // Is the quantity in inventory not at least equal to the job's input requirement?
                return false;
    }
    return true;
}

void Place::DeductJobInputs(Industry* whichIndustry)
{
    for(std::map<int,float>::iterator it = whichIndustry->inputs.begin(); it != whichIndustry->inputs.end(); ++it)
    {
            RemoveInventoryStock((*it).first,(*it).second);
            QueueDownFlyingText((*it).first, "-" + std::to_string((int)(*it).second), overworldXPosition, overworldYPosition);
    }
}

void Place::ProgressEconomy()
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
                AddInventoryStock((*jt).first, (*jt).second);
                QueueUpFlyingText((*jt).first, "+" + std::to_string((int)(*jt).second), overworldXPosition, overworldYPosition);
            }

            (*it)->SetJobStateDeductionsNecessary();
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
            inventory.cargo[(*jt).first] += (*jt).second*2;
        }
        for(std::map<int,float>::iterator jt = (*it)->outputs.begin(); jt != (*it)->outputs.end(); ++jt)
        {
            inventory.cargo[(*jt).first] += (*jt).second*1;
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
            al_draw_filled_rectangle(industriesBubbleDrawX + industriesBubbleProgressBarOffset,
                                     industriesBubbleDrawY + i*(TILE_H + industriesBubbleRowSpacing),
                                     industriesBubbleDrawX + industriesBubbleProgressBarOffset + industries[i]->productionProgressBarFill*industriesBubbleProgressBarWidth,
                                     industriesBubbleDrawY + i * (TILE_H + industriesBubbleRowSpacing) + TILE_H,
                                     COL_WHITE);

            if(industries[i]->jobState == JOB_STATE_INSUFFICIENT_INPUTS)
            {
                al_draw_filled_rectangle(industriesBubbleDrawX + industriesBubbleProgressBarOffset,
                                         industriesBubbleDrawY + i*(TILE_H + industriesBubbleRowSpacing) + TILE_H*0.75,
                                         industriesBubbleDrawX + industriesBubbleProgressBarOffset + industries[i]->pauseProgressBarFill*industriesBubbleProgressBarWidth,
                                         industriesBubbleDrawY + i*(TILE_H + industriesBubbleRowSpacing) + TILE_H,
                                         al_map_rgba(127,0,0,200));
            }

            if(industries[i]->jobState == JOB_STATE_INSUFFICIENT_INPUTS)
                al_draw_rectangle(industriesBubbleDrawX + industriesBubbleProgressBarOffset,
                                  industriesBubbleDrawY + i*(TILE_H + industriesBubbleRowSpacing),
                                  industriesBubbleDrawX + industriesBubbleProgressBarOffset+industriesBubbleProgressBarWidth,
                                  industriesBubbleDrawY + i*(TILE_H + industriesBubbleRowSpacing) + TILE_H,
                                  COL_ORANGE,
                                  1);

            else
                al_draw_rectangle(industriesBubbleDrawX + industriesBubbleProgressBarOffset,
                                  industriesBubbleDrawY + i*(TILE_H + industriesBubbleRowSpacing),
                                  industriesBubbleDrawX + industriesBubbleProgressBarOffset+industriesBubbleProgressBarWidth,
                                  industriesBubbleDrawY + i*(TILE_H + industriesBubbleRowSpacing) + TILE_H,
                                  COL_VIOLET,
                                  1);


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

                al_draw_bitmap(redArrowPng,
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
