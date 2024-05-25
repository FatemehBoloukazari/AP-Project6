#pragma once

#include "global_stuff.hpp"
#include "course.hpp"
#include "time.hpp"
#include "date.hpp"

class CourseOffer
{
public:
    CourseOffer(int _id, Course *_course, string _professor_name, int _capacity, Time *_time, Date *_exam_date, int _class_number);
    string get_name() {return course->get_name();}
    int get_id() {return id;}
    Time* get_time() {return time;}
    void show_course_overview(vector <string> &result);
    void show_course_details(vector <string> &result);
    bool can_take(int semester, int major_id);
private:
    int id;
    Course* course;
    string professor_name;
    int capacity;
    Time *time;
    Date *exam_date;
    int class_number;
};