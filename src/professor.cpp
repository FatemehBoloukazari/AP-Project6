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

void Professor::show_user_details()
{
    cout << name << ' ' << major_str << ' ' << position << ' ';
    for (int i = 0; i < (int)courses.size(); i++)
    {
        if (i != 0)
            cout << ",";
        cout << courses[i]->get_name();
    }
    cout << endl;
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
