#ifndef PLACE_H_INCLUDED
#define PLACE_H_INCLUDED

#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <cmath>
#include <iomanip>

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
    int placeIdentity;

    std::string name; // Just the simple name for identification on the overworld map.
    std::string epithet; // e.g. ", City of Dreaming Spires"

/// Population
    int totalPopulation;
    std::map<int, unsigned>population;

    std::vector<Being*>availableCrew;
    std::vector<Caravan*>citizenCaravans;
    std::vector<Caravan*>caravanserai;

    const int removeFromCaravanseraiDelay = 50; // Todo: Tie to advancement of calendar time instead of arbitrary number

/// Economy - Main
    float resourceSecurityFactor; /// The lynchpin of a city's economy, affecting supply and demand. How many multiples of its consumption must a city be overstocked for in order to alter its standard of living.
    int resourceSecurityReevaluationTime;
    int resourceSecurityReevaluationThreshold;
    int standardOfLiving;

    std::array<float, IT_MARKER_LAST+1>surplusRatio;
    std::array<float, IT_MARKER_LAST+1>deficitRatio;
    std::vector<int>surplusesTopSeven;
    std::vector<int>deficitsTopSeven;

/// Economy - Inventory
    std::array<Inventory, PLACE_INVENTORY_MARKER_LAST+1>inventory;

/// Economy - Industries
    std::vector<Industry*>industries;

/// Economy - Production
    std::map<int,float>dailyProduction;

/// Economy - Consumption
    std::array<int,IT_MARKER_LAST+1>consumptionLevel; // Standard of living, as applied to individual items.
    std::array<int,IT_MARKER_LAST+1>consumptionTimer;
    std::array<int,IT_MARKER_LAST+1>consumptionTimerThreshold;
    std::array<int,IT_MARKER_LAST+1>consumptionQuantity;
    std::array<int,IT_MARKER_LAST+1>consumptionDecimalOwing;

    std::array<int, IT_MARKER_LAST+1>maintainenceConsumptionTier; // Maintainence consumption refers to "household consumption," as opposed to industrial consumption.
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

/// Bubbles -- Caravanserai
    bool caravanseraiBubbleActive;
    float caravanseraiBubbleWidth, caravanseraiBubbleHeight;
    unsigned caravanseraiBubbleNumCols, caravanseraiBubbleNumRows;

/// Bubbles -- Surplus and Deficit
    const std::string surplusBubbleLabel = "Surplus";
    const float surplusBubbleDrawX = SCREEN_W*33/40;
    const float surplusBubbleDrawY = SCREEN_H*10/40;
    const unsigned surplusBubbleBaseCols = 1;
    const unsigned surplusBubbleBaseRows = 1;
    const unsigned surplusBubbleMaxRows = 7;
    unsigned surplusBubbleNumCols, surplusBubbleNumRows;
    float surplusBubbleWidth, surplusBubbleHeight; // Width extended by TILE_W*1.5 in UpdateSurplusBubble()

    const std::string deficitBubbleLabel = "Deficit";
    const float deficitBubbleDrawX = SCREEN_W*37/40 - TILE_W/2;
    const float deficitBubbleDrawY = SCREEN_H*10/40;
    const unsigned deficitBubbleBaseCols = 1;
    const unsigned deficitBubbleBaseRows = 1;
    const unsigned deficitBubbleMaxRows = 7;
    unsigned deficitBubbleNumCols, deficitBubbleNumRows;
    float deficitBubbleWidth, deficitBubbleHeight; // Width extended by TILE_W*1.5 in UpdateDeficitBubble()

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

    void NewCitizenCaravan();
    void DeleteCitizenCaravan(Caravan *c);
    void GenerateCitizenCaravans();

    void AddToCaravanserai(Caravan *c);
    void RemoveFromCaravanserai(Caravan *c);

/// Economy functions
    //void AdjustConsumption(int a, float b);

    //void UpdateEconomyData();
    //void UpdateProductionData();
    //void UpdateConsumptionData();

    void AddIndustry(int whichIndustry);

    bool CheckJobInputs(Industry* whichIndustry);
    void DeductJobInputs(Industry* whichIndustry);

    float CalculateConsumptionQuantity(unsigned whichItem);
    void UpdateConsumptionQuantity(unsigned whichItem);
    void ProgressProduction();
    void ProgressConsumption();

    void UpdateSurplusRatio(unsigned whichItem);
    void UpdateDeficitRatio(unsigned whichItem);
    void UpdateSurplusAndDeficitRatios(unsigned whichItem);
    void UpdateSurplusesTopSeven();
    void UpdateDeficitsTopSeven();

/// Inventory functions
    void AddInventoryStock(unsigned whichInventory, int a, int b);
    void RemoveInventoryStock(unsigned whichInventory, int a, int b);
    void SetInventoryStock(unsigned whichInventory, int a, int b);
    void TransferInventoryStock(unsigned sourceInv, unsigned destInv, int a, int b);

    void AddInitialStock();

/// Bubble functions
    void UpdateAllBubbles();
    void UpdatePopulationBubble();
    void UpdateCitizensBubble();
    void UpdateCaravanseraiBubble();
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
    void DrawCaravanseraiBubbleOnOverworld();
    void DrawSurplusBubble();
    void DrawDeficitBubble();
    void DrawInventoryBubbles();
    void DrawIndustriesBubble();
    void DrawFlyingTexts();
};

#endif // PLACE_H_INCLUDED
