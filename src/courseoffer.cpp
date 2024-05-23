#include "courseoffer.hpp"

CourseOffer::CourseOffer(int _id, Course *_course, string _professor_name, int _capacity, Time *_time, Date* _exam_date, int _class_number)
{
    id = _id;
    course = _course;
    professor_name = _professor_name;
    capacity = _capacity;
    time = _time;
    exam_date = _exam_date;
    class_number = _class_number;
}

string convert_time_to_string(Time *time)
{
    string ret = EMPTY_STRING;
    ret += time->get_day();
    ret += ':';
    ret += to_string(time->get_start_time());
    ret += '-';
    ret += to_string(time->get_end_time());
    return ret;
}

string convert_date_to_string(Date *date)
{
    string ret = EMPTY_STRING;
    ret += to_string(date->get_year());
    ret += '/';
    ret += to_string(date->get_month());
    ret += '/';
    ret += to_string(date->get_day());
    return ret;
}

void CourseOffer::show_course_overview()
{
    cout << id << ' ' << get_name() << ' ' << capacity << ' ' << professor_name << endl;
}

void CourseOffer::show_course_details()
{
    cout << id << ' ' << get_name() << ' ' << capacity << ' ' << professor_name << ' ' << convert_time_to_string(time) << ' ' << convert_date_to_string(exam_date) << ' ' << class_number << endl;
}

bool CourseOffer::can_take(int semester, int major_id)
{
    if (course->have_allowed_major(major_id) && course->have_allowed_semester(semester))
        return true;
    return false;
}
