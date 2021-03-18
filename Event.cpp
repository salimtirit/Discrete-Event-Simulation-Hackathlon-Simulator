#include <iostream>
#include "Event.h"
//#include "Hacker.h"
#include "StickerDesk.h"

Event::Event()
{
}

Event::Event(int type, int id, float time)
{
    this->type = type;
    this->idOfHacker = id;
    this->time = time;
}

Event::Event(int type, int id, float time, int nOfLines)
{
    this->type = type;
    this->idOfHacker = id;
    this->time = time;
    this->nOfLines = nOfLines;
}

bool Event::operator<(Event &other)
{
    if (other.getTime()-this->time > 0.00001)
    {
        return false;
    }
    else if (abs(this->time-other.getTime()) < 0.00001)
    {
        return this->idOfHacker > other.getId();
    }
    else
    {
        return true;
    }
}

bool Event::happen()
{
    switch (this->type)
    {
    case 0:
        return this->hackerArrived(); //complate this
        break;
    case 1:
        return this->hackerCommit(); //complate this
        break;
    case 2:
        return this->hackerQueue(); //complate this
        break;
    case 3:
        return this->leaveDeskOne(); //complate this
        break;
    case 4:
        return this->leaveDeskTwo(); //complate this
        break;
    default:
        return false;
        break;
    }
}

float Event::getTime()
{
    return this->time;
}

int Event::getId()
{
    return this->idOfHacker;
}

int Event::getType()
{
    return this->type;
}

bool Event::hackerArrived()
{
    Hacker::hackers.push_back(new Hacker(this->idOfHacker, this->time));
    return true;
}

bool Event::hackerCommit()
{
    Hacker::hackers[this->idOfHacker - 1]->commit(this->nOfLines);
    return true;
}
bool Event::hackerQueue()
{
    //when you are implementing the happen method you should also check if the desk is available
    Hacker *hacker = Hacker::hackers[this->idOfHacker - 1];
    if (hacker->canGetInQueue())
    {
        hacker->inFirstQueue(this->time);
        return true;
    }
    else
    {
        return false;
    }
}
bool Event::leaveDeskOne()
{
    //sticker desk number
    Hacker::hackers[this->idOfHacker - 1]->inSecondQueue(this->time);
    return true;
}
bool Event::leaveDeskTwo()
{
    //hoodie desk number
    Hacker::hackers[this->idOfHacker - 1]->outHoodieDesk(this->time);
    return true;
}

Event::~Event()
{
}
