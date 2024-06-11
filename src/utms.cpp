#include "utms.hpp"

UTMS::UTMS(string majors_file_path, string students_file_path, string courses_file_path, string professors_file_path)
{
    System* new_request = new System(majors_file_path, students_file_path, courses_file_path, professors_file_path);
    system = new_request;
}

CommandType get_command_type(string command)
{
    if (command == POST_STRING)
        return POST;
    if (command == DELETE_STRING)
        return DELETE;
    if (command == GET_STRING)
        return GET;
    if (command == PUT_STRING)
        return PUT;
    return NOT_COMMAND;
}

void print_output(vector <string> const &output)
{
    for (auto word : output)
        cout << word;
}

void UTMS::handle_login(vector <string> &splited_command)
{
    if (splited_command.size() != NUM_OF_POST_LOGIN_ENTRIES)
        throw BadRequest();
    string id = EMPTY_STRING;
    string pass = EMPTY_STRING;
    for (int i = FIRST_DATA_INDEX; i < NUM_OF_POST_LOGIN_ENTRIES - 1; i++)
    {
        if (splited_command[i] == ID && id == EMPTY_STRING)
            id = splited_command[i + 1], i++;
        else if (splited_command[i] == PASSWORD && pass == EMPTY_STRING)
            pass = splited_command[i + 1], i++;
        else
            throw BadRequest();
    }
    system->handle_login(id, pass);
}

void UTMS::handle_logout(vector <string> &splited_command)
{
    if (splited_command.size() != NUM_OF_POST_LOGOUT_ENTRIES)
        throw BadRequest();
    system->handle_logout();
}

void UTMS::handle_new_post(vector <string> &splited_command, bool post_type)
{
    string title = EMPTY_STRING;
    string message = EMPTY_STRING;
    string image_address = EMPTY_STRING;
    string course_offer_id = EMPTY_STRING;
    for (int i = FIRST_DATA_INDEX; i < (int)splited_command.size(); i++)
    {
        if (splited_command[i] == TITLE && title == EMPTY_STRING)
        {
            while (++i < (int)splited_command.size() && (title.empty() || title.back() != DOUBLE_QUOTATION))
            {
                if (title != EMPTY_STRING)
                    title += SPACE_CHAR;
                title += splited_command[i];
            }
            if (title == EMPTY_STRING || title.back() != DOUBLE_QUOTATION || title[0] != DOUBLE_QUOTATION)
                throw BadRequest();
            i--;
        }
        else if (splited_command[i] == MESSAGE && message == EMPTY_STRING)
        {
            while (++i < (int)splited_command.size() && (message.empty() || message.back() != DOUBLE_QUOTATION))
            {
                if (message != EMPTY_STRING)
                    message += SPACE_CHAR;
                message += splited_command[i];
            }
            if (message == EMPTY_STRING || message.back() != DOUBLE_QUOTATION || message[0] != DOUBLE_QUOTATION)
                throw BadRequest();
            i--;
        }
        else if (splited_command[i] == IMAGE && image_address == EMPTY_STRING && i != splited_command.size() - 1)
        {
            image_address = splited_command[i + 1];
            i++;
        }
        else if (splited_command[i] == ID && post_type == CHANNEL_POST && course_offer_id == EMPTY_STRING && i != splited_command.size() - 1)
        {
            course_offer_id = splited_command[i + 1];
            i++;
        }
        else
            throw BadRequest();
    }
    if (title == EMPTY_STRING || message == EMPTY_STRING)
        throw BadRequest();
    if (post_type == USER_POST)
        system->handle_new_post(title, message, image_address);
    else
    {
        if (course_offer_id == EMPTY_STRING)
            throw BadRequest();
        system->handle_new_course_post(course_offer_id, title, message, image_address);
    }
}

