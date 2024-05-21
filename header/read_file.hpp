#pragma once

#include "global_stuff.hpp"
#include "user.hpp"
#include "student.hpp"
#include "professor.hpp"
#include "course.hpp"

void read_majors_file(vector <Major*> &majors, string majors_file_path);
void read_students_file(vector <User*> &users, vector <Major*> const &majors, string students_file_path);
void read_courses_file(vector <Course*> &courses, string courses_file_path);
void read_professors_file(vector <User*> &users, vector <Major*> const &majors, string professors_file_path);