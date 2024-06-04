#pragma once

#include "global_stuff.hpp"
#include "post.hpp"

class NormalPost : public Post
{
public:
    NormalPost(string _title, string _message, int _id, string _image_address);
    virtual void show_post_overview(vector <string> &result);
    virtual void show_post_details(vector <string> &result);
protected:
    string title;
    string image_address;
};