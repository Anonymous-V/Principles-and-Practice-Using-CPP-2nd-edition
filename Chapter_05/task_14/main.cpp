/*
 * Описание задачи:
 * ================
 * Введите пары (день недели, значение) из стандартного потока ввода. Например:
 * Tuesday 23 Friday 56 Tuesday -3 Thursday 99
 * Запишите все значения для каждого дня недели в вектор vector <int>. Выведите
 * значения семи векторов для каждой недели из дней недели. Напечатайте сумму
 * чисел в каждом из векторов. Неправильный день недели, например, Funday, можно
 * игнорировать, но обычные синонимы допускаются, например, Mon и monday. Выведите
 * на печать количество отвергнутых значений.
 *
 * Идея реализации:
 * ================
 * В данной задаче потребовалось создать 7 векторов (по каждому дню) и на каждый
 * вектор расписать его допустимые значения.
 *
 * После необхоодимо только посчитать сумму и вывести на печать все необходимые
 * значения.
 *
 * Ввод значений происходит со значениями double. Это необходимо для того, чтобы
 * вывести ошибку с понятным описанием, что должны присутствовать только
 * положительные значения.
 * */

#include "../../std_lib_facilities.h"

// Вектора по дням недели
vector <int> mondays;
vector <int> tuesdays;
vector <int> wednesdays;
vector <int> thursdays;
vector <int> fridays;
vector <int> saturdays;
vector <int> sundays;
// Количество отклоненных дней
int rejected = 0;

// Функция вывода суммы значений по каждому дню
int sum_days(const vector <int> v) {
    int sum = 0;
    for (int val : v)
        sum += val;
    return sum;
}

// Функция для ввода дней и их значений
void input_days() {
    string day;
    double val_day_double;
    int val_day;

    cout << "Enter the day of the week and the value:" << endl;
    for (; cin >> day >> val_day_double;) {
        if (val_day_double - int(val_day_double) != 0)
            throw runtime_error("Only integers are allowed");
        val_day = int(val_day_double);
        if (day == "Monday" || day == "monday" || day == "Mon" || day == "mon")
            mondays.push_back(val_day);
        else if (day == "Tuesday" || day == "tuesday" || day == "Tue" || day == "tue")
            tuesdays.push_back(val_day);
        else if (day == "Wednesday" || day == "wednesday" || day == "Wed" || day == "wed")
            wednesdays.push_back(val_day);
        else if (day == "Thursday" || day == "thursday" || day == "Thu" || day == "thu")
            thursdays.push_back(val_day);
        else if (day == "Friday" || day == "friday" || day == "Fri" || day == "fri")
            fridays.push_back(val_day);
        else if (day == "Saturday" || day == "saturday" || day == "Sat" || day == "sat")
            saturdays.push_back(val_day);
        else if (day == "Sunday" || day == "sunday" || day == "Sun" || day == "sun")
            sundays.push_back(val_day);
        else ++rejected;
    }
}

int main() {
    try {
        // Ввод дней и значений пользователем
        input_days();
        // Вывод суммы значений по каждому вектору
        cout << "Monday:    " << sum_days(mondays) << endl;
        cout << "Tuesday:   " << sum_days(tuesdays) << endl;
        cout << "Wednesday: " << sum_days(wednesdays) << endl;
        cout << "Thursday:  " << sum_days(thursdays) << endl;
        cout << "Friday:    " << sum_days(fridays) << endl;
        cout << "Saturday:  " << sum_days(saturdays) << endl;
        cout << "Sunday:    " << sum_days(sundays) << endl;

        // Количество отвергнутых значений
        cout << "Rejected:  " << rejected << endl;

        return 0;
    } catch (runtime_error &e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}