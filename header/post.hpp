#pragma once

#include "global_stuff.hpp"

class Post
{
public:
    Post(string _title, string _message, int _id, string _image_address);
    void show_post_overview(vector <string> &result);
    void show_post_details(vector <string> &result);
    int get_id() {return id;}
private:
    string title;
    string message;
    int id;
    string image_address;
};