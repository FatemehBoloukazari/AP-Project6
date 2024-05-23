#include "course.hpp"

Course::Course(string _id, string _name, int _credit, int pre, vector<int> ids)
{
    id = _id;
    name = _name;
    credit = _credit;
    prerequisites = pre;
    major_ids = ids;
}

bool Course::have_allowed_major(int major_id)
{
    for (auto major : major_ids)
        if (major == major_id)
            return true;
    return false;
}

bool Course::have_allowed_semester(int semester)
{
    if (semester >= prerequisites)
        return true;
    return false;
}
