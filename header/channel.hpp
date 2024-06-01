#include "global_stuff.hpp"
#include "post.hpp"

class Channel
{
public:
    Channel();
    void add_post(string title, string message, string image_address);
private:
    vector <Post*> posts;
    int last_post_id;
};