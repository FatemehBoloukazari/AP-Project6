#pragma once

#include "global_stuff.hpp"
#include "user.hpp"
#include "time.hpp"
#include "courseoffer.hpp"
#include "ta_form.hpp"

class Professor : public User
{
public:
    Professor(string _id, string _name, int _major_id, string _major_str, string _position, string pass);
    virtual void show_user_details(vector <string> &result);
    int get_major_id() {return major_id;}
    bool time_intersects(Time *time);
    void add_course_offer(CourseOffer* new_course_offer);
    bool have_course_offer(CourseOffer* searching_course_offer);
    bool can_post_in_course_channel(CourseOffer* course_offer);
    void add_ta_form(CourseOffer *course_offer, string message);
private:
    int major_id;
    string major_str;
    string position;
    vector <CourseOffer*> courses;
};