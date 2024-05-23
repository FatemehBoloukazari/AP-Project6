#include "student.hpp"

Student::Student(string _id, string _name, int _major_id, string _major_str, int _semester, string _password)
{
    id = _id;
    name = _name;
    major_id = _major_id;
    major_str = _major_str;
    semester = _semester;
    password = _password;
    last_post_id = 0;
}

void Student::show_user_details()
{
    cout << name << ' ' << major_str << ' ' << semester << ' ';
    for (int i = 0; i < (int)courses.size(); i++)
    {
        if (i != 0)
            cout << ",";
        cout << courses[i]->get_name();
    }
    cout << endl;
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
    }
    courses.push_back(course_offer);
}
