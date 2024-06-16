#include "handlers.hpp"

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
    if (!file.empty())
    {
        utils::writeToFile(file, address);
        server->get(url, new ShowImage(address));
    }
    else
        url = DEFAULT_PROFILE;
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
    system->handle_new_post(title, message, image_url);
    Response *res = Response::redirect("/mainpage");
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
        context["message_" + to_string(i)] = posts[i][1];
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
        //res = Response::redirect("/personal_page?id=" + req->getBodyParam(ID));
    }
    catch (NotFound &ex)
    {
        res = new Response(Response::Status::notFound);
        res->setBody(NOT_FOUND_ERROR);
    }
    
    // = Response::redirect("/personal_page?id=" + req->getBodyParam(ID));

    return res;
}
