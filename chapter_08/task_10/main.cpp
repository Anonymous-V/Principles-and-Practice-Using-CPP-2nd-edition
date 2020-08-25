/*
 * Описание задачи:
 * ================
 * Напишите функцию, которая находит наименьший и наибольший элементы вектора,
 * являющегося ее аргументом, а также вычисляющую их среднее и медиану. Не
 * используйте глобальные переменные. Результаты можно вернуть либо в виде структуры
 * struct, либо с помощью механизма передачи аргументов по ссылке. Какой из этих
 * двух способов следует предпочесть и почему?
 *
 * Идея реализации:
 * ================
 * Т.к. поиск медианы предусматривает использование отсортированного вектора, то
 * лучше всего отсортировать вектор до начала вычислений. Таким образом можно
 * получить сразу минимальный и максимальный элементы. Медианой же, является
 * середина вектора, а среднее значение находится суммируя весь вектор и деля его
 * на количество элементов в нем.
 *
 * Считаю, что в данной задаче лучше использовать структуру, т.к. элементы не будут
 * "отделены" друг от друга и будут храниться в одном месте. Конечно, всё зависит от
 * конкретной задачи и каждый из способов будет более предпочтительнее.
 * */

#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::vector;


struct Values {
    double maxv;    // Максимальное значение
    double minv;    // Минимальное значение
    double avgv;    // Среднее значение
    double medv;    // Медиана
};


// Поиск максимального числа (вектор изначально отсортирован)
double maxv(const vector <double> &elems)
{
    if (elems.empty()) throw std::runtime_error("Vector is empty");

    return elems[elems.size() - 1];
}


// Поиск минимального числа (вектор изначально отсортирован)
double minv(const vector <double> &elems)
{
    if (elems.empty()) throw std::runtime_error("Vector is empty");

    return elems[0];
}


// Вычисление среднего значения
double avgv(const vector <double> &elems)
{
    if (elems.empty()) throw std::runtime_error("Vector is empty");
    
    double avg_val = 0;
    for (double elem : elems)
        avg_val += elem;

    return avg_val / elems.size();
}


// Вычисление медианы
double medv(const vector <double> &elems)
{
    if (elems.empty()) throw std::runtime_error("Vector is empty");

    int mid = elems.size() / 2;

    if (elems.size() % 2 != 0) return elems[mid];
    return (elems[mid - 1] + elems[mid]) / 2;
}


// Ввод вектора вещественных чисел
void inp_elems(vector <double> &elems)
{
    double val;

    cout << "Enter nums (any symbol to exit):" << endl;
    while (cin) {
        cin >> val;
        if (!cin) break;
        elems.push_back(val);
    }
}


Values calculate(vector <double> &nums)
{
    try {
        Values val {};

        // Сортировка вектора; необходимо для поиска медианы
        // Также упрощает поиск минимального и максимального значения
        std::sort(nums.begin(), nums.end());

        val.maxv = maxv(nums);
        val.minv = minv(nums);
        val.avgv = avgv(nums);
        val.medv = medv(nums);

        return val;
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << endl;
        return {};
    }
}


int main() {
    try {
        vector <double> nums;

        inp_elems(nums);
        Values val = calculate(nums);

        cout << "Max: " << val.maxv << '\n'
             << "Min: " << val.minv << '\n'
             << "Avg: " << val.avgv << '\n'
             << "Med: " << val.medv << '\n';

        return 0;
    } catch (...) {
        std::cerr << "Unknown exception" << endl;
        return 1;
    }
}