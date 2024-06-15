#include "handlers.hpp"

LoginHandler::LoginHandler(System *_system)
{
    system = _system;
}

Response *LoginHandler::callback(Request *req)
{
    string id = req->getBodyParam("id");
    string pass = req->getBodyParam("password");
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
    string file = req->getBodyParam("file");
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
