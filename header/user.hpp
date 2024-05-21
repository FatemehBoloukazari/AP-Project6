#pragma once

#include "global_stuff.hpp"

class User
{
public:
    void login(string pass);
    string get_id() {return id;}
    void send_post(string _title, string _message);
    void delete_post(int _id);
    virtual void show_personal_page() = 0;
    void show_posts();
    void connect(User* user);
    //void add_notification();
    //void get_notifications();
protected:
    string password;
    string id;
    vector <Post*> posts;
    int last_post_id;
    vector <User*> connected_users;
    //vector <Notification*> notifications;
};