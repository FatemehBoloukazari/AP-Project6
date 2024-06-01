#include "channel.hpp"

Channel::Channel()
{
    last_post_id = 0;
}

void Channel::add_post(string title, string message, string image_address)
{
    Post* new_post = new Post(title, message, ++last_post_id, image_address);
    posts.push_back(new_post);
}