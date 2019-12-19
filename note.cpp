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

void Note::setTrackName(string trackName)
{
    trackName.erase(trackName.size() - 4);
    this->trackName = trackName;
}

string Note::getTrackName()
{
    return trackName;
}
