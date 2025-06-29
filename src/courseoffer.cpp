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
    channel = new Channel();
}

string convert_time_to_string(Time *time)
{
    string ret = EMPTY_STRING;
    ret += time->get_day();
    ret += COLON;
    ret += to_string(time->get_start_time());
    ret += DASH;
    ret += to_string(time->get_end_time());
    return ret;
}

string convert_date_to_string(Date *date)
{
    string ret = EMPTY_STRING;
    ret += to_string(date->get_year());
    ret += SLASH;
    ret += to_string(date->get_month());
    ret += SLASH;
    ret += to_string(date->get_day());
    return ret;
}

void CourseOffer::show_course_overview(vector <vector <string>> &_result)
{
    vector <string> result;
    result.push_back(to_string(id));
    result.push_back(get_name());
    result.push_back(to_string(capacity));
    result.push_back(professor_name);
    _result.push_back(result);
}

void CourseOffer::show_course_details(vector <vector <string>> &_result)
{
    vector <string> result;
    result.push_back(to_string(id));
    result.push_back(get_name());
    result.push_back(to_string(capacity));
    result.push_back(professor_name);
    result.push_back(convert_time_to_string(time));
    result.push_back(convert_date_to_string(exam_date));
    result.push_back(to_string(class_number));
    _result.push_back(result);
}

bool CourseOffer::can_take(int semester, int major_id)
{
    if (course->have_allowed_major(major_id) && course->have_allowed_semester(semester))
        return true;
    return false;
}

void CourseOffer::add_channel_post(string author, string title, string message, string image_address)
{
    channel->add_post(author, title, message, image_address);
}

void CourseOffer::show_channel(vector <vector <string>> &result)
{
    show_course_details(result);
    channel->show_channel_posts(result);
}

void CourseOffer::view_post(vector <vector <string>> &result, int post_id)
{
    show_course_details(result);
    channel->view_post(result, post_id);
}