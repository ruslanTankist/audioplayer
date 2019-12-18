#include "notelist.h"

NoteList::NoteList()
{
    std::ifstream read("notelist");
    string rec;
    while(getline(read, rec)){
        Note note;
        string buf = note.getFullRec();
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
        note.setFullRec(files[i].toStdString());
        note.setText(getTextFromString(files[i].toStdString()));
        note.setTime(getTimeFromString(files[i].toStdString()));
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
        write << notes[i].getFullRec() << std::endl;
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
