#include "course_post.hpp"

CoursePost::CoursePost(string _author, string _title, string _message, int _id, string _image_address) 
            : NormalPost(_title, _message, _id, _image_address)
{
    author = _author;
}

void CoursePost::show_course_post_overview(vector <vector <string>> &_result)
{
    vector <string> result;
    result.push_back(to_string(id));
    result.push_back(author);
    result.push_back(title);
    _result.push_back(result);
}

void CoursePost::show_course_post_details(vector <vector <string>> &_result)
{
    vector <string> result;
    result.push_back(to_string(id));
    result.push_back(author);
    result.push_back(title);
    result.push_back(message);
    _result.push_back(result);
}