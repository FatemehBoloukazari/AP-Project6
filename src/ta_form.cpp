#include "ta_form.hpp"
#include "courseoffer.hpp"
#include "student.hpp"

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

void TAForm::get_ta_form_requests(vector<vector<string>> &result)
{
    for (auto student : ta_requests)
    {
        vector <string> student_data;
        student_data.push_back(student->get_id());
        student_data.push_back(SPACE);
        student_data.push_back(student->get_name());
        student_data.push_back(SPACE);
        student_data.push_back(to_string(student->get_semester()));
        student_data.push_back(COLON_STR);
        student_data.push_back(SPACE);
        result.push_back(student_data);
    }
}

void TAForm::handle_ta_requests_responeses(vector<Status> const responses)
{
    for (int i = 0; i < (int)ta_requests.size(); i++)
    {
        if (responses[i] == ACCEPTED)
        {
            Notification *new_notification = new Notification(to_string(course_offer->get_id()), course_offer->get_name(), TA_REQUEST_ACCEPTED_NOTIFICATION);
            ta_requests[i]->add_notification(new_notification);
            ta_requests[i]->become_ta(course_offer);
        }
        else
        {
            Notification *new_notification = new Notification(to_string(course_offer->get_id()), course_offer->get_name(), TA_REQUEST_REJECTED_NOTIFICATION);
            ta_requests[i]->add_notification(new_notification);
        }
    }
}