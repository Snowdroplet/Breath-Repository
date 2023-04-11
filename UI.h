#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include <string>

enum enumActiveUI
{
    UI_OVERWORLD,

    UI_PLACE,
    UI_BARTER,
    UI_SERVICE_SELECT,

    UI_TRAVEL,

    UI_CREW,
    UI_CREW_DETAILED,

    UI_CARGO,
    UI_MAP,
    UI_JOURNAL
};

/// Text ///
const int FONT_BUILTIN_H = 8;

/*
/// Being ///
const int BEING_PORTRAIT_W = 64;
const int BEING_PORTRAIT_H = 64;

/// Being Skills ///
const int BEING_SKILL_SQUARE_W = 32;
const int BEING_SKILL_SQUARE_H = 32;

/// Cargo ///
const int CARGO_W = 64;
const int CARGO_H = 64;
*/

/// Overworld ///

enum enumOverworldSubUI
{
    SUB_OVERWORLD_NONE = -1
};

enum enumOverworldTabs
{
    TAB_OVERWORLD_NONE = -1
};

/// Place ///

/*

enum enumPlaceSubUI
{
    SUB_PLACE_NONE = -1,
    //SUB_PLACE_DEPART_CONFIRMATION,
};

enum enumPlaceTabs
{
    TAB_PLACE_NONE = -1
};


const int UI_PLACE_NUM_NAMES = 3;
const int UI_PLACE_NAME_CENTRE_X = 320;
const int UI_PLACE_NAME_CENTRE_Y = 80;

const std::string UIPlaceNames[UI_PLACE_NUM_NAMES] =
{
    "Ericennes",
    "Keth Entweir",
    "Keth Keter"
};

const int UI_PLACE_NUM_BUTTONS = 5;
const int UI_PLACE_BUTTON_W = 100;
const int UI_PLACE_BUTTON_H = 35;
const int UI_PLACE_BUTTON_X = 500;
const int UI_PLACE_BUTTON_Y = 80;
const int UI_PLACE_BUTTON_CENTRE_X = UI_PLACE_BUTTON_X + UI_PLACE_BUTTON_W/2;
const int UI_PLACE_BUTTON_CENTRE_Y = UI_PLACE_BUTTON_Y + UI_PLACE_BUTTON_H/2;
const int UI_PLACE_BUTTON_Y_SPACING = 65;

const std::string UIPlaceButtonLabels[UI_PLACE_NUM_BUTTONS] =
{
    "Market",
    "Services",
    "People",
    "Journal",
    "Depart"
};

/// Barter ///

enum enumBarterSubUI
{
    SUB_BARTER_NONE = -1,
    SUB_BARTER_QUANTITY = 1
};

enum enumBarterTabs
{
    TAB_BARTER_NONE = -1,
    TAB_BARTER_ALL = 0,
    TAB_BARTER_VEGETABLE = 1,
    TAB_BARTER_ANIMAL = 2,
    TAB_BARTER_MINERAL = 3,
    TAB_BARTER_APPAREL = 4,
    TAB_BARTER_TOOLS = 5,
    TAB_BARTER_BOOKS = 6
};

const int UI_BARTER_NUM_TABS = 7;

const int UI_BARTER_TAB_W = 70;
const int UI_BARTER_TAB_H = 25;
const int UI_BARTER_TAB_X = 20;
const int UI_BARTER_TAB_Y = 20;
const int UI_BARTER_TAB_CENTRE_X = UI_BARTER_TAB_X + UI_BARTER_TAB_W/2;
const int UI_BARTER_TAB_CENTRE_Y = UI_BARTER_TAB_Y + UI_BARTER_TAB_H/2;
const int UI_BARTER_TAB_X_SPACING = UI_BARTER_TAB_W + 5;

const int UI_BARTER_INVENTORY_1_X = 25;
const int UI_BARTER_INVENTORY_1_Y = 50;

const int UI_BARTER_INVENTORY_2_X = 359;
const int UI_BARTER_INVENTORY_2_Y = 50;

const int UI_BARTER_INVENTORY_ROWS = 5;
const int UI_BARTER_INVENTORY_COLS = 4;

//const int UI_BARTER_QUANTITY_


const std::string UIBarterTabLabels[UI_BARTER_NUM_TABS] =
{
    "All", "Plant", "Mineral", "Beast", "Artificial", "Trade", "Travel"
};


/// Crew ///

enum enumCrewSubUI
{
    SUB_CREW_NONE = -1
                    //SUB_CREW_DETAILS
};

enum enumCrewTabs
{
    TAB_CREW_YOUR_CREW = 0,
    TAB_CREW_AVAILABLE = 1
};

const int UI_CREW_NUM_TABS = 2;
const int UI_CREW_TAB_W = 100;
const int UI_CREW_TAB_H = 35;
const int UI_CREW_TAB_X = 140;
const int UI_CREW_TAB_Y = 10;
const int UI_CREW_TAB_CENTRE_X = UI_CREW_TAB_X + UI_CREW_TAB_W/2;
const int UI_CREW_TAB_CENTRE_Y = UI_CREW_TAB_Y + UI_CREW_TAB_H/2;
const int UI_CREW_TAB_X_SPACING = 120;

const std::string UICrewTabLabels[UI_CREW_NUM_TABS] =
{
    "Your Crew",
    "Available"
};

const int UI_CREW_PORTRAIT_X = 20;
const int UI_CREW_PORTRAIT_Y = 50;
const int UI_CREW_PORTRAIT_Y_SPACING = 70;

const int UI_CREW_NAME_X = UI_CREW_PORTRAIT_X + BEING_PORTRAIT_W + 5;
const int UI_CREW_NAME_Y = UI_CREW_PORTRAIT_Y;
const int UI_CREW_NAME_Y_SPACING = UI_CREW_PORTRAIT_Y_SPACING;

const int UI_CREW_SKILL_SQUARE_X = UI_CREW_NAME_X;
const int UI_CREW_SKILL_SQUARE_Y = UI_CREW_PORTRAIT_Y + BEING_PORTRAIT_H/2;
const int UI_CREW_SKILL_SQUARE_Y_SPACING = UI_CREW_NAME_Y_SPACING;

const int UI_CREW_SKILL_VALUE_X_DISPLACEMENT = BEING_SKILL_SQUARE_W*3/4;
const int UI_CREW_SKILL_VALUE_Y_DISPLACEMENT = BEING_SKILL_SQUARE_H*3/4;
const int UI_CREW_SKILL_VALUE_X_SPACING = BEING_SKILL_SQUARE_W;
const int UI_CREW_SKILL_VALUE_Y_SPACING = UI_CREW_SKILL_SQUARE_Y_SPACING;

/// Crew Detailed ///

enum enumCrewDetailedSubUI
{
    SUB_CREW_DETAILED_NONE = -1
};

enum enumCrewDetailedTabs
{
    TAB_CREW_DETAILED_NONE = -1
};

const int UI_CREW_DETAILED_PORTRAIT_X = 320;
const int UI_CREW_DETAILED_PORTRAIT_Y = 120;

const int UI_CREW_DETAILED_NAME_X = UI_CREW_DETAILED_PORTRAIT_X;
const int UI_CREW_DETAILED_NAME_Y = UI_CREW_DETAILED_PORTRAIT_Y + BEING_PORTRAIT_H/2 + 10;

const int UI_CREW_DETAILED_SKILL_SQUARE_X = 50;
const int UI_CREW_DETAILED_SKILL_SQUARE_Y = UI_CREW_DETAILED_NAME_Y + 20;
const int UI_CREW_DETAILED_SKILL_SQUARE_Y_SPACING = BEING_SKILL_SQUARE_H + 16;

const int UI_CREW_DETAILED_SKILL_TEXT_X_DISPLACEMENT = BEING_SKILL_SQUARE_W + 5;
const int UI_CREW_DETAILED_SKILL_TEXT_Y_SPACING = UI_CREW_DETAILED_SKILL_SQUARE_Y_SPACING;

/// Travel ///

enum enumTravelSubUI
{
    SUB_TRAVEL_NONE = -1
};

enum enumTravelTab
{
    TAB_TRAVEL_NONE = -1
};

*/

#endif // UI_H_INCLUDED
