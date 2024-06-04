#include "ta_form.hpp"
#include "courseoffer.hpp"

void TAForm::show_ta_form_overview(vector<string> &result)
{
    result.push_back(to_string(id));
    result.push_back(TA_FORM_TITLE);
    result.push_back(course_offer->get_name());
    result.push_back(NEW_LINE);
}

void TAForm::show_ta_form_details(vector<string> &result)
{
    show_ta_form_overview(result);
    course_offer->show_course_details(result);
    result.push_back(message);
    result.push_back(NEW_LINE);
}
