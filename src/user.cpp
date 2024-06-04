#include "user.hpp"

void User::login(string pass)
{
    if (password != pass)
        throw PermissionDenied();
}

void User::send_post(string _title, string _message, string _image_address)
{
    NormalPost* new_post = new NormalPost(_title, _message, ++last_post_id, _image_address);
    posts.push_back(new_post);
    Notification *new_notification = new Notification(id, name, NEW_POST_NOTIFICATION);
    for (auto connected_user : connected_users)
        connected_user->add_notification(new_notification);
}

void User::delete_post(int _id)
{
    for (int i = 0; i < (int)posts.size(); i++)
    {
        if (posts[i]->get_id() == _id)
        {
            posts.erase(posts.begin() + i);
            return;
        }
    }
    throw NotFound();
}

void User::show_personal_page(vector <string> &result)
{
    show_user_details(result);
    show_posts(result);
}

void User::show_posts(vector <string> &result)
{
    for (int i = (int)posts.size() - 1; i >= 0; i--)
        posts[i]->show_post_overview(result);
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

void User::view_notifications(vector <string> &result)
{
    if (notifications.empty())
    {
        result.push_back(EMPTY);
        result.push_back(NEW_LINE);
        return;
    }
    for (int i = (int)notifications.size() - 1; i >= 0; i--)
        notifications[i]->show_notification(result);
    notifications.clear();
}

void User::view_post(vector <string> &result, int post_id)
{
    for (auto post : posts)
    {
        if (post->get_id() == post_id)
        {
            show_user_details(result);
            post->show_post_details(result);
            return;
        }
    }
    throw NotFound();
}

void User::set_profile_photo(string _image_address)
{
    profile_photo_address = _image_address;
}