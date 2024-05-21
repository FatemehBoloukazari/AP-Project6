#pragma once

#include "global_stuff.hpp"
#include "read_file.hpp"
#include "user.hpp"
#include "admin.hpp"
#include "student.hpp"

class Request
{
public:
    Request(string majors_file_path, string students_file_path, string courses_file_path, string professors_file_path);
    void handle_login(string id, string password);
    void handle_logout();
    void handle_new_post(string _title, string _message);
    void handle_post_delete(int id);
    void handle_view_personal_page(string id_str);
    void handle_connect_users(vector<string> &splited_command);
private:
    User *logged_in_user;
    vector <Course*> courses;
    vector <User*> users;
    vector <Major*> majors;
};