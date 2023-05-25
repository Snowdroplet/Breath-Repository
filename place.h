#ifndef PLACE_H_INCLUDED
#define PLACE_H_INCLUDED

#include <string>
#include <vector>
#include <array>
#include <cmath>

#include "allegrocustom.h"

#include "overworld.h"
#include "caravan.h"
#include "industry.h"
#include "flyingtext.h"
#include "resource.h"

#include "flyingtext.h"

#include "placeindex.h"
#include "economyindex.h"


/// Dependencies
class Caravan; // Circular

enum enumPlaceInventories {                                     //PLACE_INVENTORY_RESERVE     = 0,
                           PLACE_INVENTORY_MARKET = /*1,*/ 0}; // PLACE_INVENTORY_INDUSTRIAL  = 2, PLACE_INVENTORY_MAINTAINENCE = 3};
//const int PLACE_INVENTORY_MARKER_FIRST = PLACE_INVENTORY_RESERVE;
//const int PLACE_INVENTORY_MARKER_LAST = PLACE_INVENTORY_MAINTAINENCE;
const int PLACE_INVENTORY_MARKER_FIRST = PLACE_INVENTORY_MARKET;
const int PLACE_INVENTORY_MARKER_LAST =  PLACE_INVENTORY_MARKET;

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
    int totalPopulation;
    std::array<int, EXP_MARKER_LAST+1>population;

    std::vector<Being*>availableCrew;
    std::vector<Being*>citizens;
    std::vector<Caravan*>visitors;

    const int removeVisitorCaravanDelay = 50; // Todo: Tie to advancement of calendar time instead of arbitrary number

/// Economy - Inventory
    int standardOfLiving;

    std::array<Inventory, PLACE_INVENTORY_MARKER_LAST+1>inventory;

/// Economy - Industries
    std::vector<Industry*>industries;

/// Economy - Production
    //std::map<int,float>insufficiencies;

    std::map<int,float>dailyProduction;


    //std::map<int,float>demand;

/// Economy - Consumption
    std::map<int,int>consumptionTimer;
    std::map<int,float>consumptionDecimalOwing;


    //std::array<float, PLACE_INVENTORY_MARKER_LAST+1>resourceAllocation;      // Percentage out of 100 to allocate to each inventory.
    //std::array<float, PLACE_INVENTORY_MARKER_LAST+1>resourceAllocationOwing; // Consequence of items needing interger quantities. Basically which inventory has been short-changed in the past, and by how much.

    std::map<int,int>maintainenceConsumptionTier; // Maintainence consumption refers to "household consumption," as opposed to industrial consumption.
    std::map<int,float>dailyConsumption;

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

                                                                                     //  MARKET,            RESERVE,       INDUSTRIAL,    MAINTAINENCE
    const std::array<std::string, PLACE_INVENTORY_MARKER_LAST+1>inventoryBubbleLabel = {"Market"};       /*", Reserves",    "Industrial",  "Maintainence"};*/
    const std::array<float, PLACE_INVENTORY_MARKER_LAST+1>inventoryBubbleDrawX =       {SCREEN_W*22/40}; /*, SCREEN_W*28/40, SCREEN_W*28/40, SCREEN_W*34/40};*/
    const std::array<float, PLACE_INVENTORY_MARKER_LAST+1>inventoryBubbleDrawY =       {SCREEN_H*10/40}; /*, SCREEN_H* 2/40, SCREEN_H*10/40, SCREEN_H*10/40};*/
    const float inventoryBubbleRowSpacing = BUILTIN_TEXT_HEIGHT;
    const float inventoryBubbleBaseCols = 5;
    const float inventoryBubbleBaseRows = 2;
    std::array<unsigned, PLACE_INVENTORY_MARKER_LAST+1>inventoryBubbleNumCols;
    std::array<unsigned, PLACE_INVENTORY_MARKER_LAST+1>inventoryBubbleNumRows;
    std::array<unsigned, PLACE_INVENTORY_MARKER_LAST+1>inventoryBubbleWidth;
    std::array<unsigned, PLACE_INVENTORY_MARKER_LAST+1>inventoryBubbleHeight;

    const float industriesBubbleDrawX = SCREEN_W*22/40;
    const float industriesBubbleDrawY = SCREEN_H*18/40;
    const float industriesBubbleRowSpacing = 4; // Arbitrary gap
    const float industriesBubbleWidth = TILE_W*11 + bubbleWidthPadding;
    float industriesBubbleHeight;
    const float industriesBubbleProgressBarOffset = 2.5*TILE_W;
    const float industriesBubbleProgressBarWidth = industriesBubbleWidth - industriesBubbleProgressBarOffset;

/// Flying text
    std::vector<FlyingText*>upFlyingTexts;
    std::vector<FlyingText*>downFlyingTexts;

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
    void AdjustConsumption(int a, float b);

    void UpdateEconomyData();
    void UpdateProductionData();
    void UpdateConsumptionData();

    void AddIndustry(int whichIndustry, float baseProdPerTick);

    bool CheckJobInputs(Industry* whichIndustry);
    void DeductJobInputs(Industry* whichIndustry);

    void ProgressProduction();
    void ProgressConsumption();

/// Inventory functions
    void AddInventoryStock(unsigned whichInventory, int a, int b);
    void RemoveInventoryStock(unsigned whichInventory, int a, int b);
    void SetInventoryStock(unsigned whichInventory, int a, int b);
    void TransferInventoryStock(unsigned sourceInv, unsigned destInv, int a, int b);

    //void SetResourceAllocation(float reserveProportion, float marketProportion, float industrialProportion, float maintainenceProportion); // Doesn't have to be percentage. Divides by total.
    //void AllocateReserve(unsigned whichItem);
    //void AllocateReserves();


    void AddInitialStock();

/// Bubble functions
    void UpdateAllBubbles();
    void UpdateVisitorBubble();
    void UpdateInventoryBubbles();
    void UpdateInventoryBubble(unsigned whichBubble);
    void UpdateIndustriesBubble(); // Only called when industrial activity updated
    void ProgressIndustriesBubbleProgressBars(); // Called on timer tick

/// Flying text functions
    void QueueUpFlyingText(int ic, std::string t, float x, float y);
    void QueueDownFlyingText(int ic, std::string t, float x, float y);
    void ProgressFlyingTexts();

/// Overworld drawing functions
    void DrawSpriteOnOverworld();
    void DrawVisitorBubbleOnOverworld();
    void DrawInventoryBubbles();
    void DrawIndustriesBubble();
    void DrawFlyingTexts();
};

#endif // PLACE_H_INCLUDED
