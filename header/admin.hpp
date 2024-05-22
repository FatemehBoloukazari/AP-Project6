#pragma once

#include "global_stuff.hpp"
#include "user.hpp"

class Admin : public User
{
public:
    Admin(string _name, string _id, string pass);
    virtual void show_user_details();
private:
};