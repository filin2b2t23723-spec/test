#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

class Worker {
    char fio[80];
    char position[64];
    int yearStart;
    double salary;

public:
    explicit Worker(const char* f = "", const char* pos = "",
        int y = 0, double s = 0.0)
        : yearStart(y), salary(s)
    {
        std::strncpy(fio, f, sizeof(fio) - 1);
        fio[sizeof(fio) - 1] = '\0';

        std::strncpy(position, pos, sizeof(position) - 1);
        position[sizeof(position) - 1] = '\0';
    }

    const char* getPosition() const { return position; }
    int getYearStart() const { return yearStart; }
    double getSalary() const { return salary; }

    int experience(int currentYear) const {
        return currentYear - yearStart;
    }

    void print() const {
        std::cout << "ФИО: " << fio
            << " | Должность: " << position
            << " | Год поступления: " << yearStart
            << " | Зарплата: " << salary
            << "\n";
    }
};

static void printByExperienceMoreThan(const Worker* arr, int n, int currentYear, int years) {
    bool found = false;
    for (int i = 0; i < n; ++i) {
        if (arr[i].experience(currentYear) > years) {
            arr[i].print();
            found = true;
        }
    }
    if (!found) std::cout << "Ничего не найдено.\n";
}

static void printBySalaryMoreThan(const Worker* arr, int n, double s) {
    bool found = false;
    for (int i = 0; i < n; ++i) {
        if (arr[i].getSalary() > s) {
            arr[i].print();
            found = true;
        }
    }
    if (!found) std::cout << "Ничего не найдено.\n";
}

static void printByPosition(const Worker* arr, int n, const char* pos) {
    bool found = false;
    for (int i = 0; i < n; ++i) {
        if (std::strcmp(arr[i].getPosition(), pos) == 0) {
            arr[i].print();
            found = true;
        }
    }
    if (!found) std::cout << "Ничего не найдено.\n";
}

int main() {
    const int N = 6;
    Worker w[N] = {
        Worker("Иванов И.И.", "Инженер", 2016, 65000),
        Worker("Петров П.П.", "Менеджер", 2020, 55000),
        Worker("Сидорова А.А.", "Инженер", 2012, 90000),
        Worker("Кузнецов К.К.", "Бухгалтер", 2018, 52000),
        Worker("Смирнова С.С.", "Директор", 2010, 150000),
        Worker("Орлова О.О.", "Менеджер", 2015, 80000)
    };

    std::cout << "1) Стаж больше заданного числа лет\n";
    std::cout << "2) Зарплата больше заданной\n";
    std::cout << "3) Заданная должность\n";
    std::cout << "Выбор: ";

    int ch;
    std::cin >> ch;
    std::cin.ignore(10000, '\n');

    if (ch == 1) {
        int currentYear = 0;
        int years = 0;
        std::cout << "Введите текущий год: ";
        std::cin >> currentYear;
        std::cout << "Введите число лет: ";
        std::cin >> years;
        printByExperienceMoreThan(w, N, currentYear, years);
    }
    else if (ch == 2) {
        double s;
        std::cout << "Введите зарплату: ";
        std::cin >> s;
        printBySalaryMoreThan(w, N, s);
    }
    else if (ch == 3) {
        char pos[64];
        std::cout << "Введите должность: ";
        std::cin.getline(pos, 64);
        if (pos[0] == '\0') std::cin.getline(pos, 64);
        printByPosition(w, N, pos);
    }

    return 0;
}
