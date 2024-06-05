#ifndef PROFESSOR_HPP
#define PROFESSOR_HPP

#include "global_stuff.hpp"
#include "user.hpp"
#include "time.hpp"
#include "courseoffer.hpp"
#include "ta_form.hpp"

class Professor : public User
{
public:
    Professor(string _id, string _name, int _major_id, string _major_str, string _position, string pass);
    virtual void show_user_details(vector <string> &result);
    int get_major_id() {return major_id;}
    bool time_intersects(Time *time);
    void add_course_offer(CourseOffer* new_course_offer);
    bool have_course_offer(CourseOffer* searching_course_offer);
    bool can_post_in_course_channel(CourseOffer* course_offer);
    void add_ta_form(CourseOffer *course_offer, string message);
    TAForm* find_ta_form_by_id(int post_id);
    void check_having_ta_form(int post_id);
    void show_number_of_ta_requests(vector <string> &result, int form_id);
    void get_ta_form_requests(vector <vector <string>> &result, int form_id);
    void handle_ta_requests_responeses(vector <Status> const responses, int form_id);
    void handle_new_ta_request(Student *student, int form_id);
private:
    int major_id;
    string major_str;
    string position;
    vector <CourseOffer*> courses;
};

#endif