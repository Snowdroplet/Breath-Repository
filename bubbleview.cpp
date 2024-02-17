#include "bubbleview.h"

/// Bubble view
Caravan* BubbleView::currentCaravan;
Place* BubbleView::currentPlace;
Being* BubbleView::currentBeing;

bool BubbleView::beingStatusBubbleOpen;
bool BubbleView::encyclopediaBubbleOpen;

std::string BubbleView::caravanCrewBubbleLabel;
std::string BubbleView::caravanCrewBubbleEmptyText;
float BubbleView::caravanCrewBubbleWidth;

std::string BubbleView::caravanInventoryBubbleEmptyText;
std::string BubbleView::caravanInventoryBubbleLabel;
unsigned BubbleView::caravanInventoryBubbleNumCols;
unsigned BubbleView::caravanInventoryBubbleNumRows;
float BubbleView::caravanInventoryBubbleWidth, BubbleView::caravanInventoryBubbleHeight;

std::string BubbleView::caravanTradeRecordsBubbleLabel;
std::string BubbleView::caravanTradeRecordsBubbleEmptyText;
std::string BubbleView::caravanTradeRecordsBubbleNoTransactionText;
unsigned BubbleView::caravanTradeRecordsBubbleNumRows;
float BubbleView::caravanTradeRecordsBubbleHeight;

std::string BubbleView::caravanPathfindingBubbleLabel;
std::string BubbleView::caravanPathfindingBubbleEmptyText;
unsigned BubbleView::caravanPathfindingBubbleNumCols;
unsigned BubbleView::caravanPathfindingBubbleNumRows;
float BubbleView::caravanPathfindingBubbleWidth, BubbleView::caravanPathfindingBubbleHeight;


std::string BubbleView::placePopulationBubbleLabel;
std::string BubbleView::placePopulationBubbleEmptyText;
float BubbleView::placePopulationBubbleWidth;
unsigned BubbleView::placePopulationBubbleNumCols;


std::string BubbleView::placeCaravanseraiLabel;
std::string BubbleView::placeCaravanseraiEmptyText;
unsigned BubbleView::placeCaravanseraiNumCols;
unsigned BubbleView::placeCaravanseraiNumRows;
float BubbleView::placeCaravanseraiWidth;
float BubbleView::placeCaravanseraiHeight;

std::string BubbleView::placeSurplusBubbleLabel;
unsigned BubbleView::placeSurplusBubbleNumCols, BubbleView::placeSurplusBubbleNumRows;
float BubbleView::placeSurplusBubbleWidth, BubbleView::placeSurplusBubbleHeight; // Width extended by Tile::WIDTH*1.5 in UpdateplaceSurplusBubble()

std::string BubbleView::placeDeficitBubbleLabel;
unsigned BubbleView::placeDeficitBubbleNumCols, BubbleView::placeDeficitBubbleNumRows;
float BubbleView::placeDeficitBubbleWidth, BubbleView::placeDeficitBubbleHeight; // Width extended by Tile::WIDTH*1.5 in UpdateplaceDeficitBubble()

std::string BubbleView::placeMarketBubbleLabel;
std::string BubbleView::placeMarketBubbleEmptyText;
unsigned BubbleView::placeMarketBubbleNumCols;
unsigned BubbleView::placeMarketBubbleNumRows;
float BubbleView::placeMarketBubbleWidth;
float BubbleView::placeMarketBubbleHeight;

std::string BubbleView::placeIndustriesBubbleLabel;
std::string BubbleView::placeIndustriesBubbleEmptyText;
float BubbleView::placeIndustriesBubbleHeight;


/// Being status bubble
void BubbleView::OpenBeingStatusBubble(Being *b)
{
    beingStatusBubbleOpen = true;

    currentBeing = b;
}

void BubbleView::CloseBeingStatusBubble()
{
    beingStatusBubbleOpen = false;
    currentBeing = nullptr;
}

