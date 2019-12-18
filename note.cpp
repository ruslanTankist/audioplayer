#include "note.h"
#include <fstream>
#include <sstream>

Note::Note()
{

}

std::string Note::getText(){
    return text;
}

int Note::getTime()
{
   return time;
}
/*
std::string Note::getLocation()
{
    return location;
}*/

std::string Note::getFullRec()
{
    return fullRec;
}

void Note::setText(std::string text)
{
    this->text = text;
}

void Note::setTime(int time)
{
    this->time = time;
}
/*
void Note::setLocation(std::string location)
{
    this->location = location;
}*/
void Note::setFullRec(string fRec)
{
    if (!fRec.empty())
    {
        fullRec = fRec;
    } else {
        stringstream ss;
        ss << text << "@" << time;
        ss >> fullRec;
    }

}
