#include <iostream>
#include "io.h" // Підключення заголовного файлу з оголошеннями функцій та структури

using namespace std;

/**
 * @brief Сортує масиви місткостей та їх кількостей синхронно.
 *        Використовує алгоритм, схожий на сортування гнома, для сортування
 *        масиву `capacity_count` за спаданням, одночасно переставляючи
 *        елементи в `capacities`, щоб зберегти відповідність.
 * @param capacities Масив унікальних значень місткості.
 * @param capacity_count Масив кількості повторень для кожної місткості.
 * @param unique_count Кількість унікальних елементів в масивах.
 */
void sortCapacitiesManual(int* capacities, int* capacity_count, int unique_count) {
    int i = 0;
    while (i < unique_count) {
        // Рухаємось вперед, якщо це перший елемент або порядок правильний (за спаданням)
        if (i == 0 || capacity_count[i - 1] >= capacity_count[i]) {
            i++;
        } else {
            // Якщо порядок неправильний, міняємо місцями елементи в обох масивах
            swap(capacity_count[i], capacity_count[i - 1]);
            swap(capacities[i], capacities[i - 1]);
            // Робимо крок назад для перевірки попередніх елементів
            i--;
        }
    }
}

int main() {
    // Встановлення української локалі для коректного виведення символів в консолі

    int count;
    cout << "Введіть кількість аудиторій: ";
    cin >> count;

    // Динамічне виділення пам'яті для масиву структур Audience
    Audience* aud = new Audience[count];

    // Зчитування даних про аудиторії
    readData(aud, count);

    // Меню для вибору критерію сортування
    cout << "\nОберіть варіант сортування:\n"
         << "1. За номером (зростання)\n"
         << "2. За кількістю місць (спадання)\n"
         << "3. За кількістю комп'ютерів (зростання)\n"
         << "4. За дошкою та кількістю місць (пріоритет дошки)\n"
         << "Ваш вибір: ";
    int sortOption;
    cin >> sortOption;

    // Виклик функції сортування відповідно до вибору користувача
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

    // Динамічне виділення пам'яті для статистики
    int* capacities = new int[count];
    int* capacity_count = new int[count];
    int unique_count = 0; // Лічильник унікальних місткостей

    // Підрахунок статистики
    countCapacities(aud, count, capacities, capacity_count, unique_count);

    // Сортування статистики за популярністю (кількістю повторень)
    sortCapacitiesManual(capacities, capacity_count, unique_count);

    // Виведення відсортованого списку та статистики
    printResults(aud, count, capacities, capacity_count, unique_count);

    // Пошук аудиторії
    cout << "\nВведіть номер аудиторії для пошуку: ";
    int searchNumber;
    cin >> searchNumber;

    // Для роботи Jump Search масив ОБОВ'ЯЗКОВО має бути відсортований за ключем пошуку (номером)
    gnomeSort(aud, count, compareByNumberAsc);

    // Виклик функції пошуку
    int foundIndex = jumpSearch(aud, count, searchNumber);
    if (foundIndex != -1) {
        // Якщо аудиторію знайдено, виводимо інформацію про неї
        cout << "Аудиторія знайдена: №" << aud[foundIndex].number
             << ", місць: " << aud[foundIndex].seats
             << ", дошка: " << (aud[foundIndex].board ? "є" : "немає")
             << ", комп'ютерів: " << aud[foundIndex].computers << endl;
    } else {
        // Інакше повідомляємо, що аудиторію не знайдено
        cout << "Аудиторія з номером " << searchNumber << " не знайдена.\n";
    }

    // Звільнення динамічно виділеної пам'яті
    delete[] aud;
    delete[] capacities;
    delete[] capacity_count;

    return 0; // Успішне завершення програми
}
