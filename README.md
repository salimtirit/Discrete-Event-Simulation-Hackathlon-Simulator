# HackNPaper Discrete Event Simulation

## Introduction:
HackNPaper is a discrete-event simulation project that simulates a hackathon organized by Dunder Mifflin, Scranton. This simulation models the operation of the hackathon by simulating certain events that occur at certain times. Hackers arrive at different times to the event and regularly commit code snippets. They are also interested in free stuff such as stickers and hoodies, and to grab them, they visit sticker and hoodie desks, which are placed sequentially. The simulation aims to find the number of desks that would be enough for the event.

## HackNPaper Simulation:
This simulation project is designed to determine the number of sticker and hoodie desks required for the hackathon to avoid hackers spending too much time in queues and not focusing on coding. The simulation models the process of the hackathon as a series of discrete events in time, with each event marking a change of state in the system. The simulation includes the following features:

1. Hackers arrive at different times to the event and commit code snippets regularly.
2. The number of sticker and hoodie desks may vary based on the simulation configuration, and every desk is operated by an attendant who serves the gifts (stickers and hoodies), and the service takes some time due to paper-work and other activities.
3. There are two queues in the event: one for stickers and one for hoodies. The sticker desks share a common queue, and so do the hoodie desks.
4. The sticker queue works in a first-come-first-served fashion, and if two hackers arrive at the same time, the one with the lower ID is served first.
5. The attendants do not allow hackers with less than 3 commits to enter the hoodie queue, and they call such attempts "invalid."
6. The committee counts only the commits with line changes over 20 towards queue entrance.
7. The hoodie queue works based on the number of commits, and if any two hackers have an equal number of commits, the one that arrived earlier is served first.

## Input:
The committee provides all simulation configuration files in the following format:
* The first line contains an integer _N_ that denotes the total number of hackers and _N_ floats
that denote the arrival time of each hacker in terms of seconds passed from the beginning
of HackNPaper.
* The second line contains an integer _C_ which is the total number of code commits, including
the ones shorter than 20 lines.
* Each of the next _C_ lines contains two integers and one float: the ID of the hacker that
commits the code, the number of line changes in the commit, and the second T in which
the commit is made.
* The next line is the line of an integer _Q_ that denotes the number of queue entrance
attempts.
* Each of the the next _Q_ lines contains one integer and one float which are the ID of the
hacker and the second he/she attempts to enter the sticker queue, respectively.
* The next line comprises an integer D<sub>s</sub> that denotes the number of sticker desks and a list
of floats of size D<sub>s</sub>. The i<sup>th</sup> element of the list denotes the service time of the i<sup>th</sup> sticker
desk.
* The next line starts with an integer D<sub>h</sub> and is followed by a list of floats of size D<sub>h</sub>.
Similar to previous line, the i<sup>th</sup> element of the list denotes the service time of the i<sup>th</sup> hoodie desk.

![image](https://user-images.githubusercontent.com/64011660/232539422-9a70e39b-2133-470c-9e9a-d18121f65673.png)


## Output:
The output of the simulation includes the following information:

* Maximum length of the sticker queue.
* Maximum length of the hoodie queue.
* The average number of gifts grabbed per hacker.
* The average waiting time for the sticker queue.
* The average waiting time for the hoodie queue.
* The average number of code commits per hacker.
* The average change length of the commits, including the ones shorter than 20 lines.
* Average turnaround time (Turnaround time: Total time passed from the sticker queue
entrance until leaving the hoodie desk.) To compute, sum all turnaround times and divide
it by the number of turnarounds, which is also equal to the number of total gifts given
away.
* Total number of invalid attempts to enter sticker queue.
* Total number of invalid attempts to get more than 3 gifts.
* ID of the hacker who spent the most time in the queues and the waiting time of that
hacker in seconds. If more than one hacker spent the same amount of time, choose the
one with the smallest ID.
* ID of the hacker who spent the least time in the queues and the waiting time of that
hacker in seconds, among the ones who grabbed three stickers and hoodies. If more than
one hacker spent the same amount of time, choose the one with the smallest ID. If there
is no hacker that grabbed three stickers and hoodies, print -1 for both.
* Total seconds passed during the hackathon.
 
![image](https://user-images.githubusercontent.com/64011660/232539175-722e564e-511b-4cd5-94d5-be248852f006.png)
![image](https://user-images.githubusercontent.com/64011660/232539243-5a977d3e-b39f-4dd4-8890-3eb354079b09.png)


## Running the Program
This code reads the name of the input and output files from the command line. You can run the code as follows:

```
g++ *.cpp *.h -std=c++11 -o project2
./project2 inputFile outputFile
```

## Conclusion:
HackNPaper is a useful simulation project that can be used to optimize the resource allocation and queue management for hackathons. By determining the number of sticker and hoodie desks required for a given number of hackers, the simulation can help the organizers to ensure that the hackers have a good experience and can focus on coding rather than waiting in queues. This simulation project can be extended to model other events with a queuing system and can be a valuable tool for event organizers.
