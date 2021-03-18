#include <iostream>
#include <fstream>
#include <queue>
#include <limits>
#include <iomanip>
#include "Event.h"
#include "StickerDesk.h"
#include "HoodieDesk.h"

using namespace std;

int main(int argc, char const *argv[])
{
    string inputFile = argv[1];  //"input_1.txt"; 
    string outputFile = argv[2];  //"output.txt";

    ifstream infile;
    infile.open(inputFile);

    ofstream outfile;
    outfile.open(outputFile);

    int nOfHackers;
    infile >> nOfHackers;

    priority_queue<Event *, vector<Event *>, PtrLess<Event>> events;

    for (int i = 0; i < nOfHackers; i++)
    {
        float arriveTime;
        infile >> arriveTime;
        Event *event = new Event(0, i + 1, arriveTime);
        events.push(event);
    }

    int nOfCodeCommits;
    infile >> nOfCodeCommits;

    for (int i = 0; i < nOfCodeCommits; i++)
    {
        int id, nOfLines;
        float time;
        infile >> id >> nOfLines >> time;
        Event *event = new Event(1, id, time, nOfLines);
        events.push(event);
    }

    int nOfQueueAttempt;
    infile >> nOfQueueAttempt;

    for (int i = 0; i < nOfQueueAttempt; i++)
    {
        int id;
        float time;
        infile >> id >> time;
        Event *event = new Event(2, id, time);
        events.push(event); // you should implement this part
    }

    int nOfStickerDesk;
    infile >> nOfStickerDesk;

    StickerDesk stickerDesks[nOfStickerDesk];
    bool emptyStickerDesk = false;

    for (int i = 0; i < nOfStickerDesk; i++)
    {
        float serviceTime;
        infile >> serviceTime;
        stickerDesks[i].serviceTime = serviceTime;
    }

    int nOfHoodieDesk;
    infile >> nOfHoodieDesk;

    HoodieDesk hoodieDesks[nOfHoodieDesk];
    bool emptyHoodieDesk = false;

    for (int i = 0; i < nOfHoodieDesk; i++)
    {
        float serviceTime;
        infile >> serviceTime;
        hoodieDesks[i].serviceTime = serviceTime;
    }

    int maxLengthOfHoodieQueue = 0;
    int maxLengthOfStickerQueue = 0;
    float lastEventsTime = 0;
    while (!events.empty())
    {
        Event *event = events.top(); 
        bool happened = event->happen();

        if (event->getType() == 2 && happened)
        {
            int hackersId = event->getId();
            if (Hacker::stickerQueue.empty())
            {
                int deskNumber;
                bool emptyDesk = false;
                for (int i = 0; i < nOfStickerDesk; i++)
                {
                    if (stickerDesks[i].isEmpty)
                    {
                        emptyDesk = true;
                        deskNumber = i;
                        break;
                    }
                }
                if (emptyDesk)
                {
                    stickerDesks[deskNumber].isEmpty = false;
                    stickerDesks[deskNumber].id = hackersId;
                    Hacker::hackers[hackersId - 1]->inStickerDesk(event->getTime());
                    Event *event3 = new Event(3, hackersId, event->getTime() + stickerDesks[deskNumber].serviceTime);
                    events.push(event3);
                }
                else
                {
                    Hacker::stickerQueue.push(Hacker::hackers[hackersId - 1]);
                    if (Hacker::stickerQueue.size() > maxLengthOfStickerQueue)
                    {
                        maxLengthOfStickerQueue = Hacker::stickerQueue.size();
                    }
                }
            }
            else
            {
                Hacker::stickerQueue.push(Hacker::hackers[hackersId - 1]);
                if (Hacker::stickerQueue.size() > maxLengthOfStickerQueue)
                {
                    maxLengthOfStickerQueue = Hacker::stickerQueue.size();
                }
            }
        }
        else if (event->getType() == 3 && happened)
        {
            int hackersId = event->getId();
            for (int i = 0; i < nOfStickerDesk; i++)
            {
                if (stickerDesks[i].id == hackersId)
                {
                    stickerDesks[i].id = -1;
                    stickerDesks[i].isEmpty = true;
                }
            }

            if (!Hacker::stickerQueue.empty())
            {
                for (int i = 0; i < nOfStickerDesk; i++)
                {
                    if (stickerDesks[i].isEmpty)
                    {
                        stickerDesks[i].isEmpty = false;
                        stickerDesks[i].id = Hacker::stickerQueue.front()->getID();
                        Hacker::stickerQueue.front()->inStickerDesk(event->getTime());
                        Event *event3 = new Event(3, Hacker::stickerQueue.front()->getID(), event->getTime() + stickerDesks[i].serviceTime);
                        events.push(event3);
                        Hacker::stickerQueue.pop();
                    }
                }
            }

            if (Hacker::hoodieQueue.empty())
            {
                int deskNumber;
                bool emptyDesk = false;
                for (int i = 0; i < nOfHoodieDesk; i++)
                {
                    if (hoodieDesks[i].isEmpty)
                    {
                        emptyDesk = true;
                        deskNumber = i;
                        break;
                    }
                }

                if (emptyDesk)
                {
                    hoodieDesks[deskNumber].isEmpty = false;
                    hoodieDesks[deskNumber].id = hackersId;
                    Hacker::hackers[hackersId - 1]->inHoodieDesk(event->getTime());
                    Event *event4 = new Event(4, hackersId, event->getTime() + hoodieDesks[deskNumber].serviceTime);
                    events.push(event4);
                }
                else
                {
                    Hacker::hoodieQueue.push(Hacker::hackers[hackersId - 1]);
                    if (Hacker::hoodieQueue.size() > maxLengthOfHoodieQueue)
                    {
                        maxLengthOfHoodieQueue = Hacker::hoodieQueue.size();
                    }
                }
            }
            else
            {
                Hacker::hoodieQueue.push(Hacker::hackers[hackersId - 1]);
                if (Hacker::hoodieQueue.size() > maxLengthOfHoodieQueue)
                {
                    maxLengthOfHoodieQueue = Hacker::hoodieQueue.size();
                }
            }
        }
        else if (event->getType() == 4 && happened)
        {
            int hackersId = event->getId();
            for (int i = 0; i < nOfHoodieDesk; i++)
            {
                if (hoodieDesks[i].id == hackersId)
                {
                    hoodieDesks[i].id = -1;
                    hoodieDesks[i].isEmpty = true;
                }
            }

            if (!Hacker::hoodieQueue.empty())
            {
                for (int i = 0; i < nOfHoodieDesk; i++)
                {
                    if (hoodieDesks[i].isEmpty)
                    {
                        hoodieDesks[i].isEmpty = false;
                        hoodieDesks[i].id = Hacker::hoodieQueue.top()->getID();
                        Hacker::hoodieQueue.top()->inHoodieDesk(event->getTime());
                        Event *event4 = new Event(4, Hacker::hoodieQueue.top()->getID(), event->getTime() + hoodieDesks[i].serviceTime);
                        events.push(event4);
                        Hacker::hoodieQueue.pop();
                    }
                }
            }
        }
        lastEventsTime = event->getTime();
        events.pop();
        delete event;
    }

    int totalGifts = 0;
    float totalVaitingTimeSQueue = 0;
    float totalVaitingTimeHQueue = 0;
    int totalNOfCommits = 0;
    int totalNOfCommitLines = 0;
    float totalTurnaroundTime = 0;
    int totalNOfInvalidQueue = 0;
    int totalNOfInvalidGift = 0;
    float mostTimeInQueues = -1;
    int idMost = 0;
    float leastTimeInQueues = numeric_limits<float>::max();
    int idLeast = -1;

    for (int i = 0; i < nOfHackers; i++)
    {
        Hacker *myHacker = Hacker::hackers[i];
        totalGifts += myHacker->getNOfGrabbedGifts();
        totalVaitingTimeSQueue += myHacker->getTotalTimeSQueue();
        totalVaitingTimeHQueue += myHacker->getTotalTimeHQueue();
        totalNOfCommits += myHacker->getNOfCommits();
        totalNOfCommitLines += myHacker->getNOfCommitLines();
        totalTurnaroundTime += myHacker->getTurnaroundTime();
        totalNOfInvalidQueue += myHacker->getInvalidQueue();
        totalNOfInvalidGift += myHacker->getInvalidGift();
        if (myHacker->getTotalTimeHQueue() + myHacker->getTotalTimeSQueue() - mostTimeInQueues > 0.00001)
        {
            mostTimeInQueues = myHacker->getTotalTimeHQueue() + myHacker->getTotalTimeSQueue();
            idMost = i + 1;
        }
        else if (abs(myHacker->getTotalTimeHQueue() + myHacker->getTotalTimeSQueue() - mostTimeInQueues) < 0.00001)
        {
            if (idMost > i + 1)
            {
                mostTimeInQueues = myHacker->getTotalTimeHQueue() + myHacker->getTotalTimeSQueue();
                idMost = i + 1;
            }
        }
        if (myHacker->getNOfGrabbedGifts() == 3 && leastTimeInQueues - (myHacker->getTotalTimeHQueue() + myHacker->getTotalTimeSQueue()) > 0.00001)
        {
            leastTimeInQueues = myHacker->getTotalTimeHQueue() + myHacker->getTotalTimeSQueue();
            idLeast = i + 1;
        }
        else if (abs(leastTimeInQueues - (myHacker->getTotalTimeHQueue() + myHacker->getTotalTimeSQueue())) < 0.00001)
        {
            if (idLeast > i + 1)
            {
                leastTimeInQueues = myHacker->getTotalTimeHQueue() + myHacker->getTotalTimeSQueue();
                idLeast = i + 1;
            }
        }
    }
    if (idLeast == -1)
    {
        leastTimeInQueues = -1;
    }

    for (int i = 0; i < nOfHackers; i++)
    {
        delete Hacker::hackers[i];
    }
    Hacker::hackers.clear();

    float averageGiftNumber = (float)totalGifts / nOfHackers;
    float averageVaitingTimeSQueue = totalVaitingTimeSQueue / totalGifts;
    float averageVaitingTimeHQueue = totalVaitingTimeHQueue / totalGifts;
    float averageNOfCommits = (float)totalNOfCommits / nOfHackers;
    float averageNOfCommitLines = (float)totalNOfCommitLines / totalNOfCommits;
    float averageTurnaroundTime = totalTurnaroundTime / totalGifts;

    outfile << setprecision(3) << fixed;
    outfile << maxLengthOfStickerQueue << endl;
    outfile << maxLengthOfHoodieQueue << endl;
    outfile << averageGiftNumber << endl;
    outfile << averageVaitingTimeSQueue << endl;
    outfile << averageVaitingTimeHQueue << endl;
    outfile << averageNOfCommits << endl;
    outfile << averageNOfCommitLines << endl;
    outfile << averageTurnaroundTime << endl;
    outfile << totalNOfInvalidQueue << endl;
    outfile << totalNOfInvalidGift << endl;
    outfile << idMost << " " << mostTimeInQueues << endl;
    outfile << idLeast << " " << leastTimeInQueues << endl;
    outfile << lastEventsTime;

    return 0;
}
