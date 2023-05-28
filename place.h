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
    std::map<int, int>population;

    std::vector<Being*>availableCrew;
    std::vector<Being*>citizenCaravans;
    std::vector<Caravan*>visitorCaravans;

    const int removeVisitorCaravanDelay = 50; // Todo: Tie to advancement of calendar time instead of arbitrary number

/// Economy - Main
    float resourceSecurityFactor; /// The lynchpin of a city's economy, affecting supply and demand. How many multiples of its consumption must a city be overstocked for in order to alter its standard of living.
    int resourceSecurityReevaluationTime;
    int resourceSecurityReevaluationThreshold;
    int standardOfLiving;

    std::array<int, IT_MARKER_LAST+1>surplusDeficitRatio;

/// Economy - Inventory
    std::array<Inventory, PLACE_INVENTORY_MARKER_LAST+1>inventory;

/// Economy - Industries
    std::vector<Industry*>industries;

/// Economy - Production
    std::map<int,float>dailyProduction;

/// Economy - Consumption
    std::array<int, IT_MARKER_LAST+1>consumptionLevel; // Standard of living, as applied to individual items.
    std::map<int,int>consumptionTimer;
    std::map<int,float>consumptionDecimalOwing;

    std::map<int,int>maintainenceConsumptionTier; // Maintainence consumption refers to "household consumption," as opposed to industrial consumption.
    std::map<int,float>dailyConsumption;

/// Location
    int overworldXPosition, overworldYPosition; // Absolute position on the overworld.

    std::vector<Road*>connections;

/// Bubbles -- General
    const float bubblePadding = TILE_W/4;
    const float bubbleCornerRadius = 8;

/// Bubbles -- Population
    const std::string populationBubbleLabel = "Population";
    const std::string populationBubbleEmptyText = "<None>";
    const float populationBubbleDrawX = SCREEN_W*26/40;
    const float populationBubbleDrawY = SCREEN_H*6/40;
    const int populationBubbleBaseCols = 1;
    const float populationBubbleHeight = TILE_H;
    float populationBubbleWidth;
    unsigned populationBubbleNumCols;

/// Bubbles -- Citizen Caravans
    const float citizensBubbleDrawX = SCREEN_W*33/40;
    const float citizensBubbleDrawY = SCREEN_H*24/40;
    const float citizensBubbleWidth = TILE_W*6; // + bubblePadding;
    const unsigned citizensBubbleBaseRows = 1;
    unsigned citizensBubbleNumRows;
    float citizensBubbleHeight;

/// Bubbles -- Visitor Caravans
    bool visitorBubbleActive;
    float visitorBubbleWidth, visitorBubbleHeight;
    unsigned visitorBubbleNumCols, visitorBubbleNumRows;

/// Bubbles -- Surplus and Deficit
    const std::string surplusBubbleLabel = "Surplus";
    const float surplusBubbleDrawX = SCREEN_W*33/40;
    const float surplusBubbleDrawY = SCREEN_H*10/40;
    const unsigned surplusBubbleBaseCols = 2;
    const unsigned surplusBubbleBaseRows = 7;
    unsigned surplusBubbleNumCols, surplusBubbleNumRows;
    float surplusBubbleWidth, surplusBubbleHeight;

    const std::string deficitBubbleLabel = "Deficit";
    const float deficitBubbleDrawX = SCREEN_W*37/40;
    const float deficitBubbleDrawY = SCREEN_H*10/40;
    const unsigned deficitBubbleBaseCols = 2;
    const unsigned deficitBubbleBaseRows = 7;
    unsigned deficitBubbleNumCols, deficitBubbleNumRows;
    float deficitBubbleWidth, deficitBubbleHeight;

/// Bubbles -- Inventory
                                                                                     //  MARKET,            RESERVE,       INDUSTRIAL,    MAINTAINENCE
    const std::array<std::string, PLACE_INVENTORY_MARKER_LAST+1>inventoryBubbleLabel = {"Market"};       /*", Reserves",    "Industrial",  "Maintainence"};*/
    const std::string inventoryBubbleEmptyText                                       = "<No inventory>";
    const std::array<float, PLACE_INVENTORY_MARKER_LAST+1>inventoryBubbleDrawX       = {SCREEN_W*26/40}; /*, SCREEN_W*28/40, SCREEN_W*28/40, SCREEN_W*34/40};*/
    const std::array<float, PLACE_INVENTORY_MARKER_LAST+1>inventoryBubbleDrawY       = {SCREEN_H*10/40}; /*, SCREEN_H* 2/40, SCREEN_H*10/40, SCREEN_H*10/40};*/
    const float inventoryBubbleRowSpacing = BUILTIN_TEXT_HEIGHT;
    const unsigned inventoryBubbleBaseCols = 6;
    const unsigned inventoryBubbleBaseRows = 2;
    std::array<unsigned, PLACE_INVENTORY_MARKER_LAST+1>inventoryBubbleNumCols;
    std::array<unsigned, PLACE_INVENTORY_MARKER_LAST+1>inventoryBubbleNumRows;
    std::array<float, PLACE_INVENTORY_MARKER_LAST+1>inventoryBubbleWidth;
    std::array<float, PLACE_INVENTORY_MARKER_LAST+1>inventoryBubbleHeight;

/// Bubbles -- Industry
    const std::string industriesBubbleLabel = "Local Industries";
    const std::string industriesBubbleEmptyText = "<No industries>";
    const float industriesBubbleDrawX = SCREEN_W*26/40;
    const float industriesBubbleDrawY = SCREEN_H*24/40;
    const float industriesBubbleRowSpacing = 4; // Arbitrary gap
    const float industriesBubbleWidth = TILE_W*6; //+ bubblePadding;
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

    void AddCitizenCaravan(Being *b);
    void RemoveCitizenCaravan(Being *b);

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
    void UpdatePopulationBubble();
    void UpdateCitizensBubble();
    void UpdateVisitorBubble();
    void UpdateSurplusBubble();
    void UpdateDeficitBubble();
    void UpdateInventoryBubbles();
    void UpdateInventoryBubble(unsigned whichBubble);
    void UpdateIndustriesBubble(); // Only called when industrial activity updated
    void ProgressIndustriesBubbleProgressBars(); // Called on timer tick

/// Flying text functions
    void QueueUpFlyingText(int icon, std::string text, float x, float y);
    void QueueDownFlyingText(int icon, std::string text, float x, float y);
    void ProgressFlyingTexts();

/// Overworld drawing functions
    void DrawSpriteOnOverworld();
    void DrawPopulationBubble();
    void DrawCitizensBubble();
    void DrawVisitorBubbleOnOverworld();
    void DrawSurplusBubble();
    void DrawDeficitBubble();
    void DrawInventoryBubbles();
    void DrawIndustriesBubble();
    void DrawFlyingTexts();
};

#endif // PLACE_H_INCLUDED
