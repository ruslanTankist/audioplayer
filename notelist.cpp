#include "notelist.h"
#include <QtDebug>

NoteList::NoteList()
{
    string loc = "notelist" + trackName;
    std::ifstream read(loc.c_str(), ios_base::in);
    if (read.is_open())
    {
        string rec;
        while(getline(read, rec)){
            Note note;
            note.setFullRec(rec);
            string buf = note.getFullRec();
            note.setText(getTextFromString(buf));
            note.setTime(getTimeFromString(buf));
            notes.push_back(note);
        }
    }
}

void NoteList::add(string curTrackName, QStringList files)
{
    for(int i = 0; i < files.size(); i++)
    {
        Note note;
        note.setTrackName(curTrackName);
        note.setFullRec(files[i].toStdString());
        note.setText(getTextFromString(note.getFullRec()));
        note.setTime(getTimeFromString(note.getFullRec()));
        notes.push_back(note);
    }
}

void NoteList::remove(string curTrackName, int index)
{
    qDebug() << notes.size();
    notes.erase(notes.begin() + index);
    qDebug() << endl<< notes.size();
}

void NoteList::save(string curTrackName)
{
    string loc = "notelist" + curTrackName;
    std::ofstream write(loc.c_str()/*, ios_base::app*/);
    for(int i = 0; i < notes.size(); i++){
        write << notes[i].getFullRec() << std::endl;
    }
}

QStringList NoteList::getNoteList(string curTrackName)
{
    QStringList list;
    for(int i = 0; i < notes.size(); i++)
    {
        if(notes[i].getTrackName() == curTrackName){
            QString qstr = QString::fromStdString(timetostr(static_cast<int>(notes[i].getTime()))) + " - " + QString::fromStdString(notes[i].getText());
            list.push_back(qstr);
        }
    }
    return list;
}
