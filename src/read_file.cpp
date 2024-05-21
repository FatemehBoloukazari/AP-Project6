#include "read_file.hpp"

string find_major_name_by_id(vector <Major*> const &majors, int id)
{
    for (auto major : majors)
        if (major->major_id)
            return major->major;
}

void read_professors_file(vector <User*> &users, vector <Major*> const &majors, string professors_file_path)
{
    ifstream professors_file(professors_file_path);
    string professor_str;
    getline(professors_file, professor_str);
    while (getline(professors_file, professor_str))
    {
        vector <string> seprated_str = get_splited(professor_str, ',');
        string id = seprated_str[0];
        string name = seprated_str[1];
        int major_id = stoi(seprated_str[2]);
        string major_str = find_major_name_by_id(majors, major_id);
        string position = seprated_str[3];
        string password = seprated_str[4];
        Professor* new_professor = new Professor(id, name, major_id, major_str, position, password);
        users.push_back(new_professor);
    }
    professors_file.close();
}

void read_majors_file(vector<Major*> &majors, string majors_file_path)
{
    ifstream majors_file(majors_file_path);
    string major_str;
    getline(majors_file, major_str);
    while (getline(majors_file, major_str))
    {
        vector <string> seprated_str = get_splited(major_str, ',');
        int id = stoi(seprated_str[0]);
        string major = seprated_str[1];
        Major* new_major = new Major(id, major);
        majors.push_back(new_major);
    }
    majors_file.close();
}

void read_students_file(vector<User*> &users, vector <Major*> const &majors, string students_file_path)
{
    ifstream students_file(students_file_path);
    string student_str;
    getline(students_file, student_str);
    while (getline(students_file, student_str))
    {
        vector <string> seprated_str = get_splited(student_str, ',');
        string id = seprated_str[0];
        string name = seprated_str[1];
        int major_id = stoi(seprated_str[2]);
        string major_str = find_major_name_by_id(majors, major_id);
        int semester = stoi(seprated_str[3]);
        string password = seprated_str[4];
        Student* new_student = new Student(id, name, major_id, major_str, semester, password);
        users.push_back(new_student);
    }
    students_file.close();
}

void read_courses_file(vector<Course*> &courses, string courses_file_path)
{
    ifstream courses_file(courses_file_path);
    string course_str;
    getline(courses_file, course_str);
    while (getline(courses_file, course_str))
    {
        vector <string> seprated_str = get_splited(course_str, ',');
        int id = stoi(seprated_str[0]);
        string name = seprated_str[1];
        int credit = stoi(seprated_str[2]);
        int prerequisites = stoi(seprated_str[3]);
        string majors_str = seprated_str[4];
        vector <int> major_ids;
        majors_str += ';';
        string major_id = EMPTY_STRING;
        for (auto c : majors_str)
        {
            if (c == ';')
            {
                major_ids.push_back(stoi(major_id));
                major_id = EMPTY_STRING;
            }
            else
                major_id += c;
        }
        Course* course = new Course(id, name, credit, prerequisites, major_ids);
        courses.push_back(course);
    }
    courses_file.close();
}

//Course::Course(int _id, string _name, int _credit, vector<int> pre, vector<int> ids)