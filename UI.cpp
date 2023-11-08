#include "UI.h"

/// UI
bool UIChangeDelay = false;

int activeUI = UI_OVERWORLD;
int previousActiveUI = UI_OVERWORLD;

int activeSubUI = SUBUI_OVERWORLD_NONE;
int previousActiveSubUI = SUBUI_OVERWORLD_NONE;


/// Bubble view
Caravan* bubbleViewCaravan;
Place* bubbleViewPlace;
Being* bubbleViewBeing;

bool beingStatusBubbleOpen = false;
bool encyclopediaBubbleOpen = false;

/// Being status bubble

void OpenBeingStatusBubble(/*float x, float y,*/ Being *b)
{
    beingStatusBubbleOpen = true;

    bubbleViewBeing = b;
}

void CloseBeingStatusBubble()
{
    beingStatusBubbleOpen = false;
    bubbleViewBeing = nullptr;
}

void DrawBeingStatusBubble()
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

    int num_lines = count_num_lines_will_render(builtin8, encyclopediaBubbleWidth, encyclopediaBubbleEntryText);
    encyclopediaBubbleHeight = TEXT_HEIGHT_12 * (2 + num_lines); // Turns out the line spacing can be controlled by specifying a text height larger than the actual font size. Just remember to do the same in DrawEncyclopediaBubble()

    // In case the bottom of the enyclopedia bubble would end up off-screen, adjust upwards.
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


    string_al_draw_text(builtin8,COLKEY_TEXT,encyclopediaBubbleDrawX,encyclopediaBubbleDrawY,
                        ALLEGRO_ALIGN_LEFT,encyclopediaBubbleEntryName);

    string_al_draw_multiline_text(builtin8, COLKEY_TEXT,
                                  encyclopediaBubbleDrawX,encyclopediaBubbleDrawY + 2*TEXT_HEIGHT_12,
                                  encyclopediaBubbleWidth,
                                  TEXT_HEIGHT_12, // Turns out the line spacing can be controlled by specifying a text height larger than the actual font size.
                                  ALLEGRO_ALIGN_LEFT,
                                  encyclopediaBubbleEntryText);
}
