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
    void handle_post_request(vector <string> &splited_command);

    void handle_post_delete();
    void handle_delete_request(vector <string> &splited_command);

    void handle_view_personal_page();
    void handle_get_request(vector <string> &splited_command);
};