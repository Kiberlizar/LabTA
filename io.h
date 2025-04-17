#ifndef IO_H
#define IO_H

struct Audience {
    int number;
    int seats;
    bool board;
    int computers;
};

void readData(Audience* aud, int count);
void printResults(Audience* aud, int count, int* capacities, int* capacity_count, int unique_count);
void countCapacities(Audience* aud, int count, int* capacities, int* capacity_count, int &unique_count);
void gnomeSort(Audience* aud, int count, bool (*comparator)(const Audience&, const Audience&));
bool compareByNumberAsc(const Audience& a, const Audience& b);
bool compareBySeatsDesc(const Audience& a, const Audience& b);
bool compareByComputersAsc(const Audience& a, const Audience& b);
bool compareByBoardThenSeats(const Audience& a, const Audience& b);
int jumpSearch(Audience* aud, int count, int target);
int myMin(int a, int b);

#endif
