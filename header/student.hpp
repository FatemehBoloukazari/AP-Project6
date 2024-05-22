#pragma once

#include "global_stuff.hpp"
#include "user.hpp"
#include "courseoffer.hpp"

class Student : public User
{
public:
    Student(string _id, string _name, int _major_id, string _major_str, int _semester, string _password);
    virtual void show_user_details();
    //void take_course();
    //void remove_course();
    //void view_courses();
private:
    int major_id;
    string major_str;
    int semester;
    vector <CourseOffer*> courses;
};