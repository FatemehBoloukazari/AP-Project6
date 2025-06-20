#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "global_stuff.hpp"
#include "user.hpp"

class Admin : public User
{
public:
    Admin(string _name, string _id, string pass);
    virtual void show_user_details(vector <vector <string>> &result);
    bool have_course_offer(CourseOffer *course_offer) {return false;};
    bool can_post_in_course_channel(CourseOffer *course_offer) {return false;};
    virtual void get_user_data(vector <string> &result);
private:
};

#endif