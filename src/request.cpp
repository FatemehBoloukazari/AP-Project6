#include "request.hpp"

void add_admin(vector <User*> &users)
{
    Admin* new_admin = new Admin("UT_account", "0", "UT_account");
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
}

void Request::handle_login(string id, string password)
{
    if (logged_in_user != NULL)
        throw PermissionDenied();
    bool user_exists = false;
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

void Request::handle_new_post(string _title, string _message)
{
    if (logged_in_user == NULL)
        throw PermissionDenied();
    logged_in_user->send_post(_title, _message);
}

void Request::handle_post_delete(int id)
{
    if (logged_in_user == NULL)
        throw PermissionDenied();
    logged_in_user->delete_post(id);
}

void Request::handle_view_personal_page(string id_str)
{
    if (!is_a_number(id_str))
        throw BadRequest();
    for (auto user : users)
    {
        if (user->get_id() == id_str)
        {
            user->show_personal_page();
            return;
        }
    }
    throw NotFound();
}

void Request::handle_connect_users(vector<string> &splited_command)
{
    string user_id = splited_command[4];
    if (!is_a_number(user_id))
        throw BadRequest();
    if (logged_in_user == NULL)
        throw PermissionDenied();
    if (logged_in_user->get_id() == "0")
        throw PermissionDenied();
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

void Request::handle_view_notifications()
{
    if (logged_in_user == NULL)
        throw PermissionDenied();
    if (logged_in_user->get_id() == "0")
        throw PermissionDenied();
    logged_in_user->view_notifications();
}

void Request::handle_view_post(string _id, string _post_id)
{
    if (logged_in_user == NULL)
        throw PermissionDenied();
    if (!is_a_number(_id) || !is_a_number(_post_id))
        throw BadRequest();
    for (auto user : users)
    {
        if (user->get_id() == _id)
        {
            user->view_post(stoi(_post_id));
            return;
        }
    }
    throw NotFound();
}
