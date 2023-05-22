#include "calendar.h"

bool hourChangeTick = false;
bool dayChangeTick = false;

int hourFrame;
int hourOfTheDay;
int dayOfTheWeek;
int dayOfTheMonth;
int monthOfTheYear;
int year;

std::string calendarText;

void InitCalendar(int startHourOfDay, int startDayOfMonth, int startMonthOfYear, int startYear)
{
    hourChangeTick = false;

    hourFrame = 0;
    hourOfTheDay = startHourOfDay;
    if(hourOfTheDay >= HOURS_PER_DAY)
        hourOfTheDay = 0;

    dayOfTheMonth = startDayOfMonth;
    if(dayOfTheMonth > LAST_DAY_OF_MONTH || dayOfTheMonth < FIRST_DAY_OF_MONTH)
        dayOfTheMonth = FIRST_DAY_OF_MONTH;

    dayOfTheWeek = dayOfTheMonth%LAST_DAY_OF_WEEK;
    if(dayOfTheWeek > LAST_DAY_OF_WEEK || dayOfTheMonth < FIRST_DAY_OF_WEEK)
        dayOfTheWeek = FIRST_DAY_OF_WEEK;

    monthOfTheYear = startMonthOfYear;
    if(monthOfTheYear > LAST_MONTH_OF_YEAR || monthOfTheYear < FIRST_MONTH_OF_YEAR)
        monthOfTheYear = FIRST_MONTH_OF_YEAR;

    year = startYear;


}


void AdvanceHourFrame()
{
    hourFrame ++;
    if(hourFrame >= FRAMES_PER_HOUR)
    {
        hourChangeTick = true;
        hourFrame = 0;
        AdvanceHour();
    }
    else
    {
        hourChangeTick = false;
        dayChangeTick = false;
    }
}

void AdvanceHour()
{
    hourOfTheDay ++;
    if(hourOfTheDay >= HOURS_PER_DAY)
    {
        dayChangeTick = true;
        hourOfTheDay = 0;
        AdvanceDay();
    }

}

void AdvanceDay()
{
    dayOfTheWeek++;
    if(dayOfTheWeek > LAST_DAY_OF_WEEK)
    {
        dayOfTheWeek = FIRST_DAY_OF_WEEK;
    }

    dayOfTheMonth++;
    if(dayOfTheMonth > LAST_DAY_OF_MONTH)
    {
        dayOfTheMonth = FIRST_DAY_OF_MONTH;
        AdvanceMonth();
    }
}

void AdvanceMonth()
{
    monthOfTheYear++;
    if(monthOfTheYear > LAST_MONTH_OF_YEAR)
    {
        monthOfTheYear = FIRST_MONTH_OF_YEAR;
        AdvanceYear();
    }
}

void AdvanceYear()
{
    year++;
}

void UpdateCalendarText()
{
    calendarText = std::to_string(hourOfTheDay) + "00h -- "
    + dayNames.at(dayOfTheWeek) + ", "
    + std::to_string(dayOfTheMonth) + " "
    + monthNames.at(monthOfTheYear) + " "
    + std::to_string(year);
}

void DrawCalendar()
{
    string_al_draw_text(builtin, COL_BLACK, CALENDAR_TEXT_DRAW_X, CALENDAR_TEXT_DRAW_Y, ALLEGRO_ALIGN_RIGHT, calendarText);
}

