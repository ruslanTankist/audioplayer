#ifndef NOTELIST_H
#define NOTELIST_H

#include <QStringList>
#include <vector>
#include "note.h"
#include <fstream>
#include <string>
#include "utils.h"

class NoteList
{
public:
    NoteList();

    void add(QStringList files);

    void remove(int index);

    void save();

    QStringList getNoteList();

    std::vector<Note> notes;
};

#endif // NOTELIST_H
