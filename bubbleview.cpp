#include "bubbleview.h"

/// Bubble view
Caravan* BubbleView::currentCaravan;
Place* BubbleView::currentPlace;
Being* BubbleView::currentBeing;

bool BubbleView::beingStatusBubbleOpen;
bool BubbleView::encyclopediaBubbleOpen;

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
    al_draw_filled_rounded_rectangle(beingStatusBubbleDrawX - BubbleView::bubblePadding,
                                     beingStatusBubbleDrawY - BubbleView::bubblePadding,
                                     beingStatusBubbleDrawX + beingStatusBubbleWidth + BubbleView::bubblePadding,
                                     beingStatusBubbleDrawY + beingStatusBubbleHeight + BubbleView::bubblePadding,
                                     BubbleView::bubbleCornerRadius,
                                     BubbleView::bubbleCornerRadius,
                                     COLKEY_UI_BUBBLE_BODY);

    al_draw_rounded_rectangle(beingStatusBubbleDrawX - BubbleView::bubblePadding,
                              beingStatusBubbleDrawY - BubbleView::bubblePadding,
                              beingStatusBubbleDrawX + beingStatusBubbleWidth + BubbleView::bubblePadding,
                              beingStatusBubbleDrawY + beingStatusBubbleHeight + BubbleView::bubblePadding,
                              BubbleView::bubbleCornerRadius,
                              BubbleView::bubbleCornerRadius,
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
    if(encyclopediaBubbleDrawY + (encyclopediaBubbleHeight + 2*BubbleView::bubblePadding) > Display::HEIGHT)
        encyclopediaBubbleDrawY = Display::HEIGHT - encyclopediaBubbleHeight + BubbleView::bubblePadding;
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
                                     BubbleView::bubbleCornerRadius,
                                     BubbleView::bubbleCornerRadius,
                                     COLKEY_UI_BUBBLE_BODY);

    al_draw_rounded_rectangle(encyclopediaBubbleDrawX - bubblePadding,
                              encyclopediaBubbleDrawY - bubblePadding,
                              encyclopediaBubbleDrawX + encyclopediaBubbleWidth + bubblePadding,
                              encyclopediaBubbleDrawY + encyclopediaBubbleHeight + bubblePadding,
                              BubbleView::bubbleCornerRadius,
                              BubbleView::bubbleCornerRadius,
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
