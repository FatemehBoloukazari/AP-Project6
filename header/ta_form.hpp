#pragma once

#include "global_stuff.hpp"
#include "post.hpp"

class CourseOffer;

class TAForm : public Post
{
public:
    virtual void show_ta_form_overview(vector <string> &result);
    virtual void show_ta_form_details(vector <string> &result);
private:
    CourseOffer *course_offer;
};