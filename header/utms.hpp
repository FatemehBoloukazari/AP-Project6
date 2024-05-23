#pragma once

#include "global_stuff.hpp"
#include "professor.hpp"
#include "request.hpp"
#include "course.hpp"

class UTMS
{
public:
    UTMS(string, string, string, string);
    void run();
private:
    Request* request;
    void handle_login(vector <string> &splited_command);
    void handle_logout();
    void handle_new_post(vector <string> &splited_command);
    void handle_connect_users(vector <string> &splited_command);
    void handle_course_offer(vector <string> &splited_command);
    void handle_post_request(vector <string> &splited_command);

    void handle_post_delete(vector <string> &splited_command);
    void handle_delete_taken_course(vector <string> &splited_command);
    void handle_delete_request(vector <string> &splited_command);

    void handle_view_personal_page(vector <string> &splited_command);
    void handle_view_notifications();
    void handle_view_post(vector <string> &splited_command);
    void handle_view_courses(vector <string> &splited_command);
    void handle_view_taken_courses();
    void handle_get_request(vector <string> &splited_command);

    void handle_take_new_course(vector <string> &splited_command);
    void handle_put_request(vector <string> &splited_command);
};