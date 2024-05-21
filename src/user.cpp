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
