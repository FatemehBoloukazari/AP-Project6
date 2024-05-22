#include "user.hpp"

void User::login(string pass)
{
    if (password != pass)
        throw PermissionDenied();
}

void User::send_post(string _title, string _message)
{
    Post* new_post = new Post(_title, _message, ++last_post_id);
    posts.push_back(new_post);
    Notification *new_notification = new Notification(id, name, NEW_POST_NOTIFICATION);
    for (auto connected_user : connected_users)
        connected_user->add_notification(new_notification);
}

void User::delete_post(int _id)
{
    for (int i = 0; i < (int)posts.size(); i++)
    {
        if (posts[i]->id == i)
        {
            posts.erase(posts.begin() + i);
            cout << "OK" << endl;
            return;
        }
    }
    cerr << NOT_FOUND_ERROR << endl;
}

void User::show_posts()
{
    for (int i = (int)posts.size() - 1; i >= 0; i--)
        cout << posts[i]->id << ' ' << posts[i]->title << endl;
}

void User::connect(User *user)
{
    for (auto &connected_user : connected_users)
        if (connected_user == user)
            throw BadRequest();
    connected_users.push_back(user);
}

void User::add_notification(Notification *new_notification)
{
    notifications.push_back(new_notification);
}

void User::view_notifications()
{
    if (notifications.empty())
    {
        cout << EMPTY << endl;
        return;
    }
    for (auto notif : notifications)
        notif->show_notification();
    notifications.clear();
}
