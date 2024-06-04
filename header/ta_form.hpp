#pragma once

#include "global_stuff.hpp"
#include "post.hpp"

class CourseOffer;
class Student;

class TAForm : public Post
{
public:
    TAForm(CourseOffer *_course_offer, string _message, int new_post_id);
    virtual void show_post_overview(vector <string> &result);
    virtual void show_post_details(vector <string> &result);
    int get_num_of_ta_form_requests() {return (int)ta_requests.size();};
    void get_ta_form_requests(vector <vector <string>> &result);
    void handle_ta_requests_responeses(vector<Status> const responses);
    void add_new_ta_request(Student *student);
    bool have_min_semester_to_become_ta(Student *student);
private:
    CourseOffer *course_offer;
    vector <Student*> ta_requests;
};