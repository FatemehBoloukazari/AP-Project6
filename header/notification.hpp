#ifndef NOTIFICATION_HPP
#define NOTIFICATION_HPP

#include "global_stuff.hpp"

class Notification
{
public:
    Notification(string _id, string _name, string _text);
    void show_notification(vector <vector <string>> &result);
private:
    string id;
    string name;
    string text;
};

#endif