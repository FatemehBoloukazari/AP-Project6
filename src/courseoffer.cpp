#include "courseoffer.hpp"

CourseOffer::CourseOffer(Course *_course, string _professor_id, int _capacity, Time *_time, Date* _exam_date, int _class_number)
{
    course = _course;
    professor_id = _professor_id;
    capacity = _capacity;
    time = _time;
    exam_date = _exam_date;
    class_number = _class_number;
}
