#include "global_stuff.hpp"

vector <string> get_splited(string str, char seprating_char)
{
    vector <string> ret;
    str += seprating_char;
    string cur_str = "";
    for (auto c : str)
    {
        if (c == seprating_char)
        {
            ret.push_back(cur_str);
            cur_str = "";
        }
        else
            cur_str += c;
    }
    return ret;
}

bool is_a_number(string str)
{
    for (auto c : str)
    {
        if (c < '0' || c > '9')
            return false;
    }
    return true;
}