#pragma once

#include "global_stuff.hpp"
#include "user.hpp"
#include "courseoffer.hpp"

class Professor : public User
{
public:
    Professor(string _id, string _name, int _major_id, string _major_str, string _position, string pass);
    virtual void show_user_details();
private:
    int major_id;
    string major_str;
    string position;
    vector <CourseOffer*> courses;
};