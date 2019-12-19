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

    void add(string curTrackName, QStringList files);

    void remove(string curTrackName, int index);

    void save(string curTrackName);

    QStringList getNoteList(string curTrackName);

    std::vector<Note> notes;

    string trackName = "";
};

#endif // NOTELIST_H
