#ifndef UTILS_H
#define UTILS_H

#include "string"
#include <cstdlib>
#include <sstream>
#include <QDebug>

using namespace std;

//seconds to HH:MM:SS
static string timetostr(int inttime)
{
    string str;
    int hours = inttime / 3600;
    int minutes = (inttime % 3600) / 60;
    int seconds = (inttime % 3600) % 60;
    stringstream ss;
    if (hours < 10)
        ss << '0';
    ss << hours << ':';

    if (minutes < 10)
        ss << "0";
    ss << minutes << ':';

    if (seconds < 10)
        ss << "0";
    ss << seconds;

    ss >> str;
    return str;
}

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
    for(int i = 0; i <= str.size()-1; i++)
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
    for(int i = 0; i <= str.size()-1; i++)
    {
        if(text_over)
        {
            retstr += str[i];
        }
        if(str[i] == '@')
            text_over = true;
    }
    ret = atoi(retstr.c_str());
    return ret;
}

#endif
