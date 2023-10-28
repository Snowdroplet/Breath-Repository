#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include <string>

/// Tiles
const float SCREEN_W = 1280;
const float SCREEN_H = 800;

const float TILE_W = 32; // Standard width of sprites meant to be arranged in grids.
const float TILE_H = 32;

const float MINI_TILE_W = 16; // Width of half-sized versions of sprites meant to be arranged in grids.
const float MINI_TILE_H = 16;

/// Text
const unsigned BUILTIN_TEXT_HEIGHT = 8;

/// UI
extern bool UIChangeDelay;

enum enumActiveUI
{
    UI_OVERWORLD
};
extern int activeUI;
extern int previousActiveUI;

enum enumSubUI
{
    SUBUI_OVERWORLD_NONE = -1,

    SUBUI_ENCYCLOPEDIA = 0
};
extern int activeSubUI;
extern int previousActiveSubUI;

/// Bubble View
extern bool caravanInventoryBubbleOpen;
extern bool caravanTradeRecordsBubbleOpen;
extern bool caravanPathfindingBubbleOpen;

extern bool placePopulationBubbleOpen;
extern bool placeCaravanseraiBubbleOpen;
extern bool placeSurplusBubbleOpen;
extern bool placeDeficitBubbleOpen;
extern bool placeMarketBubbleOpen;
extern bool placeIndustriesBubbleOpen;

extern bool encyclopediaBubbleOpen;

/// Caravan Bubble
const float bubblePadding = TILE_W/4;
const float bubbleCornerRadius = 8;

const std::string caravanInventoryBubbleLabel = "Cargo:";
const std::string caravanInventoryBubbleEmptyText = "<No cargo carried>";
const float caravanInventoryBubbleDrawX = SCREEN_W*1/40;
const float caravanInventoryBubbleDrawY = SCREEN_H*8/40;
const float caravanInventoryBubbleRowSpacing = BUILTIN_TEXT_HEIGHT;
const float caravanInventoryBubbleBaseCols = 7;
const float caravanInventoryBubbleBaseRows = 1;

const std::string caravanTradeRecordsBubbleLabel = "Trade Records:";
const std::string caravanTradeRecordsBubbleEmptyText = "<No records>";
const std::string caravanTradeRecordsBubbleNoTransactionText = "<No transaction>";
const float caravanTradeRecordsBubbleDrawX = SCREEN_W*1/40;
const float caravanTradeRecordsBubbleDrawY = SCREEN_H*14/40;
const float caravanTradeRecordsBubbleRowSpacing = BUILTIN_TEXT_HEIGHT;
const unsigned caravanTradeRecordsBubbleBaseRows = 1;
const float caravanTradeRecordsBubbleWidth = TILE_W*7;
const unsigned caravanTradeRecordsBubbleNumIconCols = 4;
const float caravanTradeRecordsBubblePlaceNameWidth = TILE_W*3;


const std::string caravanPathfindingBubbleLabel = "Pathfinding:";
const std::string caravanPathfindingBubbleEmptyText = "<No path>";
const float caravanPathfindingBubbleColSpacing = TILE_W;
const float caravanPathfindingBubbleRowSpacing = BUILTIN_TEXT_HEIGHT;
const float caravanPathfindingBubbleDrawX = SCREEN_W*1/40;
const float caravanPathfindingBubbleDrawY = SCREEN_H*35/40;
const unsigned caravanPathfindingBubbleBaseCols = 1;
const unsigned caravanPathfindingBubbleBaseRows = 1;

/// Place Bubble
const std::string placePopulationBubbleLabel = "Population";
const std::string placePopulationBubbleEmptyText = "<None>";
const float placePopulationBubbleDrawX = SCREEN_W*26/40;
const float placePopulationBubbleDrawY = SCREEN_H*4/40;
const int placePopulationBubbleBaseCols = 1;
const float placePopulationBubbleHeight = TILE_H;

