/*
 * Описание задачи:
 * ================
 * Прочтите последовательность чисел типа double в вектор. Будем считать, что
 * каждое значение представляет собой расстояние между двумя городами,
 * расположенными на определенном маршруте.
 * 1. Вычислите и выведите на печать общее расстояние (сумму всех расстояний).
 * 2. Найдите и выведите на печать наименьшее и наибольшее расстояния между двумя
 * соседними городами.
 * 3. Найдите и выведите на печать среднее расстояние между двумя соседними городами.
 *
 * Идея реализации:
 * ================
 * 1. Необходимо пройтись по всему вектору и сложить все значения (sum_of_range)
 * 2. Присвоить первое значение вектора в переменные min_val и max_val. Это
 *    необходимо для того, чтобы корректно найти эти значения. Если взять
 *    отрицательные значения, то такое решение подойдет только для этой версии
 *    задачи (возможно при другом условии будут использоваться отрицательные
 *    значения)
 * 3. Необходимо вычислить сумму всех значений (пункт 1) и поделить на количество
 *    элементов в векторе.
 * */

#include "../../std_lib_facilities.h"

int main() {
    vector <double> vector1;
    // Сумма всех значений (расстояний) в векторе
    double sum_of_range = 0;
    // Минимальное и максимальное расстояние в векторе
    double min_val = 0, max_val = 0;

    cout << "Enter the distance in the vector:" << endl;
    for (double val; cin >> val;) {
        // Расстояния не могут быть отрицательными
        if (val >= 0)
            vector1.push_back(val);
    }

    // Проверка, что хотя бы одно значение есть в векторе
    // В противном случае программа завершается
    if (vector1.empty()) {
        simple_error("No data");
    }

    min_val = vector1[0];
    max_val = min_val;

    for (unsigned int i = 0; i < vector1.size(); ++i) {
        // Поиск минимального и максимального
        if (vector1[i] < min_val) min_val = vector1[i];
        if (vector1[i] > max_val) max_val = vector1[i];
        // Общее расстояние
        sum_of_range += vector1[i];
    }

    cout << "Total distance: " << sum_of_range << endl;
    cout << "Min value: " << min_val << "; Max value: " << max_val << endl;
    cout << "Average distance: " << sum_of_range * 1.0 / vector1.size() << endl;

    return 0;
}