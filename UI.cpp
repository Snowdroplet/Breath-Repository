#include "UI.h"

/// UI
bool UIChangeDelay = false;

int activeUI = UI_OVERWORLD;
int previousActiveUI = UI_OVERWORLD;

int activeSubUI = SUBUI_OVERWORLD_NONE;
int previousActiveSubUI = SUBUI_OVERWORLD_NONE;


/// Bubble View
Caravan* bubbleViewCaravan;
Place* bubbleViewPlace;

/*
bool caravanInventoryBubbleOpen = false;
bool caravanTradeRecordsBubbleOpen = false;
bool caravanPathfindingBubbleOpen = false;

bool placePopulationBubbleOpen = false;
bool placeCaravanseraiBubbleOpen = false;
bool placeSurplusBubbleOpen = false;
bool placeDeficitBubbleOpen = false;
bool placeMarketBubbleOpen = false;
bool placeIndustriesBubbleOpen = false;
*/

bool encyclopediaBubbleOpen = false;

/*
void OpenAllCaravanBubbles()
{
    caravanInventoryBubbleOpen = true;
    caravanTradeRecordsBubbleOpen = true;
    caravanPathfindingBubbleOpen = true;
}

void CloseAllCaravanBubbles()
{
    caravanInventoryBubbleOpen = false;
    caravanTradeRecordsBubbleOpen = false;
    caravanPathfindingBubbleOpen = false;
}

void OpenAllPlaceBubbles()
{
    placePopulationBubbleOpen = true;
    placeCaravanseraiBubbleOpen = true;
    placeSurplusBubbleOpen = true;
    placeDeficitBubbleOpen = true;
    placeMarketBubbleOpen = true;
    placeIndustriesBubbleOpen = true;
}

void CloseAllPlaceBubbles()
{
    placePopulationBubbleOpen = false;
    placeCaravanseraiBubbleOpen = false;
    placeSurplusBubbleOpen = false;
    placeDeficitBubbleOpen = false;
    placeMarketBubbleOpen = false;
    placeIndustriesBubbleOpen = false;
}
*/

void SetBubbleViewCaravan(Caravan *c)
{
    bubbleViewCaravan = c;

    /*
    if(bubbleViewCaravan == nullptr)
        CloseAllCaravanBubbles();
    else
        OpenAllCaravanBubbles();
        */
}

void SetBubbleViewPlace(Place *p)
{
    bubbleViewPlace = p;
    /*
    if(bubbleViewPlace == nullptr)
        CloseAllPlaceBubbles();
    else
        OpenAllPlaceBubbles();
        */
}

/// Encyclopedia bubble
int encyclopediaCurrentCategory; // = EN_CAT_LEYKIN;
int encyclopediaCurrentIndex; // = ANCESTRY_GENERAL;
std::string encyclopediaBubbleEntryName; // = beingAncestryNames.at(encyclopediaCurrentIndex);
std::string encyclopediaBubbleEntryText; // = encyclopedia.at(encyclopediaCurrentCategory).at(encyclopediaCurrentIndex);

float encyclopediaBubbleDrawX;
float encyclopediaBubbleDrawY;
float encyclopediaBubbleHeight;

void OpenEncyclopediaBubble(float x, float y, unsigned category, unsigned index)
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

    int num_lines = count_num_lines_will_render(builtin, encyclopediaBubbleWidth, encyclopediaBubbleEntryText);
    encyclopediaBubbleHeight = BUILTIN_TEXT_HEIGHT * (2 + num_lines);

    if(encyclopediaBubbleDrawY + (encyclopediaBubbleHeight + 2*bubblePadding) > SCREEN_H)
        encyclopediaBubbleDrawY = SCREEN_H - encyclopediaBubbleHeight + bubblePadding;
}

void CloseEncyclopediaBubble()
{
    encyclopediaBubbleOpen = false;
}

void DrawEncyclopediaBubble()
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


    string_al_draw_text(builtin,COLKEY_TEXT,encyclopediaBubbleDrawX,encyclopediaBubbleDrawY,
                        ALLEGRO_ALIGN_LEFT,encyclopediaBubbleEntryName);

    string_al_draw_multiline_text(builtin, COLKEY_TEXT,
                                  encyclopediaBubbleDrawX,encyclopediaBubbleDrawY + 2*BUILTIN_TEXT_HEIGHT,
                                  encyclopediaBubbleWidth,
                                  BUILTIN_TEXT_HEIGHT,
                                  ALLEGRO_ALIGN_LEFT,
                                  encyclopediaBubbleEntryText);

}
