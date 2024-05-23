#pragma once

#include "global_stuff.hpp"

class Time
{
public:
    Time(string _day, int _start_time, int _end_time);
    bool intersects(Time *time);
private:
    string day;
    int start_time;
    int end_time;
};