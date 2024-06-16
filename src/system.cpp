#include "system.hpp"

void add_admin(vector <User*> &users)
{
    Admin* new_admin = new Admin(ADMIN_NAME, ADMIN_ID, ADMIN_PASSWORD);
    for (auto user : users)
        new_admin->connect(user);
    users.push_back(new_admin);
}

System::System(string majors_file_path, string students_file_path, string courses_file_path, string professors_file_path)
{
    logged_in_user = NULL;
    read_majors_file(majors, majors_file_path);
    read_students_file(users,majors,  students_file_path);
    read_courses_file(courses, courses_file_path);
    read_professors_file(users, majors, professors_file_path);
    add_admin(users);
    last_course_offer_id = 0;
}

void System::handle_login(string id, string password)
{
    for (auto user : users)
    {
        if (user->get_id() == id)
        {
            try
            {
                user->login(password);
                logged_in_user = user;
                return;
            }
            catch (PermissionDenied &ex)
            {
                throw;
            }
        }
    }
    throw NotFound();
}

void System::handle_logout()
{
    if (logged_in_user == NULL)
        throw PermissionDenied();
    logged_in_user = NULL;
}

void System::handle_new_post(string _title, string _message, string _image_address)
{
    if (logged_in_user == NULL)
        throw PermissionDenied();
    logged_in_user->send_post(_title, _message, _image_address);
}

void System::handle_post_delete(string id)
{
    if (logged_in_user == NULL)
        throw PermissionDenied();
    if (!is_a_number(id) || id == ZERO)
        throw BadRequest();
    logged_in_user->delete_post(stoi(id));
}

vector <vector <string>> System::handle_view_personal_page(string id_str)
{
    if (logged_in_user == NULL)
        throw PermissionDenied();
    if (!is_a_number(id_str))
        throw BadRequest();
    for (auto user : users)
    {
        if (user->get_id() == id_str)
        {
            vector <vector <string>> result;
            user->show_personal_page(result);
            return result;
        }
    }
    throw NotFound();
}

void System::handle_connect_users(vector<string> &splited_command)
{
    string user_id = splited_command[FIRST_DATA_INDEX + 1];
    if (logged_in_user == NULL)
        throw PermissionDenied();
    if (logged_in_user->get_id() == ADMIN_ID)
        throw PermissionDenied();
    if (!is_a_number(user_id) || user_id == ZERO)
        throw BadRequest();
    for (auto user : users)
    {
        if (user->get_id() == user_id)
        {
            user->connect(logged_in_user);
            logged_in_user->connect(user);
            return;
        }
    }
    throw NotFound();
}

vector <vector <string>> System::handle_view_notifications()
{
    if (logged_in_user == NULL)
        throw PermissionDenied();
    if (logged_in_user->get_id() == ADMIN_ID)
        throw PermissionDenied();
    vector <vector <string>> result;
    logged_in_user->view_notifications(result);
    return result;
}

vector <vector <string>> System::handle_view_post(string _id, string _post_id)
{
    if (logged_in_user == NULL)
        throw PermissionDenied();
    if (!is_a_number(_id) || !is_a_number(_post_id) || _post_id == ZERO)
        throw BadRequest();
    for (auto user : users)
    {
        if (user->get_id() == _id)
        {
            vector <vector <string>> result;
            user->view_post(result, stoi(_post_id));
            return result;
        }
    }
    throw NotFound();
}

Professor* System::find_professor_by_id(string id)
{
    for (auto user : users)
    {
        if (user->get_id() == id)
        {
            Professor* professor = dynamic_cast<Professor*> (user);
            if (professor == NULL)
                throw PermissionDenied();
            return professor;
        }
    }
    throw NotFound();
}

Course* System::find_course_by_id(string id)
{
    for (auto course : courses)
    {
        if (course->get_id() == id)
            return course;
    }
    throw NotFound();
}

void System::handle_course_offer(string course_id, string professor_id, string capacity, Time* time, Date* exam_date, string class_number)
{
    if (logged_in_user == NULL || logged_in_user->get_id() != ADMIN_ID)
        throw PermissionDenied();
    if (!is_a_number(course_id) || !is_a_number(professor_id) || !is_a_number(capacity) || !is_a_number(class_number))
        throw BadRequest();
    if (course_id == ZERO || professor_id == ZERO || capacity == ZERO || class_number == ZERO)
        throw BadRequest();
    Professor* professor = find_professor_by_id(professor_id);
    Course* course = find_course_by_id(course_id);
    int major_id = professor->get_major_id();
    if (!course->have_allowed_major(major_id))
        throw PermissionDenied();
    if (professor->time_intersects(time))
        throw PermissionDenied();
    string professor_name = professor->get_name();
    CourseOffer *new_course_offer = new CourseOffer(++last_course_offer_id, course, professor_name, stoi(capacity), time, exam_date, stoi(class_number));
    professor->add_course_offer(new_course_offer);
    course_offers.push_back(new_course_offer);
    Notification *new_notification = new Notification(professor_id, professor_name, NEW_COURSE_OFFERING_NOTIFICATION);
    for (auto user : users)
        user->add_notification(new_notification);
}

