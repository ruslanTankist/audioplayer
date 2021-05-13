#include "notelist.h"
#include <QtDebug>

NoteList::NoteList()
{
    std::ifstream read("notelist", ios_base::in);
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

void NoteList::add(QStringList files)
{
    for(int i = 0; i < files.size(); i++)
    {
        Note note;
        note.setFullRec(files[i].toStdString());
        note.setText(getTextFromString(note.getFullRec()));
        note.setTime(getTimeFromString(note.getFullRec()));
        notes.push_back(note);
    }
}

void NoteList::remove(int index)
{
    qDebug() << notes.size();
    notes.erase(notes.begin() + index);
    qDebug() << endl<< notes.size();
}

void NoteList::save()
{
    std::ofstream write("notelist"/*, ios_base::app*/);
    for(int i = 0; i < notes.size(); i++){
        write << notes[i].getFullRec() << std::endl;
    }
}

QStringList NoteList::getNoteList()
{
    QStringList list;
    for(int i = 0; i < notes.size(); i++)
    {
        QString qstr = QString::fromStdString(timetostr(static_cast<int>(notes[i].getTime()))) + " - " + QString::fromStdString(notes[i].getText());
        list.push_back(qstr);
    }
    return list;
}
