#pragma once

#include "global_stuff.hpp"

class CourseOffer // ?
{
public:
    string get_name() {return "hello"/*course->name*/;}
private:
    int course_id;
    // Course* course;
    string professor_id;
    int capacity;
    //Time time;
    //Date exam_date;
    int class_number;
};