vector <vector <string>> System::handle_view_all_courses()
{
    if (logged_in_user == NULL)
        throw PermissionDenied();
    vector <vector <string>> result;
    if (course_offers.empty())
        return result;
    for (auto course_offer : course_offers)
        course_offer->show_course_details(result);
    return result;
}

vector <vector <string>> System::handle_view_course_details(string course_offer_id)
{
    if (logged_in_user == NULL)
        throw PermissionDenied();
    if (!is_a_number(course_offer_id) || course_offer_id == ZERO)
        throw BadRequest();
    int id = stoi(course_offer_id);
    for (auto course_offer : course_offers)
    {
        if (course_offer->get_id() == id)
        {
            vector <vector <string>> result;
            course_offer->show_course_details(result);
            return result;
        }
    }
    throw NotFound();
}

bool is_a_student(User* user)
{
    if (user == NULL)
        return false;
    Student* student = dynamic_cast<Student*> (user);
    if (student == NULL)
        return false;
    return true;
}

void System::handle_take_new_course(string _course_id)
{
    if (!is_a_student(logged_in_user))
        throw PermissionDenied();
    if (!is_a_number(_course_id) || _course_id == ZERO)
        throw BadRequest();
    int course_id = stoi(_course_id);
    Student* student = dynamic_cast<Student*> (logged_in_user);
    for (auto course_offer : course_offers)
    {
        if (course_offer->get_id() == course_id)
        {
            student->take_course(course_offer);
            return;
        }
    }
    throw NotFound();
}

void System::handle_delete_taken_course(string _course_id)
{
    if (!is_a_student(logged_in_user))
        throw PermissionDenied();
    if (!is_a_number(_course_id) || _course_id == ZERO)
        throw BadRequest();
    int course_id = stoi(_course_id);
    Student* student = dynamic_cast<Student*> (logged_in_user);
    student->remove_course(course_id);
}

vector <vector <string>> System::handle_view_taken_courses()
{
    if (!is_a_student(logged_in_user))
        throw PermissionDenied();
    vector <vector <string>> result;
    Student* student = dynamic_cast<Student*> (logged_in_user);
    student->view_taken_courses(result);
    return result;
}

void System::handle_add_profile_photo(string _image_address)
{
    if (logged_in_user == NULL)
        throw PermissionDenied();
    logged_in_user->set_profile_photo(_image_address);
}

CourseOffer* System::find_course_offer_by_id(int course_offer_id)
{
    for (auto course_offer : course_offers)
        if (course_offer->get_id() == course_offer_id)
            return course_offer;
    throw NotFound();
}

vector <vector <string>> System::handle_view_course_channel(string course_offer_id)
{
    if (logged_in_user == NULL)
        throw PermissionDenied();
    if (!is_a_number(course_offer_id) || course_offer_id == ZERO)
        throw BadRequest();
    CourseOffer *course_offer = find_course_offer_by_id(stoi(course_offer_id));
    if (!logged_in_user->have_course_offer(course_offer))
        throw PermissionDenied();
    vector <vector <string>> output;
    course_offer->show_channel(output);
    return output;
}

void System::handle_new_course_post(string course_offer_id_str, string title, string message, string image_address)
{
    if (logged_in_user == NULL || logged_in_user->get_id() == ADMIN_ID)
        throw PermissionDenied();
    if (!is_a_number(course_offer_id_str) || course_offer_id_str == ZERO)
        throw BadRequest();
    int course_offer_id = stoi(course_offer_id_str);
    CourseOffer *course_offer = find_course_offer_by_id(course_offer_id);
    if (!logged_in_user->can_post_in_course_channel(course_offer))
        throw PermissionDenied();
    string author = logged_in_user->get_name();
    course_offer->add_channel_post(author, title, message, image_address);
    for (auto user : users)
    {
        if (user == logged_in_user)
            continue;
        if (user->can_post_in_course_channel(course_offer) || user->have_course_offer(course_offer))
        {
            Notification *new_notification = new Notification(course_offer_id_str, course_offer->get_name(), NEW_COURSE_POST_NOTIFICATION);
            user->add_notification(new_notification);
        }
    }
}

vector <vector <string>> System::handle_view_course_post(string _id, string _post_id)
{
    if (logged_in_user == NULL)
        throw PermissionDenied();
    if (!is_a_number(_id) || !is_a_number(_post_id) || _post_id == ZERO)
        throw BadRequest();
    int id = stoi(_id);
    CourseOffer *course_offer = find_course_offer_by_id(id);
    if (!logged_in_user->can_post_in_course_channel(course_offer) && !logged_in_user->have_course_offer(course_offer))
        throw PermissionDenied();
    vector <vector <string>> result;
    course_offer->view_post(result, stoi(_post_id));
    return result;
}

