#ifndef GLOBAL_STUFF_HPP
#define GLOBAL_STUFF_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include "error.hpp"

using namespace std;

#define debug(x) cout << x << endl;

enum CommandType
{
    POST,
    DELETE,
    GET,
    PUT,
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
const string NEW_COURSE_POST_NOTIFICATION = "New Course Post";
const string NEW_TA_FORM_NOTIFICATION = "New Form";
const string TA_REQUEST_ACCEPTED_NOTIFICATION = "Your request to be a teaching assistant has been accepted.";
const string TA_REQUEST_REJECTED_NOTIFICATION = "Your request to be a teaching assistant has been rejected.";

const string ACCEPTED_STR = "accepted";
const string REJECTED_STR = "rejected";

const string TA_FORM_TITLE = "TA form for ";
const string COURSE = "course";

const string EMPTY_STRING = "";
const string SPACE = " ";
const string QUESTION_MARK = "?";
const string NEW_LINE = "\n";
const string COLON_STR = ":";
const string COMMA = ",";
const string ZERO = "0";
const string DOT = ".";
const string UNDER_SCORE = "_";


const string POST_STRING = "POST";
const string DELETE_STRING = "DELETE";
const string GET_STRING = "GET";
const string PUT_STRING = "PUT";

vector <string> get_splited(string str, char seprating_char);
bool is_a_number(string str);

const int NUM_OF_POST_LOGIN_ENTRIES = 7;
const int NUM_OF_POST_LOGOUT_ENTRIES = 3;
const int NUM_OF_POST_CONNECT_ENTRIES = 5;
const int NUM_OF_POST_COURSE_OFFER_ENTRIES = 15;
const int NUM_OF_POST_PROFILE_PHOTO_ENTRIES = 5;
const int NUM_OF_POST_COURSE_POST_ENTRIES = 11;
const int NUM_OF_POST_CLOSE_TA_FORM_ENTRIES = 5;
const int NUM_OF_TA_REQUEST_ENTRIES = 7;

const int NUM_OF_DELETE_POST_ENTRIES = 5;
const int NUM_OF_DELETE_COURSE_ENTRIES = 5;

const int NUM_OF_GET_PERSONAL_PAGE_ENTRIES = 5;
const int NUM_OF_GET_NOTIFICATION_ENTRIES = 3;
const int NUM_OF_GET_POST_ENTRIES = 7;
const int NUM_OF_GET_ALL_COURSES_ENTRIES = 3;
const int NUM_OF_GET_A_COURSE_ENTRIES = 5;
const int NUM_OF_GET_MY_COURSES_ENTRIES = 3;
const int NUM_OF_GET_COURSE_CHANNEL_ENTRIES = 5;

const int NUM_OF_PUT_MY_COURSES_ENTRIES = 5;

const int NUM_OF_WITH_IMAGE_POST_DATAS = 3;

const string ID = "id";
const string PASSWORD = "password";
const string TITLE = "title";
const string MESSAGE = "message";
const string COURSE_ID = "course_id";
const string PROFESSOR_ID = "professor_id";
const string CAPACITY = "capacity";
const string TIME = "time";
const string EXAM_DATE = "exam_date";
const string CLASS_NUMBER = "class_number";
const string LOGIN = "login";
const string LOGOUT = "logout";
const string POST_STR = "post";
const string CONNECT = "connect";
const string COURSE_OFFER = "course_offer";
const string MY_COURSES = "my_courses";
const string POST_ID = "post_id";
const string PERSONAL_PAGE = "personal_page";
const string NOTIFICATION = "notification";
const string COURSES = "courses";
const string IMAGE = "image";
const string PROFILE_PHOTO = "profile_photo";
const string PHOTO = "photo";
const string COURSE_POST = "course_post";
const string COURSE_CHANNEL = "course_channel";
const string TA_FORM = "ta_form";
const string CLOSE_TA_FORM = "close_ta_form";
const string TA_REQUEST = "ta_request";
const string FORM_ID = "form_id";
const string FILE_STR = "file";
const string COURSE_NAME  = "course_name";
const string PROFESSOR_NAME = "professor_name";
const string NUM_OF_COURSES = "num_of_courses";
const string NUM_OF_POSTS = "num_of_posts";
const string USER_TYPE = "user_type";
const string NAME = "name";
const string PROFILE_PIC_ADDRESS = "profile_pic_address";
const string SEMESTER = "semester";
const string POSITION = "position";
const string MAJOR = "major";

const string PRESSED_BUTTON = "pressed_button";
const string REMOVE_PROFILE_PHOTO = "Remove Profile Photo";

const char DASH = '-';
const char COLON = ':';
const char SLASH = '/';
const char DOUBLE_QUOTATION = '\"';
const char SPACE_CHAR = ' ';
const char COMMA_CHAR = ',';
const char SEMICOLON = ';';
const char NEWLINE_CHAR = '\n';

const int MAIN_COMMAND_INDEX = 0;
const int REQUEST_INDEX = 1;
const int QUESTION_MARK_INDEX = 2;
const int FIRST_DATA_INDEX = 3;

const string ADMIN_ID = "0";
const string ADMIN_NAME = "UT_account";
const string ADMIN_PASSWORD = "UT_account";

const bool USER_POST = false;
const bool CHANNEL_POST = true;

const string NUM_OF_TA_REQUESTS_MESSAGE_FIRST_PART = "We have received";
const string NUM_OF_TA_REQUESTS_MESSAGE_SECOND_PART = "requests for the teaching assistant position";

const string ACCEPT = "accept";
const string REJECT = "reject";

enum Status
{
    ACCEPTED,
    REJECTED
};

const string ADMIN = "admin";
const string STUDENT = "student";
const string PROFESSOR = "professor";

const string DEFAULT_PROFILE = "/images/defualt_profile.png";
const string PNG = "png";
const string IMAGE_ADDRESS = "./images/";
const string IMAGE_URL = "/images/";

const string NO_USER_SESSION_ID = "";

const string HTML_BREAK = "<br>";

const string STATUS = "status";

namespace users_data
{
    const int USER_TYPE_IND = 0;
    const int ID_IND = 1;
    const int NAME_IND = 2;
    const int PROFILE_PIC_ADDRESS_IND = 3;
    const int MAJOR_IND = 4;
    const int SEMESTER_IND = 5;
    const int POSITION_IND = 5;
}

namespace posts_data
{
    const int TITLE_IND = 0;
    const int MESSAGE_IND = 1;
    const int IMAGE_ADDRESS_IND = 2;
}

namespace courses_data
{
    const int COURSE_ID_IND = 0;
    const int COURSE_NAME_IND = 1;
    const int CAPACITY_IND = 2;
    const int PROFESSOR_NAME_IND = 3;
    const int TIME_IND = 4;
    const int EXAM_DATE_IND = 5;
    const int CLASS_NUMBER_IND = 6;
}

#endif