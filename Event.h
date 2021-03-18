#include <iostream>
#include "Hacker.h"

using namespace std;

#ifndef Event_H
#define Event_H

class Event
{
private:
    int type; //0 arrive - 1 commit - 2 attempt getting in queue - 3 leave desk one - 4 leave desk two
    float time;
    int idOfHacker;
    int nOfLines; // willl be available if the event is 1
    bool hackerArrived();
    bool hackerCommit();
    bool hackerQueue();
    bool leaveDeskOne();
    bool leaveDeskTwo();

public:
    Event(); //do i need this??
    Event(int type, int id, float time);
    Event(int type, int id, float time, int nOfLines);
    bool operator<(Event &other);
    bool happen();
    int getId();
    int getType();
    float getTime();
    ~Event(); //do i need this??
};

#endif