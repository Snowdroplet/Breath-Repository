#include "UI.h"

/// UI
bool UIChangeDelay = false;

int activeUI = UI_OVERWORLD;
int previousActiveUI = UI_OVERWORLD;

int activeSubUI = SUBUI_OVERWORLD_NONE;
int previousActiveSubUI = SUBUI_OVERWORLD_NONE;


/// Bubble View
bool caravanInventoryBubbleOpen;
bool caravanTradeRecordsBubbleOpen;
bool caravanPathfindingBubbleOpen;

bool placePopulationBubbleOpen;
bool placeCaravanseraiBubbleOpen;
bool placeSurplusBubbleOpen;
bool placeDeficitBubbleOpen;
bool placeMarketBubbleOpen;
bool placeIndustriesBubbleOpen;

bool encyclopediaBubbleOpen;
