#pragma once

#include "global_stuff.hpp"
#include "post.hpp"

class NormalPost : public Post
{
public:
    NormalPost(string _title, string _message, int _id, string _image_address);
    NormalPost(string _author, string _title, string _message, int _id, string _image_address);
    virtual void show_post_overview(vector <string> &result);
    virtual void show_post_details(vector <string> &result);
    virtual void show_course_post_overview(vector <string> &result);
    virtual void show_course_post_details(vector <string> &result);
private:
    string title;
    string author;
    string image_address;
};