void BubbleView::DrawBeingStatusBubble(Being *b)
{
    al_draw_filled_rounded_rectangle(beingStatusBubbleDrawX - bubblePadding,
                                     beingStatusBubbleDrawY - bubblePadding,
                                     beingStatusBubbleDrawX + beingStatusBubbleWidth + bubblePadding,
                                     beingStatusBubbleDrawY + beingStatusBubbleHeight + bubblePadding,
                                     bubbleCornerRadius,
                                     bubbleCornerRadius,
                                     COLKEY_UI_BUBBLE_BODY);

    al_draw_rounded_rectangle(beingStatusBubbleDrawX - bubblePadding,
                              beingStatusBubbleDrawY - bubblePadding,
                              beingStatusBubbleDrawX + beingStatusBubbleWidth + bubblePadding,
                              beingStatusBubbleDrawY + beingStatusBubbleHeight + bubblePadding,
                              bubbleCornerRadius,
                              bubbleCornerRadius,
                              COLKEY_UI_BUBBLE_FRAME, 4);

// Biography
    string_al_draw_text(Resource::builtin8, COLKEY_TEXT, beingStatusBubbleDrawX,
                        beingStatusBubbleDrawY+beingStatusBubbleBiographyPartitionHeight,
                        ALLEGRO_ALIGN_LEFT, "Name: " + b->name);

    string_al_draw_text(Resource::builtin8, COLKEY_TEXT, beingStatusBubbleDrawX,
                        beingStatusBubbleDrawY+beingStatusBubbleBiographyPartitionHeight + Resource::TEXT_HEIGHT_12,
                        ALLEGRO_ALIGN_LEFT, "Home: " + placeNames.at(b->hometown));

// Stats: Vitality
    al_draw_filled_rectangle(beingStatusBubbleDrawX,
                             beingStatusBubbleDrawY + beingStatusBubbleStatsPartitionHeight,
                             beingStatusBubbleDrawX + beingStatusBubbleWidth,
                             beingStatusBubbleDrawY + beingStatusBubbleStatsPartitionHeight + Tile::HEIGHT,
                             COLKEY_UI_BUBBLE_BEING_STATUS_VITALITY_BODY);

    al_draw_rectangle(beingStatusBubbleDrawX,
                      beingStatusBubbleDrawY + beingStatusBubbleStatsPartitionHeight,
                      beingStatusBubbleDrawX + beingStatusBubbleWidth,
                      beingStatusBubbleDrawY + beingStatusBubbleStatsPartitionHeight + Tile::HEIGHT,
                      COLKEY_UI_BUBBLE_BEING_STATUS_VITALITY_FRAME, 2);

    al_draw_text(Resource::builtin8,COLKEY_TEXT,beingStatusBubbleDrawX + beingStatusBubbleWidth/2,
                 beingStatusBubbleDrawY + beingStatusBubbleStatsPartitionHeight + Tile::HEIGHT/2 - Resource::TEXT_HEIGHT_8/2,
                 ALLEGRO_ALIGN_CENTER, "Vitality");
// Stats: Happiness
    al_draw_filled_rectangle(beingStatusBubbleDrawX,
                             beingStatusBubbleDrawY + beingStatusBubbleStatsPartitionHeight + Tile::HEIGHT,
                             beingStatusBubbleDrawX + beingStatusBubbleWidth,
                             beingStatusBubbleDrawY + beingStatusBubbleStatsPartitionHeight + Tile::HEIGHT + Tile::HEIGHT,
                             COLKEY_UI_BUBBLE_BEING_STATUS_HAPPINESS_BODY);

    al_draw_rectangle(beingStatusBubbleDrawX,
                      beingStatusBubbleDrawY + beingStatusBubbleStatsPartitionHeight + Tile::HEIGHT,
                      beingStatusBubbleDrawX + beingStatusBubbleWidth,
                      beingStatusBubbleDrawY + beingStatusBubbleStatsPartitionHeight + Tile::HEIGHT + Tile::HEIGHT,
                      COLKEY_UI_BUBBLE_BEING_STATUS_HAPPINESS_FRAME, 2);

    al_draw_text(Resource::builtin8,COLKEY_TEXT,beingStatusBubbleDrawX + beingStatusBubbleWidth/2,
                 beingStatusBubbleDrawY + beingStatusBubbleStatsPartitionHeight + Tile::HEIGHT + Tile::HEIGHT/2 - Resource::TEXT_HEIGHT_8/2,
                 ALLEGRO_ALIGN_CENTER, "Happiness");
// Stats: Purpose
    al_draw_filled_rectangle(beingStatusBubbleDrawX,
                             beingStatusBubbleDrawY + beingStatusBubbleStatsPartitionHeight + Tile::HEIGHT*2,
                             beingStatusBubbleDrawX + beingStatusBubbleWidth,
                             beingStatusBubbleDrawY + beingStatusBubbleStatsPartitionHeight + Tile::HEIGHT*2 + Tile::HEIGHT,
                             COLKEY_UI_BUBBLE_BEING_STATUS_PURPOSE_BODY);

    al_draw_rectangle(beingStatusBubbleDrawX,
                      beingStatusBubbleDrawY + beingStatusBubbleStatsPartitionHeight + Tile::HEIGHT*2,
                      beingStatusBubbleDrawX + beingStatusBubbleWidth,
                      beingStatusBubbleDrawY + beingStatusBubbleStatsPartitionHeight + Tile::HEIGHT*2 + Tile::HEIGHT,
                      COLKEY_UI_BUBBLE_BEING_STATUS_PURPOSE_FRAME, 2);

    al_draw_text(Resource::builtin8,COLKEY_TEXT,beingStatusBubbleDrawX + beingStatusBubbleWidth/2,
                 beingStatusBubbleDrawY + beingStatusBubbleStatsPartitionHeight + Tile::HEIGHT*2 + Tile::HEIGHT/2 - Resource::TEXT_HEIGHT_8/2,
                 ALLEGRO_ALIGN_CENTER, "Purpose");
}

/// Caravan Bubbles
void BubbleView::UpdateCaravanCrewBubble(Caravan *c)
{
    caravanCrewBubbleWidth = c->members.size()*Tile::WIDTH;

    c->crewBubbleNeedsUpdate = false;
}

void BubbleView::UpdateCaravanInventoryBubble(Caravan *c)
{
    caravanInventoryBubbleNumCols = caravanInventoryBubbleBaseCols;
    caravanInventoryBubbleNumRows = caravanInventoryBubbleBaseRows;

    while(c->inventory.cargo.size() > caravanInventoryBubbleNumCols*caravanInventoryBubbleNumRows)
    {
        if(caravanInventoryBubbleNumCols <= caravanInventoryBubbleNumRows)
            caravanInventoryBubbleNumCols++;
        else
            caravanInventoryBubbleNumRows++;
    }

    caravanInventoryBubbleWidth = caravanInventoryBubbleNumCols*Tile::WIDTH;
    caravanInventoryBubbleHeight = caravanInventoryBubbleNumRows*(Tile::HEIGHT+caravanInventoryBubbleRowSpacing);

    c->inventoryBubbleNeedsUpdate = false;
}

void BubbleView::UpdateCaravanTradeRecordsBubble(Caravan *c)
{
    caravanTradeRecordsBubbleNumRows = caravanTradeRecordsBubbleBaseRows;

    unsigned rowCount = 0;
    for(std::vector<TradeRecord*>::iterator it = c->tradeRecords.begin(); it != c->tradeRecords.end(); ++it)
        rowCount += (*it)->numRows;

    if(rowCount > caravanTradeRecordsBubbleBaseRows)
        caravanTradeRecordsBubbleNumRows = rowCount;

    caravanTradeRecordsBubbleHeight = caravanTradeRecordsBubbleNumRows*(Tile::HEIGHT+caravanTradeRecordsBubbleRowSpacing);

    c->tradeRecordsBubbleNeedsUpdate = false;
}

void BubbleView::UpdateCaravanPathfindingBubble(Caravan *c)
{
    caravanPathfindingBubbleNumCols = caravanPathfindingBubbleBaseCols;
    caravanPathfindingBubbleNumRows = caravanPathfindingBubbleBaseRows;

    if(c->worldGraph.path.size() > caravanPathfindingBubbleNumCols)
        caravanPathfindingBubbleNumCols = c->worldGraph.path.size();

    caravanPathfindingBubbleWidth = caravanPathfindingBubbleNumCols*(2*Tile::WIDTH+caravanPathfindingBubbleColSpacing) - caravanPathfindingBubbleColSpacing;
    caravanPathfindingBubbleHeight = caravanPathfindingBubbleNumRows*(2*Tile::HEIGHT+caravanPathfindingBubbleRowSpacing);

    c->pathfindingBubbleNeedsUpdate = false;
}

void BubbleView::UpdateAllCaravanBubbles(Caravan *c)
{
    UpdateCaravanCrewBubble(c);
    //updatecaravantravelviewbubble (c) here
    UpdateCaravanInventoryBubble(c);
    UpdateCaravanTradeRecordsBubble(c);
    UpdateCaravanPathfindingBubble(c);
}

