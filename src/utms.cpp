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
    string str;
    string id, pass;
    for (int i = 3; i <= 5; i++)
    {
        if (splited_command[i] == "id")
            id = splited_command[i + 1], i++;
        else if (splited_command[i] == "password")
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

string get_post_text()
{
    string ret = "";
    string str;
    do
    {
        if (ret != "")
            ret += ' ';
        cin >> str;
        ret += str;
    } while (str.back() != '\"');
    return ret;
}

void UTMS::handle_new_post()
{
    string title, message;
    for (int i = 0; i < 2; i++)
    {
        string input_type;
        cin >> input_type;
        if (input_type == "title")
            title = get_post_text();
        else
            message = get_post_text();
    }
    request->handle_new_post(title, message);
}

void UTMS::handle_connect_users(vector<string> &splited_command)
{
    request->handle_connect_users(splited_command);
}

void UTMS::handle_post_request(vector <string> &splited_command)
{
    if (splited_command[1] == "login")
        handle_login(splited_command);
    else if (splited_command[1] == "logout")
        handle_logout();
    else if (splited_command[1] == "post")
        handle_new_post();
    else if (splited_command[1] == "connect")
        handle_connect_users(splited_command);
    else
        throw BadRequest();
}

void UTMS::handle_post_delete()
{
    string id_str;
    int id;
    cin >> id_str >> id;
    request->handle_post_delete(id);
}

void UTMS::handle_delete_request(vector <string> &splited_command)
{
    string command;
    cin >> command;
    string question_mark;
    cin >> question_mark;
    if (command == "post")
        handle_post_delete();
}

void UTMS::handle_view_personal_page()
{
    string id_str, id;
    cin >> id_str >> id;
    request->handle_view_personal_page(id);
}

void UTMS::handle_get_request(vector <string> &splited_command)
{
    string command;
    cin >> command;
    string question_mark;
    cin >> question_mark;
    if (command == "personal_page")
        handle_view_personal_page();
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
                handle_delete_request(splited_command);
                break;
            case GET:
                handle_get_request(splited_command);
                break;
            default:
                cerr << BAD_REQUEST_ERROR << endl;
                break;
        }
    }
}