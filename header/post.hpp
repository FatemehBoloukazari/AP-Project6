#ifndef POST_HPP
#define POST_HPP

#include "global_stuff.hpp"

class Post
{
public:
    virtual void show_post_overview(vector <vector <string>> &result) = 0;
    virtual void show_post_details(vector <vector <string>> &result) = 0;
    int get_id() {return id;}
protected:
    string message;
    int id;
};

#endif