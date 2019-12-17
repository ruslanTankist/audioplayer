#ifndef TRACK_H
#define TRACK_H

#include <string>
#include <map>
#include <vector>
#include "QStringList"

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

    string name = "";

    string location = "";
};

#endif // TRACK_H
