#include "notelist.h"
#include "note.h"
#include "utils.h"

NoteList::NoteList()
{
    std::ifstream read("notelist");
    string loc;
    while(getline(read, loc)){
        Note notes;
        note.setLocation(loc);
        note.setText(getNameFromLocation(loc));
        notes.push_back(note);
    }
}

void NoteList::add(QStringList files)
{
    for(int i = 0; i < files.size(); i++)
    {
        Note note;
        note.setLocation(files[i].toStdString());
        note.setName(getNameFromLocation(files[i].toStdString()));
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

QStringList Note::getNoteList()
{
    QStringList list;
    for(int i = 0; i < notes.size(); i++)
    {
        QString qstr = QString::fromStdString(notes[i].getNote());
        list.push_back(qstr);
    }
    return list;
}