void UTMS::handle_connect_users(vector<string> &splited_command)
{
    if (splited_command.size() != NUM_OF_POST_CONNECT_ENTRIES)
        throw BadRequest();
    system->handle_connect_users(splited_command);
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
        if (c == COLON)
        {
            reading_start_time = true;
            reading_week_day = false;
        }
        else if (c == DASH)
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
        if (c == SLASH)
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
    if (splited_command.size() != NUM_OF_POST_COURSE_OFFER_ENTRIES)
        throw BadRequest();
    string course_id = EMPTY_STRING;
    string professor_id = EMPTY_STRING;
    string capacity = EMPTY_STRING;
    string time_str = EMPTY_STRING;
    string exam_date_str = EMPTY_STRING;
    string class_number = EMPTY_STRING;
    for (int i = FIRST_DATA_INDEX; i < NUM_OF_POST_COURSE_OFFER_ENTRIES - 1; i++)
    {
        if (splited_command[i] == COURSE_ID && course_id == EMPTY_STRING)
            course_id = splited_command[i + 1], i++;
        else if (splited_command[i] == PROFESSOR_ID && professor_id == EMPTY_STRING)
            professor_id = splited_command[i + 1], i++;
        else if (splited_command[i] == CAPACITY && capacity == EMPTY_STRING)
            capacity = splited_command[i + 1], i++;
        else if (splited_command[i] == TIME && time_str == EMPTY_STRING)
            time_str = splited_command[i + 1], i++;
        else if (splited_command[i] == EXAM_DATE && exam_date_str == EMPTY_STRING)
            exam_date_str = splited_command[i + 1], i++;
        else if (splited_command[i] == CLASS_NUMBER && class_number == EMPTY_STRING)
            class_number = splited_command[i + 1], i++;
        else
            throw BadRequest();
    }
    Time *time = convert_string_to_time(time_str);
    Date *exam_date = convert_string_to_date(exam_date_str);
    system->handle_course_offer(course_id, professor_id, capacity, time, exam_date, class_number);
}

void UTMS::handle_add_profile_photo(vector <string> &splited_command)
{
    if (splited_command.size() != NUM_OF_POST_PROFILE_PHOTO_ENTRIES)
        throw BadRequest();
    if (splited_command[FIRST_DATA_INDEX] != PHOTO)
        throw BadRequest();
    string image_address = splited_command[FIRST_DATA_INDEX + 1];
    system->handle_add_profile_photo(image_address);
}

void UTMS::handle_new_ta_form(vector<string> &splited_command)
{
    string message = EMPTY_STRING;
    string course_offer_id = EMPTY_STRING;
    for (int i = FIRST_DATA_INDEX; i < (int)splited_command.size(); i++)
    {
        if (splited_command[i] == MESSAGE && message == EMPTY_STRING)
        {
            while (++i < (int)splited_command.size() && (message.empty() || message.back() != DOUBLE_QUOTATION))
            {
                if (message != EMPTY_STRING)
                    message += SPACE_CHAR;
                message += splited_command[i];
            }
            if (message == EMPTY_STRING || message.back() != DOUBLE_QUOTATION || message[0] != DOUBLE_QUOTATION)
                throw BadRequest();
            i--;
        }
        else if (splited_command[i] == COURSE_ID && course_offer_id == EMPTY_STRING && i != splited_command.size() - 1)
        {
            course_offer_id = splited_command[i + 1];
            i++;
        }
        else
            throw BadRequest();
    }
    if (course_offer_id == EMPTY_STRING || message == EMPTY_STRING)
        throw BadRequest();
    system->handle_new_ta_form(course_offer_id, message);
}

void UTMS::handle_close_ta_form(vector<string> &splited_command)
{
    if (splited_command.size() != NUM_OF_POST_CLOSE_TA_FORM_ENTRIES)
        throw BadRequest();
    if (splited_command[FIRST_DATA_INDEX] != ID)
        throw BadRequest();
    string post_id = splited_command[FIRST_DATA_INDEX + 1];
    system->check_close_ta_form_access(post_id);
    int form_id = stoi(post_id);
    vector <string> output = system->show_number_of_ta_requests(form_id);
    print_output(output);
    vector <vector <string>> requests = system->get_ta_form_requests(form_id);
    vector <Status> responses;
    for (int i = 0; i < (int)requests.size();)
    {
        for (auto word : requests[i])
            cout << word;
        string status;
        getline(cin, status);
        if (status == ACCEPT)
        {
            responses.push_back(ACCEPTED);
            i++;
        }
        else if (status == REJECT)
        {
            responses.push_back(REJECTED);
            i++;
        }
    }
    system->handle_ta_requests_responeses(responses, form_id);
}

