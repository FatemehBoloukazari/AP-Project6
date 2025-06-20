#ifndef DATE_HPP
#define DATE_HPP

class Date
{
public:
    Date(int _year, int _month, int _day);
    int get_year() {return year;}
    int get_month() {return month;}
    int get_day() {return day;}
    bool intersects(Date* new_date);
private:
    int year;
    int month;
    int day;
};

#endif