void BubbleView::DrawCaravanCrewBubble(Caravan *c)
{
    al_draw_filled_rounded_rectangle(caravanCrewBubbleDrawX - bubblePadding,
                                     caravanCrewBubbleDrawY - bubblePadding,
                                     caravanCrewBubbleDrawX + caravanCrewBubbleWidth + bubblePadding,
                                     caravanCrewBubbleDrawY + caravanCrewBubbleHeight + bubblePadding,
                                     bubbleCornerRadius,
                                     bubbleCornerRadius,
                                     COLKEY_UI_BUBBLE_BODY);


    al_draw_rounded_rectangle(caravanCrewBubbleDrawX - bubblePadding,
                              caravanCrewBubbleDrawY - bubblePadding,
                              caravanCrewBubbleDrawX + caravanCrewBubbleWidth + bubblePadding,
                              caravanCrewBubbleDrawY + caravanCrewBubbleHeight + bubblePadding,
                              bubbleCornerRadius,
                              bubbleCornerRadius,
                              COLKEY_UI_BUBBLE_FRAME, 4);

    string_al_draw_text(Resource::builtin8,COLKEY_TEXT,caravanCrewBubbleDrawX, caravanCrewBubbleDrawY-bubblePadding-Resource::TEXT_HEIGHT_8, ALLEGRO_ALIGN_LEFT, caravanCrewBubbleLabel);

    if(c->members.size() > 0)
    {
        int s = 0;
        for(std::vector<Being*>::iterator it = c->members.begin(); it != c->members.end(); ++it)
        {
            float drawX = caravanCrewBubbleDrawX + s*Tile::WIDTH;
            (*it)->DrawActivity(drawX + Tile::WIDTH/2,
                                caravanCrewBubbleDrawY + Tile::HEIGHT/2);
        }
    }
    else
        string_al_draw_text(Resource::builtin8,COLKEY_TEXT,caravanCrewBubbleDrawX, caravanCrewBubbleDrawY-bubblePadding-Resource::TEXT_HEIGHT_8, ALLEGRO_ALIGN_LEFT, caravanCrewBubbleEmptyText);
}


/*
void Caravan::DrawCaravanTravelViewBubble()
{
    al_draw_filled_rounded_rectangle(caravanTravelViewBubbleDrawX - bubblePadding,
                                     caravanTravelViewBubbleDrawY - bubblePadding,
                                     caravanTravelViewBubbleDrawX + caravanTravelViewBubbleWidth + bubblePadding,
                                     caravanTravelViewBubbleDrawY + caravanTravelViewBubbleHeight + bubblePadding,
                                     bubbleCornerRadius, bubbleCornerRadius,
                                     COLKEY_UI_BUBBLE_BODY);


    al_draw_rounded_rectangle(caravanTravelViewBubbleDrawX - bubblePadding,
                                     caravanTravelViewBubbleDrawY - bubblePadding,
                                     caravanTravelViewBubbleDrawX + caravanTravelViewBubbleWidth + bubblePadding,
                                     caravanTravelViewBubbleDrawY + caravanTravelViewBubbleHeight + bubblePadding,
                                     bubbleCornerRadius, bubbleCornerRadius,
                                     COLKEY_UI_BUBBLE_FRAME, 4);
}
*/

void BubbleView::DrawCaravanInventoryBubble(Caravan *c)
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
                              COLKEY_UI_BUBBLE_FRAME, 4);

    string_al_draw_text(Resource::builtin8,COLKEY_TEXT,caravanInventoryBubbleDrawX, caravanInventoryBubbleDrawY-bubblePadding-Resource::TEXT_HEIGHT_8, ALLEGRO_ALIGN_LEFT, caravanInventoryBubbleLabel);

    if(c->inventory.cargo.size() > 0)
    {
        unsigned i = 0;
        for(std::map<int,float>::iterator it = c->inventory.cargo.begin(); it != c->inventory.cargo.end(); ++it)
        {
            float drawX = caravanInventoryBubbleDrawX + i%caravanInventoryBubbleNumCols*Tile::WIDTH;
            float drawY = caravanInventoryBubbleDrawY + i/caravanInventoryBubbleNumCols*(Tile::HEIGHT + caravanInventoryBubbleRowSpacing);

            al_draw_bitmap_region(cargoPng,
                                  ((*it).first)*Tile::WIDTH, 0,
                                  Tile::WIDTH, Tile::HEIGHT,
                                  drawX, drawY,
                                  0);

            string_al_draw_text(Resource::builtin8, COLKEY_TEXT, drawX+Tile::WIDTH, drawY+Tile::HEIGHT, ALLEGRO_ALIGN_RIGHT, std::to_string((int)(*it).second));
            i++;
        }
    }
    else
        string_al_draw_text(Resource::builtin8,COLKEY_TEXT,caravanInventoryBubbleDrawX,caravanInventoryBubbleDrawY,ALLEGRO_ALIGN_LEFT,caravanInventoryBubbleEmptyText);

    string_al_draw_text(Resource::builtin8,COLKEY_TEXT,caravanInventoryBubbleDrawX,
                        caravanInventoryBubbleDrawY+caravanInventoryBubbleHeight + Resource::TEXT_HEIGHT_8,
                        ALLEGRO_ALIGN_LEFT,
                        "Weight: " + std::to_string((int)(c->cargoWeight)) + " / " + std::to_string((int)(c->cargoWeightMax)) );

}

