#include "date.hpp"

Date::Date(int _year, int _month, int _day)
{
    year = _year;
    month = _month;
    day = _day;
}

bool Date::intersects(Date *new_date)
{
    if (year != new_date->year)
        return false;
    if (month != new_date->month)
        return false;
    if (day != new_date->day)
        return false;
    return true;
}