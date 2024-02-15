#ifndef BUBBLEVIEW_H_INCLUDED
#define BUBBLEVIEW_H_INCLUDED

#include <string>

#include <allegro5/allegro_primitives.h>

#include "display.h"
#include "tile.h"
#include "resource.h"

#include "encyclopediaindex.h"
#include "colorindex.h"

class Caravan;
class Place;

#include "being.h"
class Being;

struct BubbleView
{
    static Caravan* currentCaravan;
    static Place* currentPlace;
    static Being* currentBeing;

    static bool beingStatusBubbleOpen;
    static bool encyclopediaBubbleOpen;

    static constexpr float bubblePadding = Tile::WIDTH/4;
    static constexpr float bubbleCornerRadius = 8;

    /// Being status bubble
    static constexpr float beingStatusBubbleDrawX = Display::WIDTH*9/40;
    static constexpr float beingStatusBubbleDrawY = Display::HEIGHT*9/25;
    static constexpr float beingStatusBubbleWidth  = Tile::WIDTH*5;
    static constexpr float beingStatusBubbleBiographyPartitionHeight = 0;                                                        // Two text lines: Name, Hometown
    static constexpr float beingStatusBubbleStatsPartitionHeight = beingStatusBubbleBiographyPartitionHeight + Resource::TEXT_HEIGHT_12*2; // Three icons + bars: vitality, happiness, purpose
    static constexpr float beingStatusBubbleObjectivesPartitionHeight = beingStatusBubbleStatsPartitionHeight + Tile::HEIGHT*3;        // Three text lines: Objective A, B, C
    static constexpr float beingStatusBubbleHeight = beingStatusBubbleObjectivesPartitionHeight + Resource::TEXT_HEIGHT_12*3;


    static void Initialize()
    {
        currentCaravan = nullptr;
        currentPlace = nullptr;
        currentBeing = nullptr;

        beingStatusBubbleOpen = false;
        encyclopediaBubbleOpen = false;
    }

    /*
    static bool CaravanCrewBubbleNeedsUpdate(Caravan *c);
    static bool CaravanInventoryBubbleNeedsUpdate(Caravan *c);
    static bool CaravanPathfindingBubbleNeedsUpdate(Caravan *c);
    static bool CaravanTradeRecordsBubbleNeedsUpdate(Caravan *c);
    static bool CaravanAllBubblesNeedUpdate(Caravan *c);
    */

    static void OpenBeingStatusBubble(Being *b);
    static void CloseBeingStatusBubble();
    static void DrawBeingStatusBubble(Being *b);

    static void OpenEncyclopediaBubble(float x, float y, unsigned category, unsigned index);
    static void CloseEncyclopediaBubble();
    static void DrawEncyclopediaBubble();
};

/// Caravan Bubble

/*
const float caravanTravelViewBubbleDrawX = Display::WIDTH*10/40;
const float caravanTravelViewBubbleDrawY = Display::HEIGHT*24/40;
const float caravanTravelViewBubbleWidth = Tile::WIDTH*14;
const float caravanTravelViewBubbleHeight = Tile::HEIGHT*5;
*/

const std::string caravanCrewBubbleLabel = "Crew:";
const std::string caravanCrewBubbleEmptyText = "<No Crew>"; // Though this ought not to pop up for more than one tick, since the caravan should disband and delete.
const float caravanCrewBubbleDrawX = Display::WIDTH*1/40;
const float caravanCrewBubbleDrawY = Display::HEIGHT*1/25;
const float caravanCrewBubbleHeight = Tile::HEIGHT;

const std::string caravanInventoryBubbleLabel = "Cargo:";
const std::string caravanInventoryBubbleEmptyText = "<No cargo carried>";
const float caravanInventoryBubbleDrawX = Display::WIDTH*1/40;
const float caravanInventoryBubbleDrawY = Display::HEIGHT*4/25;
const float caravanInventoryBubbleRowSpacing = Resource::TEXT_HEIGHT_8;
const float caravanInventoryBubbleBaseCols = 7;
const float caravanInventoryBubbleBaseRows = 1;

const std::string caravanTradeRecordsBubbleLabel = "Trade Records:";
const std::string caravanTradeRecordsBubbleEmptyText = "<No records>";
const std::string caravanTradeRecordsBubbleNoTransactionText = "<No transaction>";
const float caravanTradeRecordsBubbleDrawX = Display::WIDTH* 1/40;
const float caravanTradeRecordsBubbleDrawY = Display::HEIGHT* 9/25;
const float caravanTradeRecordsBubbleRowSpacing = Resource::TEXT_HEIGHT_8;
const unsigned caravanTradeRecordsBubbleBaseRows = 1;
const float caravanTradeRecordsBubbleWidth = Tile::WIDTH*7;
const unsigned caravanTradeRecordsBubbleNumIconCols = 4;
const float caravanTradeRecordsBubblePlaceNameWidth = Tile::WIDTH*3;

