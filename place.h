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

#include "colorindex.h"
#include "resource.h"

#include "caravan.h"
#include "road.h"
#include "industry.h"
#include "flyingtext.h"

#include "placeindex.h"
#include "economyindex.h"
#include "sovereigntyindex.h"


/// Dependencies
class Caravan; // Circular
class Road;

class Place
{
public:
    static const int OVERWORLD_SPRITE_W = 64;
    static const int OVERWORLD_SPRITE_H = 64;

    static std::map <int, Place*>places;

/// Identity
    int placeIdentity;

    std::string name; // Just the simple name for identification on the overworld map.
    //std::string epithet; // e.g. ", City of Dreaming Spires"

    int sovereignty;

/// Population
    std::map<int, unsigned>population;

    //std::vector<Being*>availableCrew;

/// Citizen caravans and trade missions
    std::vector<Caravan*>citizenCaravans;

/// Caravanserai
    std::vector<Caravan*>caravanserai;

    const int removeFromCaravanseraiDelayHours = 1; // Todo: Tie to advancement of calendar time instead of arbitrary number

/// Economy - Main
    std::array<bool, InventoryIndex::IT_MARKER_LAST+1>itemsConsumedByIndustries; // Not mutually exclusive with "itemsProducedByIndustries", i.e. in the case of intermediate inputs in two stage production chains
    std::array<bool, InventoryIndex::IT_MARKER_LAST+1>itemsProducedByIndustries;
    std::array<bool, InventoryIndex::IT_MARKER_LAST+1>itemsConsumedByPopulation;

    const float maintainenceSecurityFactor = 3; /// Security factor is the lynchpin of a city's economy, affecting supply and demand. How many multiples of its consumption must a city be overstocked for in order to consider itself at a resource surplus.
    const float industrialSecurityFactor = 3;   /// As above, but for industrial inputs. Based on daily average, so a security factory of 7 means that the city wants to have enough inputs to cover 7 days' production at any time.

    std::array<float, InventoryIndex::IT_MARKER_LAST+1>surplusRatio;
    std::array<float, InventoryIndex::IT_MARKER_LAST+1>deficitRatio;
    std::vector<int>surplusesDescending;
    std::vector<int>deficitsDescending;


/// Economy - Inventory
    Inventory market;
    Inventory marketBuffer; // Items are traded from caravan to buffer to caravan, to prevent back-and-forth trades based on updates to surplus/deficit data.

/// Economy - Industries
    std::vector<Industry*>industries;

/// Economy - Industrial Production
    //std::map<int,float>dailyProduction;

/// Economy - Trading


/// Economy - Maintainence Consumption --- Maintainence consumption roughly corresponds to "household consumption" in economics, as opposed to "industrial consumption".

    std::array<int,InventoryIndex::IT_MARKER_LAST+1>maintainenceConsumptionLevel; // Standard of living, as applied to individual items.
    std::array<int,InventoryIndex::IT_MARKER_LAST+1>maintainenceConsumptionTimer; // When this increases to threshold, it's time for a consumption tick
    std::array<int,InventoryIndex::IT_MARKER_LAST+1>maintainenceConsumptionTimerThreshold;
    std::array<float,InventoryIndex::IT_MARKER_LAST+1>maintainenceConsumptionQuantityOnTick; // How much of a resource is consumed during a consumption tick
    std::array<float,InventoryIndex::IT_MARKER_LAST+1>maintainenceConsumptionQuantityDaily;

///std::array<int, IT_MARKER_LAST+1>maintainenceConsumptionTier; /// It is important to note that changing MCT only affects maintainence consumption rate (not consumption quantity), through the updatemaintainenceconsumptionquantity function
    std::map<int,float>dailyConsumption;

/// Economy - Industrial Consumption --- As opposed to maintainence consumption above.
    std::array<float,InventoryIndex::IT_MARKER_LAST+1>industrialConsumptionQuantityDaily; // How much of a resource is consumed by industries on average **per day**.

/// Location
    int overworldXPosition, overworldYPosition; // Absolute position on the overworld.

