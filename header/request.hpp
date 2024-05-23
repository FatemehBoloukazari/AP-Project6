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
    void handle_new_post(string _title, string _message);
    void handle_post_delete(int id);
    void handle_view_personal_page(string id_str);
    void handle_connect_users(vector<string> &splited_command);
    void handle_view_notifications();
    void handle_view_post(string _id, string _post_id);
    void handle_course_offer(string course_id, string professor_id, string capacity, Time *time, Date *exam_date, string class_number);
    void handle_view_all_courses();
    void handle_view_course_details(string course_offer_id);
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