void UTMS::handle_new_ta_request(vector<string> &splited_command)
{
    if (splited_command.size() != NUM_OF_TA_REQUEST_ENTRIES)
        throw BadRequest();
    string professor_id = EMPTY_STRING;
    string form_id = EMPTY_STRING;
    for (int i = FIRST_DATA_INDEX; i < NUM_OF_TA_REQUEST_ENTRIES - 1; i++)
    {
        if (splited_command[i] == PROFESSOR_ID && professor_id == EMPTY_STRING)
            professor_id = splited_command[i + 1], i++;
        else if (splited_command[i] == FORM_ID && form_id == EMPTY_STRING)
            form_id = splited_command[i + 1], i++;
        else
            throw BadRequest();
    }
    if (professor_id == EMPTY_STRING || form_id == EMPTY_STRING)
        throw BadRequest();
    system->handle_new_ta_request(professor_id, form_id);
}

void UTMS::handle_post_request(vector <string> &splited_command)
{
    if (splited_command[QUESTION_MARK_INDEX] != QUESTION_MARK)
        throw BadRequest();
    if (splited_command[REQUEST_INDEX] == LOGIN)
        handle_login(splited_command);
    else if (splited_command[REQUEST_INDEX] == LOGOUT)
        handle_logout(splited_command);
    else if (splited_command[REQUEST_INDEX] == POST_STR)
        handle_new_post(splited_command, USER_POST);
    else if (splited_command[REQUEST_INDEX] == CONNECT)
        handle_connect_users(splited_command);
    else if (splited_command[REQUEST_INDEX] == COURSE_OFFER)
        handle_course_offer(splited_command);
    else if (splited_command[REQUEST_INDEX] == PROFILE_PHOTO)
        handle_add_profile_photo(splited_command);
    else if (splited_command[REQUEST_INDEX] == COURSE_POST)
        handle_new_post(splited_command, CHANNEL_POST);
    else if (splited_command[REQUEST_INDEX] == TA_FORM)
        handle_new_ta_form(splited_command);
    else if (splited_command[REQUEST_INDEX] == CLOSE_TA_FORM)
        handle_close_ta_form(splited_command);
    else if (splited_command[REQUEST_INDEX] == TA_REQUEST)
        handle_new_ta_request(splited_command);
    else
        throw NotFound();
}

void UTMS::handle_post_delete(vector <string> &splited_command)
{
    if (splited_command.size() != NUM_OF_DELETE_POST_ENTRIES)
        throw BadRequest();
    if (splited_command[FIRST_DATA_INDEX] != ID)
        throw BadRequest();
    string id = splited_command[FIRST_DATA_INDEX + 1];
    system->handle_post_delete(id);
}

void UTMS::handle_delete_taken_course(vector<string> &splited_command)
{
    if (splited_command.size() != NUM_OF_DELETE_COURSE_ENTRIES)
        throw BadRequest();
    if (splited_command[FIRST_DATA_INDEX] != ID)
        throw BadRequest();
    string id = splited_command[FIRST_DATA_INDEX + 1];
    system->handle_delete_taken_course(id);
}

void UTMS::handle_delete_request(vector <string> &splited_command)
{
    if (splited_command[QUESTION_MARK_INDEX] != QUESTION_MARK)
        throw BadRequest();
    if (splited_command[REQUEST_INDEX] == POST_STR)
        handle_post_delete(splited_command);
    else if (splited_command[REQUEST_INDEX] == MY_COURSES)
        handle_delete_taken_course(splited_command);
    else
        throw NotFound();
}

void UTMS::handle_view_personal_page(vector <string> &splited_command)
{
    if (splited_command.size() != NUM_OF_GET_PERSONAL_PAGE_ENTRIES)
        throw BadRequest();
    if (splited_command[FIRST_DATA_INDEX] != ID)
        throw BadRequest();
    string id = splited_command[FIRST_DATA_INDEX + 1];
    vector <string> output = system->handle_view_personal_page(id);
    print_output(output);
}

void UTMS::handle_view_notifications(vector <string> &splited_command)
{
    if (splited_command.size() != NUM_OF_GET_NOTIFICATION_ENTRIES)
        throw BadRequest();
    vector <string> output = system->handle_view_notifications();
    print_output(output);
}

void UTMS::handle_view_post(vector<string> &splited_command, bool post_type)
{
    if (splited_command.size() != NUM_OF_GET_POST_ENTRIES)
        throw BadRequest();
    string id = EMPTY_STRING;
    string post_id = EMPTY_STRING;
    for (int i = FIRST_DATA_INDEX; i < NUM_OF_GET_POST_ENTRIES - 1; i++)
    {
        if (splited_command[i] == ID && id == EMPTY_STRING)
            id = splited_command[i + 1], i++;
        else if (splited_command[i] == POST_ID && post_id == EMPTY_STRING)
            post_id = splited_command[i + 1], i++;
        else
            throw BadRequest();
    }
    vector <string> output;
    if (post_type == USER_POST)
        output = system->handle_view_post(id, post_id);
    else
        output = system->handle_view_course_post(id, post_id);
    print_output(output);
}

