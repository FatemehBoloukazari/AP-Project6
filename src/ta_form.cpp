#include "ta_form.hpp"
#include "courseoffer.hpp"

TAForm::TAForm(CourseOffer *_course_offer, string _message, int new_post_id)
{
    course_offer = _course_offer;
    message = _message;
    id = new_post_id;
}

void TAForm::show_post_overview(vector<string> &result)
{
    result.push_back(to_string(id));
    result.push_back(SPACE);
    result.push_back(TA_FORM_TITLE);
    result.push_back(course_offer->get_name());
    result.push_back(SPACE);
    result.push_back(COURSE);
    result.push_back(NEW_LINE);
}

void TAForm::show_post_details(vector<string> &result)
{
    show_post_overview(result);
    course_offer->show_course_details(result);
    result.push_back(message);
    result.push_back(NEW_LINE);
}
