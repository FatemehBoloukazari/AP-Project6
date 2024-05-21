#pragma once

#include "global_stuff.hpp"

class Course
{
public:
    Course(int _id, string _name, int _credit, int pre, vector <int> ids);
    void get_course_details();
private:
    int id;
    string name;
    int credit;
    int prerequisites;
    vector <int> major_ids;
};