#pragma once

#include "global_stuff.hpp"
#include "notification.hpp"
#include "post.hpp"
#include "courseoffer.hpp"

class User
{
public:
    void login(string pass);
    string get_id() {return id;}
    string get_name() {return name;}
    void send_post(string _title, string _message, string _image_address);
    void delete_post(int _id);
    void show_personal_page(vector <string> &result);
    void show_posts(vector <string> &result);
    void connect(User* user);
    void add_notification(Notification *new_notification);
    void view_notifications(vector <string> &result);
    void view_post(vector <string> &result, int post_id);
    virtual void show_user_details(vector <string> &result) = 0;
    void set_profile_photo(string _image_address);
    virtual bool have_course_offer(CourseOffer *course_offer) = 0;
protected:
    string name;
    string password;
    string id;
    string profile_photo_address;
    vector <Post*> posts;
    int last_post_id;
    vector <User*> connected_users;
    vector <Notification*> notifications;
};