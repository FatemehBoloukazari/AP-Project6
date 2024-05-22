#include "admin.hpp"

Admin::Admin(string _name, string _id, string pass)
{
    name = _name;
    id = _id;
    password = pass;
}

void Admin::show_personal_page()
{
    cout << "UT_account" << endl;
    show_posts();
}
