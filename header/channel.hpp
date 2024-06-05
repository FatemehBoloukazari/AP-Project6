#ifndef CAHNNEL_HPP
#define CHANNEL_HPP

#include "global_stuff.hpp"
#include "course_post.hpp"

class Channel
{
public:
    Channel();
    void add_post(string author, string title, string message, string image_address);
    void show_channel_posts(vector <string> &result);
    void view_post(vector <string> &result, int post_id);
private:
    vector <CoursePost*> posts;
    int last_post_id;
};

#endif