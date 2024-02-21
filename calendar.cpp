#include "calendar.h"

bool Calendar::hourChangeTick;
bool Calendar::dayChangeTick;

int Calendar::hourFrame;
int Calendar::hourOfTheDay;
int Calendar::dayOfTheWeek;
int Calendar::dayOfTheMonth;
int Calendar::monthOfTheYear;
int Calendar::year;

std::string Calendar::calendarText;

void Calendar::Initialize(int startHourOfDay, int startDayOfMonth, int startMonthOfYear, int startYear)
{
    hourChangeTick = false;
    dayChangeTick = false;

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


void Calendar::AdvanceHourFrame()
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

void Calendar::AdvanceHour()
{
    hourOfTheDay ++;
    if(hourOfTheDay >= HOURS_PER_DAY)
    {
        dayChangeTick = true;
        hourOfTheDay = 0;
        AdvanceDay();
    }

}

void Calendar::AdvanceDay()
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

void Calendar::AdvanceMonth()
{
    monthOfTheYear++;
    if(monthOfTheYear > LAST_MONTH_OF_YEAR)
    {
        monthOfTheYear = FIRST_MONTH_OF_YEAR;
        AdvanceYear();
    }
}

void Calendar::AdvanceYear()
{
    year++;
}

void Calendar::UpdateCalendarText()
{
    calendarText = std::to_string(hourOfTheDay) + "00h -- "
    + dayNames.at(dayOfTheWeek) + ", "
    + std::to_string(dayOfTheMonth) + " "
    + monthNames.at(monthOfTheYear) + " "
    + std::to_string(year);
}

void Calendar::DrawCalendar()
{
    AllegroCustom::AllegroCustom::string_al_draw_text(Resource::builtin8, COLKEY_TEXT, CALENDAR_TEXT_DRAW_X, CALENDAR_TEXT_DRAW_Y, ALLEGRO_ALIGN_RIGHT, calendarText);
}