const std::string caravanPathfindingBubbleLabel = "Pathfinding:";
const std::string caravanPathfindingBubbleEmptyText = "<No path>";
const float caravanPathfindingBubbleColSpacing = Tile::WIDTH;
const float caravanPathfindingBubbleRowSpacing = Resource::TEXT_HEIGHT_8;
const float caravanPathfindingBubbleDrawX = Display::WIDTH*1/40;
const float caravanPathfindingBubbleDrawY = Display::HEIGHT*22/25;
const unsigned caravanPathfindingBubbleBaseCols = 1;
const unsigned caravanPathfindingBubbleBaseRows = 1;
const float caravanPathfindingBubbleHeight = 2*Tile::WIDTH + caravanPathfindingBubbleRowSpacing;

/// Place Bubble
const std::string placePopulationBubbleLabel = "Population";
const std::string placePopulationBubbleEmptyText = "<None>";
const float placePopulationBubbleDrawX = Display::WIDTH*26/40;
const float placePopulationBubbleDrawY = Display::HEIGHT*1/25;
const int placePopulationBubbleBaseCols = 1;
const float placePopulationBubbleHeight = Tile::HEIGHT;

const std::string placeCaravanseraiLabel = "Caravanserai";
const std::string placeCaravanseraiEmptyText = "<Empty>";
const float placeCaravanseraiDrawX = Display::WIDTH*33/40;
const float placeCaravanseraiDrawY = Display::HEIGHT*14/25;
const unsigned placeCaravanseraiBaseCols = 6;
const unsigned placeCaravanseraiBaseRows = 1;

const std::string placeSurplusBubbleLabel = "Surplus";
const float placeSurplusBubbleDrawX = Display::WIDTH*33/40;
const float placeSurplusBubbleDrawY = Display::HEIGHT* 4/25;
const unsigned placeSurplusBubbleBaseCols = 1;
const unsigned placeSurplusBubbleBaseRows = 1;
const unsigned placeSurplusBubbleMaxRows = 8;

const std::string placeDeficitBubbleLabel = "Deficit";
const float placeDeficitBubbleDrawX = Display::WIDTH*37/40 - Tile::WIDTH/2;
const float placeDeficitBubbleDrawY = Display::HEIGHT*4/25;
const unsigned placeDeficitBubbleBaseCols = 1;
const unsigned placeDeficitBubbleBaseRows = 1;
const unsigned placeDeficitBubbleMaxRows = 8;

const std::string placeMarketBubbleLabel = "Market";
const std::string placeMarketBubbleEmptyText = "<No inventory>";
const float placeMarketBubbleDrawX       = Display::WIDTH*26/40;
const float placeMarketBubbleDrawY       = Display::HEIGHT* 4/25;
const float placeMarketBubbleRowSpacing  = Resource::TEXT_HEIGHT_8;
const unsigned placeMarketBubbleBaseCols = 6;
const unsigned placeMarketBubbleBaseRows = 1;

const std::string placeIndustriesBubbleLabel = "Local Industries";
const std::string placeIndustriesBubbleEmptyText = "<No industries>";
const float placeIndustriesBubbleDrawX = Display::WIDTH*26/40;
const float placeIndustriesBubbleDrawY = Display::HEIGHT*14/25;
const float placeIndustriesBubbleRowSpacing = 4; // Arbitrary gap
const float placeIndustriesBubbleWidth = Tile::WIDTH*6; //+ BubbleView::bubblePadding;
const float placeIndustriesBubbleProgressBarOffset = 2.5*Tile::WIDTH;
const float placeIndustriesBubbleProgressBarWidth = placeIndustriesBubbleWidth - placeIndustriesBubbleProgressBarOffset;

/// Encyclopedia bubble
extern int encyclopediaCurrentCategory;
extern int encyclopediaCurrentIndex;
extern std::string encyclopediaBubbleEntryName;
extern std::string encyclopediaBubbleEntryText;

const std::string encyclopediaBubbleLabel = "Encyclopedia";
const float encyclopediaBubbleWidth = Tile::WIDTH*8;

extern float encyclopediaBubbleDrawX;
extern float encyclopediaBubbleDrawY;
extern float encyclopediaBubbleHeight;

#endif // BUBBLEVIEW_H_INCLUDED
