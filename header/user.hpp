#pragma once

#include "global_stuff.hpp"
#include "notification.hpp"
#include "post.hpp"

class User
{
public:
    void login(string pass);
    string get_id() {return id;}
    void send_post(string _title, string _message);
    void delete_post(int _id);
    void show_personal_page();
    void show_posts();
    void connect(User* user);
    void add_notification(Notification *new_notification);
    void view_notifications();
    void view_post(int post_id);
    virtual void show_user_details() = 0;
protected:
    string name;
    string password;
    string id;
    vector <Post*> posts;
    int last_post_id;
    vector <User*> connected_users;
    vector <Notification*> notifications;
};