#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <vector>
#include "QStringList"

using namespace std;

class Note
{
public:
    Note();

    std::string getText();

    int getTime();

    std::string getLocation();

    void setText(std::string text);

    void setTime(int time);

    void setLocation(std::string location);

private:
    std::string text = "";

    int time = 0;

    std::string location = "";
};

#endif // NOTE_H
