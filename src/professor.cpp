#include "professor.hpp"

Professor::Professor(string _id, string _name, int _major_id, string _major_str, string _position, string pass)
{
    id = _id;
    name = _name;
    major_id = _major_id;
    major_str = _major_str;
    position = _position;
    password = pass;
}

void Professor::show_personal_page()
{
    cout << name << ' ' << major_str << ' ' << position << ' ';
    for (int i = 0; i < (int)courses.size(); i++)
    {
        if (i != 0)
            cout << ",";
        cout << courses[i]->get_name();
    }
    cout << endl;
    show_posts();
}
