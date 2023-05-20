#ifndef PLACE_H_INCLUDED
#define PLACE_H_INCLUDED

#include <string>
#include <vector>

#include "allegrocustom.h"
#include "placeindex.h"
#include "overworld.h"
#include "caravan.h"
#include "industry.h"
#include "flyingtext.h"
#include "resource.h"

#include "flyingtext.h"


/// Dependencies
class Caravan; // Circular

class Place
{
public:
    static const int OVERWORLD_SPRITE_W = 64;
    static const int OVERWORLD_SPRITE_H = 64;

    static std::map <int, Place*>places;

/// Identity
    int identity;

    std::string name; // Just the simple name for identification on the overworld map.
    std::string epithet; // e.g. ", City of Dreaming Spires"

/// Population
    std::vector<Being*>availableCrew;
    std::vector<Being*>citizens;
    std::vector<Caravan*>visitors;

    const int removeVisitorCaravanDelay = 50; // Todo: Tie to advancement of calendar time instead of arbitrary number

/// Economy
    Inventory inventory;

    std::vector<Industry*>industries;

    std::map<int,float>insufficiencies;

    //std::map<int,float>production;  // per day

    //std::map<int,float>demand;

    //std::map<int,float>consumption;

/// Inventory

/// Location
    int overworldXPosition, overworldYPosition; // Absolute position on the overworld.

    std::vector<Road*>connections;

/// Bubbles
    const float bubbleWidthPadding = TILE_W/4;
    const float bubbleHeightPadding = TILE_H/4;
    const float bubbleCornerRadius = 8;

    bool visitorBubbleActive;
    float visitorBubbleWidth, visitorBubbleHeight;
    unsigned visitorBubbleNumCols;
    unsigned visitorBubbleNumRows;

    const float inventoryBubbleDrawX = SCREEN_W*6/10;
    const float inventoryBubbleDrawY = SCREEN_H*3/10;
    const float inventoryBubbleRowSpacing = BUILTIN_TEXT_HEIGHT;
    const float inventoryBubbleBaseCols = 6;
    const float inventoryBubbleBaseRows = 2;
    unsigned inventoryBubbleNumCols;
    unsigned inventoryBubbleNumRows;
    float inventoryBubbleWidth, inventoryBubbleHeight;


    const float industriesBubbleDrawX = SCREEN_W*6/10;
    const float industriesBubbleDrawY = SCREEN_H*6/10;
    const float industriesBubbleRowSpacing = 4; // Arbitrary gap
    const float industriesBubbleWidth = TILE_W*12 + bubbleWidthPadding;
    float industriesBubbleHeight;

/// Flying text
    std::vector<FlyingText*>flyingTexts;

/// Constructor
    Place(int id);
    ~Place();

/// Population functions
    void AddAvailableCrew(Being *b);
    void RemoveAvailableCrew(Being *b);

    void AddCitizen(Being *b);
    void RemoveCitizen(Being *b);

    void AddVisitorCaravan(Caravan *c);
    void RemoveVisitorCaravan(Caravan *c);

/// Economy functions
    //void AdjustProduction(int a, float b);
    //void AdjustDemand(int a, float b);
    void AddIndustry(int whichIndustry, float baseProdPerTick);
    bool ActivateJob(Industry* whichIndustry);

    void AdjustConsumption(int a, float b);

    void EvaluateEconomy();
    void EvaluateProduction();
    void EvaluateDemand();
    void EvaluateConsumption();

    void ProgressEconomy();

/// Inventory functions
    void AddInventoryStock(int a, float b);
    void RemoveInventoryStock(int a, float b);
    void SetInventoryStock(int a, float b);

    void AddInitialStock();
/// Location functions

/// Bubble functions
    void UpdateAllBubbles();
    void UpdateVisitorBubble();
    void UpdateInventoryBubble();
    void UpdateIndustriesBubble();

/// Flying text functions
    void QueueFlyingText(int ic, std::string t, float x, float y, bool up);
    void ProgressFlyingTexts();

/// Overworld drawing functions
    void DrawSpriteOnOverworld();
    void DrawVisitorBubbleOnOverworld();
    void DrawInventoryBubble();
    void DrawIndustriesBubble();
    void DrawFlyingTexts();
};

#endif // PLACE_H_INCLUDED