void BubbleView::DrawCaravanTradeRecordsBubble(Caravan *c)
{
    al_draw_filled_rounded_rectangle(caravanTradeRecordsBubbleDrawX - bubblePadding,
                                     caravanTradeRecordsBubbleDrawY - bubblePadding,
                                     caravanTradeRecordsBubbleDrawX + caravanTradeRecordsBubbleWidth + bubblePadding,
                                     caravanTradeRecordsBubbleDrawY + (caravanTradeRecordsBubbleHeight) + bubblePadding,
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


    string_al_draw_text(Resource::builtin8, COLKEY_TEXT, caravanTradeRecordsBubbleDrawX, caravanTradeRecordsBubbleDrawY-bubblePadding-Resource::TEXT_HEIGHT_8, ALLEGRO_ALIGN_LEFT, caravanTradeRecordsBubbleLabel);

    if(c->tradeRecords.size() > 0)
    {
        unsigned col = 0;
        unsigned row = 0;

        for(std::vector<TradeRecord*>::reverse_iterator rit = c->tradeRecords.rbegin(); rit != c->tradeRecords.rend(); ++rit)
        {
            string_al_draw_text(Resource::builtin8, COLKEY_TEXT,
                                caravanTradeRecordsBubbleDrawX + caravanTradeRecordsBubblePlaceNameWidth,
                                caravanTradeRecordsBubbleDrawY + row*(Tile::HEIGHT + caravanTradeRecordsBubbleRowSpacing),
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

                    float iconDrawX = caravanTradeRecordsBubbleDrawX + caravanTradeRecordsBubblePlaceNameWidth + col*(Tile::WIDTH);
                    float iconDrawY = caravanTradeRecordsBubbleDrawY + row*(Tile::HEIGHT + caravanTradeRecordsBubbleRowSpacing);

                    if((*jt).second < 0)
                        al_draw_filled_rectangle(iconDrawX, iconDrawY,
                                                 iconDrawX+Tile::WIDTH, iconDrawY+Tile::HEIGHT+caravanTradeRecordsBubbleRowSpacing,
                                                 COLKEY_UI_TRADERECORD_NEGATIVE);
                    else
                        al_draw_filled_rectangle(iconDrawX, iconDrawY,
                                                 iconDrawX+Tile::WIDTH, iconDrawY+Tile::HEIGHT+caravanTradeRecordsBubbleRowSpacing,
                                                 COLKEY_UI_TRADERECORD_POSITIVE);


                    al_draw_bitmap_region(cargoPng,
                                          ((*jt).first)*Tile::WIDTH, 0,
                                          Tile::WIDTH, Tile::HEIGHT,
                                          iconDrawX, iconDrawY,
                                          0);

                    string_al_draw_text(Resource::builtin8, COLKEY_TEXT, iconDrawX+Tile::WIDTH, iconDrawY+Tile::HEIGHT, ALLEGRO_ALIGN_RIGHT, std::to_string((*jt).second));

                    col++;
                }

            }
            else if((*rit)->tradeQuantities.size() == 0) // tradeQuantities vector empty
            {
                string_al_draw_text(Resource::builtin8, COLKEY_TEXT,
                                    caravanTradeRecordsBubbleDrawX + caravanTradeRecordsBubblePlaceNameWidth + col*(Tile::WIDTH),
                                    caravanTradeRecordsBubbleDrawY + row*(Tile::HEIGHT + caravanTradeRecordsBubbleRowSpacing) + Tile::HEIGHT/2 - Resource::TEXT_HEIGHT_8/2,
                                    ALLEGRO_ALIGN_LEFT,
                                    caravanTradeRecordsBubbleNoTransactionText);
            }

            col = 0;
            row++;
        }
    }
    else
        string_al_draw_text(Resource::builtin8,COLKEY_TEXT,caravanTradeRecordsBubbleDrawX, caravanTradeRecordsBubbleDrawY, ALLEGRO_ALIGN_LEFT, caravanTradeRecordsBubbleEmptyText);
}

void BubbleView::DrawCaravanPathfindingBubble(Caravan *c)
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

    if(! c->worldGraph.path.empty())
    {

        for(unsigned i = 0; i < c->worldGraph.path.size(); i++)
        {
            float drawX = caravanPathfindingBubbleDrawX + i*(2*Tile::HEIGHT+caravanPathfindingBubbleColSpacing);
            float drawY = caravanPathfindingBubbleDrawY;
            al_draw_bitmap_region(Resource::overworldPlacePng,
                                  c->worldGraph.path[i]*2*Tile::WIDTH, 0,
                                  2*Tile::WIDTH, 2*Tile::HEIGHT,
                                  drawX, drawY,
                                  0);

            string_al_draw_text(Resource::builtin8, COLKEY_TEXT,
                                drawX + Tile::WIDTH, drawY + 2*Tile::HEIGHT,
                                ALLEGRO_ALIGN_CENTER,
                                placeNames.at(c->worldGraph.path[i]));

            if(i < c->worldGraph.path.size()-1)
            {
                al_draw_bitmap(redArrowPng,
                               drawX+2*Tile::WIDTH,
                               drawY+Tile::HEIGHT/2,
                               0);
            }
        }
    }
    else
    {
        string_al_draw_text(Resource::builtin8, COLKEY_TEXT,
                            caravanPathfindingBubbleDrawX+caravanPathfindingBubbleWidth/2,
                            caravanPathfindingBubbleDrawY+caravanPathfindingBubbleWidth/2 - Resource::TEXT_HEIGHT_8,
                            ALLEGRO_ALIGN_CENTER, caravanPathfindingBubbleEmptyText);
    }
    string_al_draw_text(Resource::builtin8,COLKEY_TEXT,
                        caravanPathfindingBubbleDrawX,
                        caravanPathfindingBubbleDrawY-bubblePadding-Resource::TEXT_HEIGHT_8,
                        ALLEGRO_ALIGN_LEFT, caravanPathfindingBubbleLabel);
}

/// Place bubbles

void BubbleView::UpdatePlacePopulationBubble(Place *p)
{

    placePopulationBubbleNumCols = placePopulationBubbleBaseCols;

    if(p->population.size() > 0)
    {
        while(p->population.size() > placePopulationBubbleNumCols)
            placePopulationBubbleNumCols++;
    }

    placePopulationBubbleWidth = Tile::WIDTH*placePopulationBubbleNumCols;

    p->populationBubbleNeedsUpdate = false;

}


void BubbleView::UpdatePlaceCaravanseraiBubble(Place *p)
{

    placeCaravanseraiNumCols = placeCaravanseraiBaseCols;
    placeCaravanseraiNumRows = placeCaravanseraiBaseRows;

    while(p->caravanserai.size() > placeCaravanseraiNumCols*placeCaravanseraiNumRows)
    {
        if(placeCaravanseraiNumCols <= placeCaravanseraiNumRows)
            placeCaravanseraiNumCols++;
        else
            placeCaravanseraiNumRows++;
    }

    placeCaravanseraiWidth = placeCaravanseraiNumCols*Tile::WIDTH;
    placeCaravanseraiHeight = placeCaravanseraiNumRows*Tile::HEIGHT;

    p->caravanseraiBubbleNeedsUpdate = false;
}



void BubbleView::UpdatePlaceSurplusBubble(Place *p)
{

    placeSurplusBubbleNumCols = placeSurplusBubbleBaseCols;

    if(p->surplusesDescending.size() > 0)
    {
        placeSurplusBubbleNumRows = p->surplusesDescending.size();
        if(placeSurplusBubbleNumRows > placeSurplusBubbleMaxRows)
            placeSurplusBubbleNumRows = placeSurplusBubbleMaxRows;
    }
    else
        placeSurplusBubbleNumRows = placeSurplusBubbleBaseRows;

    placeSurplusBubbleWidth = placeSurplusBubbleNumCols*Tile::WIDTH + Tile::WIDTH*1.5; // inelegantly extended by Tile::WIDTH*1.5
    placeSurplusBubbleHeight = placeSurplusBubbleNumRows*Tile::HEIGHT;

    p->surplusBubbleNeedsUpdate = false;

}

void BubbleView::UpdatePlaceDeficitBubble(Place *p)
{

    placeDeficitBubbleNumCols = placeDeficitBubbleBaseCols;

    if(p->deficitsDescending.size() > 0)
    {
        placeDeficitBubbleNumRows = p->deficitsDescending.size();
        if(placeDeficitBubbleNumRows > placeDeficitBubbleMaxRows)
            placeDeficitBubbleNumRows = placeDeficitBubbleMaxRows;
    }
    else
        placeDeficitBubbleNumRows = placeDeficitBubbleMaxRows;

    placeDeficitBubbleWidth = placeDeficitBubbleNumCols*Tile::WIDTH + Tile::WIDTH*1.5; // inelegantly extended by Tile::WIDTH*1.5
    placeDeficitBubbleHeight = placeDeficitBubbleNumRows*Tile::HEIGHT;

    p->deficitBubbleNeedsUpdate = false;

}

