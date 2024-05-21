#include "admin.hpp"

Admin::Admin(string _id, string pass)
{
    id = _id;
    password = pass;
}

void Admin::show_personal_page()
{
    cout << "UT_account" << endl;
    show_posts();
}
