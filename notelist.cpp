#include "notelist.h"


NoteList::NoteList()
{
    std::ifstream read("notelist");
    string loc;
    while(getline(read, loc)){
        Note note;
        note.setLocation(loc);
        string buf = getNameFromLocation(loc);
        note.setText(getTextFromString(buf));
        note.setTime(getTimeFromString(buf));
        notes.push_back(note);
    }
}

void NoteList::add(QStringList files)
{
    for(int i = 0; i < files.size(); i++)
    {
        Note note;
        note.setLocation(files[i].toStdString());
        note.setText(getNameFromLocation(files[i].toStdString()));
        notes.push_back(note);
    }
}

void NoteList::remove(int index)
{
    notes.erase(notes.begin() + index);
}

void NoteList::save()
{
    std::ofstream write("notelist");
    for(int i = 0; i < notes.size(); i++){
        write << notes[i].getLocation() << std::endl;
    }
}

QStringList NoteList::getNoteList()
{
    QStringList list;
    for(int i = 0; i < notes.size(); i++)
    {
        QString qstr = QString::number(static_cast<int>(notes[i].getTime()));
        qstr += QString::fromStdString(notes[i].getText());
        list.push_back(qstr);
    }
    return list;
}
