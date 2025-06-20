#ifndef COURSE_POST_HPP
#define COURSE_POST_HPP

#include "global_stuff.hpp"
#include "normal_post.hpp"

class CoursePost : public NormalPost
{
public:
    CoursePost(string _author, string _title, string _message, int _id, string _image_address);
    void show_course_post_overview(vector <vector <string>> &result);
    void show_course_post_details(vector <vector <string>> &result);
private:
    string author;
};

#endif