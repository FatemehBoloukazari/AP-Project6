#include "normal_post.hpp"

NormalPost::NormalPost(string _title, string _message, int _id, string _image_address)
{
    title = _title;
    message = _message;
    id = _id;
    image_address = _image_address;
}

void NormalPost::show_post_overview(vector <vector <string>> &_result)
{
    vector <string> result;
    result.push_back(to_string(id));
    result.push_back(title);
    _result.push_back(result);
}

void NormalPost::show_post_details(vector <vector <string>> &_result)
{
    vector <string> result;
    result.push_back(title);
    result.push_back(message);
    result.push_back(image_address);
    _result.push_back(result);
}