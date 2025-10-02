#ifndef IO_H
#define IO_H

// Структура для представлення аудиторії
struct Audience {
  int number;    // Номер аудиторії
  int seats;     // Кількість місць
  bool board;    // Наявність дошки (true - є, false - немає)
  int computers; // Кількість комп'ютерів
};

// --- Оголошення функцій ---

// Функція для зчитування даних про аудиторії з консолі
void readData(Audience *aud, int count);

// Функція для виведення відсортованого списку аудиторій та статистики
void printResults(Audience *aud, int count, int *capacities,
                  int *capacity_count, int unique_count);

// Функція для підрахунку кількості аудиторій з однаковою кількістю місць
void countCapacities(Audience *aud, int count, int *capacities,
                     int *capacity_count, int &unique_count);

// Функція сортування масиву аудиторій методом "сортування гнома"
// Приймає компаратор для визначення порядку сортування
void gnomeSort(Audience *aud, int count,
               bool (*comparator)(const Audience &, const Audience &));

// Функція-компаратор для сортування за номером аудиторії (за зростанням)
bool compareByNumberAsc(const Audience &a, const Audience &b);

// Функція-компаратор для сортування за кількістю місць (за спаданням)
bool compareBySeatsDesc(const Audience &a, const Audience &b);

// Функція-компаратор для сортування за кількістю комп'ютерів (за зростанням)
bool compareByComputersAsc(const Audience &a, const Audience &b);

// Функція-компаратор для сортування спочатку за наявністю дошки, потім за
// кількістю місць
bool compareByBoardThenSeats(const Audience &a, const Audience &b);

// Функція пошуку аудиторії за номером методом "стрибків" (Jump Search)
int jumpSearch(Audience *aud, int count, int target);

// Допоміжна функція для знаходження меншого з двох чисел
int myMin(int a, int b);

#endif