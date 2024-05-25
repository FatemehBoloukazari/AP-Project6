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
    if (command == "PUT")
        return PUT;
    return NOT_COMMAND;
}


void UTMS::handle_login(vector <string> &splited_command)
{
    if (splited_command.size() != 7)
        throw BadRequest();
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

void UTMS::handle_logout(vector <string> &splited_command)
{
    if (splited_command.size() != 3)
        throw BadRequest();
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
            if (title == EMPTY_STRING || title.back() != '\"')
                throw BadRequest();
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
            if (message == EMPTY_STRING || message.back() != '\"')
                throw BadRequest();
            i--;
        }
        else
            throw BadRequest();
    }
    request->handle_new_post(title, message);
}

void UTMS::handle_connect_users(vector<string> &splited_command)
{
    if (splited_command.size() != 5)
        throw BadRequest();
    request->handle_connect_users(splited_command);
}

Time* convert_string_to_time(string time_str)
{
    bool reading_week_day = true;
    bool reading_start_time = false;
    string day = EMPTY_STRING;
    string start_time = EMPTY_STRING;
    string end_time = EMPTY_STRING;
    for (auto c : time_str)
    {
        if (c == ':')
        {
            reading_start_time = true;
            reading_week_day = false;
        }
        else if (c == '-')
        {
            reading_start_time = false;
        }
        else if (reading_week_day)
            day += c;
        else if (reading_start_time)
            start_time += c;
        else
            end_time += c;
    }
    Time* new_time = new Time(day, stoi(start_time), stoi(end_time));
    return new_time;
}

Date* convert_string_to_date(string date_str)
{
    bool reading_year = true;
    bool reading_month = false;
    string day = EMPTY_STRING;
    string year = EMPTY_STRING;
    string month = EMPTY_STRING;
    for (auto c : date_str)
    {
        if (c == '/')
        {
            if (reading_year)
            {
                reading_year = false;
                reading_month = true;
            }
            else
                reading_month = false;
        }
        else if (reading_year)
            year += c;
        else if (reading_month)
            month += c;
        else
            day += c;
    }
    Date* new_date = new Date(stoi(year), stoi(month), stoi(day));
    return new_date;
}

void UTMS::handle_course_offer(vector<string> &splited_command)
{
    if (splited_command.size() != 15)
        throw BadRequest();
    string course_id = EMPTY_STRING;
    string professor_id = EMPTY_STRING;
    string capacity = EMPTY_STRING;
    string time_str = EMPTY_STRING;
    string exam_date_str = EMPTY_STRING;
    string class_number = EMPTY_STRING;
    for (int i = 3; i < 14; i++)
    {
        if (splited_command[i] == "course_id" && course_id == EMPTY_STRING)
            course_id = splited_command[i + 1], i++;
        else if (splited_command[i] == "professor_id" && professor_id == EMPTY_STRING)
            professor_id = splited_command[i + 1], i++;
        else if (splited_command[i] == "capacity" && capacity == EMPTY_STRING)
            capacity = splited_command[i + 1], i++;
        else if (splited_command[i] == "time" && time_str == EMPTY_STRING)
            time_str = splited_command[i + 1], i++;
        else if (splited_command[i] == "exam_date" && exam_date_str == EMPTY_STRING)
            exam_date_str = splited_command[i + 1], i++;
        else if (splited_command[i] == "class_number" && class_number == EMPTY_STRING)
            class_number = splited_command[i + 1], i++;
        else
            throw BadRequest();
    }
    Time *time = convert_string_to_time(time_str);
    Date *exam_date = convert_string_to_date(exam_date_str);
    request->handle_course_offer(course_id, professor_id, capacity, time, exam_date, class_number);
}

void UTMS::handle_post_request(vector <string> &splited_command)
{
    if (splited_command[2] != "?")
        throw BadRequest();
    if (splited_command[1] == "login")
        handle_login(splited_command);
    else if (splited_command[1] == "logout")
        handle_logout(splited_command);
    else if (splited_command[1] == "post")
        handle_new_post(splited_command);
    else if (splited_command[1] == "connect")
        handle_connect_users(splited_command);
    else if (splited_command[1] == "course_offer")
        handle_course_offer(splited_command);
    else
        throw NotFound();
}

void UTMS::handle_post_delete(vector <string> &splited_command)
{
    if (splited_command.size() != 5)
        throw BadRequest();
    if (splited_command[3] != "id")
        throw BadRequest();
    string id = splited_command[4];
    request->handle_post_delete(stoi(id));
}

void UTMS::handle_delete_taken_course(vector<string> &splited_command)
{
    if (splited_command.size() != 5)
        throw BadRequest();
    if (splited_command[3] != "id")
        throw BadRequest();
    string id = splited_command[4];
    request->handle_delete_taken_course(id);
}

