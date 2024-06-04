#pragma once

#include "global_stuff.hpp"

class Course
{
public:
    Course(string _id, string _name, int _credit, int pre, vector <int> ids);
    string get_name() {return name;}
    string get_id() {return id;}
    bool have_allowed_major(int major_id);
    bool have_allowed_semester(int semester);
    int get_min_semester() {return prerequisites;};
private:
    string id;
    string name;
    int credit;
    int prerequisites;
    vector <int> major_ids;
};