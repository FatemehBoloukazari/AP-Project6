#pragma once

#include "global_stuff.hpp"
#include "post.hpp"

class CourseOffer;

class TAForm : public Post
{
public:
    TAForm(CourseOffer *_course_offer, string _message, int new_post_id);
    virtual void show_post_overview(vector <string> &result);
    virtual void show_post_details(vector <string> &result);
private:
    CourseOffer *course_offer;
};