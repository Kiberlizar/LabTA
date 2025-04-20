#include "io.h"
#include <iostream>
#include <cmath>
using namespace std;

void readData(Audience* aud, int count) {
    for (int i = 0; i < count; i++) {
        cout << "Введіть дані для аудиторії #" << i + 1
             << " (номер, кількість місць, наявність дошки (1 або 0), кількість комп'ютерів): ";
        cin >> aud[i].number >> aud[i].seats >> aud[i].board >> aud[i].computers;
    }
}

void printResults(Audience* aud, int count, int* capacities, int* capacity_count, int unique_count) {
    cout << "\nВідсортовані аудиторії:\n";
    for (int i = 0; i < count; i++) {
        cout << "Аудиторія №" << aud[i].number << ", місць: " << aud[i].seats
             << ", дошка: " << (aud[i].board ? "є" : "немає")
             << ", комп'ютерів: " << aud[i].computers << endl;
    }

    cout << "\nСтатистика за кількістю місць:\n";
    for (int i = 0; i < unique_count; i++) {
        cout << "Кількість місць: " << capacities[i]
             << " зустрічається " << capacity_count[i] << " раз(и)\n";
    }
}

void countCapacities(Audience* aud, int count, int* capacities, int* capacity_count, int &unique_count) {
    for (int i = 0; i < count; i++) {
        bool found = false;
        for (int j = 0; j < unique_count; j++) {
            if (capacities[j] == aud[i].seats) {
                capacity_count[j]++;
                found = true;
                break;
            }
        }
        if (!found) {
            capacities[unique_count] = aud[i].seats;
            capacity_count[unique_count] = 1;
            unique_count++;
        }
    }
}

void gnomeSort(Audience* aud, int count, bool (*comparator)(const Audience&, const Audience&)) {
    int i = 0;
    while (i < count) {
        if (i == 0 || comparator(aud[i - 1], aud[i])) {
            i++;
        } else {
            swap(aud[i], aud[i - 1]);
            i--;
        }
    }
}

bool compareByNumberAsc(const Audience& a, const Audience& b) {
    return a.number <= b.number;
}

bool compareBySeatsDesc(const Audience& a, const Audience& b) {
    return a.seats >= b.seats;
}

bool compareByComputersAsc(const Audience& a, const Audience& b) {
    return a.computers <= b.computers;
}

bool compareByBoardThenSeats(const Audience& a, const Audience& b) {
    if (a.board != b.board) {
        return a.board > b.board;
    }
    return a.seats >= b.seats;
}

int jumpSearch(Audience* aud, int count, int target) {
    int step = sqrt(count);
    int prev = 0;

    while (prev < count && aud[myMin(step, count) - 1].number < target) {
        prev = step;
        step += sqrt(count);
        if (prev >= count) return -1;
    }

    for (int i = prev; i < myMin(step, count); i++) {
        if (aud[i].number == target) {
            return i;
        }
    }
    return -1;
}

int myMin(int a, int b) {
    return (a < b) ? a : b;
}
