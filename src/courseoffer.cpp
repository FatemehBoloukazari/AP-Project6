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

void CourseOffer::show_course_overview(vector <string> &result)
{
    result.push_back(to_string(id));
    result.push_back(SPACE);
    result.push_back(get_name());
    result.push_back(SPACE);
    result.push_back(to_string(capacity));
    result.push_back(SPACE);
    result.push_back(professor_name);
    result.push_back("\n");
}

void CourseOffer::show_course_details(vector <string> &result)
{
    result.push_back(to_string(id));
    result.push_back(SPACE);
    result.push_back(get_name());
    result.push_back(SPACE);
    result.push_back(to_string(capacity));
    result.push_back(SPACE);
    result.push_back(professor_name);
    result.push_back(SPACE);
    result.push_back(convert_time_to_string(time));
    result.push_back(SPACE);
    result.push_back(convert_date_to_string(exam_date));
    result.push_back(SPACE);
    result.push_back(to_string(class_number));
    result.push_back("\n");
}

bool CourseOffer::can_take(int semester, int major_id)
{
    if (course->have_allowed_major(major_id) && course->have_allowed_semester(semester))
        return true;
    return false;
}
