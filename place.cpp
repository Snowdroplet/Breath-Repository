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
        break;

    case PL_CHORAS:
        overworldXPosition = TILE_W*24;
        overworldYPosition = TILE_H*12;
        AddIndustry(IND_FARM_MUSHROOMS , 30);
        break;

    case PL_KETH_KETHER:
        overworldXPosition = TILE_W*12;
        overworldYPosition = TILE_H*24;
        break;

    case PL_KETH_ENTWEIR:
        overworldXPosition = TILE_W*9;
        overworldYPosition = TILE_H*17;
        break;

    case PL_VIELLEICHT:
        overworldXPosition = TILE_W*1;
        overworldYPosition = TILE_H*28;
        break;

    case PL_QUELLUDE:
        overworldXPosition = TILE_W*6;
        overworldYPosition = TILE_H*32;
        break;

    case PL_AMBLEFORTH:
        overworldXPosition = TILE_W*4;
        overworldYPosition = TILE_H*14;
        break;

    case PL_ROSKANEL:
        overworldXPosition = TILE_W*26;
        overworldYPosition = TILE_H*24;
        break;

    case PL_ROSELLA:
        overworldXPosition = TILE_W*28;
        overworldYPosition = TILE_H*30;
        break;

    case PL_OBSERVIA:
        overworldXPosition = TILE_W*11;
        overworldYPosition = TILE_H*5;
        break;

    case PL_COLDLAKE:
        overworldXPosition = TILE_W*16;
        overworldYPosition = TILE_H*10;
        break;

    case PL_UMBERDELL:
        overworldXPosition = TILE_W*17;
        overworldYPosition = TILE_H*3;
        break;

    case PL_RAMSHORN:
        overworldXPosition = TILE_W*31;
        overworldYPosition = TILE_H*9;
        break;

    case PL_HOLLYHEAD:
        overworldXPosition = TILE_W*25;
        overworldYPosition = TILE_H*5;
        break;

    case PL_JASPER:
        overworldXPosition = TILE_W*36;
        overworldYPosition = TILE_H*2;
        break;
    }

    bubbleActive = false;
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
    AdjustBubbleDimensions();
}

void Place::RemoveVisitorCaravan(Caravan *c)
{
    for(std::vector<Caravan*>::iterator it = visitors.begin(); it != visitors.end(); ++it)
    {
        if(*it == c)
        {
            visitors.erase(it);
            break;
        }

    }

    AdjustBubbleDimensions();
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
                insufficiencies[(*jt).first] += (materialsRequested[(*jt).first] - inventory.cargo[(*jt).first]);
            }
        }
        else
        {
            materialsSufficient = false;
            insufficiencies[(*jt).first] += materialsRequested[(*jt).first];
        }
    }

    if(materialsSufficient)
    {
        for(std::map<int,float>::iterator jt = materialsRequested.begin(); jt != materialsRequested.end(); ++jt)
            inventory.cargo[(*jt).first] -= (*jt).first;

        whichIndustry->jobActive = true;
        return true; // Materials sufficient
    }
    else
    {

        return false; // Materials insufficient
    }
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
                (*it)->CountdownPausedJobActivation(1);
            }
            else
            {
                if(!ActivateJob(*it)) // Materials were insufficient
                {
                    (*it)->PauseJobActivation(24); //hours, hopefully
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
                inventory.AddStock((*jt).first, (*jt).second);
            }
        }
    }
}

void Place::AdjustBubbleDimensions()
{
    if(visitors.size() > 0)
    {
        bubbleActive = true;
        bubbleWidth = TILE_W*visitors.size() + TILE_W/2;
        bubbleHeight = TILE_H *1.5;
    }
    else
        bubbleActive = false;

    //std::cout << "bubbleWidth adjusted to: " << bubbleWidth << std::endl;
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

void Place::DrawBubbleOnOverworld()
{
    if(bubbleActive)
    {
        /// To do: Adjust for sprites that are not TILE_W in size.

        float drawX = overworldXPosition - overworldCameraXPosition;
        float drawY = overworldYPosition - overworldCameraYPosition - OVERWORLD_SPRITE_H;

        if(drawX > OVERWORLD_MIN_DRAW_X && drawX < OVERWORLD_MAX_DRAW_X
                && drawY > OVERWORLD_MIN_DRAW_Y && drawY < OVERWORLD_MAX_DRAW_Y)
        {


            al_draw_filled_rounded_rectangle(drawX - bubbleWidth/2,
                                             drawY - bubbleHeight/2,
                                             drawX + bubbleWidth/2,
                                             drawY + bubbleHeight/2,
                                             bubbleCornerRadius,
                                             bubbleCornerRadius,
                                             COL_DARK_WHITE);


            al_draw_rounded_rectangle(drawX - bubbleWidth/2,
                                      drawY - bubbleHeight/2,
                                      drawX + bubbleWidth/2,
                                      drawY + bubbleHeight/2,
                                      bubbleCornerRadius,
                                      bubbleCornerRadius,
                                      COL_INDIGO,
                                      4);


            for(unsigned i = 0; i < visitors.size(); i++)
            {
                visitors[i]->DrawActivity(drawX - bubbleWidth/2 + i*TILE_W + TILE_W*3/4,
                                          drawY);
            }

        }
    }
}