void BubbleView::UpdatePlaceMarketBubble(Place *p)
{

    placeMarketBubbleNumCols = placeMarketBubbleBaseCols;
    placeMarketBubbleNumRows = placeMarketBubbleBaseRows;

    while(p->market.cargo.size() > placeMarketBubbleNumCols*placeMarketBubbleNumRows)
    {
        if(placeMarketBubbleNumCols <= placeMarketBubbleNumRows)
            placeMarketBubbleNumCols++;
        else
            placeMarketBubbleNumRows++;
    }

    placeMarketBubbleWidth = placeMarketBubbleNumCols*Tile::WIDTH;
    placeMarketBubbleHeight = placeMarketBubbleNumRows*(Tile::HEIGHT+placeMarketBubbleRowSpacing);

    p->marketBubbleNeedsUpdate = false;

}

void BubbleView::UpdatePlaceIndustriesBubble(Place *p)
{
    placeIndustriesBubbleHeight = p->industries.size()*(Tile::HEIGHT+placeIndustriesBubbleRowSpacing + Resource::TEXT_HEIGHT_8);

    p->industriesBubbleNeedsUpdate = false;
}

void BubbleView::DrawPlacePopulationBubble(Place *p)
{

    al_draw_filled_rounded_rectangle(placePopulationBubbleDrawX - bubblePadding,
                                     placePopulationBubbleDrawY - bubblePadding,
                                     placePopulationBubbleDrawX + placePopulationBubbleWidth + bubblePadding,
                                     placePopulationBubbleDrawY + placePopulationBubbleHeight + bubblePadding,
                                     bubbleCornerRadius, bubbleCornerRadius,
                                     COLKEY_UI_BUBBLE_BODY);

    al_draw_rounded_rectangle(placePopulationBubbleDrawX - bubblePadding,
                              placePopulationBubbleDrawY - bubblePadding,
                              placePopulationBubbleDrawX + placePopulationBubbleWidth + bubblePadding,
                              placePopulationBubbleDrawY + placePopulationBubbleHeight + bubblePadding,
                              bubbleCornerRadius, bubbleCornerRadius,
                              COLKEY_UI_BUBBLE_FRAME,
                              4);

    unsigned i = 0;
    for(std::map<int, unsigned>::iterator it = p->population.begin(); it != p->population.end(); ++it)
    {
        al_draw_bitmap_region(expertiseIconPng,
                              ((*it).first)*Tile::WIDTH, 0,
                              Tile::WIDTH,Tile::HEIGHT,
                              placePopulationBubbleDrawX + i*Tile::WIDTH,
                              placePopulationBubbleDrawY,
                              0);

        string_al_draw_text(Resource::builtin8,COLKEY_TEXT, placePopulationBubbleDrawX + i*Tile::WIDTH + Tile::WIDTH, placePopulationBubbleDrawY+Tile::HEIGHT,ALLEGRO_ALIGN_RIGHT,std::to_string((*it).second));
        i++;
    }

    string_al_draw_text(Resource::builtin8,COLKEY_TEXT, placePopulationBubbleDrawX, placePopulationBubbleDrawY-bubblePadding-8, ALLEGRO_ALIGN_LEFT, placePopulationBubbleLabel);
}


void BubbleView::DrawPlaceCaravanseraiBubble(Place *p)
{
    /// To do: Adjust for sprites that are not Tile::WIDTH in size.

    al_draw_filled_rounded_rectangle(placeCaravanseraiDrawX - bubblePadding,
                                     placeCaravanseraiDrawY - bubblePadding,
                                     placeCaravanseraiDrawX + placeCaravanseraiWidth + bubblePadding,
                                     placeCaravanseraiDrawY + placeCaravanseraiHeight + bubblePadding,
                                     bubbleCornerRadius, bubbleCornerRadius,
                                     COLKEY_UI_BUBBLE_BODY);


    al_draw_rounded_rectangle(placeCaravanseraiDrawX - bubblePadding,
                              placeCaravanseraiDrawY - bubblePadding,
                              placeCaravanseraiDrawX + placeCaravanseraiWidth + bubblePadding,
                              placeCaravanseraiDrawY + placeCaravanseraiHeight + bubblePadding,
                              bubbleCornerRadius, bubbleCornerRadius,
                              COLKEY_UI_BUBBLE_FRAME, 4);

    string_al_draw_text(Resource::builtin8,COLKEY_TEXT,placeCaravanseraiDrawX, placeCaravanseraiDrawY-bubblePadding-Resource::TEXT_HEIGHT_8, ALLEGRO_ALIGN_LEFT, placeCaravanseraiLabel);

    if(p->caravanserai.size() > 0)
    {
        unsigned s = 0;
        for(std::vector<Caravan*>::iterator it = p->caravanserai.begin(); it != p->caravanserai.end(); ++it)
        {
            float drawX = placeCaravanseraiDrawX + s%placeCaravanseraiNumCols*Tile::WIDTH;
            float drawY = placeCaravanseraiDrawY + s/placeCaravanseraiNumCols*Tile::HEIGHT;

            (*it)->DrawActivity(drawX + Tile::WIDTH/2,
                                drawY + Tile::HEIGHT/2);
            s++;
        }
    }
    else
        string_al_draw_text(Resource::builtin8,COLKEY_TEXT,placeCaravanseraiDrawX,placeCaravanseraiDrawY,ALLEGRO_ALIGN_LEFT,placeCaravanseraiEmptyText);
}



