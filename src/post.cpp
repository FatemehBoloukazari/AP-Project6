#include "post.hpp"

Post::Post(string _title, string _message, int _id, string _image_address)
{
    title = _title;
    message = _message;
    id = _id;
    image_address = _image_address;
}

void Post::show_post_overview(vector <string> &result)
{
    result.push_back(to_string(id));
    result.push_back(SPACE);
    result.push_back(title);
    result.push_back(NEW_LINE);
}

void Post::show_post_details(vector <string> &result)
{
    result.push_back(to_string(id));
    result.push_back(SPACE);
    result.push_back(title);
    result.push_back(SPACE);
    result.push_back(message);
    result.push_back(NEW_LINE);
}
