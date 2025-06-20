#ifndef COURSEOFFER_HPP
#define COURSEOFFER_HPP

#include "global_stuff.hpp"
#include "course.hpp"
#include "time.hpp"
#include "date.hpp"
#include "channel.hpp"

class CourseOffer
{
public:
    CourseOffer(int _id, Course *_course, string _professor_name, int _capacity, Time *_time, Date *_exam_date, int _class_number);
    string get_name() {return course->get_name();}
    int get_id() {return id;}
    Time* get_time() {return time;}
    void show_course_overview(vector <vector <string>> &result);
    void show_course_details(vector <vector <string>> &result);
    bool can_take(int semester, int major_id);
    Date* get_exam_date() {return exam_date;}
    bool have_allowed_major(int major_id) {return course->have_allowed_major(major_id);}
    void add_channel_post(string author, string title, string message, string image_address);
    void show_channel(vector <vector <string>> &result);
    void view_post(vector <vector <string>> &result, int post_id);
    int get_min_semester() {return course->get_min_semester();};
private:
    int id;
    Course* course;
    string professor_name;
    int capacity;
    Time *time;
    Date *exam_date;
    int class_number;
    Channel* channel;
};

#endif