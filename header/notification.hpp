#include "global_stuff.hpp"

class Notification
{
public:
    Notification(string _id, string _name, string _text);
    void show_notification();
private:
    string id;
    string name;
    string text;
};