    std::vector<Road*>connections;

/// Bubbles
    bool populationBubbleNeedsUpdate;
    bool caravanseraiBubbleNeedsUpdate;
    bool surplusBubbleNeedsUpdate;
    bool deficitBubbleNeedsUpdate;
    bool marketBubbleNeedsUpdate;
    bool industriesBubbleNeedsUpdate;

    /*
/// Bubbles -- Population
    float placePopulationBubbleWidth;
    unsigned placePopulationBubbleNumCols;

/// Bubbles -- Caravanserai
    unsigned placeCaravanseraiNumCols;
    unsigned placeCaravanseraiNumRows;
    float placeCaravanseraiWidth;
    float placeCaravanseraiHeight;


/// Bubbles -- Surplus and Deficit
    unsigned placeSurplusBubbleNumCols, placeSurplusBubbleNumRows;
    float placeSurplusBubbleWidth, placeSurplusBubbleHeight; // Width extended by Tile::WIDTH*1.5 in UpdateplaceSurplusBubble()

    unsigned placeDeficitBubbleNumCols, placeDeficitBubbleNumRows;
    float placeDeficitBubbleWidth, placeDeficitBubbleHeight; // Width extended by Tile::WIDTH*1.5 in UpdateplaceDeficitBubble()


/// Bubbles -- Market
    unsigned placeMarketBubbleNumCols;
    unsigned placeMarketBubbleNumRows;
    float placeMarketBubbleWidth;
    float placeMarketBubbleHeight;

/// Bubbles -- Industry
    float placeIndustriesBubbleHeight;
    */

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
    void UpdateItemsProducedAndConsumedByIndustries();

    void UpdateSurplusAndDeficitRatios(unsigned whichItem);
    void UpdateSurplusesDescending();
    void UpdateDeficitsDescending();

/// Economy functions -- Trading
    void TradeWithCaravan(Caravan *c);

    void UnloadCaravanToMarketBuffer(Caravan *c);
    void LoadCaravan(Caravan *c);


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

    void AddMarketStock(int a, float b);
    void RemoveMarketStock(int a, float b);
    void SetMarketStock(int a, float b);

    void AddMarketBufferStock(int a, float b);
    void RemoveMarketBufferStock(int a, float b);
    void SetMarketBufferStock(int a, float b);

//Market to Caravan
    void TransferMarketStockToCaravanStock(Caravan *c, int a, float b);

// Caravan to Buffer
    void TransferCaravanStockToMarketBufferStock(Caravan *c, int a, float b);

// Buffer to Market
    void DumpMarketBufferStockToMarketStock();

    void AddInitialMarketStock();

/// Bubble functions
    void AllBubblesNeedUpdate();

    //void UpdateAllBubbles();
    /*
    void UpdatePlacePopulationBubble();
    void UpdateCitizensBubble();
    void UpdatePlaceCaravanseraiBubble();

    void UpdatePlaceSurplusBubble();
    void UpdatePlaceDeficitBubble();

    void UpdatePlaceMarketBubble();
    void UpdatePlaceIndustriesBubble(); // Only called when industrial activity updated
    */
    void ProgressPlaceIndustriesBubbleProgressBars(); // Called on timer tick

/// Flying text functions
    void QueueUpFlyingText(int icon, std::string text, float x, float y);
    void QueueDownFlyingText(int icon, std::string text, float x, float y);
    void ProgressFlyingTexts();

/// Overworld drawing functions
    void DrawSpriteOnOverworld();

    /*
    void DrawPlacePopulationBubble();
    void DrawCitizensBubble();
    void DrawPlaceCaravanseraiBubble();

    void DrawPlaceSurplusBubble();
    void DrawPlaceDeficitBubble();

    ///void DrawInventoryBubbles();
    void DrawPlaceMarketBubble();
    void DrawPlaceIndustriesBubble();
    */
    void DrawFlyingTexts();
};

#endif // PLACE_H_INCLUDED
