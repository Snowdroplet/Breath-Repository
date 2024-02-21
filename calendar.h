#ifndef CALENDAR_H_INCLUDED
#define CALENDAR_H_INCLUDED

#include <allegro5/allegro_font.h>

#include <string>
#include <map>

#include "allegrocustom.h"

#include "timer.h"
#include "camera.h"

#include "resource.h"

#include "colorindex.h"

struct Calendar
{
    static bool hourChangeTick;
static bool dayChangeTick;

static constexpr int FRAMES_PER_HOUR = Timer::FPS*1; // *smaller value = faster
static int hourFrame;

static constexpr int HOURS_PER_DAY = 24;
static int hourOfTheDay;

static constexpr int FIRST_DAY_OF_WEEK = 1;
static constexpr int LAST_DAY_OF_WEEK = 7;
static int dayOfTheWeek;

static constexpr int FIRST_DAY_OF_MONTH = 1;
static constexpr int LAST_DAY_OF_MONTH = 30;
static int dayOfTheMonth;

static constexpr int FIRST_MONTH_OF_YEAR = 1;
static constexpr int LAST_MONTH_OF_YEAR = 12;
static int monthOfTheYear;

static int year;

static std::string calendarText;

static constexpr int CALENDAR_TEXT_DRAW_X = Display::WIDTH; // Right aligned
static constexpr int CALENDAR_TEXT_DRAW_Y = Display::HEIGHT - 8;

static void Initialize(int startHour, int startDayOfMonth, int startMonthOfYear, int startYear);
static void AdvanceHourFrame();
static void AdvanceHour();
static void AdvanceDay();
static void AdvanceMonth();
static void AdvanceYear();
static void UpdateCalendarText();

static void DrawCalendar();
};

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

#endif // CALENDAR_H_INCLUDED
