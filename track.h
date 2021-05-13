#ifndef TRACK_H
#define TRACK_H

#include <string>
#include <vector>
#include "QStringList"
#include "notelist.h"

using namespace std;

class Track
{
public:
    Track();

    string getName();

    string getLocation();

    void setName(string name);

    void setLocation(string location);
private:
 //   class Notelist;

    string name = "";

    string location = "";
};

#endif // TRACK_H
