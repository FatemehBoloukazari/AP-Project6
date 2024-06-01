#include "request.hpp"

void add_admin(vector <User*> &users)
{
    Admin* new_admin = new Admin(ADMIN_NAME, ADMIN_ID, ADMIN_PASSWORD);
    for (auto user : users)
        new_admin->connect(user);
    users.push_back(new_admin);
}

Request::Request(string majors_file_path, string students_file_path, string courses_file_path, string professors_file_path)
{
    logged_in_user = NULL;
    read_majors_file(majors, majors_file_path);
    read_students_file(users,majors,  students_file_path);
    read_courses_file(courses, courses_file_path);
    read_professors_file(users, majors, professors_file_path);
    add_admin(users);
    last_course_offer_id = 0;
}

void Request::handle_login(string id, string password)
{
    if (logged_in_user != NULL)
        throw PermissionDenied();
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

void Request::handle_logout()
{
    if (logged_in_user == NULL)
        throw PermissionDenied();
    logged_in_user = NULL;
}

void Request::handle_new_post(string _title, string _message, string _image_address)
{
    if (logged_in_user == NULL)
        throw PermissionDenied();
    logged_in_user->send_post(_title, _message, _image_address);
}

void Request::handle_post_delete(string id)
{
    if (logged_in_user == NULL)
        throw PermissionDenied();
    if (!is_a_number(id) || id == ZERO)
        throw BadRequest();
    logged_in_user->delete_post(stoi(id));
}

vector <string> Request::handle_view_personal_page(string id_str)
{
    if (logged_in_user == NULL)
        throw PermissionDenied();
    if (!is_a_number(id_str))
        throw BadRequest();
    for (auto user : users)
    {
        if (user->get_id() == id_str)
        {
            vector <string> result;
            user->show_personal_page(result);
            return result;
        }
    }
    throw NotFound();
}

void Request::handle_connect_users(vector<string> &splited_command)
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

vector <string> Request::handle_view_notifications()
{
    if (logged_in_user == NULL)
        throw PermissionDenied();
    if (logged_in_user->get_id() == ADMIN_ID)
        throw PermissionDenied();
    vector <string> result;
    logged_in_user->view_notifications(result);
    return result;
}

vector <string> Request::handle_view_post(string _id, string _post_id)
{
    if (logged_in_user == NULL)
        throw PermissionDenied();
    if (!is_a_number(_id) || !is_a_number(_post_id) || _post_id == ZERO)
        throw BadRequest();
    for (auto user : users)
    {
        if (user->get_id() == _id)
        {
            vector <string> result;
            user->view_post(result, stoi(_post_id));
            return result;
        }
    }
    throw NotFound();
}

Professor* Request::find_professor_by_id(string id)
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

Course* Request::find_course_by_id(string id)
{
    for (auto course : courses)
    {
        if (course->get_id() == id)
            return course;
    }
    throw NotFound();
}

void Request::handle_course_offer(string course_id, string professor_id, string capacity, Time* time, Date* exam_date, string class_number)
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

vector <string> Request::handle_view_all_courses()
{
    if (logged_in_user == NULL)
        throw PermissionDenied();
    vector <string> result;
    if (course_offers.empty())
    {
        result.push_back(EMPTY);
        result.push_back(NEW_LINE);
        return result;
    }
    for (auto course_offer : course_offers)
        course_offer->show_course_overview(result);
    return result;
}

vector <string> Request::handle_view_course_details(string course_offer_id)
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
            vector <string> result;
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

void Request::handle_take_new_course(string _course_id)
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

void Request::handle_delete_taken_course(string _course_id)
{
    if (!is_a_student(logged_in_user))
        throw PermissionDenied();
    if (!is_a_number(_course_id) || _course_id == ZERO)
        throw BadRequest();
    int course_id = stoi(_course_id);
    Student* student = dynamic_cast<Student*> (logged_in_user);
    student->remove_course(course_id);
}

vector <string> Request::handle_view_taken_courses()
{
    if (!is_a_student(logged_in_user))
        throw PermissionDenied();
    vector <string> result;
    Student* student = dynamic_cast<Student*> (logged_in_user);
    student->view_taken_courses(result);
    return result;
}

void Request::handle_add_profile_photo(string _image_address)
{
    if (logged_in_user == NULL)
        throw PermissionDenied();
    logged_in_user->set_profile_photo(_image_address);
}