#ifndef UTILS_H
#define UTILS_H

#include "string"
#include <cstdlib>

using namespace std;

static string getNameFromLocation(string str)
{
    string ret;
    int index;

    for(int i = str.size() - 1; i >= 0; i--)
    {
        if(str[i] == '/')
        {
            index = i + 1;
            i = -1;
        }
    }

    for(; index < str.size(); index++)
    {
        ret.push_back(str[index]);
    }

    return ret;
}

static string getTextFromString(string str)
{
    string ret = "";
    for(int i = str.size() - 1; i >= 0; i--)
    {
        if(str[i] != '@')
        {
            ret += str[i];
        } else {
            break;
        }
    }

    return ret;
}

static int getTimeFromString(string str)
{
    string retstr = "";
    int ret;
    bool text_over = false;
    for(int i = str.size() - 1; i >= 0; i--)
    {
        if(str[i] == '@')
            text_over = true;
        if(text_over)
        {
            retstr += str[i];
        }
    }
    ret = atoi(retstr.c_str());
    return ret;
}

#endif
