#include "io.h"
#include <iostream>
#include <cmath> // Для використання функції sqrt (корінь квадратний) у jumpSearch

using namespace std;

/**
 * @brief Зчитує дані про аудиторії з консолі.
 * @param aud Вказівник на масив структур Audience.
 * @param count Кількість аудиторій для зчитування.
 */
void readData(Audience* aud, int count) {
    // Цикл для введення даних по кожній аудиторії
    for (int i = 0; i < count; i++) {
        cout << "Введіть дані для аудиторії #" << i + 1
             << " (номер, кількість місць, наявність дошки (1 або 0), кількість комп'ютерів): ";
        // Зчитування даних з консолі у відповідні поля структури
        cin >> aud[i].number >> aud[i].seats >> aud[i].board >> aud[i].computers;
    }
}

/**
 * @brief Виводить результати: відсортований список аудиторій та статистику за місткістю.
 * @param aud Вказівник на масив структур Audience.
 * @param count Кількість аудиторій.
 * @param capacities Масив з унікальними значеннями кількості місць.
 * @param capacity_count Масив з кількістю повторень кожної місткості.
 * @param unique_count Кількість унікальних значень місткості.
 */
void printResults(Audience* aud, int count, int* capacities, int* capacity_count, int unique_count) {
    cout << "\nВідсортовані аудиторії:\n";
    // Виведення інформації про кожну аудиторію
    for (int i = 0; i < count; i++) {
        cout << "Аудиторія №" << aud[i].number << ", місць: " << aud[i].seats
             << ", дошка: " << (aud[i].board ? "є" : "немає") // Тернарний оператор для виведення "є" або "немає"
             << ", комп'ютерів: " << aud[i].computers << endl;
    }

    cout << "\nСтатистика за кількістю місць:\n";
    // Виведення статистики
    for (int i = 0; i < unique_count; i++) {
        cout << "Кількість місць: " << capacities[i]
             << " зустрічається " << capacity_count[i] << " раз(и)\n";
    }
}

/**
 * @brief Підраховує, скільки разів зустрічається кожна унікальна місткість аудиторії.
 * @param aud Вказівник на масив Audience.
 * @param count Загальна кількість аудиторій.
 * @param capacities Масив для збереження унікальних значень місткості.
 * @param capacity_count Масив для збереження кількості повторень.
 * @param unique_count Змінна, що зберігає кількість знайдених унікальних місткостей (передається за посиланням).
 */
void countCapacities(Audience* aud, int count, int* capacities, int* capacity_count, int &unique_count) {
    // Проходимо по всіх аудиторіях
    for (int i = 0; i < count; i++) {
        bool found = false;
        // Перевіряємо, чи така місткість вже була знайдена
        for (int j = 0; j < unique_count; j++) {
            if (capacities[j] == aud[i].seats) {
                capacity_count[j]++; // Якщо так, збільшуємо лічильник
                found = true;
                break;
            }
        }
        // Якщо місткість зустрічається вперше
        if (!found) {
            capacities[unique_count] = aud[i].seats; // Додаємо її в масив унікальних
            capacity_count[unique_count] = 1;        // Встановлюємо лічильник в 1
            unique_count++;                          // Збільшуємо кількість унікальних місткостей
        }
    }
}

/**
 * @brief Сортує масив аудиторій методом "сортування гнома".
 * @param aud Вказівник на масив Audience.
 * @param count Розмір масиву.
 * @param comparator Функція-вказівник, яка визначає критерій сортування.
 */
void gnomeSort(Audience* aud, int count, bool (*comparator)(const Audience&, const Audience&)) {
    int i = 0;
    while (i < count) {
        // Якщо ми на початку або елементи в правильному порядку, рухаємось вперед
        if (i == 0 || comparator(aud[i - 1], aud[i])) {
            i++;
        } else {
            // Якщо елементи не в порядку, міняємо їх місцями і робимо крок назад
            swap(aud[i], aud[i - 1]);
            i--;
        }
    }
}

// --- Функції-компаратори для сортування ---

bool compareByNumberAsc(const Audience& a, const Audience& b) {
    return a.number <= b.number; // За зростанням номера
}

bool compareBySeatsDesc(const Audience& a, const Audience& b) {
    return a.seats >= b.seats; // За спаданням кількості місць
}

bool compareByComputersAsc(const Audience& a, const Audience& b) {
    return a.computers <= b.computers; // За зростанням кількості комп'ютерів
}

bool compareByBoardThenSeats(const Audience& a, const Audience& b) {
    // Спочатку порівнюємо за наявністю дошки (true > false)
    if (a.board != b.board) {
        return a.board > b.board; // Аудиторії з дошкою будуть першими
    }
    // Якщо наявність дошки однакова, сортуємо за кількістю місць за спаданням
    return a.seats >= b.seats;
}

/**
 * @brief Шукає аудиторію за номером, використовуючи алгоритм Jump Search.
 *        Важливо: масив має бути попередньо відсортований за номерами.
 * @param aud Вказівник на відсортований масив Audience.
 * @param count Розмір масиву.
 * @param target Номер аудиторії, яку потрібно знайти.
 * @return Індекс знайденого елемента або -1, якщо елемент не знайдено.
 */
int jumpSearch(Audience* aud, int count, int target) {
    int step = sqrt(count); // Визначаємо розмір "стрибка"
    int prev = 0;

    // "Стрибаємо" по блоках, поки не знайдемо блок, де може бути елемент
    while (prev < count && aud[myMin(step, count) - 1].number < target) {
        prev = step;
        step += sqrt(count);
        if (prev >= count) return -1; // Якщо вийшли за межі масиву, елемента немає
    }

    // Виконуємо лінійний пошук у знайденому блоці
    for (int i = prev; i < myMin(step, count); i++) {
        if (aud[i].number == target) {
            return i; // Повертаємо індекс, якщо елемент знайдено
        }
    }
    return -1; // Повертаємо -1, якщо елемент не знайдено
}

/**
 * @brief Допоміжна функція для знаходження мінімального з двох цілих чисел.
 * @param a Перше число.
 * @param b Друге число.
 * @return Менше з двох чисел.
 */
int myMin(int a, int b) {
    return (a < b) ? a : b;
}