bool is_a_professor(User *user)
{
    Professor *professor = dynamic_cast<Professor*> (user);
    if (professor == NULL)
        return false;
    return true;
}

void System::handle_new_ta_form(string course_offer_id, string message)
{
    if (logged_in_user == NULL)
        throw PermissionDenied();
    if (!is_a_number(course_offer_id) || course_offer_id == ZERO)
        throw BadRequest();
    Professor *professor = dynamic_cast<Professor*> (logged_in_user);
    if (!is_a_professor(logged_in_user))
        throw PermissionDenied();
    CourseOffer *course_offer = find_course_offer_by_id(stoi(course_offer_id));
    professor->add_ta_form(course_offer, message);
}

void System::check_close_ta_form_access(string post_id)
{
    if (logged_in_user == NULL)
        throw PermissionDenied();
    if (!is_a_number(post_id) || post_id == ZERO)
        throw PermissionDenied();
    if (!is_a_professor(logged_in_user))
        throw PermissionDenied();
    Professor *professor = dynamic_cast<Professor*> (logged_in_user);
    professor->check_having_ta_form(stoi(post_id));
}

vector <vector <string>> System::show_number_of_ta_requests(int form_id)
{
    vector <vector <string>> _result;
    vector <string> result;
    result.push_back(NUM_OF_TA_REQUESTS_MESSAGE_FIRST_PART);
    Professor *professor = dynamic_cast<Professor*> (logged_in_user);
    professor->show_number_of_ta_requests(result, form_id);
    result.push_back(NUM_OF_TA_REQUESTS_MESSAGE_SECOND_PART);
    _result.push_back(result);
    return _result;
}

vector<vector<string>> System::get_ta_form_requests(int form_id)
{
    vector <vector <string>> result;
    Professor *professor = dynamic_cast<Professor*> (logged_in_user);
    professor->get_ta_form_requests(result, form_id);
    return result;
}

void System::handle_ta_requests_responeses(vector<Status> const responses, int form_id)
{
    Professor *professor = dynamic_cast<Professor*> (logged_in_user);
    professor->handle_ta_requests_responeses(responses, form_id);
}

void System::handle_new_ta_request(string professor_id, string form_id)
{
    if (logged_in_user == NULL)
        throw PermissionDenied();
    if (!is_a_student(logged_in_user))
        throw PermissionDenied();
    Student *student = dynamic_cast<Student*> (logged_in_user);
    if (!is_a_number(professor_id) || professor_id == ZERO)
        throw BadRequest();
    if (!is_a_number(form_id) || form_id == ZERO)
        throw BadRequest();
    Professor *professor = NULL;
    for (auto user : users)
    {
        if (user->get_id() == professor_id)
        {
            Professor* cur_professor = dynamic_cast<Professor*> (user);
            if (cur_professor == NULL)
                throw NotFound();
            professor = cur_professor;
        }
    }
    if (professor == NULL)
        throw NotFound();
    professor->handle_new_ta_request(student, stoi(form_id));
}

User* System::find_user_by_id(string id)
{
    for (auto user : users)
        if (user->get_id() == id)
            return user;
    return NULL;
}

void System::set_logged_in_user(string id)
{
    logged_in_user = find_user_by_id(id);
    if (logged_in_user == NULL)
        throw NotFound();
}

vector<string> System::get_user_data() // ino virtual konam
{
    vector <string> result;
    if (logged_in_user->get_id() == "0")
    {
        result.push_back(ADMIN);
        result.push_back(logged_in_user->get_id());
        result.push_back(logged_in_user->get_name());
        result.push_back(logged_in_user->get_profile_address());
    }
    else if (is_a_student(logged_in_user))
    {
        result.push_back(STUDENT);
        result.push_back(logged_in_user->get_id());
        result.push_back(logged_in_user->get_name());
        result.push_back(logged_in_user->get_profile_address());
        Student *student = dynamic_cast<Student*> (logged_in_user);
        result.push_back(student->get_major_str());
        result.push_back(to_string(student->get_semester()));
    }
    else
    {
        result.push_back(PROFESSOR);
        result.push_back(logged_in_user->get_id());
        result.push_back(logged_in_user->get_name());
        result.push_back(logged_in_user->get_profile_address());
        Professor *professor = dynamic_cast<Professor*> (logged_in_user);
        result.push_back(professor->get_major_str());
        result.push_back(professor->get_position());
    }
    return result;
}

int System::get_logged_in_users_new_post_id()
{
    return logged_in_user->get_new_post_id();
}

vector<vector<string>> System::handle_get_posts()
{
    vector<vector<string>> result = logged_in_user->get_posts();
    return result;
}
