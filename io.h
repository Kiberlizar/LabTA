#ifndef IO_H
#define IO_H

#include <functional>

struct Audience {
    int number;
    int seats;
    bool board;
    int computers;
};

void readData(Audience* aud, int count);
void printResults(Audience* aud, int count, int* capacities, int* capacity_count, int unique_count);
void countCapacities(Audience* aud, int count, int* capacities, int* capacity_count, int &unique_count);
void gnomeSort(Audience* aud, int count, std::function<bool(const Audience&, const Audience&)> comparator);

bool compareByNumberAsc(Audience a, Audience b);
bool compareBySeatsDesc(Audience a, Audience b);
bool compareByComputersAsc(Audience a, Audience b);
bool compareByBoardThenSeats(Audience a, Audience b);
int jumpSearch(Audience* aud, int count, int target);

#endif
