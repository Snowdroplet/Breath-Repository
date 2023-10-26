#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include <string>

/// UI
extern bool UIChangeDelay;

extern int activeUI;
extern int previousActiveUI;

extern int activeSubUI;
extern int previousActiveSubUI;

extern int activeTab;
extern int previousActiveTab;

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

/// Overworld ///

enum enumOverworldSubUI
{
    SUB_OVERWORLD_NONE = -1
};

enum enumOverworldTabs
{
    TAB_OVERWORLD_NONE = -1
};

#endif // UI_H_INCLUDED
