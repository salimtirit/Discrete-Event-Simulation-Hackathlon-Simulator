#include <iostream>
#include <queue>
#include <limits>
#include <vector>

using namespace std;

template <typename T>
struct PtrLess
{
    bool operator()(T *left, T *right)
    {
        return *left < *right;
    }
};

#ifndef Hacker_H
#define Hacker_H

class Hacker
{
private:
    int id;
    float arrivingTime;
    float maxTimeInStickerQueue = numeric_limits<float>::min();
    float maxTimeInHoodieQueue = numeric_limits<float>::min();
    float totalTimeStickerQueue = 0;
    float totalTimeHoodieQueue = 0;
    float turnaroundTime = 0;
    float timeInFirstQueue;
    float timeInSecondQueue;
    int nOfValidCommits = 0;
    int nOfCommits = 0;
    int nOfCommitLines = 0;
    int nOfGrabbedGifts = 0;
    int nOfInvalidAttemptsQueue = 0;
    int nOfInvalidAttemptshGift = 0;

public:
    static vector<Hacker *> hackers;
    static queue<Hacker *> stickerQueue;
    static priority_queue<Hacker *, vector<Hacker *>, PtrLess<Hacker>> hoodieQueue;
    //static priority_queue<Hacker *> hoodieQueue;
    Hacker(int id, float arrivalTime);
    bool canGetInQueue(); //return true or false but change the value of invalid attempts
    bool operator<(Hacker &other);
    void inFirstQueue(float time);
    void inSecondQueue(float time);
    void inStickerDesk(float time);
    void inHoodieDesk(float time);
    void outHoodieDesk(float time);
    void commit(int NOfLines);
    int getID();
    float getMaxTimeHQueue();
    float getMaxTimeSQueue();
    float getTotalTimeHQueue();
    float getTotalTimeSQueue();
    float getTurnaroundTime();
    int getNOfCommitLines();
    int getInvalidQueue();
    int getInvalidGift();
    int getNOfGrabbedGifts();
    int getNOfCommits();
    ~Hacker();
};

#endif