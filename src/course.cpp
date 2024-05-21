#include "course.hpp"

Course::Course(int _id, string _name, int _credit, int pre, vector<int> ids)
{
    id = _id;
    name = _name;
    credit = _credit;
    prerequisites = pre;
    major_ids = ids;
}