void UTMS::handle_view_courses(vector<string> &splited_command)
{
    if (splited_command.size() !=  NUM_OF_GET_A_COURSE_ENTRIES && splited_command.size() != NUM_OF_GET_ALL_COURSES_ENTRIES)
        throw BadRequest();
    if (splited_command.size() == NUM_OF_GET_ALL_COURSES_ENTRIES)
    {
        vector <string> output = system->handle_view_all_courses();
        print_output(output);
        return;
    }
    if (splited_command[FIRST_DATA_INDEX] != ID)
        throw BadRequest();
    vector <string> output = system->handle_view_course_details(splited_command[FIRST_DATA_INDEX + 1]);
    print_output(output);
}

void UTMS::handle_view_taken_courses(vector <string> &splited_command)
{
    if (splited_command.size() != NUM_OF_GET_MY_COURSES_ENTRIES)
        throw BadRequest();
    vector <string> output = system->handle_view_taken_courses();
    print_output(output);
}

void UTMS::handle_view_course_channel(vector<string> &splited_command)
{
    if (splited_command.size() != NUM_OF_GET_COURSE_CHANNEL_ENTRIES)
        throw BadRequest();
    if (splited_command[FIRST_DATA_INDEX] != ID)
        throw BadRequest();
    vector <string> output = system->handle_view_course_channel(splited_command[FIRST_DATA_INDEX + 1]);
    print_output(output);
}

void UTMS::handle_get_request(vector <string> &splited_command)
{
    if (splited_command[QUESTION_MARK_INDEX] != QUESTION_MARK)
        throw BadRequest();
    if (splited_command[REQUEST_INDEX] == PERSONAL_PAGE)
        handle_view_personal_page(splited_command);
    else if (splited_command[REQUEST_INDEX] == NOTIFICATION)
        handle_view_notifications(splited_command);
    else if (splited_command[REQUEST_INDEX] == POST_STR)
        handle_view_post(splited_command, USER_POST);
    else if (splited_command[REQUEST_INDEX] == COURSES)
        handle_view_courses(splited_command);
    else if (splited_command[REQUEST_INDEX] == MY_COURSES)
        handle_view_taken_courses(splited_command);
    else if (splited_command[REQUEST_INDEX] == COURSE_CHANNEL)
        handle_view_course_channel(splited_command);
    else if (splited_command[REQUEST_INDEX] == COURSE_POST)
        handle_view_post(splited_command, CHANNEL_POST);
    else
        throw NotFound();
}

void UTMS::handle_take_new_course(vector<string> &splited_command)
{
    if (splited_command[FIRST_DATA_INDEX] != ID)
        throw BadRequest();
    if (splited_command.size() != NUM_OF_PUT_MY_COURSES_ENTRIES)
        throw BadRequest();
    system->handle_take_new_course(splited_command[FIRST_DATA_INDEX + 1]);
}

void UTMS::handle_put_request(vector<string> &splited_command)
{
    if (splited_command[QUESTION_MARK_INDEX] != QUESTION_MARK)
        throw BadRequest();
    if (splited_command[REQUEST_INDEX] == MY_COURSES)
        handle_take_new_course(splited_command);
    else
        throw NotFound();
}

void UTMS::run()
{
    string command;
    while (getline(cin, command))
    {
        vector <string> splited_command = get_splited(command, SPACE_CHAR);
        if (splited_command.empty())
            continue;
        CommandType command_type = get_command_type(splited_command[MAIN_COMMAND_INDEX]);
        try
        {
            switch (command_type)
            {
                case POST:
                    handle_post_request(splited_command);
                    if (splited_command[REQUEST_INDEX] != CLOSE_TA_FORM)
                        cout << OK << endl;
                    break;
                case DELETE:
                    handle_delete_request(splited_command);
                    cout << OK << endl;
                    break;
                case GET:
                    handle_get_request(splited_command);
                    break;
                case PUT:
                    handle_put_request(splited_command);
                    cout << OK << endl;
                    break;
                default:
                    cout << BAD_REQUEST_ERROR << endl;
                    break;
            }
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
    }
}