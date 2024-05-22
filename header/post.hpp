#include "global_stuff.hpp"

class Post
{
public:
    Post(string _title, string _message, int _id);
    void show_post_overview();
    void show_post_details();
    int get_id() {return id;}
private:
    string title;
    string message;
    int id;
};