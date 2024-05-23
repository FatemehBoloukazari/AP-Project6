#include "time.hpp"

Time::Time(string _day, int _start_time, int _end_time)
{
    day = _day;
    start_time = _start_time;
    end_time = _end_time;
}

bool Time::intersects(Time *time)
{
    if (day != time->day)
        return false;
    if (start_time == time->start_time || end_time == time->end_time)
        return true;
    if (start_time < time->start_time && time->start_time < end_time)
        return true;
    if (time->start_time < start_time && start_time < time->end_time)
        return true;
    return false;
}
