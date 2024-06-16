#include "notification.hpp"

Notification::Notification(string _id, string _name, string _text)
{
    id = _id;
    name = _name;
    text = _text;
}

void Notification::show_notification(vector <vector <string>> &_result)
{
    vector <string> result;
    result.push_back(id);
    result.push_back(name);
    result.push_back(text);
    _result.push_back(result);
}