#ifndef CALENDAR_H_INCLUDED
#define CALENDAR_H_INCLUDED

#include <allegro5/allegro_font.h>

#include <string>
#include <map>

#include "allegrocustom.h"
#include "gamestate.h"
#include "resource.h"

#include "colorindex.h"

extern bool hourChangeTick;
extern bool dayChangeTick;

const int FRAMES_PER_HOUR = FPS*1; // *smaller value = faster
extern int hourFrame;

const int HOURS_PER_DAY = 24;
extern int hourOfTheDay;

const int FIRST_DAY_OF_WEEK = 1;
const int LAST_DAY_OF_WEEK = 7;
extern int dayOfTheWeek;

const int FIRST_DAY_OF_MONTH = 1;
const int LAST_DAY_OF_MONTH = 30;
extern int dayOfTheMonth;

const int FIRST_MONTH_OF_YEAR = 1;
const int LAST_MONTH_OF_YEAR = 12;
extern int monthOfTheYear;

extern int year;

extern std::string calendarText;

const std::map<int, std::string>dayNames =
{
    {1, "Sunday"},
    {2, "Monday"},
    {3, "Tuesday"},
    {4, "Wednesday"},
    {5, "Thursday"},
    {6, "Friday"},
    {7, "Saturday"}
};

const std::map<int, std::string>monthNames =
{
    {1, "January"},
    {2, "Febuary"},
    {3, "March"},
    {4, "April"},
    {5, "May"},
    {6, "June"},
    {7, "July"},
    {8, "August"},
    {9, "September"},
    {10, "October"},
    {11, "November"},
    {12, "December"}
};

const int CALENDAR_TEXT_DRAW_X = Display::WIDTH; // Right aligned
const int CALENDAR_TEXT_DRAW_Y = Display::HEIGHT - 8;

void InitCalendar(int startHour, int startDayOfMonth, int startMonthOfYear, int startYear);
void AdvanceHourFrame();
void AdvanceHour();
void AdvanceDay();
void AdvanceMonth();
void AdvanceYear();
void UpdateCalendarText();

void DrawCalendar();

#endif // CALENDAR_H_INCLUDED
