#ifndef HANDLERS_HPP
#define HANDLERS_HPP

#include "system.hpp"
#include "global_stuff.hpp"
#include "../server/server.hpp"

class LoginHandler : public RequestHandler
{
public:
    LoginHandler(System* _system);
    Response* callback(Request*) override;
private:
    System* system;
};

class LogoutHandler : public RequestHandler
{
public:
    LogoutHandler(System* _system);
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

class SendPostHandler : public RequestHandler
{
public:
    SendPostHandler(System *_system, Server *_server_ptr);
    Response* callback(Request*) override;
private:
    System* system;
    Server* server;
};

class SearchUserHandler : public RequestHandler
{
public:
    SearchUserHandler(System* _system);
    Response* callback(Request*) override;
private:
    System *system;
};

class TakeCourseHandler : public RequestHandler
{
public:
    TakeCourseHandler(System *_system);
    Response* callback(Request*) override;
private:
    System *system;
};

class RemoveCourseHandler : public RequestHandler
{
public:
    RemoveCourseHandler(System *_system);
    Response* callback(Request*) override;
private:
    System *system;
};

class OfferCourseHandler : public RequestHandler
{
public:
    OfferCourseHandler(System *_system);
    Response* callback(Request*) override;
private:
    System *system;
};

class MainPageHandler : public TemplateHandler
{
public:
    MainPageHandler(const string& filePath, System*);
    map<string, string> handle(Request* req) override;
private:
    System* system;
};

class PersonalPageHandler : public TemplateHandler
{
public:
    PersonalPageHandler(const string& file_path, System* _system);
    map<string, string> handle(Request* req) override;
private:
    System* system;
};

class ViewTakenCoursesHandler : public TemplateHandler
{
public:
    ViewTakenCoursesHandler(const string& file_path, System* _system);
    map<string, string> handle(Request* req) override;
private:
    System* system;
};

class ViewCoursesHandler : public TemplateHandler
{
public:
    ViewCoursesHandler(const string& file_path, System* _system);
    map<string, string> handle(Request* req) override;
private:
    System* system;
};

#endif