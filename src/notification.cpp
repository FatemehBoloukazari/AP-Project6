#include "notification.hpp"

Notification::Notification(string _id, string _name, string _text)
{
    id = _id;
    name = _name;
    text = _text;
}

void Notification::show_notification(vector <string> &result)
{
    result.push_back(id);
    result.push_back(SPACE);
    result.push_back(name);
    result.push_back(COLON_STR);
    result.push_back(SPACE);
    result.push_back(text);
    result.push_back(NEW_LINE);
}