void BubbleView::DrawPlaceSurplusBubble(Place *p)
{
    al_draw_filled_rounded_rectangle(placeSurplusBubbleDrawX - bubblePadding,
                                     placeSurplusBubbleDrawY - bubblePadding,
                                     placeSurplusBubbleDrawX + placeSurplusBubbleWidth + bubblePadding,
                                     placeSurplusBubbleDrawY + placeSurplusBubbleHeight + bubblePadding,
                                     bubbleCornerRadius, bubbleCornerRadius,
                                     COLKEY_UI_BUBBLE_BODY);


    al_draw_rounded_rectangle(placeSurplusBubbleDrawX - bubblePadding,
                              placeSurplusBubbleDrawY - bubblePadding,
                              placeSurplusBubbleDrawX + placeSurplusBubbleWidth + bubblePadding,
                              placeSurplusBubbleDrawY + placeSurplusBubbleHeight + bubblePadding,
                              bubbleCornerRadius, bubbleCornerRadius,
                              COLKEY_UI_BUBBLE_FRAME, 4);

    unsigned drawRow = 0;
    for(std::vector<int>::iterator it = p->surplusesDescending.begin(); it != p->surplusesDescending.end(); ++it)
    {
        if(drawRow >= placeSurplusBubbleMaxRows)
            break;

        al_draw_bitmap_region(cargoPng,
                              (*it)*Tile::WIDTH, 0,
                              Tile::WIDTH,Tile::HEIGHT,
                              placeSurplusBubbleDrawX,placeSurplusBubbleDrawY + Tile::HEIGHT*drawRow, 0);


        std::stringstream roundedSurplusRatio;
        roundedSurplusRatio << std::fixed << std::setprecision(2) << p->surplusRatio.at(*it); // Rounded to 2 decimal places


#ifdef debug_output_place_calculate_and_draw_consumption
        string_al_draw_text(Resource::builtin8,COLKEY_UI_BUBBLE_TEXT_SURPLUS,
                            placeSurplusBubbleDrawX + Tile::WIDTH*1.125,
                            placeSurplusBubbleDrawY + Tile::HEIGHT*drawRow,
                            ALLEGRO_ALIGN_LEFT,roundedSurplusRatio.str());

        std::stringstream roundedDailyMC;
        roundedDailyMC << std::fixed << std::setprecision(2) << p->maintainenceConsumptionQuantityDaily.at(*it);
        string_al_draw_text(Resource::builtin8,COLKEY_UI_BUBBLE_TEXT_SURPLUS,
                            placeSurplusBubbleDrawX + Tile::WIDTH*1.125,
                            placeSurplusBubbleDrawY + Tile::HEIGHT*drawRow + Resource::TEXT_HEIGHT_8,
                            ALLEGRO_ALIGN_LEFT, "MC " + roundedDailyMC.str());

        std::stringstream roundedDailyIC;
        roundedDailyIC << std::fixed << std::setprecision(2) << p->industrialConsumptionQuantityDaily.at(*it);
        string_al_draw_text(Resource::builtin8,COLKEY_UI_BUBBLE_TEXT_SURPLUS,
                            placeSurplusBubbleDrawX + Tile::WIDTH*1.125,
                            placeSurplusBubbleDrawY + Tile::HEIGHT*drawRow + Resource::TEXT_HEIGHT_8*2,
                            ALLEGRO_ALIGN_LEFT, "IC " + roundedDailyIC.str());
#else
        string_al_draw_text(Resource::builtin8,COLKEY_UI_BUBBLE_TEXT_SURPLUS,
                            placeSurplusBubbleDrawX + Tile::WIDTH*1.125,
                            placeSurplusBubbleDrawY + Tile::HEIGHT*drawRow + Tile::HEIGHT/2 - Resource::TEXT_HEIGHT_8/2,
                            ALLEGRO_ALIGN_LEFT,roundedSurplusRatio.str());

#endif

        drawRow++;
    }

    string_al_draw_text(Resource::builtin8, COLKEY_TEXT, placeSurplusBubbleDrawX, placeSurplusBubbleDrawY-bubblePadding-Resource::TEXT_HEIGHT_8, ALLEGRO_ALIGN_LEFT, placeSurplusBubbleLabel);

}

void BubbleView::DrawPlaceDeficitBubble(Place *p)
{
    al_draw_filled_rounded_rectangle(placeDeficitBubbleDrawX - bubblePadding,
                                     placeDeficitBubbleDrawY - bubblePadding,
                                     placeDeficitBubbleDrawX + placeDeficitBubbleWidth + bubblePadding,
                                     placeDeficitBubbleDrawY + placeDeficitBubbleHeight + bubblePadding,
                                     bubbleCornerRadius, bubbleCornerRadius,
                                     COLKEY_UI_BUBBLE_BODY);

    al_draw_rounded_rectangle(placeDeficitBubbleDrawX - bubblePadding,
                              placeDeficitBubbleDrawY - bubblePadding,
                              placeDeficitBubbleDrawX + placeDeficitBubbleWidth + bubblePadding,
                              placeDeficitBubbleDrawY + placeDeficitBubbleHeight + bubblePadding,
                              bubbleCornerRadius, bubbleCornerRadius,
                              COLKEY_UI_BUBBLE_FRAME, 4);

    unsigned drawRow = 0;
    for(std::vector<int>::iterator it = p->deficitsDescending.begin(); it != p->deficitsDescending.end(); ++it)
    {
        if(drawRow >= placeDeficitBubbleMaxRows)
            break;

        al_draw_bitmap_region(cargoPng,
                              (*it)*Tile::WIDTH, 0,
                              Tile::WIDTH,Tile::HEIGHT,
                              placeDeficitBubbleDrawX, placeDeficitBubbleDrawY + Tile::HEIGHT*drawRow, 0);


        std::stringstream roundedDeficitRatio;
        roundedDeficitRatio << std::fixed << std::setprecision(2) << p->deficitRatio.at(*it); // Rounded to 2 decimal places


#ifdef debug_output_place_calculate_and_draw_consumption
        string_al_draw_text(Resource::builtin8,COLKEY_UI_BUBBLE_TEXT_DEFICIT,
                            placeDeficitBubbleDrawX + Tile::WIDTH*1.125,
                            placeDeficitBubbleDrawY + Tile::HEIGHT*drawRow,
                            ALLEGRO_ALIGN_LEFT, roundedDeficitRatio.str());

        std::stringstream roundedDailyMC;
        roundedDailyMC << std::fixed << std::setprecision(2) << p->maintainenceConsumptionQuantityDaily.at(*it);
        string_al_draw_text(Resource::builtin8,COLKEY_UI_BUBBLE_TEXT_DEFICIT,
                            placeDeficitBubbleDrawX + Tile::WIDTH*1.125,
                            placeDeficitBubbleDrawY + Tile::HEIGHT*drawRow + Resource::TEXT_HEIGHT_8,
                            ALLEGRO_ALIGN_LEFT, "MC " + roundedDailyMC.str());

        std::stringstream roundedDailyIC;
        roundedDailyIC << std::fixed << std::setprecision(2) << p->industrialConsumptionQuantityDaily.at(*it);
        string_al_draw_text(Resource::builtin8,COLKEY_UI_BUBBLE_TEXT_DEFICIT,
                            placeDeficitBubbleDrawX + Tile::WIDTH*1.125,
                            placeDeficitBubbleDrawY + Tile::HEIGHT*drawRow + Resource::TEXT_HEIGHT_8*2,
                            ALLEGRO_ALIGN_LEFT, "IC " + roundedDailyIC.str());
#else
        string_al_draw_text(Resource::builtin8,COLKEY_UI_BUBBLE_TEXT_DEFICIT,
                            placeDeficitBubbleDrawX + Tile::WIDTH*1.125,
                            placeDeficitBubbleDrawY + Tile::HEIGHT*drawRow + Tile::WIDTH/2 - Resource::TEXT_HEIGHT_8/2,
                            ALLEGRO_ALIGN_LEFT, roundedDeficitRatio.str());

#endif



        drawRow++;

    }

    string_al_draw_text(Resource::builtin8, COLKEY_TEXT, placeDeficitBubbleDrawX, placeDeficitBubbleDrawY-bubblePadding-Resource::TEXT_HEIGHT_8, ALLEGRO_ALIGN_LEFT, placeDeficitBubbleLabel);

}

