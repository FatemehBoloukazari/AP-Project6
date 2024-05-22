#include "utms.hpp"

UTMS::UTMS(string majors_file_path, string students_file_path, string courses_file_path, string professors_file_path)
{
    Request* new_request = new Request(majors_file_path, students_file_path, courses_file_path, professors_file_path);
    request = new_request;
}

CommandType get_command_type(string command)
{
    if (command == "POST")
        return POST;
    if (command == "DELETE")
        return DELETE;
    if (command == "GET")
        return GET;
    return NOT_COMMAND;
}


void UTMS::handle_login(vector <string> &splited_command)
{
    string id = EMPTY_STRING;
    string pass = EMPTY_STRING;
    for (int i = 3; i <= 5; i++)
    {
        if (splited_command[i] == "id" && id == EMPTY_STRING)
            id = splited_command[i + 1], i++;
        else if (splited_command[i] == "password" && pass == EMPTY_STRING)
            pass = splited_command[i + 1], i++;
        else
            throw BadRequest();
    }
    request->handle_login(id, pass);
}

void UTMS::handle_logout()
{
    request->handle_logout();
}

void UTMS::handle_new_post(vector <string> &splited_command)
{
    string title = EMPTY_STRING;
    string message = EMPTY_STRING;
    for (int i = 3; i < (int)splited_command.size(); i++)
    {
        if (splited_command[i] == "title" && title == EMPTY_STRING)
        {
            while (++i < (int)splited_command.size() && (title.empty() || title.back() != '\"'))
            {
                if (title != EMPTY_STRING)
                    title += ' ';
                title += splited_command[i];
            }
            i--;
        }
        else if (splited_command[i] == "message" && message == EMPTY_STRING)
        {
            while (++i < (int)splited_command.size() && (message.empty() || message.back() != '\"'))
            {
                if (message != EMPTY_STRING)
                    message += ' ';
                message += splited_command[i];
            }
            i--;
        }
        else
            throw BadRequest();
    }
    request->handle_new_post(title, message);
}

void UTMS::handle_connect_users(vector<string> &splited_command)
{
    request->handle_connect_users(splited_command);
}

void UTMS::handle_post_request(vector <string> &splited_command)
{
    if (splited_command[2] != "?")
        throw BadRequest();
    if (splited_command[1] == "login")
        handle_login(splited_command);
    else if (splited_command[1] == "logout")
        handle_logout();
    else if (splited_command[1] == "post")
        handle_new_post(splited_command);
    else if (splited_command[1] == "connect")
        handle_connect_users(splited_command);
    else
        throw BadRequest();
}

void UTMS::handle_post_delete(vector <string> &splited_command)
{
    if (splited_command[3] != "id")
        throw BadRequest();
    string id = splited_command[4];
    request->handle_post_delete(stoi(id));
}

void UTMS::handle_delete_request(vector <string> &splited_command)
{
    if (splited_command[2] != "?")
        throw BadRequest();
    if (splited_command[1] == "post")
        handle_post_delete(splited_command);
    else
        throw BadRequest();
}

void UTMS::handle_view_personal_page(vector <string> &splited_command)
{
    if (splited_command[3] != "id")
        throw BadRequest();
    string id = splited_command[4];
    request->handle_view_personal_page(id);
}

void UTMS::handle_view_notifications()
{
    request->handle_view_notifications();
}

void UTMS::handle_view_post(vector<string> &splited_command)
{
    string id = EMPTY_STRING;
    string post_id = EMPTY_STRING;
    for (int i = 3; i <= 5; i++)
    {
        if (splited_command[i] == "id" && id == EMPTY_STRING)
            id = splited_command[i + 1], i++;
        else if (splited_command[i] == "post_id" && post_id == EMPTY_STRING)
            post_id = splited_command[i + 1], i++;
        else
            throw BadRequest();
    }
    request->handle_view_post(id, post_id);
}

void UTMS::handle_get_request(vector <string> &splited_command)
{
    if (splited_command[2] != "?")
        throw BadRequest();
    if (splited_command[1] == "personal_page")
        handle_view_personal_page(splited_command);
    else if (splited_command[1] == "notification")
        handle_view_notifications();
    else if (splited_command[1] == "post")
        handle_view_post(splited_command);
    else
        throw BadRequest();
}

void UTMS::run()
{
    while (true)
    {
        string command;
        getline(cin, command);
        vector <string> splited_command = get_splited(command, ' ');
        CommandType command_type = get_command_type(splited_command[0]);
        switch (command_type)
        {
            case POST:
                try
                {
                    handle_post_request(splited_command);
                    cout << OK << endl; // I should probably move this to somewhere else
                }
                catch (BadRequest &ex)
                {
                    cerr << BAD_REQUEST_ERROR << endl;
                }
                catch (NotFound &ex)
                {
                    cerr << NOT_FOUND_ERROR << endl;
                }
                catch (PermissionDenied &ex)
                {
                    cerr << PERMISSION_DENIED_ERROR << endl;
                }
                break;
            case DELETE:
                try
                {
                    handle_delete_request(splited_command);
                    cout << OK << endl;
                }
                catch (BadRequest &ex)
                {
                    cerr << BAD_REQUEST_ERROR << endl;
                }
                catch (NotFound &ex)
                {
                    cerr << NOT_FOUND_ERROR << endl;
                }
                catch (PermissionDenied &ex)
                {
                    cerr << PERMISSION_DENIED_ERROR << endl;
                }
                break;
            case GET:
                try
                {
                    handle_get_request(splited_command);
                }
                catch (BadRequest &ex)
                {
                    cerr << BAD_REQUEST_ERROR << endl;
                }
                catch (NotFound &ex)
                {
                    cerr << NOT_FOUND_ERROR << endl;
                }
                catch (PermissionDenied &ex)
                {
                    cerr << PERMISSION_DENIED_ERROR << endl;
                }
                break;
            default:
                cerr << BAD_REQUEST_ERROR << endl;
                break;
        }
    }
}