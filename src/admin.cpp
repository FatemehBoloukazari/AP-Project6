#include "admin.hpp"

Admin::Admin(string _name, string _id, string pass)
{
    name = _name;
    id = _id;
    password = pass;
}

void Admin::show_user_details()
{
    cout << "UT_account" << endl;
}