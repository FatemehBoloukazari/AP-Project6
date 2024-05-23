#pragma once

class Date
{
public:
    Date(int _year, int _month, int _day);
    int get_year() {return year;}
    int get_month() {return month;}
    int get_day() {return day;}
private:
    int year;
    int month;
    int day;
};