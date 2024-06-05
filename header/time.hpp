#ifndef TIME_HPP
#define TIME_HPP

#include "global_stuff.hpp"

class Time
{
public:
    Time(string _day, int _start_time, int _end_time);
    bool intersects(Time *time);
    string get_day() {return day;}
    int get_start_time() {return start_time;}
    int get_end_time() {return end_time;}
private:
    string day;
    int start_time;
    int end_time;
};

#endif