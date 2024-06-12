#include "handlers.hpp"

LoginHandler::LoginHandler(System *_system)
{
    system = _system;
}

Response *LoginHandler::callback(Request *req)
{
    string id = req->getBodyParam("username");
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
    vector <string> user_data = system->get_user_data(req->getSessionId());
    context["user_type"] = user_data[0];
    context["id"] = user_data[1];
    context["name"] = user_data[2];
    context["profile_pic_address"] = user_data[3];
    if (context["user_type"] != ADMIN)
        context["major"] = user_data[4];
    return context;
}