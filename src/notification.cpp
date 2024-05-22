#include "notification.hpp"

Notification::Notification(string _id, string _name, string _text)
{
    id = _id;
    name = _name;
    text = _text;
}

void Notification::show_notification()
{
    cout << id << ' ' << name << ": " << text << endl;
}