#include "student.hpp"

Student::Student(string _id, string _name, int _major_id, string _major_str, int _semester, string _password)
{
    id = _id;
    name = _name;
    major_id = _major_id;
    major_str = _major_str;
    semester = _semester;
    password = _password;
    profile_photo_address = DEFAULT_PROFILE;
    last_post_id = 0;
}

void Student::show_user_details(vector <vector <string>> &_result)
{
    vector <string> result;
    result.push_back(name);
    result.push_back(major_str);
    result.push_back(to_string(semester));
    for (int i = 0; i < (int)courses.size(); i++)
    {
        if (i != 0)
            result.push_back(COMMA);
        result.push_back(courses[i]->get_name());
    }
    _result.push_back(result);
}

void Student::take_course(CourseOffer *course_offer)
{
    if (!course_offer->can_take(semester, major_id))
        throw PermissionDenied();
    for (auto taken_course : courses)
    {
        Time *taken_time = taken_course->get_time();
        Time *new_time = course_offer->get_time();
        if (taken_time->intersects(new_time))
            throw PermissionDenied();
        Date* taken_date = taken_course->get_exam_date();
        Date* new_date = course_offer->get_exam_date();
        if (taken_date->intersects(new_date))
            throw PermissionDenied();
    }
    courses.push_back(course_offer);
    Notification *new_notification = new Notification(id, name, GET_COURSE_NOTIFICATION);
    for (auto connected_user : connected_users)
        connected_user->add_notification(new_notification);
}

void Student::remove_course(int course_id)
{
    for (int i = 0; i < (int)courses.size(); i++)
    {
        CourseOffer *course_offer = courses[i];
        if (course_offer->get_id() == course_id)
        {
            courses.erase(courses.begin() + i);
            Notification *new_notification = new Notification(id, name, DELETE_COURSE_NOTIFICATION);
            for (auto connected_user : connected_users)
                connected_user->add_notification(new_notification);
            return;
        }
    }
    throw NotFound();
}

void Student::view_taken_courses(vector <vector <string>> &result)
{
    if (courses.empty())
    {
        result.push_back({EMPTY});
        return;
    }
    for (auto course_offer : courses)
        course_offer->show_course_details(result);
}

bool Student::have_course_offer(CourseOffer *searching_course_offer)
{
    for (auto course_offer : courses)
        if (course_offer == searching_course_offer)
            return true;
    return false;
}

bool Student::can_post_in_course_channel(CourseOffer *searching_course_offer)
{
    for (auto course_offer : ta_courses)
        if (course_offer == searching_course_offer)
            return true;
    return false;
}

void Student::become_ta(CourseOffer *course_offer)
{
    ta_courses.push_back(course_offer);
}