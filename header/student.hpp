#ifndef STUDENT_HPP
#define STUDENT_HPP

#include "global_stuff.hpp"
#include "user.hpp"
#include "courseoffer.hpp"

class Student : public User
{
public:
    Student(string _id, string _name, int _major_id, string _major_str, int _semester, string _password);
    virtual void show_user_details(vector <vector <string>> &result);
    void take_course(CourseOffer* course_offer);
    void remove_course(int course_id);
    void view_taken_courses(vector <vector <string>> &result);
    bool have_course_offer(CourseOffer* searching_course_offer);
    bool can_post_in_course_channel(CourseOffer* searching_course_offer);
    int get_semester() {return semester;}
    string get_major_str() {return major_str;}
    void become_ta(CourseOffer *course_offer);
private:
    int major_id;
    string major_str;
    int semester;
    vector <CourseOffer*> courses;
    vector <CourseOffer*> ta_courses;
};

#endif