void BubbleView::DrawPlaceMarketBubble(Place *p)
{
    al_draw_filled_rounded_rectangle(placeMarketBubbleDrawX - bubblePadding,
                                     placeMarketBubbleDrawY - bubblePadding,
                                     placeMarketBubbleDrawX + placeMarketBubbleWidth + bubblePadding,
                                     placeMarketBubbleDrawY + placeMarketBubbleHeight + bubblePadding,
                                     bubbleCornerRadius, bubbleCornerRadius,
                                     COLKEY_UI_BUBBLE_BODY);


    al_draw_rounded_rectangle(placeMarketBubbleDrawX - bubblePadding,
                              placeMarketBubbleDrawY - bubblePadding,
                              placeMarketBubbleDrawX + placeMarketBubbleWidth + bubblePadding,
                              placeMarketBubbleDrawY + placeMarketBubbleHeight + bubblePadding,
                              bubbleCornerRadius, bubbleCornerRadius,
                              COLKEY_UI_BUBBLE_FRAME, 4);

    string_al_draw_text(Resource::builtin8,COLKEY_TEXT,placeMarketBubbleDrawX, placeMarketBubbleDrawY-bubblePadding-Resource::TEXT_HEIGHT_8, ALLEGRO_ALIGN_LEFT, placeMarketBubbleLabel);

    if(p->market.cargo.size() > 0)
    {
        unsigned s = 0;
        for(std::map<int,float>::iterator it = p->market.cargo.begin(); it != p->market.cargo.end(); ++it)
        {
            float drawX = placeMarketBubbleDrawX + s%placeMarketBubbleNumCols*Tile::WIDTH;
            float drawY = placeMarketBubbleDrawY + s/placeMarketBubbleNumCols*(Tile::HEIGHT+placeMarketBubbleRowSpacing);

            if((*it).second >= 1)
            {
                al_draw_bitmap_region(cargoPng,
                                      0+((*it).first)*Tile::WIDTH, 0,
                                      Tile::WIDTH, Tile::HEIGHT,
                                      drawX, drawY,
                                      0);

                string_al_draw_text(Resource::builtin8, COLKEY_TEXT, drawX+Tile::WIDTH, drawY+Tile::HEIGHT, ALLEGRO_ALIGN_RIGHT, std::to_string((int)(*it).second));
                s++;
            }
        }
    }
    else
        string_al_draw_text(Resource::builtin8,COLKEY_TEXT,placeMarketBubbleDrawX,placeMarketBubbleDrawY,ALLEGRO_ALIGN_LEFT,placeMarketBubbleEmptyText);
}

void BubbleView::DrawPlaceIndustriesBubble(Place *p)
{
    al_draw_filled_rounded_rectangle(placeIndustriesBubbleDrawX - bubblePadding,
                                     placeIndustriesBubbleDrawY - bubblePadding,
                                     placeIndustriesBubbleDrawX + placeIndustriesBubbleWidth + bubblePadding,
                                     placeIndustriesBubbleDrawY + placeIndustriesBubbleHeight + bubblePadding,
                                     bubbleCornerRadius,
                                     bubbleCornerRadius,
                                     COLKEY_UI_BUBBLE_BODY);

    al_draw_rounded_rectangle(placeIndustriesBubbleDrawX - bubblePadding,
                              placeIndustriesBubbleDrawY - bubblePadding,
                              placeIndustriesBubbleDrawX + placeIndustriesBubbleWidth + bubblePadding,
                              placeIndustriesBubbleDrawY + placeIndustriesBubbleHeight + bubblePadding,
                              bubbleCornerRadius,
                              bubbleCornerRadius,
                              COLKEY_UI_BUBBLE_FRAME,
                              4);

    string_al_draw_text(Resource::builtin8,COLKEY_TEXT,placeIndustriesBubbleDrawX, placeIndustriesBubbleDrawY-bubblePadding-8, ALLEGRO_ALIGN_LEFT, placeIndustriesBubbleLabel);

    if(p->industries.size() > 0)
    {
        for(unsigned i = 0; i < p->industries.size(); i++)
        {
            float drawX = placeIndustriesBubbleDrawX + placeIndustriesBubbleProgressBarOffset;
            float drawY = placeIndustriesBubbleDrawY + i*(Tile::HEIGHT + placeIndustriesBubbleRowSpacing + Resource::TEXT_HEIGHT_8);

/// To do: Animation to fade through input/ouputs in sequence or rotate through them like cards in a stacked deck
// Draw icon and quantity text for job output
            al_draw_bitmap_region(cargoPng,
                                  (p->industries[i]->outputs.begin()->first)*Tile::WIDTH,0,
                                  Tile::WIDTH,Tile::HEIGHT,
                                  placeIndustriesBubbleDrawX+Tile::WIDTH*1.5, drawY,
                                  0);

            string_al_draw_text(Resource::builtin8, COLKEY_TEXT,
                                placeIndustriesBubbleDrawX + Tile::WIDTH*1.5 +Tile::WIDTH,
                                drawY + Tile::HEIGHT,
                                ALLEGRO_ALIGN_RIGHT,
                                std::to_string((int)p->industries[i]->outputs.begin()->second));

// Draw icon and quantity text for job inputs (if job has inputs)
            if(p->industries[i]->inputs.size() > 0)
            {

                al_draw_bitmap_region(cargoPng,
                                      (p->industries[i]->inputs.begin()->first)*Tile::WIDTH,0,
                                      Tile::WIDTH,Tile::HEIGHT,
                                      placeIndustriesBubbleDrawX, drawY,
                                      0);

                string_al_draw_text(Resource::builtin8, COLKEY_TEXT,
                                    placeIndustriesBubbleDrawX + Tile::WIDTH,
                                    drawY + Tile::HEIGHT,
                                    ALLEGRO_ALIGN_RIGHT,
                                    std::to_string((int)p->industries[i]->inputs.begin()->second));

                al_draw_bitmap(redArrowPng,
                               placeIndustriesBubbleDrawX+Tile::WIDTH*0.75,
                               drawY,
                               0);

                // Draw red X over inputs, if inputs are insufficient
                if(p->industries[i]->jobState == JOB_STATE_INSUFFICIENT_INPUTS)
                    al_draw_bitmap(redTransparentXPng,
                                   placeIndustriesBubbleDrawX, drawY,
                                   0);
            }

// Draw progress bar
            if(p->industries[i]->jobState == JOB_STATE_INSUFFICIENT_INPUTS)
                al_draw_filled_rectangle(drawX, drawY + Tile::HEIGHT*0.75,
                                         drawX + p->industries[i]->pauseProgressBarFill*placeIndustriesBubbleProgressBarWidth,
                                         drawY + Tile::HEIGHT,
                                         COLKEY_UI_BUBBLE_INDUSTRY_PROGRESS_BODY_DEFICIT);
            else
                al_draw_filled_rectangle(drawX, drawY,
                                         drawX + p->industries[i]->productionProgressBarFill*placeIndustriesBubbleProgressBarWidth,
                                         drawY + Tile::HEIGHT,
                                         COLKEY_UI_BUBBLE_INDUSTRY_PROGRESS_BODY);
// Draw progress bar outline
            if(p->industries[i]->jobState == JOB_STATE_INSUFFICIENT_INPUTS)
                al_draw_rectangle(drawX, drawY,
                                  drawX+placeIndustriesBubbleProgressBarWidth,
                                  drawY + Tile::HEIGHT,
                                  COLKEY_UI_BUBBLE_INDUSTRY_PROGRESS_FRAME_DEFICIT,
                                  1);

            else
                al_draw_rectangle(drawX, drawY,
                                  drawX+placeIndustriesBubbleProgressBarWidth,
                                  drawY + Tile::HEIGHT,
                                  COLKEY_UI_BUBBLE_INDUSTRY_PROGRESS_FRAME,
                                  1);

            string_al_draw_text(Resource::builtin8, COLKEY_TEXT,
                                placeIndustriesBubbleDrawX + 3*Tile::WIDTH,
                                drawY + Tile::HEIGHT/2-Resource::TEXT_HEIGHT_8,
                                ALLEGRO_ALIGN_LEFT, p->industries[i]->remainingTimeText);
        }
    }
    else
        string_al_draw_text(Resource::builtin8, COLKEY_TEXT, placeIndustriesBubbleDrawX,placeIndustriesBubbleDrawY,ALLEGRO_ALIGN_LEFT, placeIndustriesBubbleEmptyText);

}



