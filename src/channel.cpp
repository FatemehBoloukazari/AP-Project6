#include "channel.hpp"

Channel::Channel()
{
    last_post_id = 0;
}

void Channel::add_post(string author, string title, string message, string image_address)
{
    NormalPost* new_post = new NormalPost(author, title, message, ++last_post_id, image_address);
    posts.push_back(new_post);
}

void Channel::show_channel_posts(vector <string> &result)
{
    for (int i = (int)posts.size() - 1; i >= 0; i--)
        posts[i]->show_course_post_overview(result);
}

void Channel::view_post(vector <string> &result, int post_id)
{
    for (auto post : posts)
    {
        if (post->get_id() == post_id)
        {
            post->show_course_post_details(result);
            return;
        }
    }
    throw NotFound();
}