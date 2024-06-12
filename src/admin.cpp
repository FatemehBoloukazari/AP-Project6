#include "admin.hpp"

Admin::Admin(string _name, string _id, string pass)
{
    name = _name;
    id = _id;
    password = pass;
    profile_photo_address = DEFAULT_PROFILE;
    last_post_id = 0;
}

void Admin::show_user_details(vector <string> &result)
{
    result.push_back(name);
    result.push_back(NEW_LINE);
}