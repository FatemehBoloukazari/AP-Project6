#pragma once

#include "global_stuff.hpp"
#include "read_file.hpp"
#include "user.hpp"
#include "admin.hpp"
#include "student.hpp"
#include "date.hpp"

class Request
{
public:
    Request(string majors_file_path, string students_file_path, string courses_file_path, string professors_file_path);
    void handle_login(string id, string password);
    void handle_logout();
    void handle_new_post(string _title, string _message, string _image_address);
    void handle_post_delete(string id);
    vector <string> handle_view_personal_page(string id_str);
    void handle_connect_users(vector<string> &splited_command);
    vector <string> handle_view_notifications();
    vector <string> handle_view_post(string _id, string _post_id);
    void handle_course_offer(string course_id, string professor_id, string capacity, Time *time, Date *exam_date, string class_number);
    vector <string> handle_view_all_courses();
    vector <string> handle_view_course_details(string course_offer_id);
    void handle_take_new_course(string _course_id);
    void handle_delete_taken_course(string _course_id);
    vector <string> handle_view_taken_courses();
    void handle_add_profile_photo(string _image_address);
    void handle_new_course_post(string course_offer_id_str, string title, string message, string image_address);
    CourseOffer* find_course_offer_by_id(int course_offer_id);
    vector <string> handle_view_course_channel(string course_offer_id);
    vector <string> handle_view_course_post(string _id, string _post_id);
    void handle_new_ta_form(string course_offer_id, string message);
    void check_close_ta_form_access(string post_id);
    vector <string> show_number_of_ta_requests(int form_id);
    vector <vector <string>> get_ta_form_requests(int form_id);
    void handle_ta_requests_responeses(vector <Status> const responses, int form_id);
private:
    User *logged_in_user;
    vector <Course*> courses;
    vector <User*> users;
    vector <Major*> majors;
    vector <CourseOffer*> course_offers;
    int last_course_offer_id;
    Professor* find_professor_by_id(string id);
    Course* find_course_by_id(string id);
};