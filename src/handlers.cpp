#include "handlers.hpp"

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

LoginHandler::LoginHandler(System *_system)
{
    system = _system;
}

Response *LoginHandler::callback(Request *req)
{
    string id = req->getBodyParam(ID);
    string pass = req->getBodyParam(PASSWORD);
    Response *res;
    try
    {
        res = new Response(Response::Status::ok);
        system->handle_login(id, pass);
        res->setSessionId(id);
    }
    catch (BadRequest &ex)
    {
        res = new Response(Response::Status::badRequest);
        res->setBody(BAD_REQUEST_ERROR);
    }
    catch (NotFound &ex)
    {
        res = new Response(Response::Status::notFound);
        res->setBody(NOT_FOUND_ERROR);
    }
    catch (PermissionDenied &ex)
    {
        res = new Response(Response::Status::forbidden);
        res->setBody(PERMISSION_DENIED_ERROR);
    }
    return res;
}

MainPageHandler::MainPageHandler(const string &filePath, System *_system) : TemplateHandler(filePath)
{
    system = _system;
}

map<string, string> MainPageHandler::handle(Request *req)
{
    map<string, string> context;
    system->set_logged_in_user(req->getSessionId());
    vector <string> user_data = system->get_user_data();
    context["user_type"] = user_data[0];
    context["id"] = user_data[1];
    context["name"] = user_data[2];
    context["profile_pic_address"] = user_data[3];
    if (context["user_type"] != ADMIN)
        context["major"] = user_data[4];
    return context;
}

ProfileChangeHandler::ProfileChangeHandler(System *_system, Server *_server)
{
    system = _system;
    server = _server;
}

Response *ProfileChangeHandler::callback(Request *req)
{
    string id = req->getSessionId();
    string address = IMAGE_ADDRESS + id + DOT + PNG;
    string url = IMAGE_URL + id + DOT + PNG;
    string file = req->getBodyParam(FILE_STR);
    string add_or_remove = req->getBodyParam("pressed_button");
    if (add_or_remove == "Remove Profile Photo")
        url = DEFAULT_PROFILE;
    else if (!file.empty())
    {
        utils::writeToFile(file, address);
        server->get(url, new ShowImage(address));
    }
    else
    {
        Response *res = Response::redirect("/mainpage");
        return res;
    }
    system->set_logged_in_user(id);
    system->handle_add_profile_photo(url);
    Response *res = Response::redirect("/mainpage");
    return res;
}

SendPostHandler::SendPostHandler(System *_system, Server *_server_ptr)
{
    system = _system;
    server = _server_ptr;
}

Response *SendPostHandler::callback(Request *req)
{
    string id = req->getSessionId();
    string title = req->getBodyParam(TITLE);
    string message = req->getBodyParam(MESSAGE);
    string image = req->getBodyParam(FILE_STR);
    system->set_logged_in_user(id);
    int new_post_id = system->get_logged_in_users_new_post_id();
    string image_address = IMAGE_ADDRESS + id + UNDER_SCORE + to_string(new_post_id) + DOT + PNG; // change this
    string image_url = IMAGE_URL + id + UNDER_SCORE + to_string(new_post_id) + DOT + PNG; // change this
    if (!image.empty())
    {
        utils::writeToFile(image, image_address);
        server->get(image_url, new ShowImage(image_address));
    }
    else
        image_url = EMPTY_STRING;

    Response *res;
    try
    {
        system->handle_new_post(title, message, image_url);
        res = new Response(Response::Status::ok);
        res->setBody("/mainpage");
    }
    catch (BadRequest &ex)
    {
        res = new Response(Response::Status::badRequest);
        res->setBody(BAD_REQUEST_ERROR);
    }
    catch (NotFound &ex)
    {
        res = new Response(Response::Status::notFound);
        res->setBody(NOT_FOUND_ERROR);
    }
    catch (PermissionDenied &ex)
    {
        res = new Response(Response::Status::forbidden);
        res->setBody(PERMISSION_DENIED_ERROR);
    }
    
    return res;
}

PersonalPageHandler::PersonalPageHandler(const string &file_path, System *_system) : TemplateHandler(file_path)
{
    system = _system;
}

map<string, string> PersonalPageHandler::handle(Request *req)
{
    map<string, string> context;
    system->set_logged_in_user(req->getQueryParam(ID));
    vector <string> user_data = system->get_user_data();
    context["user_type"] = user_data[0];
    context["name"] = user_data[2];
    context["profile_pic_address"] = user_data[3];
    if (context["user_type"] == STUDENT)
        context["semester"] = user_data[5];
    else if (context["user_type"] == PROFESSOR)
        context["position"] = user_data[5];
    vector <vector <string>> posts = system->handle_get_posts();
    context["num_of_posts"] = to_string(posts.size());
    for (int i = 0; i < (int)posts.size(); i++)
    {
        context["title_" + to_string(i)] = posts[i][0];
        string message = EMPTY_STRING;
        for (auto c : posts[i][1])
        {
            if (c == '\n')
                message += "<br>";
            else
                message += c;
        }
        context["message_" + to_string(i)] = message;
        if (posts[i].size() == NUM_OF_WITH_IMAGE_POST_DATAS)
            context["image_" + to_string(i)] = posts[i][2];
    }
    return context;
}

SearchUserHandler::SearchUserHandler(System *_system)
{
    system = _system;
}

Response *SearchUserHandler::callback(Request *req)
{
    Response *res;
    try
    {
        system->set_logged_in_user(req->getBodyParam(ID));
        res = new Response(Response::Status::ok);
        res->setBody("/personal_page?id=" + req->getBodyParam(ID));
    }
    catch (NotFound &ex)
    {
        res = new Response(Response::Status::notFound);
        res->setBody(NOT_FOUND_ERROR);
    }
    return res;
}

