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
        major_name = name;
    }
    int major_id;
    string major_name;
};

const string PERMISSION_DENIED_ERROR = "Permission Denied";
const string BAD_REQUEST_ERROR = "Bad Request";
const string NOT_FOUND_ERROR = "Not Found";
const string OK = "OK";
const string EMPTY = "Empty";

const string NEW_POST_NOTIFICATION = "New Post";
const string GET_COURSE_NOTIFICATION = "Get Course";
const string DELETE_COURSE_NOTIFICATION = "Delete Course";
const string NEW_COURSE_OFFERING_NOTIFICATION = "New Course Offering";

const string EMPTY_STRING = "";

vector <string> get_splited(string str, char seprating_char);
bool is_a_number(string str);