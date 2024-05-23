#pragma once

#include "global_stuff.hpp"
#include "course.hpp"
#include "time.hpp"
#include "date.hpp"

class CourseOffer
{
public:
    CourseOffer(Course *_course, string _professor_id, int _capacity, Time *_time, Date *_exam_date, int _class_number);
    string get_name() {return course->get_name();}
    Time* get_time() {return time;}
private:
    Course* course;
    string professor_id;
    int capacity;
    Time *time;
    Date *exam_date;
    int class_number;
};