const std::string placeCaravanseraiLabel = "Caravanserai";
const std::string placeCaravanseraiEmptyText = "<Empty>";
const float placeCaravanseraiDrawX = SCREEN_W*33/40;
const float placeCaravanseraiDrawY = SCREEN_H*24/40;
const unsigned placeCaravanseraiBaseCols = 6;
const unsigned placeCaravanseraiBaseRows = 1;

const std::string placeSurplusBubbleLabel = "Surplus";
const float placeSurplusBubbleDrawX = SCREEN_W*33/40;
const float placeSurplusBubbleDrawY = SCREEN_H* 8/40;
const unsigned placeSurplusBubbleBaseCols = 1;
const unsigned placeSurplusBubbleBaseRows = 1;
const unsigned placeSurplusBubbleMaxRows = 8;

const std::string placeDeficitBubbleLabel = "Deficit";
const float placeDeficitBubbleDrawX = SCREEN_W*37/40 - TILE_W/2;
const float placeDeficitBubbleDrawY = SCREEN_H*8/40;
const unsigned placeDeficitBubbleBaseCols = 1;
const unsigned placeDeficitBubbleBaseRows = 1;
const unsigned placeDeficitBubbleMaxRows = 8;

const std::string placeMarketBubbleLabel = "Market";
const std::string placeMarketBubbleEmptyText = "<No inventory>";
const float placeMarketBubbleDrawX       = SCREEN_W*26/40;
const float placeMarketBubbleDrawY       = SCREEN_H* 8/40;
const float placeMarketBubbleRowSpacing  = BUILTIN_TEXT_HEIGHT;
const unsigned placeMarketBubbleBaseCols = 6;
const unsigned placeMarketBubbleBaseRows = 1;

const std::string placeIndustriesBubbleLabel = "Local Industries";
const std::string placeIndustriesBubbleEmptyText = "<No industries>";
const float placeIndustriesBubbleDrawX = SCREEN_W*26/40;
const float placeIndustriesBubbleDrawY = SCREEN_H*24/40;
const float placeIndustriesBubbleRowSpacing = 4; // Arbitrary gap
const float placeIndustriesBubbleWidth = TILE_W*6; //+ bubblePadding;
const float placeIndustriesBubbleProgressBarOffset = 2.5*TILE_W;
const float placeIndustriesBubbleProgressBarWidth = placeIndustriesBubbleWidth - placeIndustriesBubbleProgressBarOffset;

/// Encyclopedia bubble


const std::string encyclopediaBubbleLabel = "Encyclopedia";
const float encyclopediaBubbleDrawX = SCREEN_W*10/40;
const float encyclopediaBubbleDrawY = SCREEN_H* 8/40;

const float encyclopediaBubbleIndexTabWidth = TILE_W*4;
const float encyclopediaBubbleIndexTabHeight = TILE_H;
const float encyclopediaBubbleIndexPartitionX = encyclopediaBubbleDrawX;
const float encyclopediaBubbleIndexPartitionY = encyclopediaBubbleDrawY;

const float encyclopediaBubbleCategoriesTabWidth = TILE_W*4;
const float encyclopediaBubbleCategoriesTabHeight = TILE_H;
const float encyclopediaBubbleCategoriesPartitionX = encyclopediaBubbleDrawX;
const float encyclopediaBubbleCategoriesPartitionY = encyclopediaBubbleDrawY - TILE_H;

const float encyclopediaBubbleEntryPartitionWidth = TILE_W*20;
const float encyclopediaBubbleEntryPartitionHeight = TILE_H*15;
const float encyclopediaBubbleEntryPartitionX = encyclopediaBubbleDrawX + encyclopediaBubbleIndexTabWidth + TILE_W;
const float encyclopediaBubbleEntryPartitionY = encyclopediaBubbleDrawY + TILE_H;


#endif // UI_H_INCLUDED
