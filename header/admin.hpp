#pragma once

#include "global_stuff.hpp"
#include "user.hpp"

class Admin : public User
{
public:
    Admin(string _name, string _id, string pass);
    virtual void show_user_details(vector <string> &result);
    virtual bool have_course_offer(CourseOffer *course_offer) {return false;};
private:
};