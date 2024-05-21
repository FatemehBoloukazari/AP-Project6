#pragma once

#include "global_stuff.hpp"
#include "user.hpp"

class Admin : public User
{
public:
    Admin(string _id, string pass);
    virtual void show_personal_page();
private:
};