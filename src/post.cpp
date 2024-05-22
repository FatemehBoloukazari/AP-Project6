#include "post.hpp"

Post::Post(string _title, string _message, int _id)
{
    title = _title;
    message = _message;
    id = _id;
}

void Post::show_post_overview()
{
    cout << id << ' ' << title << endl;
}

void Post::show_post_details()
{
    cout << id << ' ' << title << ' ' << message << endl;
}
