#include "UI.h"

/// UI
bool UIChangeDelay = false;

int activeUI = UI_OVERWORLD;
int previousActiveUI = UI_OVERWORLD;

int activeSubUI = SUBUI_OVERWORLD_NONE;
int previousActiveSubUI = SUBUI_OVERWORLD_NONE;


/// Bubble View
bool caravanInventoryBubbleOpen = false;
bool caravanTradeRecordsBubbleOpen = false;
bool caravanPathfindingBubbleOpen = false;

bool placePopulationBubbleOpen = false;
bool placeCaravanseraiBubbleOpen = false;
bool placeSurplusBubbleOpen = false;
bool placeDeficitBubbleOpen = false;
bool placeMarketBubbleOpen = false;
bool placeIndustriesBubbleOpen = false;

bool encyclopediaBubbleOpen = false;

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

    encyclopediaBubbleHeight = BUILTIN_TEXT_HEIGHT * (3 + string_al_get_text_width(builtin,encyclopediaBubbleEntryText)/encyclopediaBubbleWidth);



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
