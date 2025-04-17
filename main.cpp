#include <iostream>
#include "io.h"
#include <cmath>

using namespace std;

void sortCapacitiesManual(int* capacities, int* capacity_count, int unique_count) {
    int i = 0;
    while (i < unique_count) {
        if (i == 0 || capacity_count[i - 1] >= capacity_count[i]) {
            i++;
        } else {
            swap(capacity_count[i], capacity_count[i - 1]);
            swap(capacities[i], capacities[i - 1]);
            i--;
        }
    }
}

int main() {
    int count;
    cout << "Введіть кількість аудиторій: ";
    cin >> count;

    Audience* aud = new Audience[count];

    readData(aud, count);

    cout << "\nОберіть варіант сортування:\n"
         << "1. За номером (зростання)\n"
         << "2. За кількістю місць (спадання)\n"
         << "3. За кількістю комп'ютерів (зростання)\n"
         << "4. За дошкою та кількістю місць (пріоритет дошки)\n"
         << "Ваш вибір: ";
    int sortOption;
    cin >> sortOption;

    switch (sortOption) {
        case 1:
            gnomeSort(aud, count, compareByNumberAsc);
            break;
        case 2:
            gnomeSort(aud, count, compareBySeatsDesc);
            break;
        case 3:
            gnomeSort(aud, count, compareByComputersAsc);
            break;
        case 4:
            gnomeSort(aud, count, compareByBoardThenSeats);
            break;
        default:
            cout << "Неправильний вибір. Виконується сортування за номером.\n";
            gnomeSort(aud, count, compareByNumberAsc);
            break;
    }

    int* capacities = new int[count];
    int* capacity_count = new int[count];
    int unique_count = 0;

    countCapacities(aud, count, capacities, capacity_count, unique_count);

    sortCapacitiesManual(capacities, capacity_count, unique_count);

    printResults(aud, count, capacities, capacity_count, unique_count);

    cout << "\nВведіть номер аудиторії для пошуку: ";
    int searchNumber;
    cin >> searchNumber;

    gnomeSort(aud, count, compareByNumberAsc);

    int foundIndex = jumpSearch(aud, count, searchNumber);
    if (foundIndex != -1) {
        cout << "Аудиторія знайдена: №" << aud[foundIndex].number
             << ", місць: " << aud[foundIndex].seats
             << ", дошка: " << (aud[foundIndex].board ? "є" : "немає")
             << ", комп'ютерів: " << aud[foundIndex].computers << endl;
    } else {
        cout << "Аудиторія з номером " << searchNumber << " не знайдена.\n";
    }

    delete[] aud;
    delete[] capacities;
    delete[] capacity_count;

    return 0;
}
