#ifndef HANDLERS_HPP
#define HANDLERS_HPP

#include "system.hpp"
#include "../server/server.hpp"

class LoginHandler : public RequestHandler
{
public:
    LoginHandler(System* _system);
    Response* callback(Request*) override;
private:
    System* system;
};

class ProfileChangeHandler : public RequestHandler
{
public:
    ProfileChangeHandler(System *_system, Server *_server);
    Response* callback(Request*) override;
private:
    System* system;
    Server* server;
};

class MainPageHandler : public TemplateHandler
{
public:
    MainPageHandler(const string& filePath, System*);
    map<string, string> handle(Request* req) override;
private:
    System* system;
};

#endif