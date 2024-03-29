#include "being.h"

std::vector<Being*> Being::people;

Being::Being()
{
    SetActive(true);

    SetActivity(ACT_WALKING);

    travelSpeed = 1.0;

    vitality = 100;
    happiness = 100;
    purpose = 100;

    //std::cout << "Being created." << std::endl;
}

Being::~Being()
{
    //std::cout << "Being deleted." << std::endl;
}

void Being::SetActive(bool a)
{
    active = a;
}

void Being::SetActivity(int act)
{
    activity = act;
    currentFrame = 0;
    frameDelayCount = 0;
    frameDelayThreshold = 6;

    switch(activity)
    {
    case ACT_WALKING:
        maxFrame = 1;
        break;
    }
}

void Being::SetName(std::string n)
{
    name = n;
}
void Being::SetAncestry(int a)
{
    ancestry = a;
    spriteWidth = Tile::WIDTH;
    spriteHeight = Tile::HEIGHT;
    spriteVariant = rand()% resourceBeingNumSpriteVariants.at(ancestry);
}

void Being::SetHometown(int h)
{
    hometown = h;
}


bool Being::IsActive()
{
    return active;
}

void Being::Progress()
{
    ProgressAnimation();
}

void Being::DrawActivity(float x, float y)
{
    if(x > Camera::OVERWORLD_MIN_DRAW_X && x < Camera::OVERWORLD_MAX_DRAW_X
            && y > Camera::OVERWORLD_MIN_DRAW_Y && y < Camera::OVERWORLD_MAX_DRAW_Y)
    {
        int f = 0;
        if(!facingLeft)
            f = ALLEGRO_FLIP_HORIZONTAL;

        if(activity == ACT_WALKING)
            al_draw_bitmap_region(Resource::beingPng[ancestry],
                                  spriteVariant*Resource::resourceBeingNumWalkFrames*spriteWidth + spriteWidth*currentFrame,
                                  spriteHeight*activity,
                                  spriteWidth,
                                  spriteHeight,
                                  x - (spriteWidth/2),
                                  y - (spriteHeight/2),
                                  f);
    }
}

void Being::ProgressAnimation()
{
    if(maxFrame > 0)
    {
        frameDelayCount++;
        if(frameDelayCount >= frameDelayThreshold)
        {
            frameDelayCount = 0;
            currentFrame++;
            if(currentFrame > maxFrame)
                currentFrame = 0;
        }
    }
}

/**
void Being::DrawBeingStatusBubble()
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
    AllegroCustom::string_al_draw_text(Resource::builtin8, COLKEY_TEXT, beingStatusBubbleDrawX,
                        beingStatusBubbleDrawY+beingStatusBubbleBiographyPartitionHeight,
                        ALLEGRO_ALIGN_LEFT, "Name: " + name);

    AllegroCustom::string_al_draw_text(Resource::builtin8, COLKEY_TEXT, beingStatusBubbleDrawX,
                        beingStatusBubbleDrawY+beingStatusBubbleBiographyPartitionHeight + Resource::TEXT_HEIGHT_12,
                        ALLEGRO_ALIGN_LEFT, "Home: " + placeNames.at(hometown));

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
*/