TakeCourseHandler::TakeCourseHandler(System *_system)
{
    system = _system;
}

Response *TakeCourseHandler::callback(Request *req)
{
    string id = req->getSessionId();
    string course_id = req->getBodyParam(COURSE_ID);
    system->set_logged_in_user(id);
    Response *res;
    try
    {
        res = new Response(Response::Status::ok);
        system->handle_take_new_course(course_id);
    }
    catch (BadRequest &ex)
    {
        res = new Response(Response::Status::badRequest);
        res->setBody(BAD_REQUEST_ERROR);
    }
    catch (NotFound &ex)
    {
        res = new Response(Response::Status::notFound);
        res->setBody(NOT_FOUND_ERROR);
    }
    catch (PermissionDenied &ex)
    {
        res = new Response(Response::Status::forbidden);
        res->setBody(PERMISSION_DENIED_ERROR);
    }
    return res;
}

RemoveCourseHandler::RemoveCourseHandler(System *_system)
{
    system = _system;
}

Response *RemoveCourseHandler::callback(Request *req)
{
    string id = req->getSessionId();
    string course_id = req->getBodyParam(COURSE_ID);
    system->set_logged_in_user(id);
    Response *res;
    try
    {
        res = new Response(Response::Status::ok);
        system->handle_delete_taken_course(course_id);
    }
    catch (BadRequest &ex)
    {
        res = new Response(Response::Status::badRequest);
        res->setBody(BAD_REQUEST_ERROR);
    }
    catch (NotFound &ex)
    {
        res = new Response(Response::Status::notFound);
        res->setBody(NOT_FOUND_ERROR);
    }
    catch (PermissionDenied &ex)
    {
        res = new Response(Response::Status::forbidden);
        res->setBody(PERMISSION_DENIED_ERROR);
    }
    return res;
}

ViewTakenCoursesHandler::ViewTakenCoursesHandler(const string &file_path, System *_system) : TemplateHandler(file_path)
{
    system = _system;
}

map<string, string> ViewTakenCoursesHandler::handle(Request *req)
{
    map<string, string> context;
    system->set_logged_in_user(req->getSessionId());
    vector <vector <string>> courses_data = system->handle_view_taken_courses();
    context["num_of_courses"] = to_string(courses_data.size());
    for (int i = 0; i < (int)courses_data.size(); i++)
    {
        context["course_id_" + to_string(i)] = courses_data[i][0];
        context["course_name_" + to_string(i)] = courses_data[i][1];
        context["capacity_" + to_string(i)] = courses_data[i][2];
        context["professor_name_" + to_string(i)] = courses_data[i][3];
        context["time_" + to_string(i)] = courses_data[i][4];
        context["exam_date_" + to_string(i)] = courses_data[i][5];
        context["class_number_" + to_string(i)] = courses_data[i][6];
    }
    return context;
}

OfferCourseHandler::OfferCourseHandler(System *_system)
{
    system = _system;
}

Response *OfferCourseHandler::callback(Request *req)
{
    string id = req->getSessionId();
    system->set_logged_in_user(id);
    string course_id = req->getBodyParam(COURSE_ID);
    string professor_id = req->getBodyParam(PROFESSOR_ID);
    string capacity = req->getBodyParam(CAPACITY);
    string time_str = req->getBodyParam(TIME);
    string exam_date_str = req->getBodyParam(EXAM_DATE);
    string class_number = req->getBodyParam(CLASS_NUMBER);
    Time *time = convert_string_to_time(time_str);
    Date *exam_date = convert_string_to_date(exam_date_str);
    Response *res;
    try
    {
        res = new Response(Response::Status::ok);
        system->handle_course_offer(course_id, professor_id, capacity, time, exam_date, class_number);
    }
    catch (BadRequest &ex)
    {
        res = new Response(Response::Status::badRequest);
        res->setBody(BAD_REQUEST_ERROR);
    }
    catch (NotFound &ex)
    {
        res = new Response(Response::Status::notFound);
        res->setBody(NOT_FOUND_ERROR);
    }
    catch (PermissionDenied &ex)
    {
        res = new Response(Response::Status::forbidden);
        res->setBody(PERMISSION_DENIED_ERROR);
    }
    return res;
}

LogoutHandler::LogoutHandler(System *_system)
{
    system = _system;
}

Response *LogoutHandler::callback(Request *req)
{
    Response *res = Response::redirect("/login");
    res->setSessionId(NO_USER_SESSION_ID);
    return res;
}

ViewCoursesHandler::ViewCoursesHandler(const string &file_path, System *_system) : TemplateHandler(file_path)
{
    system = _system;
}

map<string, string> ViewCoursesHandler::handle(Request *req)
{
    map<string, string> context;
    system->set_logged_in_user(req->getSessionId());
    vector <vector <string>> courses_data = system->handle_view_all_courses();
    context["num_of_courses"] = to_string(courses_data.size());
    for (int i = 0; i < (int)courses_data.size(); i++)
    {
        context["course_id_" + to_string(i)] = courses_data[i][0];
        context["course_name_" + to_string(i)] = courses_data[i][1];
        context["capacity_" + to_string(i)] = courses_data[i][2];
        context["professor_name_" + to_string(i)] = courses_data[i][3];
        context["time_" + to_string(i)] = courses_data[i][4];
        context["exam_date_" + to_string(i)] = courses_data[i][5];
        context["class_number_" + to_string(i)] = courses_data[i][6];
    }
    return context;
}