/// Encyclopedia bubble
int encyclopediaCurrentCategory; // = EN_CAT_LEYKIN;
int encyclopediaCurrentIndex; // = ANCESTRY_GENERAL;
std::string encyclopediaBubbleEntryName; // = beingAncestryNames.at(encyclopediaCurrentIndex);
std::string encyclopediaBubbleEntryText; // = encyclopedia.at(encyclopediaCurrentCategory).at(encyclopediaCurrentIndex);

float encyclopediaBubbleDrawX;
float encyclopediaBubbleDrawY;
float encyclopediaBubbleHeight;

void BubbleView::OpenEncyclopediaBubble(float x, float y, unsigned category, unsigned index)
{
    encyclopediaBubbleOpen = true;

    encyclopediaBubbleDrawX = x;
    encyclopediaBubbleDrawY = y;

    encyclopediaCurrentCategory = category;
    encyclopediaCurrentIndex = index;

    switch(category)
    {
    case EN_CAT_LEYKIN:
        encyclopediaBubbleEntryName = beingAncestryNames.at(encyclopediaCurrentIndex);
        break;
    case EN_CAT_FACTIONS:
        encyclopediaBubbleEntryName = sovereigntyNames.at(encyclopediaCurrentIndex);
        break;
    case EN_CAT_PLACES:
        encyclopediaBubbleEntryName = placeNames.at(encyclopediaCurrentIndex);
        break;
    case EN_CAT_CARGO:
        encyclopediaBubbleEntryName = itemNames.at(encyclopediaCurrentIndex);
        break;
    }

    encyclopediaBubbleEntryText = encyclopedia.at(encyclopediaCurrentCategory).at(encyclopediaCurrentIndex);

    int num_lines = count_num_lines_will_render(Resource::builtin8, encyclopediaBubbleWidth, encyclopediaBubbleEntryText);
    encyclopediaBubbleHeight = Resource::TEXT_HEIGHT_12 * (2 + num_lines); // Turns out the line spacing can be controlled by specifying a text height larger than the actual font size. Just remember to do the same in DrawEncyclopediaBubble()

    // In case the bottom of the enyclopedia bubble would end up off-screen, adjust upwards.
    if(encyclopediaBubbleDrawY + (encyclopediaBubbleHeight + 2*bubblePadding) > Display::HEIGHT)
        encyclopediaBubbleDrawY = Display::HEIGHT - encyclopediaBubbleHeight + bubblePadding;
}

void BubbleView::CloseEncyclopediaBubble()
{
    encyclopediaBubbleOpen = false;
}

void BubbleView::DrawEncyclopediaBubble()
{
    al_draw_filled_rounded_rectangle(encyclopediaBubbleDrawX - bubblePadding,
                                     encyclopediaBubbleDrawY - bubblePadding,
                                     encyclopediaBubbleDrawX + encyclopediaBubbleWidth + bubblePadding,
                                     encyclopediaBubbleDrawY + encyclopediaBubbleHeight + bubblePadding,
                                     bubbleCornerRadius,
                                     bubbleCornerRadius,
                                     COLKEY_UI_BUBBLE_BODY);

    al_draw_rounded_rectangle(encyclopediaBubbleDrawX - bubblePadding,
                              encyclopediaBubbleDrawY - bubblePadding,
                              encyclopediaBubbleDrawX + encyclopediaBubbleWidth + bubblePadding,
                              encyclopediaBubbleDrawY + encyclopediaBubbleHeight + bubblePadding,
                              bubbleCornerRadius,
                              bubbleCornerRadius,
                              COLKEY_UI_BUBBLE_FRAME,
                              4);


    string_al_draw_text(Resource::builtin8,COLKEY_TEXT,encyclopediaBubbleDrawX,encyclopediaBubbleDrawY,
                        ALLEGRO_ALIGN_LEFT,encyclopediaBubbleEntryName);

    string_al_draw_multiline_text(Resource::builtin8, COLKEY_TEXT,
                                  encyclopediaBubbleDrawX,encyclopediaBubbleDrawY + 2*Resource::TEXT_HEIGHT_12,
                                  encyclopediaBubbleWidth,
                                  Resource::TEXT_HEIGHT_12, // Turns out the line spacing can be controlled by specifying a text height larger than the actual font size.
                                  ALLEGRO_ALIGN_LEFT,
                                  encyclopediaBubbleEntryText);
}
