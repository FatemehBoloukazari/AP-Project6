#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "error.hpp"

using namespace std;

#define debug(x) cout << x << endl;

enum CommandType
{
    POST,
    DELETE,
    GET,
    NOT_COMMAND
};

struct Major
{
    Major(int id, string name)
    {
        major_id = id;
        major = name;
    }
    int major_id;
    string major;
};

struct Post
{
    Post(string _title, string _message, int _id)
    {
        title = _title;
        message = _message;
        id = _id;
    }
    string title;
    string message;
    int id;
};

const string PERMISSION_DENIED_ERROR = "Permission Denied";
const string BAD_REQUEST_ERROR = "Bad Request";
const string NOT_FOUND_ERROR = "Not Found";
const string OK = "OK";

vector <string> get_splited(string str, char seprating_char);
bool is_a_number(string str);