void UTMS::handle_delete_request(vector <string> &splited_command)
{
    if (splited_command[2] != "?")
        throw BadRequest();
    if (splited_command[1] == "post")
        handle_post_delete(splited_command);
    else if (splited_command[1] == "my_courses")
        handle_delete_taken_course(splited_command);
    else
        throw NotFound();
}

void UTMS::handle_view_personal_page(vector <string> &splited_command)
{
    if (splited_command.size() != 5)
        throw BadRequest();
    if (splited_command[3] != "id")
        throw BadRequest();
    string id = splited_command[4];
    request->handle_view_personal_page(id);
}

void UTMS::handle_view_notifications(vector <string> &splited_command)
{
    if (splited_command.size() != 3)
        throw BadRequest();
    request->handle_view_notifications();
}

void UTMS::handle_view_post(vector<string> &splited_command)
{
    if (splited_command.size() != 7)
        throw BadRequest();
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

void UTMS::handle_view_courses(vector<string> &splited_command)
{
    if (splited_command.size() != 5 && splited_command.size() != 3)
        throw BadRequest();
    if (splited_command.size() == 3)
    {
        request->handle_view_all_courses();
        return;
    }
    if (splited_command[3] != "id")
        throw BadRequest();
    request->handle_view_course_details(splited_command[4]);
}

void UTMS::handle_view_taken_courses(vector <string> &splited_command)
{
    if (splited_command.size() != 3)
        throw BadRequest();
    request->handle_view_taken_courses();
}

void UTMS::handle_get_request(vector <string> &splited_command)
{
    if (splited_command[2] != "?")
        throw BadRequest();
    if (splited_command[1] == "personal_page")
        handle_view_personal_page(splited_command);
    else if (splited_command[1] == "notification")
        handle_view_notifications(splited_command);
    else if (splited_command[1] == "post")
        handle_view_post(splited_command);
    else if (splited_command[1] == "courses")
        handle_view_courses(splited_command);
    else if (splited_command[1] == "my_courses")
        handle_view_taken_courses(splited_command);
    else
        throw NotFound();
}

void UTMS::handle_take_new_course(vector<string> &splited_command)
{
    if (splited_command[3] != "id")
        throw BadRequest();
    request->handle_take_new_course(splited_command[4]);
}

void UTMS::handle_put_request(vector<string> &splited_command)
{
    if (splited_command[2] != "?")
        throw BadRequest();
    if (splited_command[1] == "my_courses")
        handle_take_new_course(splited_command);
    else
        throw NotFound();
}

void UTMS::run()
{
    while (true)
    {
        string command;
        getline(cin, command);
        vector <string> splited_command = get_splited(command, ' ');
        if (splited_command.empty())
            continue;
        CommandType command_type = get_command_type(splited_command[0]);
        switch (command_type)
        {
            case POST:
                try
                {
                    handle_post_request(splited_command);
                    cout << OK << endl;
                }
                catch (BadRequest &ex)
                {
                    cout << BAD_REQUEST_ERROR << endl;
                }
                catch (NotFound &ex)
                {
                    cout << NOT_FOUND_ERROR << endl;
                }
                catch (PermissionDenied &ex)
                {
                    cout << PERMISSION_DENIED_ERROR << endl;
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
                    cout << BAD_REQUEST_ERROR << endl;
                }
                catch (NotFound &ex)
                {
                    cout << NOT_FOUND_ERROR << endl;
                }
                catch (PermissionDenied &ex)
                {
                    cout << PERMISSION_DENIED_ERROR << endl;
                }
                break;
            case GET:
                try
                {
                    handle_get_request(splited_command);
                }
                catch (BadRequest &ex)
                {
                    cout << BAD_REQUEST_ERROR << endl;
                }
                catch (NotFound &ex)
                {
                    cout << NOT_FOUND_ERROR << endl;
                }
                catch (PermissionDenied &ex)
                {
                    cout << PERMISSION_DENIED_ERROR << endl;
                }
                break;
            case PUT:
                try
                {
                    handle_put_request(splited_command);
                    cout << OK << endl;
                }
                catch (BadRequest &ex)
                {
                    cout << BAD_REQUEST_ERROR << endl;
                }
                catch (NotFound &ex)
                {
                    cout << NOT_FOUND_ERROR << endl;
                }
                catch (PermissionDenied &ex)
                {
                    cout << PERMISSION_DENIED_ERROR << endl;
                }
                break;
            default:
                cout << BAD_REQUEST_ERROR << endl;
                break;
        }
    }
}