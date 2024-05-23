#include "admin.hpp"

Admin::Admin(string _name, string _id, string pass)
{
    name = _name;
    id = _id;
    password = pass;
    last_post_id = 0;
}

void Admin::show_user_details()
{
    cout << "UT_account" << endl;
}