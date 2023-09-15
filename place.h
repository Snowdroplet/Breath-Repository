#ifndef PLACE_H_INCLUDED
#define PLACE_H_INCLUDED

//#define debug_output_place_progress_maintainence_consumption
#define debug_output_place_calculate_and_draw_consumption

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
//#include "economy.h"

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

    //std::vector<Being*>availableCrew;

/// Citizen caravans and trade missions
    std::vector<Caravan*>citizenCaravans;

/// Caravanserai
    std::vector<Caravan*>caravanserai;

    const int removeFromCaravanseraiDelay = 50; // Todo: Tie to advancement of calendar time instead of arbitrary number

/// Economy - Main
    float maintainenceSecurityFactor; /// Security factor is the lynchpin of a city's economy, affecting supply and demand. How many multiples of its consumption must a city be overstocked for in order to consider itself at a resource surplus for its consumption tier.
    float industrialSecurityFactor;   /// As above, but for industrial inputs. Based on daily average, so a security factory of 7 means that the city wants to have enough inputs to cover 7 days' production at any time.
    /// To do: split maintainence security factor into array with indexes for five thresholds - corresponding to consumption tiers (destitute, poor, comfortable, wealthy, profligate)

    int resourceSecurityReevaluationTime;
    int resourceSecurityReevaluationThreshold;
    int initialStandardOfLiving; /// See maintainenceConsumptionTier

    std::array<float, IT_MARKER_LAST+1>surplusRatio;
    std::array<float, IT_MARKER_LAST+1>deficitRatio;
    std::vector<int>surplusesTopTen;
    std::vector<int>deficitsTopTen;

/// Economy - Inventory
    std::array<Inventory, PLACE_INVENTORY_MARKER_LAST+1>inventory;

/// Economy - Industries
    std::vector<Industry*>industries;

/// Economy - Industrial Production
    //std::map<int,float>dailyProduction;

/// Economy - Maintainence Consumption --- Maintainence consumption roughly corresponds to "household consumption" in economics, as opposed to "industrial consumption".
    std::array<int,IT_MARKER_LAST+1>maintainenceConsumptionLevel; // Standard of living, as applied to individual items.
    std::array<int,IT_MARKER_LAST+1>maintainenceConsumptionTimer; // When this increases to threshold, it's time for a consumption tick
    std::array<int,IT_MARKER_LAST+1>maintainenceConsumptionTimerThreshold;
    std::array<float,IT_MARKER_LAST+1>maintainenceConsumptionQuantityOnTick; // How much of a resource is consumed during a consumption tick
    std::array<float,IT_MARKER_LAST+1>maintainenceConsumptionQuantityDaily;

    const std::array<unsigned, LIVING_MARKER_LAST+1>maintainenceConsumptionTierSecurityThreshold = { /*Destitute:*/ 0, /*Poor*/ 1, /*confortable*/ 3, /*wealthy*/ 7, /*profligate*/ 20};
    std::array<int, IT_MARKER_LAST+1>maintainenceConsumptionTier; /// It is important to note that changing MCT only affects maintainence consumption rate (not consumption quantity), through the updatemaintainenceconsumptionquantity function
    std::map<int,float>dailyConsumption;

/// Economy - Industrial Consumption --- As opposed to maintainence consumption above.
    std::array<float,IT_MARKER_LAST+1>industrialConsumptionQuantityDaily; // How much of a resource is consumed by industries on average **per day**.

/// Trade mission

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

/*
/// Bubbles -- Citizen Caravans
    const std::string citizensBubbleLabel = "Associated Caravans";
    const float citizensBubbleDrawX = SCREEN_W*33/40;
    const float citizensBubbleDrawY = SCREEN_H*28/40;
    const float citizensBubbleWidth = TILE_W*6; // + bubblePadding;
    const unsigned citizensBubbleBaseRows = 1;
    unsigned citizensBubbleNumRows;
    float citizensBubbleHeight;
*/

/// Bubbles -- Caravanserai
    const std::string caravanseraiBubbleLabel = "Caravanserai";
    const std::string caravanseraiBubbleEmptyText = "<Empty>";
    const float caravanseraiBubbleDrawX = SCREEN_W*33/40;
    const float caravanseraiBubbleDrawY = SCREEN_H*28/40;
    const unsigned caravanseraiBubbleBaseCols = 6;
    const unsigned caravanseraiBubbleBaseRows = 1;
    unsigned caravanseraiBubbleNumCols;
    unsigned caravanseraiBubbleNumRows;
    float caravanseraiBubbleWidth;
    float caravanseraiBubbleHeight;


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
                                                                                    //  MARKET,              RESERVE,       INDUSTRIAL,    MAINTAINENCE
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
    const float industriesBubbleDrawY = SCREEN_H*28/40;
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

/// Citizen caravans (soon to have scope reduced to hometown only)
    void NewCitizenCaravan();
    void DeleteCitizenCaravan(Caravan *c);
    void GenerateCitizenCaravans();

/// Caravanserai functions
    void AddToCaravanserai(Caravan *c);
    void RemoveFromCaravanserai(Caravan *c);

/// Economy functions -- Main functions
    void UpdateSurplusAndDeficitRatios(unsigned whichItem);
    void UpdateSurplusesTopTen();
    void UpdateDeficitsTopTen();

/// Economy functions -- Maintainence consumption
    void UpdateMaintainenceConsumptionTimerThreshold(unsigned whichItem);

    float CalculateMaintainenceConsumptionQuantityOnTick(unsigned whichItem);
    void UpdateMaintainenceConsumptionQuantityOnTick(unsigned whichItem);

    float CalculateMaintainenceConsumptionQuantityDaily(unsigned whichItem);
    void UpdateMaintainenceConsumptionQuantityDaily(unsigned whichItem);

    void UpdateMaintainenceConsumptionTier(unsigned whichItem);
    void ProgressMaintainenceConsumption();

/// Economy functions -- Industrial consumption
    float CalculateIndustrialConsumptionQuantityDaily(unsigned whichItem); // Daily average
    void UpdateIndustrialConsumptionQuantityDaily(unsigned whichItem);

/// Industry functions
    void AddIndustry(int whichIndustry);
    bool CheckJobInputs(Industry* whichIndustry);
    void DeductJobInputs(Industry* whichIndustry);
    void ProgressProduction();

/// Inventory functions
    void AddInventoryStock(unsigned whichInventory, int a, float b);
    void RemoveInventoryStock(unsigned whichInventory, int a, float b);
    void SetInventoryStock(unsigned whichInventory, int a, float b);
    void TransferInventoryStock(unsigned sourceInv, unsigned destInv, int a, float b);
    void TransferInventoryStockToCaravan(unsigned sourceInv, Caravan *c, int a, float b);
    void TransferInventoryStockFromCaravan(unsigned destInv, Caravan *c, int a, float b);

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
    //void DrawCaravanseraiBubbleOnOverworld();
    void DrawCaravanseraiBubble();
    void DrawSurplusBubble();
    void DrawDeficitBubble();
    void DrawInventoryBubbles();
    void DrawIndustriesBubble();
    void DrawFlyingTexts();
};

#endif // PLACE_H_INCLUDED
