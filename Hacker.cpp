#include <iostream>
#include "Hacker.h"

Hacker::Hacker(int id, float arrivalTime)
{
    this->id = id;
    this->arrivingTime = arrivalTime;
}

vector<Hacker *> Hacker::hackers;
queue<Hacker *> Hacker::stickerQueue;
priority_queue<Hacker *, vector<Hacker *>, PtrLess<Hacker>> Hacker::hoodieQueue;
//priority_queue<Hacker *> Hacker::hoodieQueue;

bool Hacker::canGetInQueue() //return true or false but change the value of invalid attempt
{
    if (this->nOfValidCommits < 3)
    {
        this->nOfInvalidAttemptsQueue++;
        return false;
    }
    else if (this->nOfGrabbedGifts >= 3)
    {
        this->nOfInvalidAttemptshGift++;
        return false;
    }
    else
    {
        return true;
    }
}

bool Hacker::operator<(Hacker &other)
{
    if (this->nOfValidCommits < other.nOfValidCommits)
    {
        return true;
    }
    else if (this->nOfValidCommits == other.nOfValidCommits)
    {
        return this->timeInSecondQueue > other.timeInSecondQueue;
        //return this->id > other.id;
    }
    else
    {
        return false;
    }
}

void Hacker::inFirstQueue(float time)
{
    this->timeInFirstQueue = time;
}

void Hacker::inStickerDesk(float time)
{
    float spentTime = time - this->timeInFirstQueue;
    if (spentTime > this->maxTimeInStickerQueue)
    {
        this->maxTimeInStickerQueue = spentTime;
    }
    this->totalTimeStickerQueue += spentTime;
}

void Hacker::inSecondQueue(float time)
{
    this->timeInSecondQueue = time;
}

void Hacker::inHoodieDesk(float time)
{
    float spentTime = time - this->timeInSecondQueue;
    if (spentTime > this->maxTimeInHoodieQueue)
    {
        this->maxTimeInHoodieQueue = spentTime;
    }
    this->totalTimeHoodieQueue += spentTime;
}

void Hacker::outHoodieDesk(float time)
{
    this->nOfGrabbedGifts++;
    this->turnaroundTime += (time - this->timeInFirstQueue);
}

void Hacker::commit(int NOfLines)
{
    if (NOfLines >= 20)
    {
        this->nOfValidCommits++;
    }
    this->nOfCommits++;
    this->nOfCommitLines += NOfLines;
}

float Hacker::getMaxTimeHQueue()
{
    return this->maxTimeInHoodieQueue;
}

float Hacker::getMaxTimeSQueue()
{
    return this->maxTimeInStickerQueue;
}

float Hacker::getTotalTimeHQueue()
{
    return this->totalTimeHoodieQueue;
}

float Hacker::getTotalTimeSQueue()
{
    return this->totalTimeStickerQueue;
}

float Hacker::getTurnaroundTime()
{
    return this->turnaroundTime;
}

int Hacker::getNOfCommitLines()
{
    return this->nOfCommitLines;
}

int Hacker::getInvalidQueue()
{
    return this->nOfInvalidAttemptsQueue;
}

int Hacker::getInvalidGift()
{
    return this->nOfInvalidAttemptshGift;
}

int Hacker::getID()
{
    return this->id;
}

int Hacker::getNOfGrabbedGifts()
{
    return this->nOfGrabbedGifts;
}

int Hacker::getNOfCommits()
{
    return this->nOfCommits;
}

Hacker::~Hacker()
{
}