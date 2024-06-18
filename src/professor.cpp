#include "professor.hpp"

Professor::Professor(string _id, string _name, int _major_id, string _major_str, string _position, string pass)
{
    id = _id;
    name = _name;
    major_id = _major_id;
    major_str = _major_str;
    position = _position;
    password = pass;
    profile_photo_address = DEFAULT_PROFILE;
    last_post_id = 0;
}

void Professor::show_user_details(vector <vector<string>> &_result)
{
    vector <string> result;
    result.push_back(name);
    result.push_back(major_str);
    result.push_back(position);
    for (int i = 0; i < (int)courses.size(); i++)
    {
        if (i != 0)
            result.push_back(COMMA);
        result.push_back(courses[i]->get_name());
    }
    _result.push_back(result);
}

bool Professor::time_intersects(Time *time)
{
    for (auto course_offer : courses)
    {
        Time* course_time = course_offer->get_time();
        if (course_time->intersects(time))
            return true;
    }
    return false;
}

void Professor::add_course_offer(CourseOffer *new_course_offer)
{
    courses.push_back(new_course_offer);
}

bool Professor::have_course_offer(CourseOffer *searching_course_offer)
{
    for (auto course_offer : courses)
        if (course_offer == searching_course_offer)
            return true;
    return false;
}

bool Professor::can_post_in_course_channel(CourseOffer *course_offer)
{
    return have_course_offer(course_offer);
}

void Professor::add_ta_form(CourseOffer *course_offer, string message)
{
    if (!have_course_offer(course_offer))
        throw PermissionDenied();
    TAForm* new_ta_form = new TAForm(course_offer, message, ++last_post_id);
    posts.push_back(new_ta_form);
    Notification *new_notification = new Notification(id, name, NEW_TA_FORM_NOTIFICATION);
    for (auto connected_user : connected_users)
        connected_user->add_notification(new_notification);
}

TAForm* Professor::find_ta_form_by_id(int post_id)
{
    for (auto post : posts)
    {
        if (post->get_id() == post_id)
        {
            TAForm *ta_form = dynamic_cast<TAForm*> (post);
            if (ta_form == NULL)
                throw NotFound();
            return ta_form;
        }
    }
    return NULL;
}

void Professor::check_having_ta_form(int post_id)
{
    if (find_ta_form_by_id(post_id) == NULL)
        throw NotFound();
}

void Professor::show_number_of_ta_requests(vector <string> &result, int form_id)
{
    TAForm *ta_form = find_ta_form_by_id(form_id);
    int num_of_ta_form_requests = ta_form->get_num_of_ta_form_requests();
    result.push_back(to_string(num_of_ta_form_requests));
}

void Professor::get_ta_form_requests(vector<vector<string>> &result, int form_id)
{
    TAForm *ta_form = find_ta_form_by_id(form_id);
    ta_form->get_ta_form_requests(result);
}

void Professor::handle_ta_requests_responeses(vector<Status> const responses, int form_id)
{
    TAForm *ta_form = find_ta_form_by_id(form_id);
    ta_form->handle_ta_requests_responeses(responses);
    for (int i = 0; i < (int)posts.size(); i++)
    {
        if (posts[i]->get_id() == ta_form->get_id())
        {
            auto temp = posts[i];
            posts.erase(posts.begin() + i);
            delete temp;
            return;
        }
    }
}

void Professor::handle_new_ta_request(Student *student, int form_id)
{
    TAForm *ta_form = find_ta_form_by_id(form_id);
    if (ta_form == NULL)
        throw NotFound();
    if (!ta_form->have_min_semester_to_become_ta(student))
        throw PermissionDenied();
    ta_form->add_new_ta_request(student);
}

void Professor::get_user_data(vector<string> &result)
{
    result.push_back(PROFESSOR);
    result.push_back(get_id());
    result.push_back(get_name());
    result.push_back(get_profile_address());
    result.push_back(get_major_str());
    result.push_back(get_position());
}
