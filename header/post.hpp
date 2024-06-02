#pragma once

#include "global_stuff.hpp"

class Post
{
public:
    Post(string _title, string _message, int _id, string _image_address);
    Post(string _author, string _title, string _message, int _id, string _image_address);
    void show_post_overview(vector <string> &result);
    void show_post_details(vector <string> &result);
    void show_course_post_overview(vector <string> &result);
    void show_course_post_details(vector <string> &result);
    int get_id() {return id;}
private:
    string title;
    string message;
    string author;
    int id;
    string image_address;
};