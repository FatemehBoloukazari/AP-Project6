#include "professor.hpp"

Professor::Professor(string _id, string _name, int _major_id, string _major_str, string _position, string pass)
{
    id = _id;
    name = _name;
    major_id = _major_id;
    major_str = _major_str;
    position = _position;
    password = pass;
    last_post_id = 0;
}

void Professor::show_user_details(vector <string> &result)
{
    result.push_back(name);
    result.push_back(SPACE);
    result.push_back(major_str);
    result.push_back(SPACE);
    result.push_back(position);
    result.push_back(SPACE);
    for (int i = 0; i < (int)courses.size(); i++)
    {
        if (i != 0)
            result.push_back(COMMA);
        result.push_back(courses[i]->get_name());
    }
    result.push_back(NEW_LINE);
}

bool Professor::time_intersects(Time *time)
{
    for (auto course_offer : courses)
    {
        Time* course_time = course_offer->get_time();
        if (course_time->intersects(time))
            return true;
    }
    return false;
}

void Professor::add_course_offer(CourseOffer *new_course_offer)
{
    courses.push_back(new_course_offer);
}

bool Professor::have_course_offer(CourseOffer *searching_course_offer)
{
    for (auto course_offer : courses)
        if (course_offer == searching_course_offer)
            return true;
    return false;
}

bool Professor::can_post_in_course_channel(CourseOffer *course_offer)
{
    return have_course_offer(course_offer);
}

void Professor::add_ta_form(CourseOffer *course_offer, string message)
{
    if (!have_course_offer(course_offer))
        throw PermissionDenied();
    TAForm* new_ta_form = new TAForm(course_offer, message, ++last_post_id);
    posts.push_back(new_ta_form);
    Notification *new_notification = new Notification(id, name, NEW_TA_FORM_NOTIFICATION);
    for (auto connected_user : connected_users)
        connected_user->add_notification(new_notification);
}