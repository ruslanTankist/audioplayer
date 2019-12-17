#include "note.h"
#include <fstream>

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

std::string Note::getLocation()
{
    return location;
}

void Note::setText(std::string text)
{
    this->text = text;
}

void Note::setTime(int time)
{
    this->time = time;
}

void Note::setLocation(std::string location)
{
    this->location = location;
}
