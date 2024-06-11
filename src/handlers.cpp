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
        system->handle_login(id, pass);
        res = Response::redirect("/music");
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